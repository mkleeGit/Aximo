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
/*User code begin*/

/*user code end*/
#if LWIP_TCP
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/*User code begin*/


struct Modebuf{
	int percent;
	uint8_t Percentbuf[4];
};

bool tcp_wait;
uint8_t tcp_create;
int tcp_timestamp = 0;

uint8_t clientSend_buf[200];

uint8_t inv_Statebuf[4];
uint8_t inv_Errorbuf[4];
uint8_t inv_Modebuf[4];
uint8_t inv_ActPosbuf[8];

uint8_t inv_supplybuf[4];
uint8_t inv_STObuf[4];

uint8_t inv_Velmode_velbuf[4];
uint8_t inv_Posmode_velbuf[4];


uint8_t client_percentVelRPM;

uint8_t client_percentPosRPM;

uint8_t client_TempVel_VelSet[4];

uint8_t client_TempPos_PosSet[8];
uint8_t client_TempPos_VelSet[4];

uint8_t client_TempHome_PosSet[8];

uint8_t client_cTempControlword[4];
uint16_t client_iTempControlword;

int client_percentVel_Vel;
int client_percentPos_Vel;

//LWIP STM32 IP
uint8_t IP_ADDRESS[4]; //extern variable

/*User code end*/
u8_t  recev_buf[100];
__IO uint32_t message_count=0;

u8_t   data[200];

struct tcp_pcb *echoclient_pcb;
struct echoclient *echo;
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
};

/* Private function prototypes -----------------------------------------------*/
static err_t tcp_echoclient_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
static void tcp_echoclient_connection_close(struct tcp_pcb *tpcb, struct echoclient * es);
static err_t tcp_echoclient_poll(void *arg, struct tcp_pcb *tpcb);
static err_t tcp_echoclient_sent(void *arg, struct tcp_pcb *tpcb, u16_t len);
static void tcp_echoclient_send(struct tcp_pcb *tpcb, struct echoclient * es);
static err_t tcp_echoclient_connected(void *arg, struct tcp_pcb *tpcb, err_t err);

/* Private functions ---------------------------------------------------------*/

/*User code begin*/
void tcp_client_send_data(uint8_t* recv_buf, uint16_t buf_len);
void tcp_serial_inf(uint8_t* Buffer, uint16_t Buffersize);
void tcp_timeout_check();
/*User code end*/



/**
  * @brief  Connects to the TCP echo server
  * @param  None
  * @retval None
  */
void tcp_echoclient_connect(void)
{
	ip_addr_t DestIPaddr;

	/* create new tcp pcb */
	if(GVLTCP_state == 0 && GVLTCP_Cable_state == 2){
		echoclient_pcb = tcp_new();
		if (echoclient_pcb != NULL)
		{
			IP4_ADDR(&DestIPaddr, DEST_IP_ADDR0, DEST_IP_ADDR1, DEST_IP_ADDR2, DEST_IP_ADDR3);
			/* connect to destination address/port */
			tcp_connect(echoclient_pcb,&DestIPaddr,DEST_PORT,tcp_echoclient_connected);
			/*User code begin*/
			GVLTCP_state = 1;
			GVLTCP_connection = 1;
			/*User code end*/
		}
		else
		{
			/*User code begin*/
			GVLTCP_state = 0;
			/*user code end*/
			/* deallocate the pcb */
			memp_free(MEMP_TCP_PCB, echoclient_pcb);
#ifdef SERIAL_DEBUG
			printf("\n\r can not create tcp pcb");
#endif
			return;
		}
	}
}

/**
  * @brief Function called when TCP connection established
  * @param tpcb: pointer on the connection contol block
  * @param err: when connection correctly established err should be ERR_OK 
  * @retval err_t: returned error 
  */
static err_t tcp_echoclient_connected(void *arg, struct tcp_pcb *tpcb, err_t err)
{
  struct echoclient *es = NULL;
  /*User code begin*/
  struct pbuf *ptr;
  /*User code end*/
  if (err == ERR_OK)   
  {
    /* allocate structure es to maintain tcp connection informations */
    es = (struct echoclient *)mem_malloc(sizeof(struct echoclient));
  
    if (es != NULL)
    {
    /*User code begin*/
      GVLTCP_state = 2;
      //tcp_create = 2;
      ptr = es->p_tx;
    /*User code end*/
      es->state = ES_CONNECTED;
      es->pcb = tpcb;
      
      //sprintf((char*)data, "sending tcp client message %d", (int)message_count);
      /* allocate pbuf */
      memset(clientSend_buf, 0 ,sizeof(clientSend_buf));
      es->p_tx = pbuf_alloc(PBUF_TRANSPORT, strlen((char*)data) , PBUF_POOL);
      //es->p_tx = pbuf_alloc(PBUF_TRANSPORT, strlen((char*)data) , PBUF_POOL);
      if (es->p_tx)
      {
        /* copy data to pbuf */
    	pbuf_take(es->p_tx, (char*)data, strlen((char*)data));
        //pbuf_take(es->p_tx, (char*)data, strlen((char*)data));
        /* pass newly allocated es structure as argument to tpcb */
        tcp_arg(tpcb, es);
  
        /* initialize LwIP tcp_recv callback function */ 
        tcp_recv(tpcb, tcp_echoclient_recv);
  
        /* initialize LwIP tcp_sent callback function */
        tcp_sent(tpcb, tcp_echoclient_sent);
  
        /* initialize LwIP tcp_poll callback function */
        tcp_poll(tpcb, tcp_echoclient_poll, 1);
    
        /* send data */
        tcp_echoclient_send(tpcb,es);
        
        return ERR_OK;
      }
    }
    else
    {
      /* close connection */
      tcp_echoclient_connection_close(tpcb, es);
      
      /* return memory allocation error */
      return ERR_MEM;  
    }
  }
  else
  {
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
  * @retval err_t: retuned error  
  */
static err_t tcp_echoclient_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{ 
  struct echoclient *es;
  err_t ret_err; 

  LWIP_ASSERT("arg != NULL",arg != NULL);
  
  es = (struct echoclient *)arg;
  
  /* if we receive an empty tcp frame from server => close connection */
  if (p == NULL)
  {
    /* remote host closed connection */
    es->state = ES_CLOSING;
    if(es->p_tx == NULL)
    {
       /* we're done sending, close connection */
       tcp_echoclient_connection_close(tpcb, es);
    }
    else
    {    
      /* send remaining data*/
      tcp_echoclient_send(tpcb, es);
    }
    ret_err = ERR_OK;
  }   
  /* else : a non empty frame was received from echo server but for some reason err != ERR_OK */
  else if(err != ERR_OK)
  {
	/*User code begin*/
	es->state = ES_CLOSING;
	tcp_echoclient_connection_close(tpcb, es);
	/*User code end*/

    /* free received pbuf*/
    if (p != NULL)
    {
      pbuf_free(p);
    }
    ret_err = err;
  }
  else if(es->state == ES_CONNECTED)
  {

    /* increment message count */
    //message_count++;

    /* Acknowledge data reception */
    tcp_recved(tpcb, p->tot_len);

    /*User code begin*/
	if(es->p_tx == NULL)
	{
		es->p_tx = p;
		tcp_client_send_data(p->payload, sizeof(clientSend_buf)/*p->tot_len*/);
		tcp_echoclient_send(tpcb, es);

		tcp_timestamp = tcp_timestamp + 1;
	}
	/*User code end*/
    //pbuf_free(p);
    /* tcp_client close after sending message
	tcp_echoclient_connection_close(tpcb, es);
	*/
    ret_err = ERR_OK;
  }

  /* data received when connection already closed */
  else
  {
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
    ptr->payload = clientSend_buf;
    ptr->len = strlen(clientSend_buf);//es->p_tx->len;//sizeof(clientSend_buf);
    /* enqueue data for transmission */
    if(strlen(ptr->payload) != 0)
    	wr_err = tcp_write(tpcb, ptr->payload, ptr->len, 1);
    /*User code begin*/
    //wr_err = tcp_write(tpcb, &clientSend_buf, sizeof(clientSend_buf), 1);
    /*User code end*/

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

	 /*User code begin*/
	 es->state = ES_CLOSING;
	 tcp_echoclient_connection_close(tpcb, es);
	 /*User code end*/
   }
  }
}

/**
  * @brief  This function implements the tcp_poll callback function
  * @param  arg: pointer on argument passed to callback
  * @param  tpcb: tcp connection control block
  * @retval err_t: error code
  */
static err_t tcp_echoclient_poll(void *arg, struct tcp_pcb *tpcb)
{
  err_t ret_err;
  struct echoclient *es;

  es = (struct echoclient*)arg;
  if (es != NULL)
  {
    if (es->p_tx != NULL)
    {
      /* there is a remaining pbuf (chain) , try to send data */
      tcp_echoclient_send(tpcb, es);
    }
    else
    {
    	/*if(GVLTCP_state == 1)
    	{
    		es->state = ES_CLOSING;
    	}*/
      /* no remaining pbuf (chain)  */
      if(es->state == ES_CLOSING)
      {
        /* close tcp connection */
        tcp_echoclient_connection_close(tpcb, es);
      }
      /*User code begin*/
      else if(GVLTCP_Cable_state == 1)
      {
		  tcp_echoclient_connection_close(tpcb, es);
      }
      /*User code end*/
    }
    ret_err = ERR_OK;
  }
  else
  {
    /* nothing to be done */
    tcp_abort(tpcb);
    ret_err = ERR_ABRT;

    /*User code begin*/
    es->state = ES_CLOSING;
    tcp_echoclient_connection_close(tpcb, es);
    /*User code end*/
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
static void tcp_echoclient_connection_close(struct tcp_pcb *tpcb, struct echoclient * es )
{
	/* remove callbacks */
	tcp_recv(tpcb, NULL);
	tcp_sent(tpcb, NULL);
	tcp_poll(tpcb, NULL,0);
	echoclient_pcb = NULL;
	if (es != NULL)
	{
	mem_free(es);
	}

	/* close tcp connection */
	tcp_close(tpcb);
	/*User code begin*/
	tcp_abort(echoclient_pcb);
	tcp_create = 0;
	GVLTCP_state = 0;
	GVLTCP_connection = 0;
	/*User code end*/
}

/*User code begin*/

void tcp_client_send_data(uint8_t* recv_buf, uint16_t buf_len)
{
	struct Modebuf Possetrpm;
	struct Modebuf Velsetrpm;
	struct Modebuf Actrpm;
	int i = 0;
	int j = 0;
	uint8_t test[2];
	if(recv_buf[0] == 0x02 && recv_buf[1] == 0x01 && recv_buf[2] == 0x02 && recv_buf[3] == 0x05)
		Datacopy(*clientSend_buf);
	//memset(clientSend_buf, 0,sizeof(clientSend_buf));


	uint8_t ctcpAddress[2];

	if((GVLAddnumber > 0) && (GVLAddnumber < 10))
	{
		ctcpAddress[0] = 0x30;
		ctcpAddress[1] = (char)(GVLAddnumber + '0');
	}
	else if (GVLAddnumber >= 10 && GVLAddnumber < 100)
	{
		ctcpAddress[0] = (char)((GVLAddnumber / 10) + '0');
		ctcpAddress[1] = (char)((GVLAddnumber % 10) + '0');
	}

/*
	for(i = 0; i < buf_len; i++)
	{
		if(recv_buf[i] == 0x02) // STX
		{
			if(recv_buf[i+1] == ctcpAddress[0] && recv_buf[i+2] == ctcpAddress[1])
			{
				if(recv_buf[i+8] == 0x05) //ENQ
				{
					if(recv_buf[i+3] == 0x04){	//READ
						if(recv_buf[i+4] == 0x32 && recv_buf[i+5] == 0x31 && recv_buf[i+6] == 0x30 &&recv_buf[i+7] == 0x43) //st12 state code 0x210C
						{
							clientSend_buf[j++] = 0x02;
							clientSend_buf[j++] = ctcpAddress[0];
							clientSend_buf[j++] = GVLTCP_inv_Statebuf[0];
							clientSend_buf[j++] = GVLTCP_inv_Statebuf[1];
							clientSend_buf[j++] = GVLTCP_inv_Statebuf[2];
							clientSend_buf[j++] = GVLTCP_inv_Statebuf[3];
							clientSend_buf[j++] = 0x05;
						}
						if(recv_buf[i+4] == 0x32 && recv_buf[i+5] == 0x43 && recv_buf[i+6] == 0x30 && recv_buf[i+7] == 0x31) //ru01 error code 0x2C01
						{
							clientSend_buf[j++] = 0x02;
							clientSend_buf[j++] = ctcpAddress[0];
							clientSend_buf[j++] = ctcpAddress[1];
							clientSend_buf[j++] = recv_buf[i+4];
							clientSend_buf[j++] = recv_buf[i+5];
							clientSend_buf[j++] = recv_buf[i+6];
							clientSend_buf[j++] = recv_buf[i+7];
							clientSend_buf[j++] = GVLTCP_inv_Errorbuf[0];
							clientSend_buf[j++] = GVLTCP_inv_Errorbuf[1];
							clientSend_buf[j++] = GVLTCP_inv_Errorbuf[2];
							clientSend_buf[j++] = GVLTCP_inv_Errorbuf[3];
							clientSend_buf[j++] = 0x05;
						}
						if(recv_buf[i+4] == 0x32 && recv_buf[i+5] == 0x31 && recv_buf[i+6] == 0x30 && recv_buf[i+7] == 0x32) //st02 mode of operation display 0x2102
						{
							clientSend_buf[j++] = 0x02;
							clientSend_buf[j++] = ctcpAddress[0];
							clientSend_buf[j++] = ctcpAddress[1];
							clientSend_buf[j++] = recv_buf[i+4];
							clientSend_buf[j++] = recv_buf[i+5];
							clientSend_buf[j++] = recv_buf[i+6];
							clientSend_buf[j++] = recv_buf[i+7];
							clientSend_buf[j++] = GVLTCP_inv_Modebuf[0];
							clientSend_buf[j++] = GVLTCP_inv_Modebuf[1];
							clientSend_buf[j++] = GVLTCP_inv_Modebuf[2];
							clientSend_buf[j++] = GVLTCP_inv_Modebuf[3];
							clientSend_buf[j++] = 0x05;
						}
						if(recv_buf[i+4] == 0x32 && recv_buf[i+5] == 0x43 && recv_buf[i+6] == 0x30 && recv_buf[i+7] == 0x34) //ru04 supply unit state 0x2C04
						{
							clientSend_buf[j++] = 0x02;
							clientSend_buf[j++] = ctcpAddress[0];
							clientSend_buf[j++] = ctcpAddress[1];
							clientSend_buf[j++] = recv_buf[i+4];
							clientSend_buf[j++] = recv_buf[i+5];
							clientSend_buf[j++] = recv_buf[i+6];
							clientSend_buf[j++] = recv_buf[i+7];
							clientSend_buf[j++] = GVLTCP_inv_supplybuf[0];
							clientSend_buf[j++] = GVLTCP_inv_supplybuf[1];
							clientSend_buf[j++] = GVLTCP_inv_supplybuf[2];
							clientSend_buf[j++] = GVLTCP_inv_supplybuf[3];
							clientSend_buf[j++] = 0x05;
						}
						if(recv_buf[i+4] == 0x32 && recv_buf[i+5] == 0x43 && recv_buf[i+6] == 0x31 && recv_buf[i+7] == 0x32) //ru18 dig.input state(STO) 0x2C12
						{
							clientSend_buf[j++] = 0x02;
							clientSend_buf[j++] = ctcpAddress[0];
							clientSend_buf[j++] = ctcpAddress[1];
							clientSend_buf[j++] = recv_buf[i+4];
							clientSend_buf[j++] = recv_buf[i+5];
							clientSend_buf[j++] = recv_buf[i+6];
							clientSend_buf[j++] = recv_buf[i+7];
							clientSend_buf[j++] = GVLTCP_inv_STObuf[0];
							clientSend_buf[j++] = GVLTCP_inv_STObuf[1];
							clientSend_buf[j++] = GVLTCP_inv_STObuf[2];
							clientSend_buf[j++] = GVLTCP_inv_STObuf[3];
							clientSend_buf[j++] = 0x05;
						}
						if(recv_buf[i+4] == 0x32 && recv_buf[i+5] == 0x33 && recv_buf[i+6] == 0x31 && recv_buf[i+7] == 0x34) //vl20 Target velocity(set value)	//use Vel Mode
						{
							Velsetrpm.percent = (float)GVLinverter[GVLAddnumber].VelTargetRpmvalue / GVLinverter[GVLAddnumber].minmaxRpmvalue * 100;
							KEB_dectohex(Velsetrpm.percent, Velsetrpm.Percentbuf);
							clientSend_buf[j++] = 0x02;
							clientSend_buf[j++] = ctcpAddress[0];
							clientSend_buf[j++] = ctcpAddress[1];
							clientSend_buf[j++] = recv_buf[i+4];
							clientSend_buf[j++] = recv_buf[i+5];
							clientSend_buf[j++] = recv_buf[i+6];
							clientSend_buf[j++] = recv_buf[i+7];
							clientSend_buf[j++] = Velsetrpm.Percentbuf[0];
							clientSend_buf[j++] = Velsetrpm.Percentbuf[1];
							clientSend_buf[j++] = Velsetrpm.Percentbuf[2];
							clientSend_buf[j++] = Velsetrpm.Percentbuf[3];
							clientSend_buf[j++] = 0x05;
						}
						if(recv_buf[i+4] == 0x32 && recv_buf[i+5] == 0x45 && recv_buf[i+6] == 0x31 && recv_buf[i+7] == 0x45) //ps30 profile velocity (set value)	//Position mode
						{
							Possetrpm.percent = (float)GVLinverter[GVLAddnumber].PosTargetRpmvalue / GVLinverter[GVLAddnumber].minmaxRpmvalue * 100;
							KEB_dectohex(Possetrpm.percent, Possetrpm.Percentbuf);
							clientSend_buf[j++] = 0x02;
							clientSend_buf[j++] = ctcpAddress[0];
							clientSend_buf[j++] = ctcpAddress[1];
							clientSend_buf[j++] = recv_buf[i+4];
							clientSend_buf[j++] = recv_buf[i+5];
							clientSend_buf[j++] = recv_buf[i+6];
							clientSend_buf[j++] = recv_buf[i+7];
							clientSend_buf[j++] = Possetrpm.Percentbuf[0];
							clientSend_buf[j++] = Possetrpm.Percentbuf[1];
							clientSend_buf[j++] = Possetrpm.Percentbuf[2];
							clientSend_buf[j++] = Possetrpm.Percentbuf[3];
							clientSend_buf[j++] = 0x05;
						}
						if(recv_buf[i+4] == 0x32 && recv_buf[i+5] == 0x31 && recv_buf[i+6] == 0x30 && recv_buf[i+7] == 0x33) //st03 act velocity
						{
							Actrpm.percent = (float)GVLinverter[GVLAddnumber].actRpmvalue / GVLinverter[GVLAddnumber].minmaxRpmvalue * 100;
							KEB_dectohex(Actrpm.percent, Actrpm.Percentbuf);
							clientSend_buf[j++] = 0x02;
							clientSend_buf[j++] = ctcpAddress[0];
							clientSend_buf[j++] = ctcpAddress[1];
							clientSend_buf[j++] = recv_buf[i+4];
							clientSend_buf[j++] = recv_buf[i+5];
							clientSend_buf[j++] = recv_buf[i+6];
							clientSend_buf[j++] = recv_buf[i+7];
							clientSend_buf[j++] = Actrpm.Percentbuf[0];
							clientSend_buf[j++] = Actrpm.Percentbuf[1];
							clientSend_buf[j++] = Actrpm.Percentbuf[2];
							clientSend_buf[j++] = Actrpm.Percentbuf[3];
							clientSend_buf[j++] = 0x05;
						}
						if(recv_buf[i+4] == 0x32 && recv_buf[i+5] == 0x31 && recv_buf[i+6] == 0x32 && recv_buf[i+7] == 0x31)  //st33 position actual value
						{
							KEB_dec32tohex(GVLinverter[GVLAddnumber].PosActPosvalue, &inv_ActPosbuf);
							clientSend_buf[j++] = 0x02; // STX
							clientSend_buf[j++] = ctcpAddress[0];
							clientSend_buf[j++] = ctcpAddress[1];
							clientSend_buf[j++] = recv_buf[i+4]; // PARA ADDRESS[0];
							clientSend_buf[j++] = recv_buf[i+5]; // PARA ADDRESS[1];
							clientSend_buf[j++] = recv_buf[i+6]; // PARA ADDRESS[2];
							clientSend_buf[j++] = recv_buf[i+7]; // PARA ADDRESS[3];
							clientSend_buf[j++] = inv_ActPosbuf[0];	// PARA DATA[0];
							clientSend_buf[j++] = inv_ActPosbuf[1];	// PARA DATA[1];
							clientSend_buf[j++] = inv_ActPosbuf[2];	// PARA DATA[2];
							clientSend_buf[j++] = inv_ActPosbuf[3];	// PARA DATA[3];
							clientSend_buf[j++] = inv_ActPosbuf[4];	// PARA DATA[4];
							clientSend_buf[j++] = inv_ActPosbuf[5];	// PARA DATA[5];
							clientSend_buf[j++] = inv_ActPosbuf[6];	// PARA DATA[6];
							clientSend_buf[j++] = inv_ActPosbuf[7];	// PARA DATA[7];
							clientSend_buf[j++] = 0x05;	// ENQ
						}
					}
				}
				else if(recv_buf[i+12] == 0x03)
				{
					if(recv_buf[i+1] == ctcpAddress[0] && recv_buf[i+2] == ctcpAddress[1])
					{
						if(recv_buf[i+3] == 0x06)
						{
							if(recv_buf[i+4] == 0x32 && recv_buf[i+5] == 0x33 && recv_buf[i+6] == 0x31 && recv_buf[i+7] == 0x34) // Velocity mode Set RPM
							{
								client_TempVel_VelSet[0] = recv_buf[i+8];
								client_TempVel_VelSet[1] = recv_buf[i+9];
								client_TempVel_VelSet[2] = recv_buf[i+10];
								client_TempVel_VelSet[3] = recv_buf[i+11];
								client_percentVel_Vel = KEB_hextodec(&client_TempVel_VelSet);
								if(GVLinverter[GVLAddnumber].iMode == Velocity)
								{
									if(client_percentVel_Vel != 0)
									{
										GVLinverter[GVLAddnumber].VelsetRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue * client_percentVel_Vel / 100;
									}
									else
									{
										GVLinverter[GVLAddnumber].VelsetRpmvalue = 0;
									}
									GVLVelRpmset = true;
									GVLWriteon	= true;
								}
							}
							else if(recv_buf[i+4] == 0x32 && recv_buf[i+5] == 0x45 && recv_buf[i+6] == 0x31 && recv_buf[i+7]== 0x45) // Position mode Set RPM
							{
								client_TempPos_VelSet[0] = recv_buf[i+8];
								client_TempPos_VelSet[1] = recv_buf[i+9];
								client_TempPos_VelSet[2] = recv_buf[i+10];
								client_TempPos_VelSet[3] = recv_buf[i+11];
								client_percentPos_Vel = KEB_hextodec(&client_TempPos_VelSet);
								if(GVLinverter[GVLAddnumber].iMode == Position)
								{
									if(client_percentPos_Vel != 0 && client_percentPos_Vel > 0)
									{
										GVLinverter[GVLAddnumber].PossetRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue * client_percentPos_Vel / 100;
									}
									else if(client_percentPos_Vel <= 0)
									{
										GVLinverter[GVLAddnumber].PossetRpmvalue = 0;
									}
									GVLPosRpmset = true;
									GVLWriteon = true;
								}
							}
							else if(recv_buf[i+4] == 0x32 && recv_buf[i+5] == 0x35 && recv_buf[i+6] == 0x30 && recv_buf[i+7]== 0x30) // Controlword
							{
								GVLWriteon = true;
								GVLsendControlword = true;
								client_cTempControlword[0] = recv_buf[i + 8];
								client_cTempControlword[1] = recv_buf[i + 9];
								client_cTempControlword[2] = recv_buf[i + 10];
								client_cTempControlword[3] = recv_buf[i + 11];
								client_iTempControlword = KEB_hextodec(client_cTempControlword);
								if(client_iTempControlword == 7){
									GVLinverterenable = true;
									GVLPoweroff = true;
									GVLPoweron = false;
								}
								else if(client_iTempControlword == 15){
									GVLinverterenable = true;
									GVLPoweron = true;
									GVLPoweroff = false;
								}
								else if(client_iTempControlword == 16){
									if(GVLinverter[GVLAddnumber].iMode == Home)
										GVLHomeset = true;
								}
								else if(client_iTempControlword == 48){
									if(GVLinverter[GVLAddnumber].iMode == Position)
										GVLPosStart = true;
								}
								else if(client_iTempControlword == 128){
									GVLReset = true;
								}
								else if(client_iTempControlword == 256){
									GVLPosStop = true;
								}
							}
							else if(recv_buf[i+4] == 0x32 && recv_buf[i+5] == 0x35 && recv_buf[i+6] == 0x30 && recv_buf[i+7] == 0x31) //choose Mode
							{
								if(recv_buf[i+8] == 0x30 && recv_buf[i+9] == 0x30 && recv_buf[i+10] == 0x30 && recv_buf[i+11] == 0x31) //Position Mode
								{
									GVLWriteon = true;
									GVLsendMode = true;
									GVL_iModevalue = Position;	//Position
								}
								if(recv_buf[i+8] == 0x30 && recv_buf[i+9] == 0x30 && recv_buf[i+10] == 0x30 && recv_buf[i+11] == 0x32) // Velocity Mode
								{
									GVLWriteon = true;
									GVLsendMode = true;
									GVL_iModevalue = Velocity; //Velocity
								}
								if(recv_buf[i+8] == 0x30 && recv_buf[i+9] == 0x30 && recv_buf[i+10] == 0x30 && recv_buf[i+11] == 0x36) // Home Mode
								{
									GVLWriteon = true;
									GVLsendMode = true;
									GVL_iModevalue = Home; //Home
								}
							}
							else if(recv_buf[i+4] == 0x31 && recv_buf[i+5] == 0x36 && recv_buf[i+6] == 0x30 && recv_buf[i+7] == 0x30) // choose Ethercat,serial
							{
								if(recv_buf[i+8] == 0x30 && recv_buf[i+9] == 0x30 && recv_buf[i+10] == 0x30 && recv_buf[i+11] == 0x38) // Ethercat
								{
									GVLWriteon = true;
									GVLComon = true;
								}
								else if(recv_buf[i+8] == 0x30 && recv_buf[i+9] == 0x30 && recv_buf[i+10] == 0x30 && recv_buf[i+11] == 0x30) //serial
								{
									GVLWriteon = true;
									GVLComoff = true;
								}
							}
							else if(recv_buf[i+4] == 0x34 && recv_buf[i+5] == 0x30 && recv_buf[i+6] == 0x30 && recv_buf[i+7] == 0x30) //MC on and MC off
							{
								if(recv_buf[i+8] == 0x30 && recv_buf[i+9] == 0x30 && recv_buf[i+10] == 0x30 && recv_buf[i+11] == 0x31) //turn on
								{
									GVLMCinput = true;
									GVLMCoutput = true;
								}
								else if(recv_buf[i+8] == 0x30 && recv_buf[i+9] == 0x30 && recv_buf[i+10] == 0x30 && recv_buf[i+11] == 0x30) //turn off
								{
									GVLMCinput = false;
									GVLMCoutput = false;
								}
							}
							else if(recv_buf[i+4] == 0x34 && recv_buf[i+5] == 0x31 && recv_buf[i+6] == 0x30 && recv_buf[i+7] == 0x30) //bypassSTO
							{
								if(recv_buf[i+8] == 0x30 && recv_buf[i+9] == 0x30 && recv_buf[i+10] == 0x30 && recv_buf[i+11] == 0x31) //turn on
								{
									GVLbypassSTO = true;
								}
								else if(recv_buf[i+8] == 0x30 && recv_buf[i+9] == 0x30 && recv_buf[i+10] == 0x30 && recv_buf[i+11] == 0x30) //turn off
								{
									GVLbypassSTO = false;
								}
							}
						}
					}
					else if(recv_buf[i + 16] == 0x03)
					{
						if(recv_buf[i+1] == ctcpAddress[0] && recv_buf[i+2] == ctcpAddress[1])
						{
							if(recv_buf[i+3] == 0x06)
							{
								if(recv_buf[i+4] == 0x32 && recv_buf[i+5] == 0x35 && recv_buf[i+6] == 0x31 && recv_buf[i+7] == 0x33)// position set mm
								{
									client_TempPos_PosSet[0] = recv_buf[i+8];
									client_TempPos_PosSet[1] = recv_buf[i+9];
									client_TempPos_PosSet[2] = recv_buf[i+10];
									client_TempPos_PosSet[3] = recv_buf[i+11];
									client_TempPos_PosSet[4] = recv_buf[i+12];
									client_TempPos_PosSet[5] = recv_buf[i+13];
									client_TempPos_PosSet[6] = recv_buf[i+14];
									client_TempPos_PosSet[7] = recv_buf[i+15];
									if(GVLinverter[GVLAddnumber].iMode == Position)
									{
										GVLinverter[GVLAddnumber].PosSetPosvalue = KEB_hextodec32(&client_TempPos_PosSet);
										GVLPosposset = true;
										GVLWriteon = true;
									}
								}
								if(recv_buf[i+4] == 0x33 && recv_buf[i+5] == 0x31 && recv_buf[i+6] == 0x30 && recv_buf[i+7] == 0x30)// Home set mm
								{
									client_TempHome_PosSet[0] = recv_buf[i+8];
									client_TempHome_PosSet[1] = recv_buf[i+9];
									client_TempHome_PosSet[2] = recv_buf[i+10];
									client_TempHome_PosSet[3] = recv_buf[i+11];
									client_TempHome_PosSet[4] = recv_buf[i+12];
									client_TempHome_PosSet[5] = recv_buf[i+13];
									client_TempHome_PosSet[6] = recv_buf[i+14];
									client_TempHome_PosSet[7] = recv_buf[i+15];
									if(GVLinverter[GVLAddnumber].iMode == Home)
									{
										GVLinverter[GVLAddnumber].HomeSetPosvalue = KEB_hextodec32(&client_TempHome_PosSet);
										GVLHomeposset = true;
										GVLWriteon = true;
									}
								}
							}
						}
					}
				}
			}
		}
	}*/
}
void tcp_serial_inf(uint8_t* Buffer, uint16_t Buffersize)
{
	int i = 0;

	for(i = 0; i < Buffersize; i++){
		if(Buffer[i] == 0x02 && Buffer[i + 9] == 0x03){
			if(Buffer[i+1] == 0x32 && Buffer[i+2] == 0x31 && Buffer[i+3] == 0x30 && Buffer[i+4] == 0x43){//State
				memcpy(inv_Statebuf, Buffer + (i + 5), 4);
			}
			if(Buffer[i+1] == 0x32 && Buffer[i+2] == 0x43 && Buffer[i+3] == 0x30 && Buffer[i+4] == 0x31){//Error
				memcpy(inv_Errorbuf, Buffer + (i + 5), 4);
			}
			if(Buffer[i+1] == 0x32 && Buffer[i+2] == 0x31 && Buffer[i+3] == 0x30 && Buffer[i+4] == 0x32){//Mode of operation display
				memcpy(inv_Modebuf, Buffer + (i + 5), 4);
			}
			if(Buffer[i+1] == 0x32 && Buffer[i+2] == 0x43 && Buffer[i+3] == 0x30 && Buffer[i+4] == 0x34){//Supply state
				memcpy(inv_supplybuf, Buffer + (i + 5), 4);
			}
			if(Buffer[i+1] == 0x32 && Buffer[i+2] == 0x43 && Buffer[i+3] == 0x31 && Buffer[i+4] == 0x32){ //ru18 dig.input state(STO)
				memcpy(inv_STObuf, Buffer + (i + 5), 4);
			}
		}
	}
}

void tcp_timeout_check()
{
	static int temp_timestamp = 0;
	static int tcp_timeout = 0;
	struct tcp_pcb *tpcb;
	struct echoclient *echo;

	uint32_t serveriaddr;
	uint32_t stmiaddr;


	serveriaddr = (DEST_IP_ADDR0 * pow(256 ,0)) + (DEST_IP_ADDR1 * pow(256 , 1)) + (DEST_IP_ADDR2 * pow(256 , 2)) + (DEST_IP_ADDR3 * pow(256 , 3));
	stmiaddr = (IP_ADDRESS[0] * pow(256,0)) + (IP_ADDRESS[1] * pow(256, 1)) + (IP_ADDRESS[2] * pow(256, 2)) + (IP_ADDRESS[3] * pow(256,3));

	/*if(GVLTCP_state == 2)
	{
		if(temp_timestamp == tcp_timestamp)
		{
			tcp_timeout = tcp_timeout + 1;
			if(tcp_timeout >= 500)
			{
				temp_timestamp = 0;
				tcp_echoclient_connection_close(tpcb, echo);
			}
		}
		else if(temp_timestamp != tcp_timestamp)
		{
			temp_timestamp = 0;
			temp_timestamp = tcp_timestamp;
			tcp_timeout = 0;
		}
	}*/
	if(GVLTCP_state == 2 && GVLTCP_Cable_state == 1)
	{
		tcp_echoclient_send(tpcb, echo);
	}
	if(/*GVLTCP_state < 2 &&*/ (echoclient_pcb->local_ip.addr != stmiaddr && echoclient_pcb->local_port != DEST_PORT))
		GVLTCP_state = 0;
}

/*User code end*/

#endif /* LWIP_TCP */

