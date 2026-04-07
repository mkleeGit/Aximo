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
//#include "bootloader.h"
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
#include "Logic.hpp"
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
#define FLASH_USER_END_ADDR		ADDR_FLASH_SECTOR_7 + GetSectorSize(ADDR_FLASH_SECTOR_7)

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

uint16_t MCP23017_Input_GPIOA_Read = 0;
uint16_t MCP23017_Input_GPIOB_Read = 0;

uint8_t SPITx1stInput[3] = {0x00, };
uint8_t SPITx2ndInput[3] = {0x00, };

uint8_t SPIRx1stInput[3] = {0x00, };
uint8_t SPIRx2ndInput[3] = {0x00, };

uint8_t SPIRx1stOutput[3] = {0x00, };
uint8_t SPIRx2ndOutput[3] = {0x00, };

uint8_t SPI_WC_Data_Test[6] = {0x00, };
uint8_t SPI_RC_Data_Test[6] = {0x00, };

uint8_t SPI_RD_Test[1];


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

//CAN TPDO4 BUFFER

//CAN Heartbeat
uint8_t Heartbeatconsumer;
//CAN Convert hexto16uint
uint16_t TPDO3Statusword_dec;
uint16_t TPDO3Errorcode_dec;
uint16_t TPDO3DigitalInput_dec;

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
uint8_t u8ttl_init_Step;


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

uint32_t uiADCresult[5] = {0,};

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

uint8_t FRAMTxCMD[4] = {0};
uint8_t FRAMRxCMD[3] = {0};

uint8_t FRAMRXData[4] = {0};
uint8_t testrxarry[3] = {0};

uint32_t FRAMEncoderData = 0;

Logic logic;

uint8_t testttttt;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
//static void MPU_Initialize(void);
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
//void HAL_receive(UART_HandleTypeDef *huart);
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
//void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart);
void disconnectstate();

//void StateControlword(StatecontrolwordTypedef *p, int value);
//void StateMachine(StateMachineTypedef *p, int value);
void BrakeStatus(BrakeStatusTypedef *p, int value);

void Statusword(StatuswordTypedef *p, uint16_t value);
void InvDigitalInput(InvDigitalInputTypedef *p, uint16_t value);

void save_flash();

static void App_LoadSettingsFromFlash(void);
static void IO_ReadInputs_MCP23S17(void);
static void IO_WriteOutputs_MCP23S17(void);

static void Encoder_ReadTTL(void);
static void Canopen_Comm_StartStop(void);

static void FRAM_Write(void);
void FRAM_Read(void);
void DirectHome(uint32_t value, GPIO_TypeDef* Port, uint16_t Pin);

static void DirectUpDown(void);

//Flash memory Test function
static uint32_t GetSector(uint32_t Address);
static uint32_t GetSectorSize(uint32_t Sector);

//can communicaiton
void can_filter_config(void);
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


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

uint32_t GetSectorSize(uint32_t Sector)
{
  uint32_t sectorsize = 0x00;

  if((Sector == FLASH_SECTOR_0) || (Sector == FLASH_SECTOR_1) || (Sector == FLASH_SECTOR_2) || (Sector == FLASH_SECTOR_3))
  {
    sectorsize = 32 * 1024;
  }
  else if(Sector == FLASH_SECTOR_4)
  {
    sectorsize = 128 * 1024;
  }
  else
  {
    sectorsize = 256 * 1024;
  }
  return sectorsize;
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
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address + 0, (uint32_t)g_st_FlashMemory.u32FlashSaveDen);		//Moter shaft
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address + 4, (uint32_t)g_st_FlashMemory.u32FlashSaveNum);		//Gear end shaft
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address + 8, (uint32_t)g_st_FlashMemory.u32FlashSaveDiameter);	//move
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address + 12, (uint32_t)g_st_FlashMemory.u32FlashSaveMaxPos);	// Max Position
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address + 16, (uint32_t)g_st_FlashMemory.u32FlashSaveMinPos);	// Min Position
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address + 20, (uint32_t)g_st_FlashMemory.u32FlashSaveMinMaxRpm); // MinMax Rpm
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address + 24, (uint32_t)g_st_FlashMemory.u32FlashSaveDriveType);	// Type (ex : Direct, Inverter ...)
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address + 28, (uint32_t)g_st_FlashMemory.u32FlashSaveWire);		// Wire width
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address + 32, (uint32_t)g_st_FlashMemory.u32FlashSaveYoYo);		// YoYo type or no YoYo Type
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address + 36, (uint32_t)g_st_FlashMemory.u32FlashSaveParking);		// SecondBrake type or no SecondBrake Type
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address + 40, (uint32_t)g_st_FlashMemory.u32FlashSaveWireOut);			// WireOut type or no WireOut Type
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address + 44, (uint32_t)g_st_FlashMemory.u32FlashSaveEmgBrake);		// EmgBrake type or no EmgBrake Type
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address + 48, (uint32_t)g_st_FlashMemory.u32FlashSaveEncPulse);	// Encoder Pulse(ex : 1024, 2048, 4192..);
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
	  memcpy(&g_st_PDOBuffer.u8TPDO3statusword, &rcvd_msg, 2);	// 2byte controlworda
	  KEB_CAN.KEB_CAN_Func_reverse_array(g_st_PDOBuffer.u8TPDO3statusword, 2);//KEB_CAN_Func_reverse_array(TPDO3statusword, 2);

	  memcpy(&g_st_PDOBuffer.u8TPDO3Modes, &rcvd_msg[2], 1);		// 1byte Modes of operation

	  memcpy(&g_st_PDOBuffer.u8TPDO3Errorcode, &rcvd_msg[3], 1); // 1byte errorcode

	  memcpy(&g_st_PDOBuffer.u8TPDO3DigitalInput, &rcvd_msg[4], 2); // 2byte Inv Digtal Input
	  KEB_CAN.KEB_CAN_Func_reverse_array(g_st_PDOBuffer.u8TPDO3DigitalInput, 2);
  }

  if(CANRxHeader.StdId == TXPDO4 + CAN_ID)		//KEB 4th transmit POD Mapping + CANopen Node ID
  {
	  memcpy(&g_st_PDOBuffer.u8TPDO4PositionAct, &rcvd_msg, 4);	// READ KEB Actual Postion
	  KEB_CAN.KEB_CAN_Func_reverse_array(g_st_PDOBuffer.u8TPDO4PositionAct, 4);//KEB_CAN_Func_reverse_array(TPDO4PositionAct, 4);

	  memcpy(&g_st_PDOBuffer.u8TPDO4VelocityAct, &rcvd_msg[4], 4);	//READ KEB Actual Velocity
	  KEB_CAN.KEB_CAN_Func_reverse_array(g_st_PDOBuffer.u8TPDO4VelocityAct, 4);//KEB_CAN_Func_reverse_array(TPDO4VelocityAct, 4);
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
	strcpy(g_Tcp_SerialNumber, TCP_SERIAL_NUMBER_DEFAULT);

	strcpy(g_Tcp_FWversion, FirmwareVersion);

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

	g_st_inverter.s8TouchgfxMode = Position;

	g_st_Setting.bUsingMCCB = false;
	g_st_Setting.bUsingBrake = false;
	g_st_Setting.bUsingMcIn = false;
	g_st_Setting.bUsingMcOut = false;
	g_st_Setting.bUsingDoubleBrake = false;

	HAL_GPIO_WritePin(ARDUINO_D6_GPIO_Port, ARDUINO_D6_Pin, GPIO_PIN_SET);


	FRAM_Read();

	DirectHome(FRAMEncoderData, ARDUINO_D7_GPIO_Port, ARDUINO_D7_Pin);

	binit = true;
}
/*init Function End*/

void disconnectstate()
{
	strcpy(g_st_inverter.cStateStringDisplay,"disconnect");
	strcpy(g_st_inverter.cErrorStringDisplay,"disconnect");
	strcpy(g_st_inverter.cModeStringDisplay,"disconnect");
	g_st_inverter.ActRpmvalue = 0000;
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

void InvDigitalInput(InvDigitalInputTypedef *p, uint16_t value)
{
	p->bSTO2 = value & 0x8000;
	p->bSTO1 = value & 0x4000;
	p->bCW2 = value & 0x2000;
	p->bCW2 = value & 0x1000;
	p->bID = value & 0x0800;
	p->bIC = value & 0x0400;
	p->bIB = value & 0x0200;
	p->bIA = value & 0x0100;
	p->bI8 = value & 0x0080;
	p->bI7 = value & 0x0040;
	p->bI6 = value & 0x0020;
	p->bI5 = value & 0x0010;
	p->bI4 = value & 0x0008;
	p->bI3 = value & 0x0004;
	p->bI2 = value & 0x0002;
	p->bI1 = value & 0x0001;
}

/*void StateControlword(StatecontrolwordTypedef *p, int value)
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
}*/
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
}
/*void StateMachine(StateMachineTypedef *p, int value)
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
}*/
static void App_LoadSettingsFromFlash(void)
{
	  if (*(float*)(Address + 0) > 0)g_st_Setting.fGearDenominator	= *(float*)(Address + 0);//g_st_Setting.fGearDenominator	//Setting Gear Demominator
	  else g_st_Setting.fGearDenominator = 1;
	  if (*(float*)(Address + 4) > 0)g_st_Setting.fGearNumerator = *(float*)(Address + 4);//g_st_Setting.fGearNumerator		//Setting Gear Numerator
	  else g_st_Setting.fGearNumerator = 1;
	  if (*(float*)(Address + 8) > 0)g_st_Setting.fDiameter = *(float*)(Address + 8);//g_st_Setting.fDiameter	//Setting idiamter
	  else g_st_Setting.fDiameter = 1;

	  g_st_Setting.s32MaxPosValue		= *(int*)(Address + 12);			//Setting Max Position
	  g_st_Setting.s32MinPosValue		= *(int*)(Address + 16);			//Setting Min Position
	  g_st_inverter.MinMaxRpmvalue		= *(int*)(Address + 20);			//Setting Motor Rpm
	  g_st_Setting.s32DriveSettingType	= *(int*)(Address + 24);			//Select the mode to use : Direct, Direct Incremental, Inverter + Encoder;
	  g_st_Setting.fWire				= *(float*)(Address + 28);			//Setting Wire width
	  g_st_Setting.s32YoYo				= *(int*)(Address + 32);			//Select the mode to use : YoYo, Nothing
	  g_st_Setting.s32Parking	  		= *(int*)(Address + 36);			//Select the mode to use : SecondBrake, Nothing
	  g_st_Setting.s32WireOut 			= *(int*)(Address + 40);			//Select the mode to use : WireOut, Nothing
	  g_st_Setting.s32EmgBrake			= *(int*)(Address + 44);			//Select the mode to use : EmgBrake, Nothing

	  if(*(uint16_t*)(Address + 48) > 0)g_st_Direct.u16EncoderPulse = *(uint16_t*)(Address + 48);
	  else g_st_Direct.u16EncoderPulse = 1;

	  if(g_st_FlashMemory.bFlashWrite == true)										//Flash Save
	  {
		  save_flash();
		  g_st_FlashMemory.bFlashWrite = false;
	  }
}
static void Canopen_Comm_StartStop(void)
{
	/*if(g_st_IO.IN_Local == false && g_Tcp_STM_RemoteEnable == false)//Remote Mode 이며 Tcp STM Mode 전환 x 일때
	{
	  HAL_CAN_Stop(&hcan1);			// CAN 통신 STOP
	  HAL_TIM_Base_Stop_IT(&htim14); // CAN 통신 TIMER STOP
	}
	else if(g_st_IO.IN_Local == true) // Local Mode 이거나 Remote Mode이며 Tcp STM Mode 전환 o 일때
	{
	  HAL_CAN_Start(&hcan1);		// CAN 통신 START
	  HAL_TIM_Base_Start_IT(&htim14); // CAN 통신 TIMER START
	}*/
	HAL_CAN_Start(&hcan1);		// CAN 통신 START
	HAL_TIM_Base_Start_IT(&htim14); // CAN 통신 TIMER START
}

static void IO_ReadInputs_MCP23S17(void)
{
	/*g_bIO_Input[0]~[9]까지 INPUT 10개*/
	//Local(Remote = false, Local = true) //1번 INPUT
	/*if(g_bIO_Input[0] == true)
	 g_st_IO.IN_Local = true;
	 else
	 g_st_IO.IN_Local = false;*/
	g_st_IO.IN_Local = true;
	//EMG Input Status		// 2번 Input
	if (g_bIO_Input[1] == true)
		g_st_IO.IN_EMG = true;
	else
		g_st_IO.IN_EMG = false;

	//LimitFF Input Status		// 3번 Input
	if (g_bIO_Input[2] == true)
		g_st_IO.IN_FinalPosLimit = true;
	else
		g_st_IO.IN_FinalPosLimit = false;

	//LimitF Input Status		//4번 Input
	if (g_bIO_Input[3] == true)
		g_st_IO.IN_PosLimit = true;
	else
		g_st_IO.IN_PosLimit = false;

	//LimitR Input Status		//5번 Input
	if (g_bIO_Input[4] == true)
		g_st_IO.IN_NegLimit = true;
	else
		g_st_IO.IN_NegLimit = false;

	//LimitFR Input Status		//6번 Input
	if (g_bIO_Input[5] == true)
		g_st_IO.IN_FinalNegLimit = true;
	else
		g_st_IO.IN_FinalNegLimit = false;

	//MCCB Input Status		//7번 Input
	if (g_bIO_Input[6] == true)
		g_st_IO.IN_MCCB = true;
	else
	{
		if(g_st_Setting.bUsingMCCB == false)
			g_st_IO.IN_MCCB = true;
		else
			g_st_IO.IN_MCCB = false;
	}

	//MC IN Input Status	//8번 Input
	if (g_bIO_Input[7] == true)
		g_st_IO.IN_McIn = true;
	else
	{
		if(g_st_Setting.bUsingMcIn == false)
			g_st_IO.IN_McIn = true;
		else
			g_st_IO.IN_McIn = false;
	}

	//MC OUT Input Status		//9번 Input
	if (g_bIO_Input[8] == true)
		g_st_IO.IN_McOut = true;
	else
	{
		if(g_st_Setting.bUsingMcOut == false)
			g_st_IO.IN_McOut = true;
		else
			g_st_IO.IN_McOut = false;
	}

	//EOCR Input Status		//10번 Input
	if (g_bIO_Input[9] == true)
		g_st_IO.IN_EOCR = true;
	else
	{
		if(g_st_Setting.bUsingEOCR == false)
			g_st_IO.IN_EOCR = true;
		else
			g_st_IO.IN_EOCR = false;
	}

	//Brake Input Status		//11번 Input
	if(g_bIO_Input[10] == true)
		g_st_IO.IN_Brake = true;
	else
		g_st_IO.IN_Brake = false;

	//2NDBrake Input Status		//12번 Input
	if(g_bIO_Input[11] == true)
		g_st_IO.IN_DoubleBrake = true;
	else
		g_st_IO.IN_DoubleBrake = false;

	//Wire Out Input Status		//13번 Input
	if(g_bIO_Input[12] == true)
	{
		if(g_st_Setting.s32WireOut == false)
			g_st_IO.IN_WireOut = false;
		else
			g_st_IO.IN_WireOut = true;
	}
	else
		g_st_IO.IN_WireOut = false;

	//Emergency Brake Input Status		//14번 Input
	if(g_bIO_Input[13] == true)
	{
		if(g_st_Setting.s32EmgBrake == false)
			g_st_IO.IN_EmgBrake = false;
		else
			g_st_IO.IN_EmgBrake = true;
	}
	else
		g_st_IO.IN_EmgBrake = false;

	//Parking Input Status		//15번 Input
	if(g_bIO_Input[14] == true)
		if(g_st_Setting.s32Parking == false)
			g_st_IO.IN_Parking = false;
		else
			g_st_IO.IN_Parking = true;
	else
		g_st_IO.IN_Parking = false;

	//Spare		//16번 Input
	if(g_bIO_Input[15] == true)
		;
	else
		;

	//MCP23S17 INPUT
	SPITxData[0] = 0x40; //Address = 0;
	SPITxData[1] = 0x00; //IODIRA = 0x00;
	SPITxData[2] = 0xFF; //If 1, Input, IF 2, Output
	HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, SPITxData, 3, 500);
	HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_SET);

	SPITxData[0] = 0x40;
	SPITxData[1] = 0x01; // IODIRA = 0x01;
	SPITxData[2] = 0xFF; // IF 1, Input, IF 2, Output
	HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, SPITxData, 3, 500);
	HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_SET);

	SPITxData[0] = 0x41;
	SPITxData[1] = 0x12;
	SPITxData[2] = 0x00;
	HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi2, SPITxData, SPIRxData, 3, 500);
	HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_SET);

	for(uint8_t u8IO_InputIndex = 0; u8IO_InputIndex < 8; u8IO_InputIndex++)
	{
	  if(SPIRxData[2] != -1)
		  g_bIO_Input[u8IO_InputIndex] = (SPIRxData[2] >> u8IO_InputIndex) & 0x01;
	  else
		  g_bIO_Input[u8IO_InputIndex] = 0x00;
	}

	SPITxData[0] = 0x41;
	SPITxData[1] = 0x13;
	SPITxData[2] = 0x00;
	HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi2, SPITxData, SPIRxData, 3, 500);
	HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_SET);

	for(uint8_t u8IO_InputIndex = 0; u8IO_InputIndex < 8; u8IO_InputIndex++)
	{
	  if(SPIRxData[2] != -1)
		  g_bIO_Input[u8IO_InputIndex + 8] = (SPIRxData[2] >> u8IO_InputIndex) & 0x01;
	  else
		  g_bIO_Input[u8IO_InputIndex] = 0x00;
	}
}
static void IO_WriteOutputs_MCP23S17(void)
{
	//MCP23S17 OUTPUT
	SPITxData[0] = 0x42;	//Address = 1;
	SPITxData[1] = 0x00;	//IODIRA = 0x00;
	SPITxData[2] = 0x00;	//1 일경우 input, 0 일 경우 output
	HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, SPITxData, 3, 500);
	HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_SET);

	SPITxData[0] = 0x42;	//Address = 1;
	SPITxData[1] = 0x01;	//IODIRB = 0x01;
	SPITxData[2] = 0x00;	//1 일경우 input, 0 일 경우 output
	HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, SPITxData, 3, 500);
	HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_SET);

	//Inverter STO is same EMG Signal
	if (g_st_IO.OUT_InvSTO)
		SPITxData[2] |= 0x01;
	else
		SPITxData[2] &= ~0x01;

	//Local enable signal notification to the PLC
	if (g_st_IO.OUT_Local)
		SPITxData[2] |= 0x02;
	else
		SPITxData[2] &= ~0x02;

	//Inverter MC Input
	if (g_st_IO.OUT_McIn)
		SPITxData[2] |= 0x04;
	else
		SPITxData[2] &= ~0x04;

	//Inverte MC Output
	if (g_st_IO.OUT_McOut)
		SPITxData[2] |= 0x08;
	else
		SPITxData[2] &= ~0x08;

	/*Double Brake Relay code begin*/
	if (g_st_IO.OUT_DoubleBrake)
		SPITxData[2] |= 0x10;
	else
		SPITxData[2] &= ~0x10;
	/*Double Brake Relay code end*/

	//Direct Up,Down
	if (g_st_IO.OUT_DirectUp)
		SPITxData[2] |= 0x20;
	else
		SPITxData[2] &= ~0x20;

	if (g_st_IO.OUT_DirectDown)
		SPITxData[2] |= 0x40;
	else
		SPITxData[2] &= ~0x40;

	SPITxData[0] = 0x42;	//Address = 1;
	SPITxData[1] = 0x12;	//GPIOA = 0x12;
	//SPITxData[2] = 0xFF;	//1 일 경우 = true, 0 일 경우 = false;
	HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, SPITxData, 3, 500);
	HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_SET);

	/*if (g_st_IO.IN_Local == true) {
		if ((g_st_Setting.s32DriveSettingType == Direct_No_Enc) || (g_st_Setting.s32DriveSettingType == Direct_INC) || (g_st_Setting.s32DriveSettingType == Direct_ABS))
		{
			if (g_st_IO.OUT_DirectUp == false && g_st_IO.OUT_DirectDown == false
					&& g_st_IO.OUT_DoubleBrake == false)
			{
				SPITxData[2] |= 0x01;
				SPITxData[2] &= ~0x02;
			}
			else
			{
				;
			}
		}
		else if ((g_st_Setting.s32DriveSettingType == Inverter_No_Enc) || (g_st_Setting.s32DriveSettingType == Inverter_INC) || (g_st_Setting.s32DriveSettingType == Inverter_ABS))
			if (g_st_IO.OUT_DoubleBrake == false && g_st_Statusword.manufacturer_spec_15 == false && g_st_Statusword.no_quick_stop)
			{
				SPITxData[2] &= ~0x01;
				SPITxData[2] |= 0x02;
			}
			else
			{
				;
			}
		else
			;
	}
	else
	{
		;
	}*/
	if (g_st_IO.OUT_PDOon)
		SPITxData[2] |= 0x01;
	else
		SPITxData[2] &= ~0x01;

	if (g_st_IO.OUT_PDOoff)
		SPITxData[2] |= 0x02;
	else
		SPITxData[2] &= ~0x02;

	SPITxData[0] = 0x42;	//Address = 1;
	SPITxData[1] = 0x13;	//GPIOB = 0x13;
	//SPITxData[2] = 0x03;	//1 일 경우 = true, 0 일 경우 = false;

	HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, SPITxData, 3, 500);
	HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_SET);

	SPITxData[0] = 0x43;
	SPITxData[1] = 0x12;
	SPITxData[2] = 0x00;

	HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi2, SPITxData, SPIRxData, 3, 500);
	HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_SET);

	for (uint8_t u8IO_OutputIndex = 0; u8IO_OutputIndex < 8;
			u8IO_OutputIndex++) {
		g_bIO_Output[u8IO_OutputIndex] = (SPIRxData[2] >> u8IO_OutputIndex)
				& 0x01;
	}

	/*if(g_st_IO.OUT_InvSTO == g_bIO_Output[0]) //STO
		;
	else
		g_st_IO.ICError = true;

	if(g_st_IO.OUT_Local == g_bIO_Output[1]) //Local
		;
	else
		g_st_IO.ICError = true;

	if(g_st_IO.OUT_McIn == g_bIO_Output[2]) //MC IN
		;
	else
		g_st_IO.ICError = true;

	if(g_st_IO.OUT_McOut == g_bIO_Output[3])//MC OUT
		;
	else
		g_st_IO.ICError = true;

	if(g_st_IO.OUT_DoubleBrake == g_bIO_Output[4]) //Double Brake
		;
	else
		g_st_IO.ICError = true;

	if(g_st_IO.OUT_DirectUp == g_bIO_Output[5]) // Direct Up
		;
	else
		g_st_IO.ICError = true;

	if(g_st_IO.OUT_DirectDown == g_bIO_Output[6]) // Direct Down
		;
	else
		g_st_IO.ICError = true;*/

	//g_bIO_Output[7] = spare

	SPITxData[0] = 0x43;
	SPITxData[1] = 0x13;
	SPITxData[2] = 0x00;

	HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi2, SPITxData, SPIRxData, 3, 500);
	HAL_GPIO_WritePin(ARDUINO_D4_GPIO_Port, ARDUINO_D4_Pin, GPIO_PIN_SET);

	for (uint8_t u8IO_OutputIndex = 0; u8IO_OutputIndex < 2;
			u8IO_OutputIndex++) {
		g_bIO_Output[u8IO_OutputIndex + 8] = (SPIRxData[2] >> u8IO_OutputIndex)
				& 0x01;
	}

	if(g_st_IO.OUT_PDOon == g_bIO_Output[8])	//PDO on
		;
	else
		g_st_IO.ICError = true;


	if(g_st_IO.OUT_PDOoff == g_bIO_Output[9])	//PDO off
		;
	else
		g_st_IO.ICError = true;

}
void FRAM_Read(void)
{
	//READ
	FRAMRxCMD[0] = 0x03;	// READ : 0x03
	FRAMRxCMD[1] = 0x00;	// Address[0]
	FRAMRxCMD[2] = 0x00;	// Address[1]

	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, FRAMRxCMD, 3, 500);
	HAL_SPI_Receive(&hspi2, &FRAMRXData[0], 1, 500);
	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_SET);

	FRAMRxCMD[0] = 0x03;	//READ : 0x03
	FRAMRxCMD[1] = 0x00;	// Address[0]
	FRAMRxCMD[2] = 0x01;	// Address[1]

	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, FRAMRxCMD, 3, 500);
	HAL_SPI_Receive(&hspi2, &FRAMRXData[1], 1, 500);
	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_SET);

	FRAMRxCMD[0] = 0x03;	//READ : 0x03;
	FRAMRxCMD[1] = 0x00;	// Address[0]
	FRAMRxCMD[2] = 0x02;	// Address[1]

	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, FRAMRxCMD, 3, 500);
	HAL_SPI_Receive(&hspi2, &FRAMRXData[2], 1, 500);
	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_SET);

	FRAMRxCMD[0] = 0x03;	//READ : 0x03
	FRAMRxCMD[1] = 0x00;	// Address[0]
	FRAMRxCMD[2] = 0x03;	// Address[1]

	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, FRAMRxCMD, 3, 500);
	HAL_SPI_Receive(&hspi2, &FRAMRXData[3], 1, 500);
	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_SET);

	FRAMEncoderData = 0;
	FRAMEncoderData |= ((uint32_t)FRAMRXData[0] << 24);
	FRAMEncoderData |= ((uint32_t)FRAMRXData[1] << 16);
	FRAMEncoderData |= ((uint32_t)FRAMRXData[2] << 8);
	FRAMEncoderData |= ((uint32_t)FRAMRXData[3] << 0);
}
static void FRAM_Write(void)
{
	/* FRAM Code begin*/
	uint8_t wren = 0x06; //Write Enable Register
	uint8_t rdwren = 0x05;	//Read Status Register
	uint8_t testredwren;

	//Write Eanble
	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, &wren, 1, 500);
	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_SET);

	//Readd Status
	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, &rdwren, 1, 500);
	HAL_SPI_Receive(&hspi2, &testredwren, 1, 500);
	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_SET);

	// WRITE
	FRAMTxCMD[0] = 0x02;	// WRITE : 0x02
	FRAMTxCMD[1] = 0x00;	// Address[0]
	FRAMTxCMD[2] = 0x00;	// Address[1]
	FRAMTxCMD[3] = SPIEncoderRxData[1];	//Write Data

	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, FRAMTxCMD, 4, 500);
	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_SET);

	//READ
	/*FRAMRxCMD[0] = 0x03;	// READ : 0x03
	FRAMRxCMD[1] = 0x00;	// Address[0]
	FRAMRxCMD[2] = 0x00;	// Address[1]

	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, FRAMRxCMD, 3, 500);
	HAL_SPI_Receive(&hspi2, &FRAMRXData[0], 1, 500);
	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_SET);*/

	//Write Enable
	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, &wren, 1, 500);
	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, &rdwren, 1, 500);
	HAL_SPI_Receive(&hspi2, &testredwren, 1, 500);
	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_SET);

	FRAMTxCMD[0] = 0x02;	// WRITE : 0x02
	FRAMTxCMD[1] = 0x00;	// Address[0]
	FRAMTxCMD[2] = 0x01;	// Address[1]
	FRAMTxCMD[3] = SPIEncoderRxData[2];//Write Data

	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, FRAMTxCMD, 4, 500);
	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_SET);

	/*FRAMRxCMD[0] = 0x03;	//READ : 0x03
	FRAMRxCMD[1] = 0x00;	// Address[0]
	FRAMRxCMD[2] = 0x01;	// Address[1]

	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, FRAMRxCMD, 3, 500);
	HAL_SPI_Receive(&hspi2, &FRAMRXData[1], 1, 500);
	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_SET);*/

	//Write Enable
	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, &wren, 1, 500);
	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, &rdwren, 1, 500);
	HAL_SPI_Receive(&hspi2, &testredwren, 1, 500);
	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_SET);

	FRAMTxCMD[0] = 0x02;	// WRITE 0x02
	FRAMTxCMD[1] = 0x00;	// Address[0]
	FRAMTxCMD[2] = 0x02;	// Address[1]
	FRAMTxCMD[3] = SPIEncoderRxData[3];//Write Data

	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, FRAMTxCMD, 4, 500);
	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_SET);

	/*FRAMRxCMD[0] = 0x03;	//READ : 0x03;
	FRAMRxCMD[1] = 0x00;	// Address[0]
	FRAMRxCMD[2] = 0x02;	// Address[1]

	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, FRAMRxCMD, 3, 500);
	HAL_SPI_Receive(&hspi2, &FRAMRXData[2], 1, 500);
	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_SET);*/

	//Write Enable
	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, &wren, 1, 500);
	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, &rdwren, 1, 500);
	HAL_SPI_Receive(&hspi2, &testredwren, 1, 500);
	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_SET);

	FRAMTxCMD[0] = 0x02;	// WRITE : 0x02
	FRAMTxCMD[1] = 0x00;	// Address[0]
	FRAMTxCMD[2] = 0x03;	// Address[1]
	FRAMTxCMD[3] = SPIEncoderRxData[4];//Write Data

	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, FRAMTxCMD, 4, 500);
	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_SET);

	/*FRAMRxCMD[0] = 0x03;	//READ : 0x03
	FRAMRxCMD[1] = 0x00;	// Address[0]
	FRAMRxCMD[2] = 0x03;	// Address[1]

	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, FRAMRxCMD, 3, 500);
	HAL_SPI_Receive(&hspi2, &FRAMRXData[3], 1, 500);
	HAL_GPIO_WritePin(ARDUINO_D8_GPIO_Port, ARDUINO_D8_Pin, GPIO_PIN_SET);*/

	/* FRAM Code End*/
}

void DirectHome(uint32_t value, GPIO_TypeDef* Port, uint16_t Pin)
{
	uint8_t TxData[5] = {0};
	TxData[0] = 0x98;
	TxData[1] = ((uint8_t)(value >> 24));
	TxData[2] = ((uint8_t)(value >> 16));
	TxData[3] = ((uint8_t)(value >> 8));
	TxData[4] = ((uint8_t)(value >> 0));
	HAL_GPIO_WritePin(Port, Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, TxData, 5, 500);
	HAL_GPIO_WritePin(Port, Pin, GPIO_PIN_SET);

	TxData[0] = 0xE0;
	HAL_GPIO_WritePin(Port, Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, TxData, 1, 500);
	HAL_GPIO_WritePin(Port, Pin, GPIO_PIN_SET);
}

void DirectUpDown(void)
{
	//monitor Direct Type Limit Status And Position. if Limit status is false, g_st_Direct.bUp, g_st_Direct.bDown variable change false
	if(logic.bOUT_MCUp)
	{
		g_st_Direct.bUp = true;
		g_st_Direct.bDown = false;
	}
	else if(logic.bOUT_MCDown)
	{
		g_st_Direct.bUp = false;
		g_st_Direct.bDown = true;
	}
	else
	{
		g_st_Direct.bTouchgfxUpButton = false;
		g_st_Direct.bTouchgfxDownButton = false;
		g_st_Direct.bUp = false;
		g_st_Direct.bDown = false;
	}
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
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 3072);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of Serial_Task */
  osThreadDef(Serial_Task, StartTask02, osPriorityNormal, 0, 512);
  Serial_TaskHandle = osThreadCreate(osThread(Serial_Task), NULL);

  /* definition and creation of ETHTask */
  osThreadDef(ETHTask, StartTask03, osPriorityNormal, 0, 512);
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
  HAL_GPIO_WritePin(GPIOH, DCMI_PWR_EN_Pin|ARDUINO_D6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ARDUINO_D10_GPIO_Port, ARDUINO_D10_Pin, GPIO_PIN_RESET);

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

  /*Configure GPIO pins : DCMI_PWR_EN_Pin ARDUINO_D6_Pin */
  GPIO_InitStruct.Pin = DCMI_PWR_EN_Pin|ARDUINO_D6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

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

  can_filter_config();

  /*Encoder TTL Setting begin*/
  SPIEncoderTxData[0] = 0x88;			//MDR0 WRITE ADDRESS 0x88
  SPIEncoderTxData[1] = 0x01;			//
  HAL_GPIO_WritePin(ARDUINO_D7_GPIO_Port, ARDUINO_D7_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi2, SPIEncoderTxData, 2, 1000);
  HAL_GPIO_WritePin(ARDUINO_D7_GPIO_Port, ARDUINO_D7_Pin, GPIO_PIN_SET);

  SPIEncoderTxData[0] = 0x90;				//
  SPIEncoderTxData[1] = 0x00;
  HAL_GPIO_WritePin(ARDUINO_D7_GPIO_Port, ARDUINO_D7_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi2, SPIEncoderTxData, 2, 1000);
  HAL_GPIO_WritePin(ARDUINO_D7_GPIO_Port, ARDUINO_D7_Pin, GPIO_PIN_SET);

  SPIEncoderTxData[0] = 0x20;
  HAL_GPIO_WritePin(ARDUINO_D7_GPIO_Port, ARDUINO_D7_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi2, SPIEncoderTxData, 1, 1000);
  HAL_GPIO_WritePin(ARDUINO_D7_GPIO_Port, ARDUINO_D7_Pin, GPIO_PIN_SET);

  SPIEncoderTxData[0] = 0x30;
  HAL_GPIO_WritePin(ARDUINO_D7_GPIO_Port, ARDUINO_D7_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi2, SPIEncoderTxData, 1, 1000);
  HAL_GPIO_WritePin(ARDUINO_D7_GPIO_Port, ARDUINO_D7_Pin, GPIO_PIN_SET);
  /*Encoder TTL Setting end*/

  /* Infinite loop */
  for(;;)
  {
	  if (binit == false)
	  {
		  variableinit();
		  /*Canopen Start,Stop*/
		  Canopen_Comm_StartStop();
	  }
	  else
	  {
		  /* flash memory */
		  App_LoadSettingsFromFlash();

		  g_Tcp_LocalCtrlOn = g_st_IO.IN_Local;
		  g_Tcp_LimitFF = g_st_IO.IN_FinalPosLimit;
		  g_Tcp_LimitF = g_st_IO.IN_PosLimit;
		  g_Tcp_LimitR = g_st_IO.IN_NegLimit;
		  g_Tcp_LimitFR = g_st_IO.IN_FinalNegLimit;
		  g_Tcp_WireOut = g_st_IO.IN_WireOut;
		  g_Tcp_EmgBrake = g_st_IO.IN_EmgBrake;
		  g_Tcp_LocalCtrlOn = g_st_IO.OUT_Local;
		  g_Tcp_IsError = g_bError;
		  g_Tcp_ErrorCode = g_u16Errorcode;
		  g_Tcp_ErrorType = g_u8ErrorType;
		  if(g_st_Setting.s32DriveSettingType == Direct_ABS || Direct_INC)
			  g_Tcp_ActPos = (int)g_st_Direct.s32DirectActPos;
		  else
			  g_Tcp_ActPos = (int)g_st_inverter.PosActPosvalue;

		  if(g_st_Setting.s32DriveSettingType == Direct_No_Enc|| g_st_Setting.s32DriveSettingType == Direct_INC || g_st_Setting.s32DriveSettingType == Direct_ABS)
			  g_Tcp_PowerStatus = g_st_IO.IN_MCCB;
		  else if(g_st_Setting.s32DriveSettingType == Inverter_No_Enc || g_st_Setting.s32DriveSettingType == Inverter_INC || g_st_Setting.s32DriveSettingType == Inverter_ABS)
			  g_Tcp_PowerStatus = (g_st_IO.IN_MCCB && (g_st_IO.IN_McIn && g_st_IO.IN_McOut));
		  else
			  g_Tcp_PowerStatus = false;

		  if(g_Tcp_DriveType == Direct_No_Enc)
		  {
			  if(g_Tcp_DirectUp)
			  {
				  if(g_Tcp_LimitFF && g_Tcp_LimitF)
				  {
					  g_Tcp_IsRunning = true;
					  g_Tcp_IsArrived = false;
				  }
				  else
				  {
					  g_Tcp_IsRunning = false;
					  g_Tcp_IsArrived = true;
				  }
			  }
			  else if(g_Tcp_DirectDown)
			  {
				  if(g_Tcp_LimitFR && g_Tcp_LimitR)
				  {
					  g_Tcp_IsRunning = true;
					  g_Tcp_IsArrived = false;
				  }
				  else
				  {
					  g_Tcp_IsRunning = false;
					  g_Tcp_IsArrived = true;
				  }
			  }
			  else
			  {
				  g_Tcp_IsRunning = false;
				  g_Tcp_IsArrived = false;
			  }
		  }
		  else if(g_Tcp_DriveType == Direct_INC || g_Tcp_DriveType == Direct_ABS)
		  {
			  if(g_Tcp_DirectUp)
			  {
				  if(g_Tcp_LimitFF && g_Tcp_LimitF)
				  {
					  if(g_Tcp_TargetPos > g_Tcp_ActPos)
					  {
						  g_Tcp_IsRunning = true;
						  g_Tcp_IsArrived = false;
					  }
					  else if(g_Tcp_TargetPos <= g_Tcp_ActPos)
					  {
						  g_Tcp_IsRunning = false;
						  g_Tcp_IsArrived = true;
					  }
				  }
				  else
				  {
					  g_Tcp_IsRunning = false;
					  g_Tcp_IsArrived = true;
				  }
			  }
			  else if(g_Tcp_DirectDown)
			  {
				  if(g_Tcp_LimitFR && g_Tcp_LimitR)
				  {
					  if(g_Tcp_TargetPos < g_Tcp_ActPos)
					  {
						  g_Tcp_IsRunning = true;
						  g_Tcp_IsArrived = false;
					  }
					  else if(g_Tcp_TargetPos >= g_Tcp_ActPos)
					  {
						  g_Tcp_IsRunning = false;
						  g_Tcp_IsArrived = true;
					  }
				  }
				  else
				  {
					  g_Tcp_IsRunning = false;
					  g_Tcp_IsArrived = true;
				  }
			  }
			  else
			  {
				  g_Tcp_IsRunning = false;
				  g_Tcp_IsArrived = false;
			  }
		  }
		  else if(g_Tcp_DriveType == Inverter_INC || g_Tcp_DriveType == Inverter_ABS)
		  {
			  if(g_st_inverter.ActRpmvalue != 0 && g_st_Statusword.target_reached == false)
			  {
				  g_Tcp_IsRunning = true;
				  g_Tcp_IsArrived = false;
			  }
			  else if(g_st_inverter.ActRpmvalue == 0 && g_st_Statusword.target_reached == true)
			  {
				  g_Tcp_IsRunning = false;
				  g_Tcp_IsArrived = true;
			  }
			  else
			  {
				  g_Tcp_IsRunning = false;
				  g_Tcp_IsArrived = false;
			  }
		  }

		  //logic <-> Global IO
		  logic.bIN_Local = g_st_IO.IN_Local;					//Local
		  logic.bIN_EMG = g_st_IO.IN_EMG;						//EMG
		  logic.bIN_FinalPosLimit = g_st_IO.IN_FinalPosLimit;	//Limit FF
		  logic.bIN_PosLimit = g_st_IO.IN_PosLimit;				//Limit F
		  logic.bIN_NegLimit = g_st_IO.IN_NegLimit;				//Limit R
		  logic.bIN_FinalNegLimit = g_st_IO.IN_FinalNegLimit;	//Limit FR
		  logic.bIN_MCCB = g_st_IO.IN_MCCB;						//MCCB
		  logic.bIN_McIn = g_st_IO.IN_McIn;						//MCIN
		  logic.bIN_McOut = g_st_IO.IN_McOut;					//MCOUT
		  logic.bIN_EOCR = g_st_IO.IN_EOCR;						//EOCR
		  logic.bIN_Brake = g_st_IO.IN_Brake;					//BRAKE
		  logic.bIN_DoubleBrake = g_st_IO.IN_DoubleBrake;			//2n
		  logic.bIN_WireOut = g_st_IO.IN_WireOut;
		  logic.bIN_EmgBrake = g_st_IO.IN_EmgBrake;
		  logic.bIN_Parking = g_st_IO.IN_Parking;


		  g_st_IO.OUT_InvSTO = logic.bOUT_STO;
		  g_st_IO.OUT_Local = logic.bOUT_Local;
		  g_st_IO.OUT_DirectUp = g_st_Direct.bUp;
		  g_st_IO.OUT_DirectDown = g_st_Direct.bDown;
		  g_st_IO.OUT_McIn = logic.bOUT_McIn;
		  g_st_IO.OUT_McOut = logic.bOUT_McOut;
		  g_st_IO.OUT_DoubleBrake = logic.bOUT_DoubleBrake;
		  g_st_IO.OUT_PDOoff = logic.bOUT_PDOoff;
		  g_st_IO.OUT_PDOon = logic.bOUT_PDOon;


		  //Main Logic
		  logic.MainLogic();
		  //IO Input,Output
		  IO_ReadInputs_MCP23S17();
		  IO_WriteOutputs_MCP23S17();

		  //FRAM Write(TTL Data Save)
		  FRAM_Write();

		  /*Encoder TTL Count Begin */
		  SPIEncoderTxData[0] = 0x60;
		  SPIEncoderTxData[1] = 0x00;
		  SPIEncoderTxData[2] = 0x00;
		  SPIEncoderTxData[3] = 0x00;
		  SPIEncoderTxData[4] = 0x00;
		  HAL_GPIO_WritePin(ARDUINO_D7_GPIO_Port, ARDUINO_D7_Pin, GPIO_PIN_RESET);
		  HAL_SPI_TransmitReceive(&hspi2, SPIEncoderTxData, SPIEncoderRxData, 5, 500);
		  HAL_GPIO_WritePin(ARDUINO_D7_GPIO_Port, ARDUINO_D7_Pin, GPIO_PIN_SET);
		  /*Encoder TTL Count End */

		  //TTL Encoder Count Data Change uint8_t [1]~[4] -> int32_t
		  SPIEncoderData = 0;
		  SPIEncoderData |= ((uint32_t)SPIEncoderRxData[1] << 24);
		  SPIEncoderData |= ((uint32_t)SPIEncoderRxData[2] << 16);
		  SPIEncoderData |= ((uint32_t)SPIEncoderRxData[3] << 8);
		  SPIEncoderData |= ((uint32_t)SPIEncoderRxData[4] << 0);

		  g_st_Direct.s32EncodercountValue = SPIEncoderData;	//TTL Encoder Count value

		  //Home Setting
		  if(g_st_Setting.s32DriveSettingType == Direct_INC) // Direct Encoder count
		  {
			  g_st_Direct.fHomerated = (g_st_Setting.fGearDenominator / g_st_Setting.fGearDenominator);
			  g_st_Direct.fHomePoscount = (g_st_Direct.s32DirectHomeOffset * g_st_Direct.u16EncoderPulse);
			  g_st_Direct.fHomeFeedconstant = 1/(g_st_Setting.fDiameter);
			  g_st_Direct.s32HomeCountvalue = g_st_Direct.fHomerated * g_st_Direct.fHomePoscount * g_st_Direct.fHomeFeedconstant;
		  }
		  else if(g_st_Setting.s32DriveSettingType == Inverter_ABS) // Inverter Encoder count
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

		  if(g_st_Direct.bHoming == true)
		  {
			  DirectHome(g_st_Direct.s32HomeCountvalue, ARDUINO_D7_GPIO_Port, ARDUINO_D7_Pin);
			  g_st_Direct.bHoming = false;
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
		  KEB_CAN.KEB_CAN_Func_32dectohex(Countvalue, g_st_PDOBuffer.u8RPDOTargetPos, 4);

		  //RPDO4 Target Vel
		  KEB_CAN.KEB_CAN_Func_32dectohex(g_st_inverter.PosSetRpmvalue, g_st_PDOBuffer.u8RPDOTargetVel, 4);

		  //PRDO4 Target Home Pos
		  //convert Homecountvalue 32dec -> hex
		  KEB_CAN.KEB_CAN_Func_32dectohex(HomeCountvalue, g_st_PDOBuffer.u8RPDOHomeoffset, 4);

		  //Read Status
		  TPDO3Statusword_dec = KEB_CAN.KEB_CAN_Func_hexto16uint(g_st_PDOBuffer.u8TPDO3statusword, 2);
		  Statusword(&g_st_Statusword, TPDO3Statusword_dec);

		  //Read Inverter Digital Input
		  TPDO3DigitalInput_dec = KEB_CAN.KEB_CAN_Func_hexto16uint(g_st_PDOBuffer.u8TPDO3DigitalInput, 2);
		  InvDigitalInput(&g_st_InvDigitalInput, TPDO3DigitalInput_dec);
		  //TPO Errorcode(READ)
		  //KEB_CAN.KEB_CAN_errorcode(g_st_PDOBuffer.u8TPDO3Errorcode, g_st_inverter.cErrorStringDisplay);

		  //TCP Errorcode
		  if(g_st_Setting.s32DriveSettingType == Inverter_ABS || g_st_Setting.s32DriveSettingType == Inverter_INC || g_st_Setting.s32DriveSettingType == Inverter_No_Enc)
			  logic.InvError(g_st_PDOBuffer.u8TPDO3Errorcode, g_st_inverter.cErrorStringDisplay);
		  logic.IOError(g_st_inverter.cErrorStringDisplay);
		  logic.IOError(g_st_Direct.cErrorStringDisplay);
		   g_u8ErrorType = logic.ErrorType;

		  //TPDO Stateword(READ)
		  KEB_CAN.KEB_CAN_Stateword(TPDO3Statusword_dec, g_st_inverter.cStateStringDisplay);

		  //TPDO ModeBuffer(READ)
		  g_st_inverter.s8CurrentMode = g_st_PDOBuffer.u8TPDO3Modes;
		  KEB_CAN.KEB_CAN_ModeState(g_st_PDOBuffer.u8TPDO3Modes, g_st_inverter.cModeStringDisplay);

		  //RPDO ModeBuffer(WRITE)
		  KEB_CAN.KEB_CAN_ModeChange(g_st_inverter.bTouchgfxModeWrite, g_st_inverter.s8TouchgfxMode, g_st_PDOBuffer.s8RPDOModeSelect, g_st_inverter.s8CurrentMode);

		  if(g_st_Statusword.voltage_enabled == true)
			  strcpy(g_st_inverter.cReadystate,"RUN");
		  else
			  strcpy(g_st_inverter.cReadystate,"FAULT");

		  g_st_inverter.ActRpmvalue = KEB_CAN.KEB_CAN_Func_hexto32dec(g_st_PDOBuffer.u8TPDO4VelocityAct, 4) / 8; // co02 : Velocity shift factor = default value 10(3bit) = 1/8 rpm

		  g_st_inverter.PosActPoscount = KEB_CAN.KEB_CAN_Func_hexto32dec(g_st_PDOBuffer.u8TPDO4PositionAct, 4);

		  //Direct Up Down Variable
		  DirectUpDown();

		  // Analog RPM setting
		  if(g_st_IO.IN_Local)
		  {
			  HAL_ADC_Start_DMA(&hadc3, &uiADCresult[0], 5);
			  /*if(GVLiMode == Velocity)
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
			  }*/
			  if(g_st_Setting.s32DriveSettingType == Inverter_No_Enc || g_st_Setting.s32DriveSettingType == Inverter_INC || g_st_Setting.s32DriveSettingType == Inverter_ABS)
			  {
				  if(uiADCresult[2] >= 0 && uiADCresult[2] <= 4096)
				  {
					  iTempAnalog = (float)uiADCresult[2] / 4090 * 100;
					  g_st_inverter.PosSetRpmvalue = g_st_inverter.MinMaxRpmvalue * iTempAnalog / 100;
				  }
			  }
		  }
		  else
		  {
			  HAL_ADC_Stop_DMA(&hadc3);
		  }

		  //Axis Actual Position
		  if(g_st_Setting.s32DriveSettingType == Direct_INC)//Direct Encoder Actual Position
		  {
			  g_st_Direct.fActrotate = g_st_Direct.s32EncodercountValue / g_st_Direct.u16EncoderPulse;

			  g_st_Direct.s32DirectActPos = ((g_st_Direct.fActrotate * (g_st_Setting.fGearNumerator / g_st_Setting.fGearDenominator))
					  * g_st_Setting.fDiameter);// + g_st_Direct.s32DirectHomeOffset;
		  }
		  else if(g_st_Setting.s32DriveSettingType == Inverter_ABS)//Inverter Encoder Actual Position
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

  /* Infinite loop */
  for(;;)
  {
	  tcp_echoclient_connect();

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
			//HAL_GPIO_TogglePin(ARDUINO_D10_GPIO_Port, ARDUINO_D10_Pin);
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

		g_st_PDOBuffer.u16Controlword = g_st_controlword.switch_on + g_st_controlword.enable_voltage
				+ g_st_controlword.no_quick_stop + g_st_controlword.enable_operation
				+ g_st_controlword.op_mode_spec_four + g_st_controlword.op_mode_spec_five
				+ g_st_controlword.op_mode_spec_six + g_st_controlword.fault_reset
				+ g_st_controlword.halt + g_st_controlword.op_mode_spec_nine
				+ g_st_controlword.reserved + g_st_controlword.manufacturer_spec_11
				+ g_st_controlword.manufacturer_spec_12 + g_st_controlword.manufacturer_spec_13
				+ g_st_controlword.manufacturer_spec_14 + g_st_controlword.brake_ctrl_15;

		KEB_CAN.KEB_CAN_Func_Controlword_dectohex(g_st_PDOBuffer.u16Controlword, (uint8_t*)&g_st_PDOBuffer.u8RPDOControlword);//KEB_CAN_Func_Controlword_dectohex(GVL_iControlword, (uint8_t*)&g_st_PDOBuffer.u8Controlword);

		CAN1RPDO3Data[0] = g_st_PDOBuffer.u8RPDOControlword[1];
		CAN1RPDO3Data[1] = g_st_PDOBuffer.u8RPDOControlword[0];
		CAN1RPDO3Data[2] = g_st_PDOBuffer.s8RPDOModeSelect;
		CAN1RPDO3Data[3] = g_st_PDOBuffer.u8RPDOHomeoffset[3];
		CAN1RPDO3Data[4] = g_st_PDOBuffer.u8RPDOHomeoffset[2];
		CAN1RPDO3Data[5] = g_st_PDOBuffer.u8RPDOHomeoffset[1];
		CAN1RPDO3Data[6] = g_st_PDOBuffer.u8RPDOHomeoffset[0];
		CAN1RPDO3Data[7] = 0x00;

		CAN1RPDO4Data[0] = g_st_PDOBuffer.u8RPDOTargetPos[3];
		CAN1RPDO4Data[1] = g_st_PDOBuffer.u8RPDOTargetPos[2];
		CAN1RPDO4Data[2] = g_st_PDOBuffer.u8RPDOTargetPos[1];
		CAN1RPDO4Data[3] = g_st_PDOBuffer.u8RPDOTargetPos[0];
		CAN1RPDO4Data[4] = g_st_PDOBuffer.u8RPDOTargetVel[3];
		CAN1RPDO4Data[5] = g_st_PDOBuffer.u8RPDOTargetVel[2];
		CAN1RPDO4Data[6] = g_st_PDOBuffer.u8RPDOTargetVel[1];
		CAN1RPDO4Data[7] = g_st_PDOBuffer.u8RPDOTargetVel[0];

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
	//if (htim->Instance == TIM13){
		//HAL_GPIO_TogglePin(ARDUINO_D10_GPIO_Port, ARDUINO_D10_Pin); //TIMER 시간 설정 필요
	//}

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

