/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
//#include <KEB_CAN_Func.h>
#include <KEB_CAN_Func_Copy.hpp>
#include <KEB_PROTOCAL.h>
#include "main.h"
#include "cmath"
#include "cmsis_os.h"
#include "fatfs.h"
#include "lwip.h"
#include "app_touchgfx.h"
#include "usb_host.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stm32746g_discovery.h>
#include <stm32746g_discovery_qspi.h>
//#include "global.h"
#include "SerialCom.h"
#include "lwip/opt.h"
#include "lwip/init.h"
#include "lwip/netif.h"
#include "lwip/timeouts.h"
#include "netif/etharp.h"
#include "ethernetif.h"
#include "tcp_echoclient.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#include <string.h>

KEB_CAN_FUNC KEB_CAN;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define REFRESH_COUNT        1835

#define SDRAM_TIMEOUT                            ((uint32_t)0xFFFF)
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)


#define TCPreceiveSize 512
#define TCPsendSize 512

#define RxDataSize 512
#define TxDataSize 30

#define DATA_BUF_SIZE 512

#define inverter_total 7	//inverter Total unit
//test
#define ARRAY_LEN(x) (sizeof(x) / sizeof(x)[0])

#define STX 0x02

#define R_END 0x05
#define W_END 0x03


/*CAN define*/
#define NMT 0x000

#define NMTHeartbeat 0x700
#define NMTconsumer 0x77F

#define TXPDO3 0x380
#define TXPDO4 0x480

#define RXPDO3 0x400
#define RxPDO4 0x500

#define CAN_ID 0x001
/*					*/


//Flash memory test
#define FLASH_USER_START_ADDR	ADDR_FLASH_SECTOR_6
#define FLASH_USER_END_ADDR		ADDR_FLASH_SECTOR_7 + GetSectorSize(ADDR_FLAH_SECTOR_7)

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc3;
DMA_HandleTypeDef hdma_adc3;

CAN_HandleTypeDef hcan1;

CRC_HandleTypeDef hcrc;

DMA2D_HandleTypeDef hdma2d;

I2C_HandleTypeDef hi2c3;

LTDC_HandleTypeDef hltdc;

QSPI_HandleTypeDef hqspi;

RTC_HandleTypeDef hrtc;

SD_HandleTypeDef hsd1;

SPI_HandleTypeDef hspi2;
DMA_HandleTypeDef hdma_spi2_tx;
DMA_HandleTypeDef hdma_spi2_rx;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim8;
TIM_HandleTypeDef htim12;
TIM_HandleTypeDef htim13;
TIM_HandleTypeDef htim14;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart6;
DMA_HandleTypeDef hdma_usart6_rx;

SDRAM_HandleTypeDef hsdram1;

osThreadId defaultTaskHandle;
osThreadId Serial_TaskHandle;
osThreadId ETHTaskHandle;
/* USER CODE BEGIN PV */

//Can communication
CAN_FilterTypeDef canFilter1;

CAN_RxHeaderTypeDef CANRxHeader;

CAN_TxHeaderTypeDef CANTxHeader;

HAL_StatusTypeDef ret;

uint8_t SPIRxData[3] = {0x00, };
uint8_t SPITxData[3] = {0x00, };

uint8_t SPITx1stInput[3] = {0x00, };
uint8_t SPITx2ndInput[3] = {0x00, };

uint8_t SPIRx1stInput[3] = {0x00, };
uint8_t SPIRx2ndInput[3] = {0x00, };

uint8_t SPIRx1stOutput[3] = {0x00, };
uint8_t SPIRx2ndOutput[3] = {0x00, };



uint8_t SPIEncoderTxData[5] = {0x00, };
uint8_t SPIEncoderRxData[5] = {0x00, };

int32_t SPIEncoderData;

uint16_t LEDTest = 0;

uint8_t CAN1Rx0Data[8];
uint8_t CAN1RPDO3Data[8] = {0x00, };
uint8_t CAN1RPDO4Data[8] = {0x00, };
uint8_t CAN1NMTData[8] = {0x00, };
uint32_t TxMailBox;

uint32_t cobID = 0x000;
uint8_t Node;
uint8_t len;


uint32_t PDOcurrentuitime = 0;
uint32_t PDOgetuiTime = 0;
uint32_t PDObeforeuiTime = 0;

uint32_t PDOcurrentuitime2 = 0;
uint32_t PDObeforeuiTime2 = 0;

uint32_t currentuiTime = 0;
uint32_t getuiTime = 0;
uint32_t beforeuiTime = 0;

uint8_t TempPowerStart[2];

/*CAN CROSS PROTOCAL BEGIN*/

//CAN TPDO3 BUFFER
uint8_t TPDO3statusword[2];
uint8_t TPDO3Modes;
uint8_t TPDO3Errorcode;
//CAN TPDO4 BUFFER
uint8_t TPDO4PositionAct[4];
uint8_t TPDO4VelocityAct[4];
//CAN Heartbeat
uint8_t Heartbeatconsumer;
//CAN Convert hexto16uint
uint16_t TPDO3Statusword_dec;
uint16_t TPDO3Errorcode_dec;

/*CAN CROSS PROTOCAL END*/


static FMC_SDRAM_CommandTypeDef Command;
//Flash memory
static FLASH_EraseInitTypeDef EraseInitStruct;

uint32_t FirstSector = 0, NbOfSectors = 0;
uint32_t Address = ADDR_FLASH_SECTOR_7, SECTORError = 0;
__IO uint32_t data32 = 0 , MemoryProgramStatus = 0;


//



//global variable

//StatecontrolwordTypedef GVLStatecontrolword;
//StateMachineTypedef GVLStateMachine;
//BrakeStatusTypedef GVLBrakeStatus;

//StatuswordTypedef GVLStatusword;

uint16_t GVLControlWordValue;

//Velocity Mode RPM CW,CCW
bool GVLPosStop			= false;
bool GVLPosposset		= false;

//Home Mode




uint8_t GVLTCP_inv_Statebuf[4];
uint8_t GVLTCP_inv_Errorbuf[4];
uint8_t GVLTCP_inv_Modebuf[4];
uint8_t GVLTCP_inv_supplybuf[4];
uint8_t GVLTCP_inv_STObuf[4];

//uint8_t g_u8Mode;//GVLiMode;

int ReadControlvalue;
int ReadStatevalue;
int ReadBrakeStatusvalue;
uint8_t GVLCount;


//initialize
bool binit;

bool Velmode_Zerorpm_Set;
bool Posmode_Zerorpm_Set;


//RS485 rx/tx
uint8_t Buffer_Rx[RxDataSize];
uint8_t Buffer_Tx[TxDataSize];


//readmode, writemode select
bool bReadmode = true;
bool bWritemode = false;

uint8_t uiReadDataStep;

uint8_t uiSelectNum;

uint8_t testTime;
bool Trig;

//Analog value
int iTempAnalog = 0;

//System counter
char oldsystime[inverter_total][4];
uint8_t timeout;

uint8_t rcv_Flag = 0;
uint16_t wrPtr;
uint16_t rdPtr;
uint16_t rcvlen;
uint8_t* ReadTx;
uint8_t* WriteTx;

uint32_t NDTR,oldNDTR;

uint8_t RxBuf[DATA_BUF_SIZE] = {0, };

uint16_t uiADCresult[5] = {0,};

int flashtest;

//uint8_t uitest[4];
int itest;
bool GPIOTest;
int SPIsteptest;

bool testcount1 = true;
bool testcount2;
bool testcount3;

uint8_t modetest;

uint8_t u8Modestep;

uint8_t Tcp_ReceiveData[17];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void MPU_Initialize(void);
static void MPU_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_CRC_Init(void);
static void MX_DMA2D_Init(void);
static void MX_FMC_Init(void);
static void MX_I2C3_Init(void);
static void MX_LTDC_Init(void);
static void MX_QUADSPI_Init(void);
static void MX_RTC_Init(void);
static void MX_SDMMC1_SD_Init(void);
static void MX_SPI2_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM5_Init(void);
static void MX_TIM8_Init(void);
static void MX_TIM12_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART6_UART_Init(void);
static void MX_ADC3_Init(void);
static void MX_CAN1_Init(void);
static void MX_TIM13_Init(void);
static void MX_TIM14_Init(void);
void StartDefaultTask(void const * argument);
void StartTask02(void const * argument);
void StartTask03(void const * argument);

/* USER CODE BEGIN PFP */
void variableinit();
void HAL_receive(UART_HandleTypeDef *huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart);
void disconnectstate();

void StateControlword(StatecontrolwordTypedef *p, int value);
void StateMachine(StateMachineTypedef *p, int value);
void BrakeStatus(BrakeStatusTypedef *p, int value);

void Statusword(StatuswordTypedef *p, uint16_t value);

void save_flash();
//Flash memory Test function
static uint32_t GetSector(uint32_t Address);
static uint32_t GetSectorSize(uint32_t Sector);

//can communicaiton
void can_filter_config(void);
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

//test
void Datacopy(uint8_t *cpData)	//삭제해도 될듯
{
	cpData[0] = STX;
	cpData[1] = 0x01;
	cpData[2] = TPDO3statusword[0];
	cpData[3] = TPDO3statusword[1];
	cpData[4] = TPDO3Modes;
	cpData[5] = TPDO3Errorcode;
	cpData[6] = TPDO4PositionAct[0];
	cpData[7] = TPDO4PositionAct[1];
	cpData[8] = TPDO4PositionAct[2];
	cpData[9] = TPDO4PositionAct[3];
	cpData[10] = TPDO4VelocityAct[0];
	cpData[11] = TPDO4VelocityAct[1];
	cpData[12] = TPDO4VelocityAct[2];
	cpData[13] = TPDO4VelocityAct[3];
	cpData[14] = g_bMCinputstate;
	cpData[15] = g_bMCoutputstate;
	cpData[16] = g_bBypassSTO;
	cpData[17] = 0x00;
	cpData[18] = 0x05;
}

/*SPI Communication */
void HAL_DMA_STATE_CHANGE(SPI_HandleTypeDef *hspi)
{
	hspi->State = HAL_SPI_STATE_READY;
}
/*void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	;//HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_SET);
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if(hspi-> Instance == SPI2)
	{
		HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_SET);
		SPIsteptest = SPIsteptest + 1;
		testcount1 = false;
	}
}*/

/*Flash Memory Function begin*/
uint32_t GetSector(uint32_t Address)
{
	uint32_t sector = 0;

	if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
	{
		sector = FLASH_SECTOR_0;
	}
	else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
	{
		sector = FLASH_SECTOR_1;
	}
	else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
	{
		sector = FLASH_SECTOR_2;
	}
	else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
	{
		sector = FLASH_SECTOR_3;
	}
	else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
	{
		sector = FLASH_SECTOR_4;
	}
	else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
	{
		sector = FLASH_SECTOR_5;
	}
	else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
	{
		sector = FLASH_SECTOR_6;
	}
	else
	{
		sector = FLASH_SECTOR_7;
	}
	return sector;
}

void save_flash()
{
	HAL_FLASH_Unlock(); // unlock flash memory
	FirstSector = GetSector(ADDR_FLASH_SECTOR_7);
	NbOfSectors = (GetSector(ADDR_FLASH_SECTOR_7)- FirstSector) + 1;

	EraseInitStruct.TypeErase		= FLASH_TYPEERASE_SECTORS;
	EraseInitStruct.VoltageRange	= FLASH_VOLTAGE_RANGE_3;
	EraseInitStruct.Sector			= FirstSector;
	EraseInitStruct.NbSectors		= NbOfSectors;
	HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError);

	//Save Data
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address + 0, (uint32_t)g_u32FlashSaveDen);		//Moter shaft
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address + 4, (uint32_t)g_u32FlashSaveNum);		//Gear end shaft
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address + 8, (uint32_t)g_u32FlashSaveDiameter);	//move
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address + 12, (uint32_t)g_u32FlashSaveMaxPos);	// Max Position
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address + 16, (uint32_t)g_u32FlashSaveMinPos);	// Min Position
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address + 20, (uint32_t)g_u32FlashSaveMinMaxRpm); // MinMax Rpm
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address + 24, (uint32_t)g_u32FlashSaveDriveType);	// Type (ex : Direct, Inverter ...)
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address + 28, (uint32_t)g_u32FlashSaveWire);		// Wire width
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address + 32, (uint32_t)g_u32FlashSaveYoYo);		// YoYo type or no YoYo Type
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address + 36, (uint32_t)g_u32FlashSaveEncPulse);	// Encoder Pulse(ex : 1024, 2048, 4192..);
	HAL_FLASH_Lock();
}
/*Flash Memory Function End*/

/*CAN CROSS(Canopen Protocal) Protocal Begin*/
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  uint8_t rcvd_msg[8] = {0, };

  if(HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &CANRxHeader, rcvd_msg) != HAL_OK)
  {
    Error_Handler();
  }

  if(CANRxHeader.StdId == TXPDO3 + CAN_ID)		//KEB 3rd transmit PDO Mapping + CANopen Node ID
  {
	  memcpy(&TPDO3statusword, &rcvd_msg, 2);	// 2byte controlword
	  KEB_CAN.KEB_CAN_Func_reverse_array(TPDO3statusword, 2);//KEB_CAN_Func_reverse_array(TPDO3statusword, 2);

	  memcpy(&TPDO3Modes, &rcvd_msg[2], 1);		// 1byte Modes of operation

	  memcpy(&TPDO3Errorcode, &rcvd_msg[3], 1); // 1byte errorcode
  }

  if(CANRxHeader.StdId == TXPDO4 + CAN_ID)		//KEB 4th transmit POD Mapping + CANopen Node ID
  {
	  memcpy(&TPDO4PositionAct, &rcvd_msg, 4);	// READ KEB Actual Postion
	  KEB_CAN.KEB_CAN_Func_reverse_array(TPDO4PositionAct, 4);//KEB_CAN_Func_reverse_array(TPDO4PositionAct, 4);

	  memcpy(&TPDO4VelocityAct, &rcvd_msg[4], 4);	//READ KEB Actual Velocity
	  KEB_CAN.KEB_CAN_Func_reverse_array(TPDO4VelocityAct, 4);//KEB_CAN_Func_reverse_array(TPDO4VelocityAct, 4);
  }
  if(CANRxHeader.StdId == NMTHeartbeat + CAN_ID)	//READ KEB Canopen Heartbeat
  {
	  memcpy(&Heartbeatconsumer, rcvd_msg, 1);
  }
}

void can_filter_config(void)
{

	canFilter1.FilterActivation = ENABLE;
	canFilter1.FilterBank = 0;
	canFilter1.FilterFIFOAssignment = CAN_RX_FIFO0;
	canFilter1.FilterIdHigh = (0x7F0 << 5);
	canFilter1.FilterMaskIdHigh = (0x7F0 << 5);//(0x7F0 << 5);
	canFilter1.FilterIdLow = 0;
	canFilter1.FilterMaskIdLow = 0;//(0x7F0 << 5);
	canFilter1.FilterMode = CAN_FILTERMODE_IDMASK;
	canFilter1.FilterScale = CAN_FILTERSCALE_16BIT;

	if(HAL_CAN_ConfigFilter(&hcan1, &canFilter1) != HAL_OK)
	{
		Error_Handler();
	}

	if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
	{
		Error_Handler();
	}

}
/*CAN CROSS(Canopen Protocal)Protocal End*/

/*init Function Begin*/
void variableinit()
{
	g_st_u8IP[0] = DEST_IP_ADDR0;
	g_st_u8IP[1] = DEST_IP_ADDR1;
	g_st_u8IP[2] = DEST_IP_ADDR2;
	g_st_u8IP[3] = DEST_IP_ADDR3;

	strcpy(g_st_inverter.cName,"Inverter01");

	g_st_inverter.VelsetRpmvalue = 0;

	g_st_inverter.PosSetRpmvalue = 0;

	g_st_inverter.increments = 65536;	//g_st_Setting.fIncrements;

	g_st_Setting.fDiameter = 1;		//g_st_Setting.fDiameter;

	if(g_st_Setting.fGearNumerator <= 0)	//g_st_Setting.fGearNumerator;
		g_st_Setting.fGearNumerator = 1;	//g_st_Setting.fGearNumerator;

	if(g_st_Setting.fGearDenominator <= 0)	//g_st_Setting.fGearDenominator;
		g_st_Setting.fGearDenominator = 1; //g_st_Setting.fGearDenominator;

	g_s8Mode = Position;
	g_bModeWrite = true;

	binit = true;
}
/*init Function End*/

void disconnectstate()
{
	strcpy(g_st_inverter.cState,"disconnect");
	strcpy(g_st_inverter.cError,"disconnect");
	strcpy(g_st_inverter.cMode,"disconnect");
	g_st_inverter.actRpmvalue = 0000;
	g_st_inverter.VelTargetRpmvalue = 0000;
	g_st_inverter.PosTargetRpmvalue = 0000;
	memset(RxBuf, 0,DATA_BUF_SIZE);
}

void Statusword(StatuswordTypedef *p, uint16_t value)
{
	p->manufacturer_spec_15 = value & 0x8000;
	p->special_function = value & 0x4000;
	p->op_mode_spec_13 = value & 0x2000;
	p->op_mode_spec_12 = value & 0x1000;
	p->internal_limit_active = value & 0x0800;
	p->target_reached = value & 0x0400;
	p->remote = value & 0x0200;
	p->synchron = value & 0x0100;
	p->warning = value & 0x0080;
	p->switch_on_disabled = value & 0x0040;
	p->no_quick_stop = value & 0x0020;
	p->voltage_enabled = value & 0x0010;
	p->fault = value & 0x0008;
	p->operation_enabled = value & 0x0004;
	p->switched_on = value & 0x0002;
	p->ready_to_switch_on = value & 0x0001;
}

void StateControlword(StatecontrolwordTypedef *p, int value)
{
    p->brake_ctrl_15 = value & 0x8000;
    p->manufacturer_spec_14 = value & 0x4000;
    p->manufacturer_spec_13 = value & 0x2000;
    p->manufacturer_spec_12 = value & 0x1000;
    p->manufacturer_spec_11 = value & 0x0800;
    p->reserved = value & 0x0400;
    p->op_mode_spec_nine = value & 0x0200;
    p->halt = value & 0x0100;
    p->fault_reset = value & 0x0080;
    p->op_mode_spec_six = value & 0x0040;
    p->op_mode_spec_five = value & 0x0020;
    p->op_mode_spec_four = value & 0x0010;
    p->enable_operation = value & 0x0008;
    p->no_quick_stop = value & 0x0004;
    p->enable_voltage = value & 0x0002;
    p->switch_on = value & 0x0001;
}
void BrakeStatus(BrakeStatusTypedef *p, int value)
{
    p->Reserved_15 = value & 0x8000;
    p->Reserved_14 = value & 0x4000;
    p->Reserved_13 = value & 0x2000;
    p->Reserved_12 = value & 0x1000;
    p->Reserved_11 = value & 0x0800;
    p->Reserved_10 = value & 0x0400;
    p->Reserved_9 = value & 0x0200;
    p->Reserved_8 = value & 0x0100;
    p->State_closing = value & 0x0050;
    p->State_close_delay = value & 0x0040;
    p->State_open = value & 0x0030;
    p->State_opening = value & 0x0020;
    p->State_open_delay = value & 0x0010;
    p->State_closed = !(p->State_closing || p->State_close_delay || p->State_open || p->State_opening || p->State_open_delay);
    p->Reserved_3 = value & 0x0008;
    p->BrakeCtrlRef = value & 0x0004;
    p->BrakeCtrlSigal = value & 0x0002;
    p->BrakeCtrlVal = value & 0x0001;
	/*if((value - 32768) > -1)
		{
			p->Reserved_15 = true;
			value = value - 32768;
		}
		else
			p->Reserved_15 = false;

		if((value - 16384) > -1)
		{
			p->Reserved_14 = true;
			value = value - 16384;
		}
		else
			p->Reserved_14= false;

		if((value - 8192) > -1)
		{
			p->Reserved_13 = true;
			value = value - 8192;
		}
		else
			p->Reserved_13 = false;

		if((value - 4096) > -1)
		{
			p->Reserved_12 = true;
			value = value - 4096;
		}
		else
			p->Reserved_12 = false;

		if((value - 2048) > -1)
		{
			p->Reserved_11 = true;
			value = value - 2048;
		}
		else
			p->Reserved_11 = false;

		if((value - 1024) > -1)
		{
			p->Reserved_10 = true;
			value = value - 1024;
		}
		else
			p->Reserved_10 = false;

		if((value - 512) > -1)
		{
			p->Reserved_9 = true;
			value = value - 512;
		}
		else
			p->Reserved_9 = false;

		if((value - 256) > -1)
		{
			p->Reserved_8 = true;
			value = value - 256;
		}
		else
			p->Reserved_8 = false;

		if((value - 80) > -1)
		{
			p->State_closing = true;
			value = value - 80;
		}
		else
			p->State_closing = false;

		if((value - 64) > -1)
		{
			p->State_close_delay = true;
			value = value - 64;
		}
		else
			p->State_close_delay = false;

		if((value - 48) > -1)
		{
			p-> State_open= true;
			value = value -32;
		}
		else
			p-> State_open = false;
		if((value - 32) > -1)
		{
			p-> State_opening = true;
		}
		else
			p-> State_opening = false;
		if((value - 16) > -1)
		{
			p-> State_open_delay = true;
			value = value - 16;
		}
		else
			p-> State_open_delay = false;

		if(p->State_closing == false && p->State_close_delay == false && p->State_open == false && p->State_opening == false && p-> State_open_delay == false)
		{
			p-> State_closed = true;
		}
		else
			p-> State_closed = false;

		if((value - 8) > -1)
		{
			p-> Reserved_3 = true;
			value = value - 8;
		}
		else
			p-> Reserved_3 = false;

		if((value - 4) > -1)
		{
			p->BrakeCtrlRef = true;
			value = value - 4;
		}
		else
			p->BrakeCtrlRef = false;

		if((value - 2) > -1)
		{
			p->BrakeCtrlSigal = true;
			value = value - 2;
		}
		else
			p->BrakeCtrlSigal = false;

		if((value - 1) > -1)
		{
			p->BrakeCtrlVal = true;
			value = value - 1;
		}
		else
			p->BrakeCtrlVal = false;*/
}
void StateMachine(StateMachineTypedef *p, int value)
{
	p->Initialization = (value == 0);
	p->not_ready_to_switch_on = (value == 1);
	p->switch_on_disable = (value == 2);
	p->ready_to_switch_on = (value == 3);
	p->switched_on = (value == 4);
	p->operation_enabled = (value == 5);
	p->Quick_stop_active = (value == 6);
	p->fault_reaction_active = (value == 7);
	p->fault = (value == 8);
	p->Shutdown_active = (value == 9);
	p->disable_operation_active = (value == 10);
	p->mod_off_pause_active = (value == 11);
	p->start_operation_active = (value == 12);
	p->power_Off = (value == 13);
	p->protection_time_active = (value == 14);
	p->protection_time_end = (value == 15);
	p->endless_protection_time = (value == 16);
	p->suppressed_error = (value == 17);
	/*p->Initialization = false;
	p->not_ready_to_switch_on = false;
	p->switch_on_disable = false;
	p->ready_to_switch_on = false;
	p->switched_on = false;
	p->operation_enabled = false;
	p->Quick_stop_active = false;
	p->fault_reaction_active = false;
	p->fault = false;
	p->Shutdown_active = false;
	p->disable_operation_active = false;
	p->mod_off_pause_active = false;
	p->start_operation_active = false;
	p->power_Off = false;
	p->protection_time_active = false;
	p->protection_time_end = false;
	p->endless_protection_time = false;
	p->suppressed_error = false;

	switch (value) {
		case 0:
			p->Initialization = true;
			break;
		case 1:
			p->not_ready_to_switch_on = true;
			break;
		case 2:
			p->switch_on_disable = true;
			break;
		case 3:
			p->ready_to_switch_on = true;
			break;
		case 4:
			p->switched_on = true;
			break;
		case 5:
			p->operation_enabled = true;
			break;
		case 6:
			p->Quick_stop_active = true;
			break;
		case 7:
			p->fault_reaction_active = true;
			break;
		case 8:
			p->fault = true;
			break;
		case 9:
			p->Shutdown_active = true;
			break;
		case 10:
			p->disable_operation_active = true;
			break;
		case 11:
			p->mod_off_pause_active = true;
			break;
		case 12:
			p->start_operation_active = true;
			break;
		case 13:
			p->power_Off = true;
			break;
		case 14:
			p->protection_time_active = true;
			break;
		case 15:
			p->protection_time_end = true;
			break;
		case 16:
			p->endless_protection_time = true;
			break;
		case 17:
			p->suppressed_error = true;
			break;
	}*/
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

/* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_CRC_Init();
  MX_DMA2D_Init();
  MX_FMC_Init();
  MX_I2C3_Init();
  MX_LTDC_Init();
  MX_QUADSPI_Init();
  MX_RTC_Init();
  MX_SDMMC1_SD_Init();
  MX_SPI2_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM5_Init();
  MX_TIM8_Init();
  MX_TIM12_Init();
  MX_USART1_UART_Init();
  MX_USART6_UART_Init();
  MX_FATFS_Init();
  MX_ADC3_Init();
  MX_CAN1_Init();
  MX_TIM13_Init();
  MX_TIM14_Init();
  MX_TouchGFX_Init();
  /* Call PreOsInit function */
  MX_TouchGFX_PreOSInit();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 2048);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of Serial_Task */
  osThreadDef(Serial_Task, StartTask02, osPriorityNormal, 0, 1024);
  Serial_TaskHandle = osThreadCreate(osThread(Serial_Task), NULL);

  /* definition and creation of ETHTask */
  osThreadDef(ETHTask, StartTask03, osPriorityNormal, 0, 1024);
  ETHTaskHandle = osThreadCreate(osThread(ETHTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 400;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC|RCC_PERIPHCLK_SDMMC1
                              |RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 384;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 5;
  PeriphClkInitStruct.PLLSAI.PLLSAIQ = 2;
  PeriphClkInitStruct.PLLSAI.PLLSAIP = RCC_PLLSAIP_DIV8;
  PeriphClkInitStruct.PLLSAIDivQ = 1;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_8;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLLSAIP;
  PeriphClkInitStruct.Sdmmc1ClockSelection = RCC_SDMMC1CLKSOURCE_CLK48;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC3_Init(void)
{

  /* USER CODE BEGIN ADC3_Init 0 */

  /* USER CODE END ADC3_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC3_Init 1 */

  /* USER CODE END ADC3_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc3.Instance = ADC3;
  hadc3.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc3.Init.Resolution = ADC_RESOLUTION_12B;
  hadc3.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc3.Init.ContinuousConvMode = ENABLE;
  hadc3.Init.DiscontinuousConvMode = DISABLE;
  hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc3.Init.NbrOfConversion = 1;
  hadc3.Init.DMAContinuousRequests = ENABLE;
  hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC3_Init 2 */

  /* USER CODE END ADC3_Init 2 */

}

/**
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 10;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_8TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
  hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
  hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
  hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
  hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

/**
  * @brief DMA2D Initialization Function
  * @param None
  * @retval None
  */
static void MX_DMA2D_Init(void)
{

  /* USER CODE BEGIN DMA2D_Init 0 */

  /* USER CODE END DMA2D_Init 0 */

  /* USER CODE BEGIN DMA2D_Init 1 */

  /* USER CODE END DMA2D_Init 1 */
  hdma2d.Instance = DMA2D;
  hdma2d.Init.Mode = DMA2D_M2M;
  hdma2d.Init.ColorMode = DMA2D_OUTPUT_ARGB8888;
  hdma2d.Init.OutputOffset = 0;
  hdma2d.LayerCfg[1].InputOffset = 0;
  hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_ARGB8888;
  hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d.LayerCfg[1].InputAlpha = 0;
  if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DMA2D_Init 2 */

  /* USER CODE END DMA2D_Init 2 */

}

/**
  * @brief I2C3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C3_Init(void)
{

  /* USER CODE BEGIN I2C3_Init 0 */

  /* USER CODE END I2C3_Init 0 */

  /* USER CODE BEGIN I2C3_Init 1 */

  /* USER CODE END I2C3_Init 1 */
  hi2c3.Instance = I2C3;
  hi2c3.Init.Timing = 0x00C0EAFF;
  hi2c3.Init.OwnAddress1 = 0;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c3, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c3, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C3_Init 2 */

  /* USER CODE END I2C3_Init 2 */

}

/**
  * @brief LTDC Initialization Function
  * @param None
  * @retval None
  */
static void MX_LTDC_Init(void)
{

  /* USER CODE BEGIN LTDC_Init 0 */

  /* USER CODE END LTDC_Init 0 */

  LTDC_LayerCfgTypeDef pLayerCfg = {0};

  /* USER CODE BEGIN LTDC_Init 1 */

  /* USER CODE END LTDC_Init 1 */
  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 40;
  hltdc.Init.VerticalSync = 9;
  hltdc.Init.AccumulatedHBP = 53;
  hltdc.Init.AccumulatedVBP = 11;
  hltdc.Init.AccumulatedActiveW = 533;
  hltdc.Init.AccumulatedActiveH = 283;
  hltdc.Init.TotalWidth = 565;
  hltdc.Init.TotalHeigh = 285;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 480;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = 272;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
  pLayerCfg.Alpha = 255;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg.FBStartAdress = 0xC0000000;
  pLayerCfg.ImageWidth = 480;
  pLayerCfg.ImageHeight = 272;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LTDC_Init 2 */

  /* USER CODE END LTDC_Init 2 */

}

/**
  * @brief QUADSPI Initialization Function
  * @param None
  * @retval None
  */
static void MX_QUADSPI_Init(void)
{

  /* USER CODE BEGIN QUADSPI_Init 0 */

  /* USER CODE END QUADSPI_Init 0 */

  /* USER CODE BEGIN QUADSPI_Init 1 */

  /* USER CODE END QUADSPI_Init 1 */
  /* QUADSPI parameter configuration*/
  hqspi.Instance = QUADSPI;
  hqspi.Init.ClockPrescaler = 1;
  hqspi.Init.FifoThreshold = 4;
  hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE;
  hqspi.Init.FlashSize = 24;
  hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_6_CYCLE;
  hqspi.Init.ClockMode = QSPI_CLOCK_MODE_0;
  hqspi.Init.FlashID = QSPI_FLASH_ID_1;
  hqspi.Init.DualFlash = QSPI_DUALFLASH_DISABLE;
  if (HAL_QSPI_Init(&hqspi) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN QUADSPI_Init 2 */
  BSP_QSPI_Init();

  BSP_QSPI_MemoryMappedMode();
  HAL_NVIC_DisableIRQ(QUADSPI_IRQn);
  /* USER CODE END QUADSPI_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};
  RTC_AlarmTypeDef sAlarm = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 0x1;
  sDate.Year = 0x0;
  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable the Alarm A
  */
  sAlarm.AlarmTime.Hours = 0x0;
  sAlarm.AlarmTime.Minutes = 0x0;
  sAlarm.AlarmTime.Seconds = 0x0;
  sAlarm.AlarmTime.SubSeconds = 0x0;
  sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
  sAlarm.AlarmMask = RTC_ALARMMASK_NONE;
  sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
  sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
  sAlarm.AlarmDateWeekDay = 0x1;
  sAlarm.Alarm = RTC_ALARM_A;
  if (HAL_RTC_SetAlarm(&hrtc, &sAlarm, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable the Alarm B
  */
  sAlarm.Alarm = RTC_ALARM_B;
  if (HAL_RTC_SetAlarm(&hrtc, &sAlarm, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable the TimeStamp
  */
  if (HAL_RTCEx_SetTimeStamp(&hrtc, RTC_TIMESTAMPEDGE_RISING, RTC_TIMESTAMPPIN_POS1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief SDMMC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SDMMC1_SD_Init(void)
{

  /* USER CODE BEGIN SDMMC1_Init 0 */

  /* USER CODE END SDMMC1_Init 0 */

  /* USER CODE BEGIN SDMMC1_Init 1 */

  /* USER CODE END SDMMC1_Init 1 */
  hsd1.Instance = SDMMC1;
  hsd1.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
  hsd1.Init.ClockBypass = SDMMC_CLOCK_BYPASS_DISABLE;
  hsd1.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;
  hsd1.Init.BusWide = SDMMC_BUS_WIDE_4B;
  hsd1.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
  hsd1.Init.ClockDiv = 0;
  /* USER CODE BEGIN SDMMC1_Init 2 */

  /* USER CODE END SDMMC1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
	hspi2.Instance = SPI2;
	hspi2.Init.Mode = SPI_MODE_MASTER;
	hspi2.Init.Direction = SPI_DIRECTION_2LINES;
	hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi2.Init.NSS = SPI_NSS_SOFT;
	hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi2.Init.CRCPolynomial = 7;
	hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
	hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
	if (HAL_SPI_Init(&hspi2) != HAL_OK)
	{
		Error_Handler();
	}
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 4294967295;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief TIM5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM5_Init(void)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 0;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 4294967295;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM5_Init 2 */

  /* USER CODE END TIM5_Init 2 */
  HAL_TIM_MspPostInit(&htim5);

}

/**
  * @brief TIM8 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM8_Init(void)
{

  /* USER CODE BEGIN TIM8_Init 0 */

  /* USER CODE END TIM8_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM8_Init 1 */

  /* USER CODE END TIM8_Init 1 */
  htim8.Instance = TIM8;
  htim8.Init.Prescaler = 0;
  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim8.Init.Period = 65535;
  htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim8.Init.RepetitionCounter = 0;
  htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim8, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM8_Init 2 */

  /* USER CODE END TIM8_Init 2 */

}

/**
  * @brief TIM12 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM12_Init(void)
{

  /* USER CODE BEGIN TIM12_Init 0 */

  /* USER CODE END TIM12_Init 0 */

  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM12_Init 1 */

  /* USER CODE END TIM12_Init 1 */
  htim12.Instance = TIM12;
  htim12.Init.Prescaler = 0;
  htim12.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim12.Init.Period = 65535;
  htim12.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim12.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim12) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM12_Init 2 */

  /* USER CODE END TIM12_Init 2 */
  HAL_TIM_MspPostInit(&htim12);

}

/**
  * @brief TIM13 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM13_Init(void)
{

  /* USER CODE BEGIN TIM13_Init 0 */

  /* USER CODE END TIM13_Init 0 */

  /* USER CODE BEGIN TIM13_Init 1 */

  /* USER CODE END TIM13_Init 1 */
  htim13.Instance = TIM13;
  htim13.Init.Prescaler = 199;
  htim13.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim13.Init.Period = 1000;
  htim13.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim13.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim13) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM13_Init 2 */

  /* USER CODE END TIM13_Init 2 */

}



/**
  * @brief TIM14 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM14_Init(void)
{

  /* USER CODE BEGIN TIM14_Init 0 */

  /* USER CODE END TIM14_Init 0 */

  /* USER CODE BEGIN TIM14_Init 1 */

  /* USER CODE END TIM14_Init 1 */
  htim14.Instance = TIM14;
  htim14.Init.Prescaler = 199;
  htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim14.Init.Period = 1000;
  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM14_Init 2 */

  /* USER CODE END TIM14_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 38400;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_EVEN;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  huart6.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart6.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream3_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);
  /* DMA1_Stream4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream4_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
  /* DMA2_Stream1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);

}

/* FMC initialization function */
static void MX_FMC_Init(void)
{

  /* USER CODE BEGIN FMC_Init 0 */

  /* USER CODE END FMC_Init 0 */

  FMC_SDRAM_TimingTypeDef SdramTiming = {0};

  /* USER CODE BEGIN FMC_Init 1 */

  /* USER CODE END FMC_Init 1 */

  /** Perform the SDRAM1 memory initialization sequence
  */
  hsdram1.Instance = FMC_SDRAM_DEVICE;
  /* hsdram1.Init */
  hsdram1.Init.SDBank = FMC_SDRAM_BANK1;
  hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;
  hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;
  hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
  hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
  hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;
  hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
  hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
  hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;
  hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_0;
  /* SdramTiming */
  SdramTiming.LoadToActiveDelay = 2;
  SdramTiming.ExitSelfRefreshDelay = 7;
  SdramTiming.SelfRefreshTime = 4;
  SdramTiming.RowCycleDelay = 7;
  SdramTiming.WriteRecoveryTime = 3;
  SdramTiming.RPDelay = 2;
  SdramTiming.RCDDelay = 2;

  if (HAL_SDRAM_Init(&hsdram1, &SdramTiming) != HAL_OK)
  {
    Error_Handler( );
  }

  /* USER CODE BEGIN FMC_Init 2 */
  __IO uint32_t tmpmrd = 0;

      /* Step 1: Configure a clock configuration enable command */
      Command.CommandMode            = FMC_SDRAM_CMD_CLK_ENABLE;
      Command.CommandTarget          =  FMC_SDRAM_CMD_TARGET_BANK1;
      Command.AutoRefreshNumber      = 1;
      Command.ModeRegisterDefinition = 0;

      /* Send the command */
      HAL_SDRAM_SendCommand(&hsdram1, &Command, SDRAM_TIMEOUT);

      /* Step 2: Insert 100 us minimum delay */
      /* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
      HAL_Delay(1);

      /* Step 3: Configure a PALL (precharge all) command */
      Command.CommandMode            = FMC_SDRAM_CMD_PALL;
      Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
      Command.AutoRefreshNumber      = 1;
      Command.ModeRegisterDefinition = 0;

      /* Send the command */
      HAL_SDRAM_SendCommand(&hsdram1, &Command, SDRAM_TIMEOUT);

      /* Step 4: Configure an Auto Refresh command */
      Command.CommandMode            = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
      Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
      Command.AutoRefreshNumber      = 8;
      Command.ModeRegisterDefinition = 0;

      /* Send the command */
      HAL_SDRAM_SendCommand(&hsdram1, &Command, SDRAM_TIMEOUT);

      /* Step 5: Program the external memory mode register */
      tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1 | \
               SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL    | \
               SDRAM_MODEREG_CAS_LATENCY_3            | \
               SDRAM_MODEREG_OPERATING_MODE_STANDARD  | \
               SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

      Command.CommandMode            = FMC_SDRAM_CMD_LOAD_MODE;
      Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
      Command.AutoRefreshNumber      = 1;
      Command.ModeRegisterDefinition = tmpmrd;

      /* Send the command */
      HAL_SDRAM_SendCommand(&hsdram1, &Command, SDRAM_TIMEOUT);

      /* Step 6: Set the refresh rate counter */

      /* Set the device refresh rate */
      HAL_SDRAM_ProgramRefreshRate(&hsdram1, REFRESH_COUNT);

      //Deactivate speculative/cache access to first FMC Bank to save FMC bandwidth
      FMC_Bank1->BTCR[0] = 0x000030D2;
  /* USER CODE END FMC_Init 2 */
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOJ_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOK_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OTG_FS_PowerSwitchOn_GPIO_Port, OTG_FS_PowerSwitchOn_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOI, ARDUINO_D7_Pin|ARDUINO_D8_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_BL_CTRL_GPIO_Port, LCD_BL_CTRL_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_DISP_GPIO_Port, LCD_DISP_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(DCMI_PWR_EN_GPIO_Port, DCMI_PWR_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, ARDUINO_D4_Pin|ARDUINO_D2_Pin|EXT_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : OTG_HS_OverCurrent_Pin */
  GPIO_InitStruct.Pin = OTG_HS_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OTG_HS_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ULPI_D7_Pin ULPI_D6_Pin ULPI_D5_Pin ULPI_D3_Pin
                           ULPI_D2_Pin ULPI_D1_Pin ULPI_D4_Pin */
  GPIO_InitStruct.Pin = ULPI_D7_Pin|ULPI_D6_Pin|ULPI_D5_Pin|ULPI_D3_Pin
                          |ULPI_D2_Pin|ULPI_D1_Pin|ULPI_D4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : SPDIF_RX0_Pin */
  GPIO_InitStruct.Pin = SPDIF_RX0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF8_SPDIFRX;
  HAL_GPIO_Init(SPDIF_RX0_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DCMI_D6_Pin DCMI_D7_Pin */
  GPIO_InitStruct.Pin = DCMI_D6_Pin|DCMI_D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_VBUS_Pin */
  GPIO_InitStruct.Pin = OTG_FS_VBUS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OTG_FS_VBUS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Audio_INT_Pin */
  GPIO_InitStruct.Pin = Audio_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Audio_INT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SAI2_MCLKA_Pin SAI2_SCKA_Pin SAI2_FSA_Pin SAI2_SDA_Pin */
  GPIO_InitStruct.Pin = SAI2_MCLKA_Pin|SAI2_SCKA_Pin|SAI2_FSA_Pin|SAI2_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF10_SAI2;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

  /*Configure GPIO pin : SAI2_SDB_Pin */
  GPIO_InitStruct.Pin = SAI2_SDB_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF10_SAI2;
  HAL_GPIO_Init(SAI2_SDB_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = OTG_FS_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(OTG_FS_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : DCMI_D5_Pin */
  GPIO_InitStruct.Pin = DCMI_D5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(DCMI_D5_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ARDUINO_D7_Pin ARDUINO_D8_Pin LCD_DISP_Pin */
  GPIO_InitStruct.Pin = ARDUINO_D7_Pin|ARDUINO_D8_Pin|LCD_DISP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

  /*Configure GPIO pin : uSD_Detect_Pin */
  GPIO_InitStruct.Pin = uSD_Detect_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(uSD_Detect_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_BL_CTRL_Pin */
  GPIO_InitStruct.Pin = LCD_BL_CTRL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_BL_CTRL_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : DCMI_VSYNC_Pin */
  GPIO_InitStruct.Pin = DCMI_VSYNC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(DCMI_VSYNC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_OverCurrent_Pin */
  GPIO_InitStruct.Pin = OTG_FS_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OTG_FS_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : TP3_Pin NC2_Pin */
  GPIO_InitStruct.Pin = TP3_Pin|NC2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /*Configure GPIO pin : DCMI_PWR_EN_Pin */
  GPIO_InitStruct.Pin = DCMI_PWR_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DCMI_PWR_EN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DCMI_D4_Pin DCMI_D3_Pin DCMI_D0_Pin DCMI_D2_Pin
                           DCMI_D1_Pin */
  GPIO_InitStruct.Pin = DCMI_D4_Pin|DCMI_D3_Pin|DCMI_D0_Pin|DCMI_D2_Pin
                          |DCMI_D1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /*Configure GPIO pin : ARDUINO_D10_Pin */
  GPIO_InitStruct.Pin = ARDUINO_D10_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ARDUINO_D10_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_INT_Pin */
  GPIO_InitStruct.Pin = LCD_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(LCD_INT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : ULPI_NXT_Pin */
  GPIO_InitStruct.Pin = ULPI_NXT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
  HAL_GPIO_Init(ULPI_NXT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ARDUINO_D4_Pin ARDUINO_D2_Pin EXT_RST_Pin */
  GPIO_InitStruct.Pin = ARDUINO_D4_Pin|ARDUINO_D2_Pin|EXT_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : ULPI_STP_Pin ULPI_DIR_Pin */
  GPIO_InitStruct.Pin = ULPI_STP_Pin|ULPI_DIR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : RMII_RXER_Pin */
  GPIO_InitStruct.Pin = RMII_RXER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(RMII_RXER_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DCMI_HSYNC_Pin PA6 */
  GPIO_InitStruct.Pin = DCMI_HSYNC_Pin|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : ULPI_CLK_Pin ULPI_D0_Pin */
  GPIO_InitStruct.Pin = ULPI_CLK_Pin|ULPI_D0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */

/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* init code for USB_HOST */
  MX_USB_HOST_Init();

  /* init code for LWIP */
  //MX_LWIP_Init();
  /* USER CODE BEGIN 5 */
  MX_TouchGFX_Process();
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the Serial_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void const * argument)
{
  /* USER CODE BEGIN StartTask02 */
  uint8_t Localchange = 0;
  int Uartreconnect = 0;

  float rated;
  float Poscount;
  float Feedconstant;
  int32_t  Countvalue;

  float Homerated;
  float HomePoscount;
  float HomeFeedconstant;
  int32_t HomeCountvalue;


  float fYoYoDiamerter;
  float fYoYoTempDiamerter;
  int32_t s32YoYoRotateCount;


  //HAL_TIM_Base_Start_IT(&htim14);
  //HAL_CAN_Start(&hcan1);

  can_filter_config();
  /*HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_SET);

  SPITxData[0] = 0x40;
  SPITxData[1] = 0x0A;
  SPITxData[2] = 0x00;*/

  //HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_RESET);
  //__SPI2_CLK_ENABLE();
  //HAL_SPI_TransmitReceive(&hspi2, SPITxData, SPIRxData, 3, 500);
  //HAL_SPI_Transmit(&hspi2, SPITxData, 3, 500);
  //HAL_SPI_TransmitReceive_DMA(&hspi2, SPITxData, SPIRxData, 3);
  //HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_SET);
  //__SPI2_CLK_DISABLE();

  //HAL_DMA_STATE_CHANGE(&hspi2);



  //HAL_DMA_STATE_CHANGE(&hspi2);

  /*Encoder TTL Setting begin*/
  //HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_SET); //TEST 나중에 삭제

  //HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_SET);
  SPIEncoderTxData[0] = 0x88;			//MDR0 WRITE ADDRESS 0x88
  //SPIEncoderTxData[1] = 0x03;
  SPIEncoderTxData[1] = 0x03;
  HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi2, SPIEncoderTxData, 2, 500);
  //HAL_SPI_Transmit_IT(&hspi2, SPIEncoderTxData, 2);
  HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_SET);

  SPIEncoderTxData[0] = 0x90;
  //SPIEncoderTxData[1] = 0x00;
  SPIEncoderTxData[1] = 0x10;
  HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_RESET);
  //testcount2 = true;
  HAL_SPI_Transmit(&hspi2, SPIEncoderTxData, 2, 500);
  //HAL_SPI_Transmit_IT(&hspi2, SPIEncoderTxData, 2);
  HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_SET);

  SPIEncoderTxData[0] = 0x20;
  HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_RESET);
  //testcount2 = true;
  HAL_SPI_Transmit(&hspi2, SPIEncoderTxData, 1, 500);
  //HAL_SPI_Transmit_IT(&hspi2, SPIEncoderTxData, 1);
  HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_SET);

  SPIEncoderTxData[0] = 0x30;
  HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_RESET);
  //testcount2 = true;
  HAL_SPI_Transmit(&hspi2, SPIEncoderTxData, 1, 500);
  //HAL_SPI_Transmit_IT(&hspi2, SPIEncoderTxData, 1);
  HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_SET);
  /*Encoder TTL Setting end*/

  SPIEncoderTxData[0] = 0x98;
  SPIEncoderTxData[1] = 0x00;
  SPIEncoderTxData[2] = 0x98;
  SPIEncoderTxData[3] = 0x96;
  SPIEncoderTxData[4] = 0x7F;
  HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_RESET);
  //testcount2 = true;
  HAL_SPI_Transmit(&hspi2, SPIEncoderTxData, 5, 500);
  //HAL_SPI_Transmit_IT(&hspi2, SPIEncoderTxData, 1);
  HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_SET);

  SPIEncoderTxData[0] = 0xE0;
  HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_RESET);
  //testcount2 = true;
  HAL_SPI_Transmit(&hspi2, SPIEncoderTxData, 1, 500);
  //HAL_SPI_Transmit_IT(&hspi2, SPIEncoderTxData, 1);
  HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_SET);
  /*Encoder TTL Setting end*/

  /*RELAY I/O WATCHDOG TIMER BEGIN*/
  HAL_TIM_Base_Start_IT(&htim13);
  /*RELAY I/O WATCHDOG TIMER END */

  /* Infinite loop */
  for(;;)
  {
	  if (binit == false)
	  {
		  variableinit();
	  }
	  else
	  {

		  /*	flash memory begin	*/
		  if (*(float*)(Address + 0) > 0)g_st_Setting.fGearDenominator	= *(float*)(Address + 0);//g_st_Setting.fGearDenominator	//Setting Gear Demominator
		  else g_st_Setting.fGearDenominator = 1;
		  if (*(float*)(Address + 4) > 0)g_st_Setting.fGearNumerator = *(float*)(Address + 4);//g_st_Setting.fGearNumerator		//Setting Gear Numerator
		  else g_st_Setting.fGearNumerator = 1;
		  if (*(float*)(Address + 8) > 0)g_st_Setting.fDiameter = *(float*)(Address + 8);//g_st_Setting.fDiameter	//Setting idiamter
		  else g_st_Setting.fDiameter = 1;

		  g_s32MaxPosValue					= *(int*)(Address + 12);//g_st_Setting.g_s32MaxPosValue		//Setting Max Position
		  g_s32MinPosValue					= *(int*)(Address + 16);//g_st_Setting.g_s32MinPosValue		//Setting Min Position
		  g_st_inverter.minmaxRpmvalue		= *(int*)(Address + 20);//g_st_Setting.g_s32MinMaxRpmValue		//Setting Motor Rpm
		  g_s32DriveSettingType				= *(int*)(Address + 24);//g_st_Setting.g_s32DriveSettingType		//Select the mode to use : Direct, Direct Incremental, Inverter + Encoder;
		  g_fWire							= *(float*)(Address + 28);//g_st_Setting.g_fWire		//Setting Wire width
		  g_s32YoYo							= *(int*)(Address + 32);//g_st_Setting.g_s32YoYo		//Select the mode to use : YoYo, Nothing

		  if(*(uint16_t*)(Address + 36) > 0)g_st_Direct.u16EncoderPulse = *(uint16_t*)(Address + 36);
		  else g_st_Direct.u16EncoderPulse = 1;

		  if(g_bFlashWrite == true)										//Flash Save
		  {
			  save_flash();
			  g_bFlashWrite = false;
		  }
		  /* flash memory end */


		  // Select Local Mode code begin
		  if(g_bLocal == false)
		  {
			  HAL_CAN_Stop(&hcan1);			// CAN 통신 STOP
			  HAL_TIM_Base_Stop_IT(&htim14); // CAN 통신 TIMER STOP
		  }
		  else if(g_bLocal == true)
		  {
			  HAL_CAN_Start(&hcan1);		// CAN 통신 START
			  HAL_TIM_Base_Start_IT(&htim14); // CAN 통신 TIMER START
		  }
		  //HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_SET); //TEST 나중에 삭제
		  // Select Local Mode code end
		  /*SPITx1stInput[0] = 0x40;
		  SPITx1stInput[1] = 0x00;
		  SPITx1stInput[2] = 0xFF;

		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_RESET);
		  //HAL_SPI_TransmitR(&hspi2, SPITx1stInput, 3, 500);
		  HAL_SPI_TransmitReceive(&hspi2, SPITx1stInput, SPIRx1stInput, 3, 500);
		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_SET);

		  //Limit Code begin
		  SPITx2ndInput[0] = 0x40;
		  SPITx2ndInput[1] = 0x01;
		  SPITx2ndInput[2] = 0xFF;

		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_RESET);
		  //HAL_SPI_Transmit(&hspi2, SPITx2ndInput, 3, 500);
		  HAL_SPI_TransmitReceive(&hspi2, SPITx2ndInput, SPIRx2ndInput, 3, 500);
		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_SET);

		  SPITx1stInput[0] = 0x41;
		  SPITx1stInput[1] = 0x12;
		  //SPITx1stInput[2] = 0x00;

		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_RESET);
		  HAL_SPI_TransmitReceive(&hspi2, SPITx1stInput, SPIRx1stInput, 3, 500);
		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_SET);
		  //Limit Code End


		  //EMG Code begin
		  if(SPIRx1stInput[2] & 0x01)
			  g_bEMG = true;
		  else
			  g_bEMG = false;
		  //EMG Code end

		  //Local Code begin
		  //if(SPIRxData[2] & 0x02)
		//	  g_bLocal = true;
		 // else
		//	  g_bLocal = false;
		  // Local Code end

		  //Limit Code begin
		  if (SPIRx1stInput[2] & 0x04)
			  g_st_Setting.bFinalPosLimit = true;
		  else
			  g_st_Setting.bFinalPosLimit = false;
		  if (SPIRx1stInput[2] & 0x08)
			  g_st_Setting.bPosLimit = true;
		  else
			  g_st_Setting.bPosLimit = false;
		  if (SPIRx1stInput[2] & 0x10)
			  g_st_Setting.bNegLimit = true;
		  else
			  g_st_Setting.bNegLimit = false;
		  if(SPIRx1stInput[2] & 0x20)
			  g_st_Setting.bFinalNegLimit = true;
		  else
			  g_st_Setting.bFinalNegLimit = false;
		  //Limit Code end

		  SPITx2ndInput[0] = 0x41;
		  SPITx2ndInput[1] = 0x13;
		  SPITx2ndInput[2] = 0x00;

		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_RESET);
		  HAL_SPI_TransmitReceive(&hspi2, SPITx2ndInput, SPIRx2ndInput, 3, 500);
		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_SET);*/

		  /*SPITxData[0] = 0x42;
		  SPITxData[1] = 0x00;
		  SPITxData[2] = 0x00;

		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_RESET);
		  HAL_SPI_Transmit_DMA(&hspi2, SPITxData, 3);
		  //HAL_SPI_Transmit(&hspi2, SPITxData, 3, 500);
		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_SET);

		  SPITxData[0] = 0x42;
		  SPITxData[1] = 0x01;
		  SPITxData[2] = 0x00;

		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_RESET);
		  HAL_SPI_Transmit_DMA(&hspi2, SPITxData, 3);
		  //HAL_SPI_Transmit(&hspi2, SPITxData, 3, 500);
		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_SET);
		  //__SPI2_CLK_DISABLE();

		  SPITxData[0] = 0x42;
		  SPITxData[1] = 0x12;
		  //SPITxData[2] = 0xFF;
		  itest = itest + 1;
		  if(itest <= 500)
		  {
			  SPITxData[2] = 0x00;
		  }
		  else if(itest >= 500 && itest <= 1000)
		  {
			  SPITxData[2] = 0xFF;
		  }
		  else if(itest > 1000)
		  {
			  itest = 0;
		  }

		  //if(g_st_Direct.bUp)
			//  SPITxData[2] |= 0x10;
		  //else
			//  SPITxData[2] &= ~0x10;
		  //if(g_st_Direct.bDown)
			//  SPITxData[2] |= 0x20;
		  //else
			//  SPITxData[2] &= ~0x20;
		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_RESET);
		  HAL_SPI_Transmit_DMA(&hspi2, SPITxData, 3);
		  //HAL_SPI_Transmit(&hspi2, SPITxData, 3, 500);
		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_SET);

		  SPITxData[0] = 0x42;
		  SPITxData[1] = 0x13;
		  //SPITxData[2] = 0x03;

		  if(itest <= 500)
		  {
			  SPITxData[2] = 0x00;
		  }
		  else if(itest >= 500 && itest <= 1000)
		  {
			  SPITxData[2] = 0x03;
		  }
		  else if(itest > 1000)
		  {
			  itest = 0;
		  }

		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_RESET);
		  HAL_SPI_Transmit(&hspi2, SPITxData, 3, 500);
		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_SET);

		  SPITxData[0] = 0x43;
		  SPITxData[1] = 0x12;
		  SPITxData[2] = 0x00;

		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_RESET);
		  HAL_SPI_TransmitReceive_DMA(&hspi2, SPITxData, SPIRxData, 3);
		  //HAL_SPI_TransmitReceive(&hspi2, SPITxData, SPIRxData, 3, 500);
		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_SET);




		  SPITxData[0] = 0x43;
		  SPITxData[1] = 0x13;
		  SPITxData[2] = 0x00;

		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_RESET);
		  HAL_SPI_TransmitReceive_DMA(&hspi2, SPITxData, SPIRxData, 3);
		  //HAL_SPI_TransmitReceive(&hspi2, SPITxData, SPIRxData, 3, 500);
		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_SET);
*/
		  /*SPITxData[0] = 0x42;
		  SPITxData[1] = 0x00;
		  SPITxData[2] = 0x00;
		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_RESET);
		  HAL_SPI_Transmit(&hspi2, SPITxData, 3, 500);
		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_SET);

		  SPITxData[0] = 0x42;
		  SPITxData[1] = 0x01;
		  SPITxData[2] = 0x00;
		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_RESET);
		  HAL_SPI_Transmit(&hspi2, SPITxData, 3, 500);
		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_SET);

		  SPITxData[0] = 0x42;
		  SPITxData[1] = 0x12;
		  SPITxData[2] = 0xFF;
		  if(g_st_Direct.bUp)
			  SPITxData[2] |= 0x10;
		  else
			  SPITxData[2] &= ~0x10;

		  if(g_st_Direct.bDown)
			  SPITxData[2] |= 0x20;
		  else
			  SPITxData[2] &= ~0x20;
		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_RESET);
		  HAL_SPI_Transmit(&hspi2, SPITxData, 3, 500);
		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_SET);

		  SPITxData[0] = 0x42;
		  SPITxData[1] = 0x13;
		  SPITxData[2] = 0x03;
		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_RESET);
		  HAL_SPI_Transmit(&hspi2, SPITxData, 3, 500);
		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_SET);

		  SPITxData[0] = 0x43;
		  SPITxData[1] = 0x12;
		  SPITxData[2] = 0x00;
		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_RESET);
		  HAL_SPI_TransmitReceive(&hspi2, SPITxData, SPIRxData, 3, 500);
		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_SET);*/


		  /*Encoder TTL Count Begin */
		  SPIEncoderTxData[0] = 0x60;
		  SPIEncoderTxData[1] = 0x00;
		  HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_RESET);
		  //testcount2 = true;
		  //HAL_SPI_TransmitReceive_IT(&hspi2, SPIEncoderTxData, SPIEncoderRxData, 5);
		  HAL_SPI_TransmitReceive(&hspi2, SPIEncoderTxData, SPIEncoderRxData, 5, 500);
		  HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_SET);
		  /*Encoder TTL Count End */

		  //TTL Encoder Count Data Change uint8_t [1]~[4] -> int32_t
		  SPIEncoderData = 0;
		  SPIEncoderData |= ((uint32_t)SPIEncoderRxData[1] << 24);
		  SPIEncoderData |= ((uint32_t)SPIEncoderRxData[2] << 16);
		  SPIEncoderData |= ((uint32_t)SPIEncoderRxData[3] << 8);
		  SPIEncoderData |= ((uint32_t)SPIEncoderRxData[4] << 0);

		  g_st_Direct.s32EncodercountValue = SPIEncoderData;	//TTL Encoder Count value

		  /*if (ResetTest == true) HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_SET);
		  else HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_RESET);

		  if (HAL_GPIO_ReadPin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin) == GPIO_PIN_SET )
		  {

			  GPIOTest = true;
		  }
		  else
		  {
			  GPIOTest = false;
		  }*/

		  //Home Setting
		  if(g_s32DriveSettingType == Direct_encoder) // Direct Encoder count
		  {
			  g_st_Direct.fHomerated = (g_st_Setting.fGearDenominator / g_st_Setting.fGearDenominator);
			  g_st_Direct.fHomePoscount = (g_st_Direct.s32DirectHomeOffset * g_st_Direct.u16EncoderPulse);
			  g_st_Direct.fHomeFeedconstant = 1/(g_st_Setting.fDiameter);
			  g_st_Direct.s32HomeCountvalue = g_st_Direct.fHomerated * g_st_Direct.fHomePoscount * g_st_Direct.fHomeFeedconstant;
		  }
		  else if(g_s32DriveSettingType == inverter_encoder) // Inverter Encoder count
		  {
			  rated = (g_st_Setting.fGearDenominator / g_st_Setting.fGearNumerator);
			  Poscount = (g_st_inverter.PosSetPosvalue * g_st_inverter.increments);
			  Feedconstant = 1/(g_st_Setting.fDiameter);
			  Countvalue = rated * Poscount * Feedconstant;

			  Homerated = (g_st_Setting.fGearDenominator / g_st_Setting.fGearNumerator);
			  HomePoscount = (g_st_inverter.HomeSetPosvalue * g_st_inverter.increments);
			  HomeFeedconstant = 1/(g_st_Setting.fDiameter);
			  HomeCountvalue = Homerated * HomePoscount * HomeFeedconstant;
		  }

		  if(g_bDirect_HomeTrig == true)
		  {
			  SPIEncoderTxData[0] = 0x98;
			  SPIEncoderTxData[1] = ((uint8_t)(g_st_Direct.s32HomeCountvalue >> 24));
			  SPIEncoderTxData[2] = ((uint8_t)(g_st_Direct.s32HomeCountvalue >> 16));
			  SPIEncoderTxData[3] = ((uint8_t)(g_st_Direct.s32HomeCountvalue >> 8));
			  SPIEncoderTxData[4] = ((uint8_t)(g_st_Direct.s32HomeCountvalue >> 0));
			  HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_RESET);
			  HAL_SPI_Transmit(&hspi2, SPIEncoderTxData, 5, 500);
			  HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_SET);

			  SPIEncoderTxData[0] = 0xE0;
			  HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_RESET);
			  HAL_SPI_Transmit(&hspi2, SPIEncoderTxData, 1, 500);
			  HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_SET);

			  g_bDirect_HomeTrig = false;
		  }



		  /*if (bool(g_s32YoYo) == true)
		  {
			s32YoYoRotateCount = floor(g_st_Direct.s32EncodercountValue * rated / g_st_Direct.u16EncoderPulse);
		  }

		  rated = (g_st_Setting.fGearDenominator / g_st_Setting.fGearNumerator);		//Gear rate
		  Poscount = (g_st_inverter.PosSetPosvalue * g_st_inverter.increments);			//Position Count Calculation
		  Feedconstant = 1/(g_st_Setting.fDiameter);									//FeedConstat Calculation
		  Countvalue = rated * Poscount * Feedconstant;									//Encoder Count Calculation
*/
		  //RPDO4 Target Pos
		  KEB_CAN.KEB_CAN_Func_32dectohex(Countvalue, g_u8BufTargetPos, 4);//KEB_CAN_Func_32dectohex(Countvalue, TempTargetPos, 4);

		  //RPDO4 Target Vel
		  KEB_CAN.KEB_CAN_Func_32dectohex(g_st_inverter.PosSetRpmvalue, g_u8BufTargetVel, 4);//KEB_CAN_Func_32dectohex(GVLinverter[GVLAddnumber].PossetRpmvalue , TempTargetVel, 4);

		  //PRDO4 Target Home Pos
		  //convert Homecountvalue 32dec -> hex
		  KEB_CAN.KEB_CAN_Func_32dectohex(HomeCountvalue, g_u8BufHomeoffset, 4);//KEB_CAN_Func_32dectohex(HomeCountvalue, TempHomeoffset, 4); //

		  TPDO3Statusword_dec = KEB_CAN.KEB_CAN_Func_hexto16uint(TPDO3statusword, 2);//TPDO3Statusword_dec = KEB_CAN_Func_hexto16uint(TPDO3statusword, 2);

		  //Read Status
		  Statusword(&g_st_Statusword, TPDO3Statusword_dec);

		  KEB_CAN.KEB_CAN_errorcode(TPDO3Errorcode, g_st_inverter.cError);//KEB_CAN_errorcode(TPDO3Errorcode, GVLinverter[GVLAddnumber].cError);

		  //TPDO Stateword(READ)
		  KEB_CAN.KEB_CAN_Stateword(TPDO3Statusword_dec, g_st_inverter.cState);

		  //TPDO ModeBuffer(READ)
		  g_st_inverter.s8Mode = TPDO3Modes;
		  KEB_CAN.KEB_CAN_ModeState(TPDO3Modes, g_st_inverter.cMode);//KEB_CAN_Modes(TPDO3Modes, GVLinverter[GVLAddnumber].cMode);

		  //RPDO ModeBuffer(WRITE)
		  KEB_CAN.KEB_CAN_ModeChange(g_bModeWrite, g_s8Mode, g_s8ModeSelect, g_st_inverter.s8Mode);


		  if(g_st_Statusword.voltage_enabled == true)
			  strcpy(g_st_inverter.cReadystate,"RUN");
		  else
			  strcpy(g_st_inverter.cReadystate,"FAULT");


		  g_st_inverter.actRpmvalue = KEB_CAN.KEB_CAN_Func_hexto32dec(TPDO4VelocityAct, 4) / 8; // co02 : Velocity shift factor = default value 10(3bit) = 1/8 rpm

		  g_st_inverter.PosActPoscount = KEB_CAN.KEB_CAN_Func_hexto32dec(TPDO4PositionAct, 4);
		  if(g_st_Direct.s16UpPosSetValue <= g_st_Direct.s32DirectActPos || g_s32MaxPosValue <= g_st_Direct.s32DirectActPos)
			  g_st_Direct.bUp = false;
		  else if(g_st_Direct.s16DownPosSetValue >= g_st_Direct.s32DirectActPos || g_s32MinPosValue >= g_st_Direct.s32DirectActPos)
			  g_st_Direct.bDown = false;
		  /*if(g_st_Direct.bUp == true && (g_st_Setting.bPosLimit == false || g_st_Setting.bFinalPosLimit == false) )
			  g_st_Direct.bUp = false;
		  else if(g_st_Direct.bDown == true && (g_st_Setting.bNegLimit == false || g_st_Setting.bFinalNegLimit == false))
			  g_st_Direct.bDown = false;*/

		  ////////////////////Bypass STO relay//////////////////////////////////////
		  /*if(g_bBypassSTO)
		  {
			  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_SET);
		  }
		  else
		  {
			  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_RESET);
		  }*/

		  ///////////////////MC INPUT, OUTPUT Relay/////////////////////////////////
		  if (g_bMCinput == true && g_bMCoutput == true)
		  {
			  //HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_SET);
			  //HAL_GPIO_WritePin(ARDUINO_D7_GPIO_Port, ARDUINO_D7_Pin, GPIO_PIN_SET);
			  g_bMCinputstate = true;
			  g_bMCoutputstate = true;
		  }
		  else
		  {
			 //HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_RESET);
			 //HAL_GPIO_WritePin(ARDUINO_D7_GPIO_Port, ARDUINO_D7_Pin, GPIO_PIN_RESET);
			  g_bMCinputstate = false;
			  g_bMCoutputstate = false;
		  }
		  //////////////////////////////////////////////////////////////////////////

		  /////////////////////Double Brake relay///////////////////////////////////
		  if(g_st_StateMachine.switched_on && g_bPoweron && GVLComstate == 0)
		  {
			  ;//HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_SET);
		  }
		  else if((g_st_BrakeStatus.State_closed && (g_st_StateMachine.operation_enabled == false)) || GVLComstate == 8)
		  {
			  ;//HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_RESET);
		  }
		  ///////////////////////////////////////////////////////////////////////////

		  ///////////////////Read Local switch input/////////////////////////////////
		  /*temp test*/
		  //g_bLocal;
		  /*if(HAL_GPIO_ReadPin(ARDUINO_D10_GPIO_Port, ARDUINO_D10_Pin))
		  {
			  GVLLocal = true;
			  Localchange = 0;
		  }
		  else
		  {
			  GVLLocal = false;
			  switch(Localchange)
			  {
			  case 0:
				  GVLComon = true;
				  GVLWriteon = true;
				  Localchange = 1;
				  break;
			  case 1:
				  if(GVLWriteon == false && GVLComstate == 0)
					  Localchange = 0;
				  break;
			  }
		  }*/
		  ///////////////////////////////////////////////////////////////////////////

		  // Analog RPM setting
		  /*if(GVLLocal)
		  {
			  HAL_ADC_Start_DMA(&hadc3, &uiADCresult[0], 5);
			  if(GVLiMode == Velocity)
			  {
				  if(GVLVel_RPM_direction == false)
				  {
					  iTempAnalog = (float)uiADCresult[0] / 4090 * 100;
					  GVLinverter[GVLAddnumber].VelsetRpmvalue =  GVLinverter[GVLAddnumber].minmaxRpmvalue * iTempAnalog / 100;
				  }
				  else
				  {
					  iTempAnalog = (float)uiADCresult[0] / 4090 * 100;
					  GVLinverter[GVLAddnumber].VelsetRpmvalue = -GVLinverter[GVLAddnumber].minmaxRpmvalue * iTempAnalog / 100;
				  }
			  }
			  else if(GVLiMode == Position)
			  {
				  if(uiADCresult[0] >= 0 && uiADCresult[0] <= 4096)
				  {
					  iTempAnalog = (float)uiADCresult[0] / 4090 * 100;
					  GVLinverter[GVLAddnumber].PossetRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue * iTempAnalog / 100;
				  }
			  }
		  }
		  else
		  {
			  HAL_ADC_Stop_DMA(&hadc3);
		  }*/


		  //TCP to use buffer
		  /*KEB_StateBuf(RxBuf, DATA_BUF_SIZE, GVLTCP_inv_Statebuf);
		  KEB_ErrorBuf(RxBuf, DATA_BUF_SIZE, GVLTCP_inv_Errorbuf);
		  KEB_ModeBuf(RxBuf, DATA_BUF_SIZE, GVLTCP_inv_Modebuf);
		  KEB_SupplyBuf(RxBuf, DATA_BUF_SIZE, GVLTCP_inv_supplybuf);
		  KEB_STOBuf(RxBuf, DATA_BUF_SIZE, GVLTCP_inv_STObuf);*/

		  //Axis Actual Position
		  if(g_s32DriveSettingType == Direct_encoder)//Direct Encoder Actual Position
		  {
			  g_st_Direct.fActrotate = g_st_Direct.s32EncodercountValue / g_st_Direct.u16EncoderPulse;

			  g_st_Direct.s32DirectActPos = ((g_st_Direct.fActrotate * (g_st_Setting.fGearNumerator / g_st_Setting.fGearDenominator))
					  * g_st_Setting.fDiameter);// + g_st_Direct.s32DirectHomeOffset;
		  }
		  else if(g_s32DriveSettingType == inverter_encoder)//Inverter Encoder Actual Position
		  {
			  g_st_inverter.iActrotate = g_st_inverter.PosActPoscount / g_st_inverter.increments;

			  g_st_inverter.PosActPosvalue = (g_st_inverter.iActrotate * (g_st_Setting.fGearNumerator / g_st_Setting.fGearDenominator))
					  * g_st_Setting.fDiameter; //* 3.14;
		  }


		  /*if(GVLinverter[GVLAddnumber].iMode == Position)
		  {
			  GVLinverter[GVLAddnumber].PosTargetPoscount = KEB_TgtPositiondisplay(RxBuf, DATA_BUF_SIZE);
			  GVLinverter[GVLAddnumber].iTgtrotate = GVLinverter[GVLAddnumber].PosTargetPoscount / GVLinverter[GVLAddnumber].increments;
			  GVLinverter[GVLAddnumber].PosTargetPosvalue = (GVLinverter[GVLAddnumber].iTgtrotate * (GVLinverter[GVLAddnumber].iGearNumerator / GVLinverter[GVLAddnumber].iGearDenominator))
							  * GVLinverter[GVLAddnumber].idiameter;// * 3.14;
		  }
		  else if(GVLinverter[GVLAddnumber].iMode == Home)
		  {
			  GVLinverter[GVLAddnumber].HomeTargetPoscount = KEB_TgtHomePositiondisplay(RxBuf, DATA_BUF_SIZE);
			  GVLinverter[GVLAddnumber].iTgtrotate = GVLinverter[GVLAddnumber].HomeTargetPoscount / GVLinverter[GVLAddnumber].increments;
			  GVLinverter[GVLAddnumber].HomeTargetPosvalue = (GVLinverter[GVLAddnumber].iTgtrotate * (GVLinverter[GVLAddnumber].iGearNumerator / GVLinverter[GVLAddnumber].iGearDenominator))
							  * GVLinverter[GVLAddnumber].idiameter;// * 3.14;
		  }*/

	  }
	  osDelay(1);
  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the ETHTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void const * argument)
{
  /* USER CODE BEGIN StartTask03 */
  MX_LWIP_Init();
  /*if THe TCP Server is used
  MX_IP_check(&GVL_IP);
  tcp_echoserver_init();*/
  /* Infinite loop */
  for(;;)
  {
	//if(GVLTCP_connection == 0)
	//{
	  tcp_echoclient_connect();
	  tcp_loop_send();
	//}
	//sys_check_timeouts();
	//tcp_serial_inf(RxBuf, DATA_BUF_SIZE);
	//tcp_timeout_check();
    osDelay(1);
  }
  /* USER CODE END StartTask03 */
}

/* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x90000000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_256MB;
  MPU_InitStruct.SubRegionDisable = 0x0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Number = MPU_REGION_NUMBER1;
  MPU_InitStruct.Size = MPU_REGION_SIZE_16MB;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Number = MPU_REGION_NUMBER2;
  MPU_InitStruct.Size = MPU_REGION_SIZE_1MB;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	/* USER CODE BEGIN Callback 0 */
	if (htim->Instance == TIM14){//if(htim == &htim14){
		getuiTime = HAL_GetTick();
		currentuiTime = getuiTime - beforeuiTime;
		if(currentuiTime >= 200)	//200ms
		{
			HAL_GPIO_TogglePin(ARDUINO_D10_GPIO_Port, ARDUINO_D10_Pin);
			beforeuiTime = getuiTime;
			if(Heartbeatconsumer == 0x05)	//KEB Parameter CANopen fieldbus state[2] = 5(CAN301_STATE_OPERATIONAL)
			{
				CAN1NMTData[0] = 0x01;
				CAN1NMTData[1] = (uint8_t)CAN_ID;
				CAN1NMTData[2] = 0x00;
				CAN1NMTData[3] = 0x00;
				CAN1NMTData[4] = 0x00;
				CAN1NMTData[5] = 0x00;
				CAN1NMTData[6] = 0x00;
				CAN1NMTData[7] = 0x00;
				if (HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) > 0){
					CANTxHeader.StdId = NMTconsumer;
					CANTxHeader.RTR = 0;
					CANTxHeader.IDE = CAN_ID_STD;
					CANTxHeader.DLC = 2;
					ret = HAL_CAN_AddTxMessage(&hcan1, &CANTxHeader, CAN1NMTData, &TxMailBox);
					if (ret != HAL_OK){
						Error_Handler();// Error 처리 코드
					}
				}
				if (HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) > 0){
					CANTxHeader.StdId = NMT;
					CANTxHeader.RTR = 0;
					CANTxHeader.IDE = CAN_ID_STD;
					CANTxHeader.DLC = 2;
					ret = HAL_CAN_AddTxMessage(&hcan1, &CANTxHeader, CAN1NMTData, &TxMailBox);
					if (ret != HAL_OK){
						Error_Handler();// Error 처리 코드
					}
				}
			}
			if(Heartbeatconsumer == 0x7F)	//KEB Parameter CANopen fieldbus state[2] = 127(CAN301_STATE_PREOPERATIONAL
			{
				if (HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) > 0){
					CAN1NMTData[0] = 0x81;
					CAN1NMTData[1] = (uint8_t)CAN_ID;
					CAN1NMTData[2] = 0x00;
					CAN1NMTData[3] = 0x00;
					CAN1NMTData[4] = 0x00;
					CAN1NMTData[5] = 0x00;
					CAN1NMTData[6] = 0x00;
					CAN1NMTData[7] = 0x00;
					CANTxHeader.StdId = NMT;
					CANTxHeader.RTR = 0;
					CANTxHeader.IDE = CAN_ID_STD;
					CANTxHeader.DLC = 2;
					ret = HAL_CAN_AddTxMessage(&hcan1, &CANTxHeader, CAN1NMTData, &TxMailBox);
					if (ret != HAL_OK){
						Error_Handler();// Error 처리 코드
					}
				}
			}

		}

		GVL_iControlword = g_st_controlword.switch_on + g_st_controlword.enable_voltage
				+ g_st_controlword.no_quick_stop + g_st_controlword.enable_operation
				+ g_st_controlword.op_mode_spec_four + g_st_controlword.op_mode_spec_five
				+ g_st_controlword.op_mode_spec_six + g_st_controlword.fault_reset
				+ g_st_controlword.halt + g_st_controlword.op_mode_spec_nine
				+ g_st_controlword.reserved + g_st_controlword.manufacturer_spec_11
				+ g_st_controlword.manufacturer_spec_12 + g_st_controlword.manufacturer_spec_13
				+ g_st_controlword.manufacturer_spec_14 + g_st_controlword.brake_ctrl_15;

		KEB_CAN.KEB_CAN_Func_Controlword_dectohex(GVL_iControlword, (uint8_t*)&GVL_cControlword);//KEB_CAN_Func_Controlword_dectohex(GVL_iControlword, (uint8_t*)&GVL_cControlword);

		CAN1RPDO3Data[0] = GVL_cControlword[1];
		CAN1RPDO3Data[1] = GVL_cControlword[0];
		CAN1RPDO3Data[2] = g_s8ModeSelect;
		CAN1RPDO3Data[3] = g_u8BufHomeoffset[3];
		CAN1RPDO3Data[4] = g_u8BufHomeoffset[2];
		CAN1RPDO3Data[5] = g_u8BufHomeoffset[1];
		CAN1RPDO3Data[6] = g_u8BufHomeoffset[0];
		CAN1RPDO3Data[7] = 0x00;

		CAN1RPDO4Data[0] = g_u8BufTargetPos[3];
		CAN1RPDO4Data[1] = g_u8BufTargetPos[2];
		CAN1RPDO4Data[2] = g_u8BufTargetPos[1];
		CAN1RPDO4Data[3] = g_u8BufTargetPos[0];
		CAN1RPDO4Data[4] = g_u8BufTargetVel[3];
		CAN1RPDO4Data[5] = g_u8BufTargetVel[2];
		CAN1RPDO4Data[6] = g_u8BufTargetVel[1];
		CAN1RPDO4Data[7] = g_u8BufTargetVel[0];

		PDOgetuiTime = HAL_GetTick();
		PDOcurrentuitime = PDOgetuiTime - PDObeforeuiTime;
		if(PDOcurrentuitime >= 10){
			PDObeforeuiTime = PDOgetuiTime;
			if (HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) > 0){
				CANTxHeader.StdId = RXPDO3 + CAN_ID;//Canopen function
				CANTxHeader.RTR = 0;				//
				CANTxHeader.IDE = CAN_ID_STD;		//
				CANTxHeader.DLC = 7;				//Data length
				ret = HAL_CAN_AddTxMessage(&hcan1, &CANTxHeader, CAN1RPDO3Data, &TxMailBox);	//Can Write
				if (ret != HAL_OK){
					Error_Handler();// ?���? 처리 코드
				}
				else
				{
					if(g_st_controlword.op_mode_spec_four == 16)
						g_st_controlword.op_mode_spec_four = 0;
					if(g_st_controlword.op_mode_spec_five == 32)
						g_st_controlword.op_mode_spec_five = 0;
					if(g_st_controlword.fault_reset == 128)
						g_st_controlword.fault_reset = 0;
					if(g_st_controlword.halt == 256)
						g_st_controlword.halt = 0;
				}
			}
		}
		PDOcurrentuitime2 = PDOgetuiTime - PDObeforeuiTime2;
		if(PDOcurrentuitime2 >= 10){
			PDObeforeuiTime2 = PDOgetuiTime;
			if(HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) > 0){
				CANTxHeader.StdId = RxPDO4 + CAN_ID;
				CANTxHeader.RTR = 0;
				CANTxHeader.IDE = CAN_ID_STD;
				CANTxHeader.DLC = 8;
				ret = HAL_CAN_AddTxMessage(&hcan1, &CANTxHeader, CAN1RPDO4Data, &TxMailBox);
				if (ret != HAL_OK){
					Error_Handler();// ?���? 처리 코드
				}
			}
		}
	}
	//INPUT, OUTPUT IC WATCHDOG TIMER
	if (htim->Instance == TIM13){
;//		HAL_GPIO_TogglePin(ARDUINO_D10_GPIO_Port, ARDUINO_D10_Pin); //TIMER 시간 설정 필요
	}

	/* USER CODE END Callback 0 */
	if (htim->Instance == TIM6) {
		HAL_IncTick();
	}
	/* USER CODE BEGIN Callback 1 */

	/* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

