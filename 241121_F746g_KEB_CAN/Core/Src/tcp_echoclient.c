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
uint8_t IP_ADDRESS[4]; //extern variable
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
};

/* Private function prototypes -----------------------------------------------*/
static err_t tcp_echoclient_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
static void tcp_echoclient_connection_close(struct tcp_pcb *tpcb, struct echoclient * es);
static err_t tcp_echoclient_poll(void *arg, struct tcp_pcb *tpcb);
static err_t tcp_echoclient_sent(void *arg, struct tcp_pcb *tpcb, u16_t len);
static void tcp_echoclient_send(struct tcp_pcb *tpcb, struct echoclient * es);
static err_t tcp_echoclient_connected(void *arg, struct tcp_pcb *tpcb, err_t err);

/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Connects to the TCP echo server
  * @param  None
  * @retval None
  */
void tcp_echoclient_connect(void)
{
  ip_addr_t DestIPaddr;
  /*User code begin*/
  if (GVLTCP_state == 0 || echoclient_pcb == NULL )
  {
	  echoclient_pcb = tcp_new();
  }
  /*User code end*/
  if (echoclient_pcb != NULL)
  {
    IP4_ADDR( &DestIPaddr, DEST_IP_ADDR0, DEST_IP_ADDR1, DEST_IP_ADDR2, DEST_IP_ADDR3 );

    /* connect to destination address/port */
    tcp_connect(echoclient_pcb,&DestIPaddr,DEST_PORT,tcp_echoclient_connected);
    /*User code begin*/
    GVLTCP_state = 1;
    /*User code end*/
  }
  else
  {
	/*User code begin*/
	GVLTCP_state = 0;
	/*User code end*/
    /* deallocate the pcb */
    memp_free(MEMP_TCP_PCB, echoclient_pcb);
#ifdef SERIAL_DEBUG
    printf("\n\r can not create tcp pcb");
#endif
  }
}

/**
  * @brief Function called when TCP connection established
  * @param tpcb: pointer on the connection control block
  * @param err: when connection correctly established err should be ERR_OK 
  * @retval err_t: returned error 
  */
static err_t tcp_echoclient_connected(void *arg, struct tcp_pcb *tpcb, err_t err)
{
  struct echoclient *es = NULL;

  if (err == ERR_OK)   
  {
    /* allocate structure es to maintain tcp connection informations */
    es = (struct echoclient *)mem_malloc(sizeof(struct echoclient));
  
    if (es != NULL)
    {
      es->state = ES_CONNECTED;
      es->pcb = tpcb;
      /*User code begin*/
      es->p_tx = NULL;

      /*User code end*/
      sprintf((char*)data, "sending tcp client message %d", (int)message_count);

      /* allocate pbuf */
      es->p_tx = pbuf_alloc(PBUF_TRANSPORT, strlen((char*)data) , PBUF_POOL);

      if (es->p_tx)
      {
        /* copy data to pbuf */
        pbuf_take(es->p_tx, (char*)data, strlen((char*)data));

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
  * @retval err_t: returned error
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
    uint8_t *data = (uint8_t *)p->payload;
    if (p->len < 4 || data[0] != 0xAA || data[1] != 0x55) {
        pbuf_free(p);
        return ERR_OK;
    }

    uint8_t payload_len = data[2];
    if (p->len < 3 + payload_len + 1) { // +1 for checksum
        pbuf_free(p);
        return ERR_OK;
    }

    // Checksum 검사
    uint8_t checksum = 0;
    for (int i = 2; i < 3 + payload_len; i++) checksum ^= data[i];
    if (checksum != data[3 + payload_len]) {
        pbuf_free(p);
        return ERR_OK;
    }

    // READ 요청
    if (data[3] == 0x10) {
        send_tlv_response_to_csharp(tpcb);
    }
    // WRITE 요청
    else if (data[3] >= 0x80) {
        parse_write_payload(&data[3], payload_len);
    }
    /*User code end*/
    pbuf_free(p);
   // tcp_echoclient_connection_close(tpcb, es);
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
      /* no remaining pbuf (chain)  */
      if(es->state == ES_CLOSING)
      {
        /* close tcp connection */
        tcp_echoclient_connection_close(tpcb, es);
      }
    }
    ret_err = ERR_OK;
  }
  else
  {
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
static void tcp_echoclient_connection_close(struct tcp_pcb *tpcb, struct echoclient * es )
{
  /* remove callbacks */
  tcp_recv(tpcb, NULL);
  tcp_sent(tpcb, NULL);
  tcp_poll(tpcb, NULL,0);

  if (es != NULL)
  {
    mem_free(es);
  }
	/*User code begin*/
	GVLTCP_state = 0;
	echoclient_pcb = NULL;
	/*User code end*/

  /* close tcp connection */
  tcp_close(tpcb);
}

void tcp_loop_send()
{
	struct tcp_pcb* tpcb;
	struct ehoclient *echo;
	if(GVLTCP_state == 1)
	{
		;//tcp_echoclient_send(tpcb, echo);
	}
	uint32_t serveriaddr;
	uint32_t stmiaddr;


	serveriaddr = (DEST_IP_ADDR0 * pow(256, 0)) + (DEST_IP_ADDR1 * pow(256, 1)) + (DEST_IP_ADDR2 * pow(256, 2)) + (DEST_IP_ADDR3 * pow(256, 3));
	stmiaddr = (IP_ADDRESS[0] * pow(256, 0)) + (IP_ADDRESS[1] * pow(256, 1)) + (IP_ADDRESS[2] * pow(256, 2)) + (IP_ADDRESS[3] * pow(256, 3));
}

void send_tlv_response_to_csharp(struct tcp_pcb *tpcb)
{
    int velocity = g_st_inverter.PosSetRpmvalue;
    int16_t position = g_st_inverter.PosSetPosvalue;
    uint32_t count = Enc_Count;

    uint8_t tlv[32];
    int i = 0;
    tlv[i++] = 0xAA;
    tlv[i++] = 0x55;
    int payloadIndex = i++; // 자리 확보

    tlv[i++] = 0x01; tlv[i++] = 4;
    memcpy(&tlv[i], &velocity, 4); i += 4;

    tlv[i++] = 0x02; tlv[i++] = 2;
    memcpy(&tlv[i], &position, 2); i += 2;

    tlv[i++] = 0x03; tlv[i++] = 4;
    memcpy(&tlv[i], &count, 4); i += 4;

    tlv[payloadIndex] = i - (payloadIndex + 1);

    uint8_t checksum = 0;
    for (int j = 2; j < i; j++) checksum ^= tlv[j];
    tlv[i++] = checksum;

    tcp_write(tpcb, tlv, i, TCP_WRITE_FLAG_COPY);
}

void parse_write_payload(uint8_t *payload, uint8_t len)
{
    int i = 0;
    while (i < len)
    {
        uint8_t id = payload[i++];
        uint8_t dlen = payload[i++];

        switch (id)
        {
            case 0x81:
                if (dlen == 4) memcpy(&g_st_inverter.PosSetRpmvalue, &payload[i], 4);
                break;
            case 0x82:
                if (dlen == 2) memcpy(&g_st_inverter.PosSetPosvalue, &payload[i], 2);
                break;
            case 0x83:
                if (dlen == 1) g_st_inverter.s8Mode = payload[i];
                break;
            case 0x84:
                if (dlen == 4) memcpy(&g_st_Direct.s32EncodercountValue, &payload[i], 4);
                break;
            // 필요한 경우 추가적인 case 가능
        }
        i += dlen;
    }
}
#endif /* LWIP_TCP */


