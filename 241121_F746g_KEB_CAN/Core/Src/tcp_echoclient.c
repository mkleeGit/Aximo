/**
  ******************************************************************************
  * @file    LwIP/LwIP_TCP_Echo_Client/Src/tcp_echoclient.c
  * @author  MCD Application Team
  * @brief   tcp echoclient application using LwIP RAW API
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"
#include "lwip/memp.h"
#include <stdio.h>
#include <string.h>
#include "tcp_echoclient.h"
#include "global.h"
#include "cJSON.h"

#if LWIP_TCP
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
u8_t  recev_buf[50];
__IO uint32_t message_count=0;

u8_t   data[100];

/*User code begin*/
float Inv_Velocity = 1.23f;
//float Inv_Position = 1.23f;
uint32_t Enc_Count = 12345;
uint8_t IP_ADDRESS[4]; //extern variable STM32 IP Display

int ConnectionTimeout;
/*User code end*/

struct tcp_pcb *echoclient_pcb;

/* ECHO protocol states */
enum echoclient_states
{
  ES_NOT_CONNECTED = 0,
  ES_CONNECTED,
  ES_RECEIVED,
  ES_CLOSING,
};

/* structure to be passed as argument to the tcp callbacks */
struct echoclient
{
  enum echoclient_states state; /* connection status */
  struct tcp_pcb *pcb;          /* pointer on the current tcp_pcb */
  struct pbuf *p_tx;            /* pointer on pbuf to be transmitted */
  /*User code begin*/
  uint8_t tx_pending;
  /*User code end*/
};

/* Private function prototypes -----------------------------------------------*/
static err_t tcp_echoclient_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
static void tcp_echoclient_connection_close(struct tcp_pcb *tpcb, struct echoclient * es);
static err_t tcp_echoclient_poll(void *arg, struct tcp_pcb *tpcb);
static err_t tcp_echoclient_sent(void *arg, struct tcp_pcb *tpcb, u16_t len);
static void tcp_echoclient_send(struct tcp_pcb *tpcb, struct echoclient * es);
static err_t tcp_echoclient_connected(void *arg, struct tcp_pcb *tpcb, err_t err);

static int  append_frame_u8 (uint8_t *out, int max, uint8_t id, uint8_t  v);
static int  append_frame_u16(uint8_t *out, int max, uint8_t id, uint16_t v);
static int append_frame_i16(uint8_t *out, int max, uint8_t id, int16_t v);
static int  append_frame_i32(uint8_t *out, int max, uint8_t id, int32_t  v);
static float  append_frame_f32(uint8_t *out, int max, uint8_t id, float  v);
static void parse_write_Json(char *jsonstr);
static void parse_write_payload(uint8_t *payload, uint16_t len);
void Tcpvariableinit();

/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Connects to the TCP echo server
  * @param  None
  * @retval None
  */

void tcp_echoclient_connect(void)
{
	static int ConnectTimeOut = 0;
	static int ConnectionStep = 0;
  ip_addr_t DestIPaddr;
  ip_addr_t local_ip;

  IP4_ADDR( &DestIPaddr, DEST_IP_ADDR0, DEST_IP_ADDR1, DEST_IP_ADDR2, DEST_IP_ADDR3 );
  IP4_ADDR(&local_ip, IP_ADDRESS[0],IP_ADDRESS[1],IP_ADDRESS[2],IP_ADDRESS[3]);

  switch(ConnectionStep)
  {
  case 0:
	  if (echoclient_pcb == NULL && (echoclient_pcb->state != ESTABLISHED && g_bEthernet_ConnectionStatus))//if ((g_u8Ethernet_TcpStatus == 0 && g_bEthernet_ConnectionStatus)|| echoclient_pcb == NULL )
	  {
		  echoclient_pcb = tcp_new();
		  tcp_bind(echoclient_pcb, &local_ip, 0);
		  ConnectionStep = 1;
		  ConnectTimeOut = 0;
	  }
	  else if (echoclient_pcb != NULL && echoclient_pcb->state == ESTABLISHED)
	  {
		  ConnectionStep = 999;
		  ConnectTimeOut = 0;
	  }
	  else
	  {
			ConnectTimeOut = ConnectTimeOut + 1;
			if(ConnectTimeOut >= 2000)
			{
				tcp_abort(echoclient_pcb);
				//mem_free(echoclient_pcb);
				echoclient_pcb = NULL;
				ConnectTimeOut = 0;
				ConnectionStep = 0;
			}
	  }
	  break;
  case 1:
	  if (echoclient_pcb != NULL)
	  {
		    tcp_connect(echoclient_pcb,&DestIPaddr,DEST_PORT,tcp_echoclient_connected);
		    if(!ip_addr_cmp(&echoclient_pcb->local_ip, &local_ip))
		    {
				ConnectTimeOut = ConnectTimeOut + 1;
				if(ConnectTimeOut >= 2000)
				{
					tcp_abort(echoclient_pcb);
					//mem_free(echoclient_pcb);
					echoclient_pcb = NULL;
					ConnectTimeOut = 0;
					ConnectionStep = 0;
				}
		    }
		    else
		    {
		    	ConnectionStep = 2;
		    	ConnectTimeOut = 0;
		    }
	  }
	  else
	  {
		  ConnectionStep = 999;
		  ConnectTimeOut = 0;
	  }
	  break;
  case 2:
	  if (echoclient_pcb != NULL)
	  {
		    if(!ip_addr_cmp(&echoclient_pcb->local_ip, &local_ip))
		    {
				ConnectTimeOut = ConnectTimeOut + 1;
				if(ConnectTimeOut >= 2000)
				{
					tcp_abort(echoclient_pcb);
					//mem_free(echoclient_pcb);
					echoclient_pcb = NULL;
					ConnectTimeOut = 0;
					ConnectionStep = 0;
				}
		    }
		    else if(g_bEthernet_ConnectionStatus == false)
		    {
		    	ConnectionStep = 999;
		    	ConnectTimeOut = 0;
		    }
	  }
	  else
	  {
		  ConnectionStep = 999;
		  ConnectTimeOut = 0;
	  }
	  break;
  case 999:
	  tcp_arg(echoclient_pcb, NULL);
	  tcp_recv(echoclient_pcb, NULL);
	  tcp_sent(echoclient_pcb, NULL);
	  tcp_poll(echoclient_pcb, NULL, 0);
	  tcp_close(echoclient_pcb);
	  ConnectionStep = 0;
	  break;
  }
  //User code begin
  /*if ((echoclient_pcb->state != ESTABLISHED && g_bEthernet_ConnectionStatus)|| echoclient_pcb == NULL )//if ((g_u8Ethernet_TcpStatus == 0 && g_bEthernet_ConnectionStatus)|| echoclient_pcb == NULL )
  {
	  echoclient_pcb = tcp_new();
	  tcp_bind(echoclient_pcb, &local_ip, 0);
  }
  //User code end
  if (echoclient_pcb != NULL)
  {
    //IP4_ADDR( &DestIPaddr, DEST_IP_ADDR0, DEST_IP_ADDR1, DEST_IP_ADDR2, DEST_IP_ADDR3 );

    // connect to destination address/port
    tcp_connect(echoclient_pcb,&DestIPaddr,DEST_PORT,tcp_echoclient_connected);
    if(!ip_addr_cmp(&echoclient_pcb->local_ip, &local_ip))
    {
    	//if(echoclient_pcb->state == CLOSED || echoclient_pcb->state == SYN_SENT)
    	//{
    		ConnectTimeOut = ConnectTimeOut + 1;
			if(ConnectTimeOut >= 2000)
			{
				tcp_abort(echoclient_pcb);
				//mem_free(echoclient_pcb);
				echoclient_pcb = NULL;
				g_u8Ethernet_TcpStatus = 0;
				ConnectTimeOut = 0;
		    	return;
			}
    	//}
    }
    else
    {
    	ConnectTimeOut = 0;
    }*/
    /*else if(g_u8Ethernet_TcpStatus == 1)
    {
		ConnectTimeOut = ConnectTimeOut + 1;
		if(ConnectTimeOut >= 2000)
		{
			tcp_abort(echoclient_pcb);
			echoclient_pcb = NULL;
			g_u8Ethernet_TcpStatus = 0;
			ConnectTimeOut = 0;
	    	return;
		}
    }
    else
    {
    	g_u8Ethernet_TcpStatus = 1;
    }*/
    //User code begin

    //User code end
  //}
  /*else if(g_u8Ethernet_TcpStatus == 2 && echoclient_pcb->state == ESTABLISHED && g_bEthernet_ConnectionStatus == false)
  {
	  tcp_arg(echoclient_pcb, NULL);
	  tcp_recv(echoclient_pcb, NULL);
	  tcp_sent(echoclient_pcb, NULL);
	  tcp_poll(echoclient_pcb, NULL, 0);
	  tcp_close(echoclient_pcb);
  }
  else
  {
	//User code begin
	  g_u8Ethernet_TcpStatus = 0;
	//User code end
    //deallocate the pcb
    //memp_free(MEMP_TCP_PCB, echoclient_pcb);
#ifdef SERIAL_DEBUG
    printf("\n\r can not create tcp pcb");
#endif
  }*/
}

/**
  * @brief Function called when TCP connection established
  * @param tpcb: pointer on the connection control block
  * @param err: when connection correctly established err should be ERR_OK 
  * @retval err_t: returned error 
  */
static err_t tcp_echoclient_connected(void *arg, struct tcp_pcb *tpcb,
		err_t err) {
	struct echoclient *es = NULL;
	u8_t payload[128] = {0};
	int w = 0;
	if (err == ERR_OK) {
		/* allocate structure es to maintain tcp connection informations */
		es = (struct echoclient*) mem_malloc(sizeof(struct echoclient));

		if (es != NULL) {
			es->state = ES_CONNECTED;
			es->pcb = tpcb;
			/*User code begin*/
			es->p_tx = NULL;
			ConnectionTimeout = 0;
			/*User code end*/

			//sprintf((char*)data, "sending tcp client message %d", (int)message_count);
			cJSON *JSONpayload = cJSON_CreateObject();
			cJSON_AddStringToObject(JSONpayload, "TCPStatus", "Init");
			cJSON_AddStringToObject(JSONpayload, "SerialNumber", g_Tcp_SerialNumber);

			char *jsonstr = cJSON_PrintUnformatted(JSONpayload);

			if (jsonstr) {
			    size_t len = strlen(jsonstr);
			    if (len > sizeof(payload) - 1) len = sizeof(payload) - 1;
			    memcpy(payload, jsonstr, len);
			    payload[len] = '\0';
			    w = (int)len;
			    cJSON_free(jsonstr);
			}
			cJSON_Delete(JSONpayload);

			/* allocate pbuf */
			/*es->p_tx = pbuf_alloc(PBUF_TRANSPORT, strlen((char*) payload),
					PBUF_POOL);*/
			es->p_tx = pbuf_alloc(PBUF_TRANSPORT, (u16_t)w, PBUF_POOL);
			if (es->p_tx) {
				/* copy data to pbuf */
				//pbuf_take(es->p_tx, (char*) payload, strlen((char*) payload));
				pbuf_take(es->p_tx, payload, (u16_t)w);

				/* pass newly allocated es structure as argument to tpcb */
				tcp_arg(tpcb, es);

				/* initialize LwIP tcp_recv callback function */
				tcp_recv(tpcb, tcp_echoclient_recv);

				/* initialize LwIP tcp_sent callback function */
				tcp_sent(tpcb, tcp_echoclient_sent);

				/* initialize LwIP tcp_poll callback function */
				tcp_poll(tpcb, tcp_echoclient_poll, 1);

				/* send data */
				tcp_echoclient_send(tpcb, es);

				return ERR_OK;
			}
		} else {
			/* close connection */
			tcp_echoclient_connection_close(tpcb, es);
			/* return memory allocation error */
			return ERR_MEM;
		}
	} else {
		/* close connection */
		tcp_echoclient_connection_close(tpcb, es);
	}
	return err;
}

/**
  * @brief tcp_receiv callback
  * @param arg: argument to be passed to receive callback 
  * @param tpcb: tcp connection control block 
  * @param err: receive error code 
  * @retval err_t: returned error
  */
static err_t tcp_echoclient_recv(void *arg, struct tcp_pcb *tpcb,
		struct pbuf *p, err_t err) {
	struct echoclient *es;
	err_t ret_err;

	LWIP_ASSERT("arg != NULL", arg != NULL);

	es = (struct echoclient*) arg;

	/* if we receive an empty tcp frame from server => close connection */
	if (p == NULL) {
		/* remote host closed connection */
		es->state = ES_CLOSING;
		if (es->p_tx == NULL) {
			/* we're done sending, close connection */
			tcp_echoclient_connection_close(tpcb, es);
		} else {
			/* send remaining data*/
			tcp_echoclient_send(tpcb, es);
		}
		ret_err = ERR_OK;
	}
	/* else : a non empty frame was received from echo server but for some reason err != ERR_OK */
	else if (err != ERR_OK) {
		/* free received pbuf*/
		if (p != NULL) {
			pbuf_free(p);
		}
		ret_err = err;
	} else if (es->state == ES_CONNECTED) {
		if (!p) { /* close ... */
			return ERR_OK;
		}
		if (err != ERR_OK) {
			pbuf_free(p);
			return err;
		}

		char jsonstr[1024] = {0};
		uint8_t rx[1024]= {0};

		u16_t tot = p->tot_len;

		uint16_t n = pbuf_copy_partial(p, rx, LWIP_MIN(tot, sizeof(rx)-1), 0);
		tcp_recved(tpcb, tot);
		pbuf_free(p);

		if(n >= sizeof(jsonstr)) n = sizeof(jsonstr) - 1;
		memcpy(jsonstr, rx, n);
		jsonstr[n] = '\0';


		parse_write_Json(jsonstr);

		send_tlv_response_to_csharp(echoclient_pcb);

		es->tx_pending = 1;

		return ERR_OK;
	}

	/* data received when connection already closed */
	else {
		/* Acknowledge data reception */
		tcp_recved(tpcb, p->tot_len);

		/* free pbuf and do nothing */
		pbuf_free(p);
		ret_err = ERR_OK;
	}
	return ret_err;
}

/**
  * @brief function used to send data
  * @param  tpcb: tcp control block
  * @param  es: pointer on structure of type echoclient containing info on data 
  *             to be sent
  * @retval None 
  */
static void tcp_echoclient_send(struct tcp_pcb *tpcb, struct echoclient * es)
{
  struct pbuf *ptr;
  err_t wr_err = ERR_OK;
 
  while ((wr_err == ERR_OK) &&
         (es->p_tx != NULL) && 
         (es->p_tx->len <= tcp_sndbuf(tpcb)))
  {

    /* get pointer on pbuf from es structure */
    ptr = es->p_tx;

    /* enqueue data for transmission */
    wr_err = tcp_write(tpcb, ptr->payload, ptr->len, 1);

    if (wr_err == ERR_OK)
    { 
      /* continue with next pbuf in chain (if any) */
      es->p_tx = ptr->next;
      
      if(es->p_tx != NULL)
      {
        /* increment reference count for es->p */
        pbuf_ref(es->p_tx);
      }
      
      /* free pbuf: will free pbufs up to es->p (because es->p has a reference count > 0) */
      pbuf_free(ptr);
   }
   else if(wr_err == ERR_MEM)
   {
      /* we are low on memory, try later, defer to poll */
     es->p_tx = ptr;
   }
   else
   {
     /* other problem ?? */
   }
  }
}

/**
  * @brief  This function implements the tcp_poll callback function
  * @param  arg: pointer on argument passed to callback
  * @param  tpcb: tcp connection control block
  * @retval err_t: error code
  */
static err_t tcp_echoclient_poll(void *arg, struct tcp_pcb *tpcb) {
	err_t ret_err;
	struct echoclient *es;
	static int TcpTimeout;
	static long long prevTimestamp;

	es = (struct echoclient*) arg;
	if (es != NULL) {
		if (es->p_tx != NULL) {
			/* there is a remaining pbuf (chain) , try to send data */
			tcp_echoclient_send(tpcb, es);
		} else {
			/* no remaining pbuf (chain)  */
			if (es->state == ES_CLOSING) {
				/* close tcp connection */
				tcp_echoclient_connection_close(tpcb, es);
				es->tx_pending = 0;
			}
			else if(es->state == ES_CONNECTED)
			{
				if(g_Tcp_Timestamp != prevTimestamp)
				{
					prevTimestamp = g_Tcp_Timestamp;
					TcpTimeout = 0;
				}
				else if(g_Tcp_Timestamp == prevTimestamp)
				{
					TcpTimeout = TcpTimeout + 1;
					if(TcpTimeout >= 5)
					{
						g_Tcp_Timestamp = 0;
						TcpTimeout = 0;
						tcp_echoclient_connection_close(tpcb, es);
					}
				}
			}
			/*if (es->tx_pending == 1) {
				send_tlv_response_to_csharp(tpcb);
				es->tx_pending = 0;
			}*/
		}
		ret_err = ERR_OK;
	} else {
		/* nothing to be done */
		tcp_abort(tpcb);
		ret_err = ERR_ABRT;
	}
	return ret_err;
}

/**
  * @brief  This function implements the tcp_sent LwIP callback (called when ACK
  *         is received from remote host for sent data) 
  * @param  arg: pointer on argument passed to callback
  * @param  tcp_pcb: tcp connection control block
  * @param  len: length of data sent 
  * @retval err_t: returned error code
  */
static err_t tcp_echoclient_sent(void *arg, struct tcp_pcb *tpcb, u16_t len)
{
  struct echoclient *es;

  LWIP_UNUSED_ARG(len);

  es = (struct echoclient *)arg;
  
  if(es->p_tx != NULL)
  {
    /* still got pbufs to send */
    tcp_echoclient_send(tpcb, es);
  }

  return ERR_OK;
}

/**
  * @brief This function is used to close the tcp connection with server
  * @param tpcb: tcp connection control block
  * @param es: pointer on echoclient structure
  * @retval None
  */
static void tcp_echoclient_connection_close(struct tcp_pcb *tpcb,struct echoclient *es)
{
	/* remove callbacks */
	tcp_arg(tpcb, NULL);
	tcp_recv(tpcb, NULL);
	tcp_sent(tpcb, NULL);
	tcp_poll(tpcb, NULL, 0);
	Tcpvariableinit();

	if (es != NULL)
	{
		/*User code begin*/
		if (es->p_tx)
		{
			pbuf_free(es->p_tx);
			es->p_tx = NULL;
		}
		/*Usercode end*/
		mem_free(es);
	}
	/*User code begin*/
	echoclient_pcb = NULL;
	/*User code end*/

	/* close tcp connection */
	tcp_close(tpcb);
}

void tcp_loop_send()
{
	/*struct tcp_pcb *tpcb;
	struct echoclient *es;
	static long long prevTimestamp = 0;
	static int Timeout = 0;
	if(echoclient_pcb->state == ESTABLISHED)
	{
		if(g_Tcp_Timestamp != prevTimestamp)
		{
			prevTimestamp = g_Tcp_Timestamp;
			Timeout = 0;
		}
		else if(g_Tcp_Timestamp == prevTimestamp)
		{
			Timeout = Timeout + 1;
			if(Timeout >= 200)
			{
				tcp_echoclient_connection_close(tpcb, es);
				Timeout = 0;
			}
		}
	}*/
	;
}

void send_tlv_response_to_csharp(struct tcp_pcb *tpcb)
{
	struct echoclient *es;
    int velocity = g_st_inverter.PosSetRpmvalue;
    int16_t position = g_st_inverter.PosSetPosvalue;
    uint32_t count = Enc_Count;

    static uint8_t buf[1024]; // 넉넉히
	int w = 0, r;
	cJSON *JSONpayload = cJSON_CreateObject();
	cJSON_AddStringToObject(JSONpayload, "TCPStatus", "WRITE");
	cJSON_AddStringToObject(JSONpayload, "SerialNumber", g_Tcp_SerialNumber);
	cJSON_AddStringToObject(JSONpayload, "Firmware", g_Tcp_FWversion);
	cJSON_AddBoolToObject(JSONpayload, "LocalCtrlOn", g_Tcp_LocalCtrlOn);
	cJSON_AddBoolToObject(JSONpayload, "PowerStatus", g_Tcp_PowerStatus);
	cJSON_AddBoolToObject(JSONpayload, "LimitFF", g_Tcp_LimitFF);
	cJSON_AddBoolToObject(JSONpayload, "LimitF", g_Tcp_LimitF);
	cJSON_AddBoolToObject(JSONpayload, "LimitR", g_Tcp_LimitR);
	cJSON_AddBoolToObject(JSONpayload, "LimitFR", g_Tcp_LimitFR);
	cJSON_AddBoolToObject(JSONpayload, "WireOut", g_Tcp_WireOut);
	cJSON_AddBoolToObject(JSONpayload, "EmgBrake",g_Tcp_EmgBrake);
	cJSON_AddBoolToObject(JSONpayload, "IsError", g_Tcp_IsError);
	cJSON_AddNumberToObject(JSONpayload,"ErrorCode",g_Tcp_ErrorCode);
	cJSON_AddNumberToObject(JSONpayload, "ErrorType", g_Tcp_ErrorType);
	cJSON_AddNumberToObject(JSONpayload, "ActPos", g_Tcp_ActPos);
	cJSON_AddBoolToObject(JSONpayload, "IsRunning",g_Tcp_Running);
	cJSON_AddBoolToObject(JSONpayload, "IsArrived",g_Tcp_Arrived);

	char *jsonstr = cJSON_PrintUnformatted(JSONpayload);

	cJSON_Delete(JSONpayload);

	if(!jsonstr) return;

	size_t len = strlen(jsonstr);
	if(len > sizeof(buf) - 1) len = sizeof(buf) - 1;
	memcpy(buf, jsonstr, len);
	buf[len] = '\0';
	w = (int)len;
	cJSON_free(jsonstr);

	err_t e = tcp_write(tpcb, buf, (u16_t)w, TCP_WRITE_FLAG_COPY);
	if (e == ERR_OK)
		tcp_output(tpcb);
}


static void parse_write_Json(char *jsonstr){
	cJSON *root = cJSON_Parse(jsonstr);

	if (!root)
		return;//return ERR_OK;

	cJSON *jSTM_SerialNumber = cJSON_GetObjectItemCaseSensitive(root, "STM_SerialNumber");
	if (jSTM_SerialNumber == NULL || !cJSON_IsString(jSTM_SerialNumber) || jSTM_SerialNumber->valuestring == NULL)
	{
		cJSON_Delete(root);
		return;
	}
	if (strcmp(jSTM_SerialNumber->valuestring, TCP_SERIAL_NUMBER_DEFAULT) != 0)
	{
		cJSON_Delete(root);
		return;
	}

	cJSON *jSTM_RemoteEnable = cJSON_GetObjectItemCaseSensitive(root, "STM_RemoteEnable");
	cJSON *jPower = cJSON_GetObjectItemCaseSensitive(root, "STM_Power");
	cJSON *jStart = cJSON_GetObjectItemCaseSensitive(root, "STM_Start");
	cJSON *jStop = cJSON_GetObjectItemCaseSensitive(root, "STM_Stop");
	cJSON *jReset = cJSON_GetObjectItemCaseSensitive(root, "STM_Reset");
	cJSON *jMcOn = cJSON_GetObjectItemCaseSensitive(root, "STM_McOn");
	cJSON *jHomeSet = cJSON_GetObjectItemCaseSensitive(root, "STM_HomeSet");
	cJSON *jDriveType = cJSON_GetObjectItemCaseSensitive(root, "STM_DriveType");
	cJSON *jSpeed = cJSON_GetObjectItemCaseSensitive(root, "STM_Speed");
	cJSON *jTargetPos = cJSON_GetObjectItemCaseSensitive(root, "STM_TargetPos");
	cJSON *jHomeSetPos = cJSON_GetObjectItemCaseSensitive(root, "STM_HomeSetPos");
	cJSON *jDirectUp = cJSON_GetObjectItemCaseSensitive(root, "STM_DirectUp");
	cJSON *jDirectDown = cJSON_GetObjectItemCaseSensitive(root, "STM_DirectDown");
	cJSON *jDirectStop = cJSON_GetObjectItemCaseSensitive(root, "STM_DirectStop");
	cJSON *jConsoleEMG = cJSON_GetObjectItemCaseSensitive(root, "STM_ConsoleEMG");
	cJSON *jTimestamp = cJSON_GetObjectItemCaseSensitive(root, "STM_Timestamp");

	//Tcpvariableinit();

	if (cJSON_IsBool(jSTM_RemoteEnable))g_Tcp_STM_RemoteEnable = cJSON_IsTrue(jSTM_RemoteEnable);
	if (cJSON_IsBool(jPower))g_Tcp_Power = cJSON_IsTrue(jPower);
	if (cJSON_IsBool(jStart))g_Tcp_Start = cJSON_IsTrue(jStart);
	if (cJSON_IsBool(jStop))g_Tcp_Stop = cJSON_IsTrue(jStop);
	if (cJSON_IsBool(jReset))g_Tcp_Reset = cJSON_IsTrue(jReset);
	if (cJSON_IsBool(jMcOn))g_Tcp_McOn = cJSON_IsTrue(jMcOn);
	if (cJSON_IsNumber(jDriveType))g_Tcp_DriveType = jDriveType ->valueint;//g_Tcp_DriveType = jDriveType->valueint;
	if (cJSON_IsNumber(jSpeed))g_Tcp_Speed = jSpeed->valueint;
	if (cJSON_IsNumber(jTargetPos))g_Tcp_TargetPos = jTargetPos->valueint;
	if (cJSON_IsNumber(jHomeSetPos))g_Tcp_HomeSetPos = jHomeSetPos->valueint;
	if (cJSON_IsBool(jHomeSet))g_Tcp_HomeSet = cJSON_IsTrue(jHomeSet);
	if (cJSON_IsBool(jDirectUp))g_Tcp_DirectUp = cJSON_IsTrue(jDirectUp);
	if (cJSON_IsBool(jDirectDown))g_Tcp_DirectDown = cJSON_IsTrue(jDirectDown);
	if (cJSON_IsBool(jDirectStop))g_Tcp_DirectStop = cJSON_IsTrue(jDirectStop);
	if (cJSON_IsBool(jConsoleEMG))g_Tcp_ConsoleEMG = cJSON_IsTrue(jConsoleEMG);
	if (cJSON_IsNumber(jTimestamp))g_Tcp_Timestamp = jTimestamp->valuedouble;


 	cJSON_Delete(root);
}
void Tcpvariableinit()
{
	g_Tcp_STM_RemoteEnable = false;
	g_Tcp_Power = false;
	g_Tcp_Start = false;
	g_Tcp_Stop = false;
	g_Tcp_Reset = false;
	g_Tcp_McOn = false;
	g_Tcp_DriveType = 0;
	g_Tcp_Speed = 0;
	g_Tcp_TargetPos = 0;
	g_Tcp_HomeSetPos = 0;
	g_Tcp_HomeSet = false;
	g_Tcp_DirectUp = false;
	g_Tcp_DirectDown = false;
	g_Tcp_DirectStop = false;
	g_Tcp_ConsoleEMG = false;
	g_Tcp_Timestamp = 0;
}
#endif /* LWIP_TCP */


