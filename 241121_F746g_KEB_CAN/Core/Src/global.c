/*
 * global.c
 *
 *  Created on: Mar 18, 2024
 *      Author: LEEMINKOO
 */
#include "global.h"
#include "stdbool.h"


//Direct
int16_t g_s16DirectSetPosvalue;

//Board 관련 Digital I/O

bool g_bEMG;
bool g_bLocal = true;			//로컬전환신호
bool ResetTest;

bool g_bBypassSTO;		//Relay
bool g_bMCinput;		//인버터 3상 전압 공급 마크네틱 Input
bool g_bMCinputstate;	//인버터 3상 전압 공급 마그네틱 상태
bool g_bMCoutput;		//인버터 3상 출력 마그네틱 output
bool g_bMCoutputstate;	//인버터 3상 출력 마그네틱 상태



//temp
int8_t g_s8ModeSelect;
bool g_bModeWrite;


uint8_t g_u8BufHomeoffset[4];
uint8_t g_u8BufPowerStart[2];//delete

uint8_t g_u8BufTargetPos[4];
uint8_t g_u8BufTargetVel[4];

int32_t g_s32Addnumber; //g_s32Address

bool g_bDirect_HomeTrig;

bool g_bPowerstate;
bool g_bPoweroff;
bool g_bPoweron;

bool GVLComon = false;
bool GVLComoff = false;

int GVLComstate = 0;

//IP Address
uint8_t g_st_u8IP[4];
uint8_t GVLTCP_connection = 0;
int GVLTCP_state = 0;
int GVLTCP_Cable_state = 0;

int8_t g_s8Mode;





int32_t g_s32Vel_input_Rpmvalue;
uint8_t g_u8BufVel_input_Rpmvalue[4];

int32_t g_s32Pos_input_Rpmvalue;
uint8_t g_u8BufPos_input_Rpmvalue[4];

int32_t g_s32Pos_input_Posvalue;
uint8_t g_u8BufPos_input_Posvalue[8];

int32_t g_s32Home_input_Posvalue;
uint8_t g_u8BufHome_input_Posvalue[8];

int32_t g_s32Direct_input_UpPosvalue;

int32_t g_s32Direct_input_DownPosvalue;

int32_t g_s32Direct_input_Homevalue;

uint16_t GVL_iControlword;
uint8_t GVL_cControlword[2];

//int32_t GVL_iModevalue;
uint8_t GVL_cModevalue[4]; // Serial Mode

//Min, Max Pos
int32_t g_s32MaxPosValue;
int32_t g_s32MinPosValue;

int g_s32DriveSettingType;	//드라이브 타입 설정

//Flash memory
uint32_t g_u32FlashSaveMaxPos;
uint32_t g_u32FlashSaveMinPos;
uint32_t g_u32FlashSaveDen;
uint32_t g_u32FlashSaveNum;
uint32_t g_u32FlashSaveDiameter;
uint32_t g_u32FlashSaveMinMaxRpm;
uint32_t g_u32FlashSaveDriveType;
uint32_t g_u32FlashSaveWire;
uint32_t g_u32FlashSaveYoYo;
uint32_t g_u32FlashSaveEncPulse;

bool g_bFlashWrite = false;

float g_fWire;

int g_s32YoYo;

//struct
SettingTypedef g_st_Setting;

DirectTypedef g_st_Direct;

inverterTypedef g_st_inverter;

controlwordTypedef g_st_controlword; // controlword

StatecontrolwordTypedef g_st_Statecontrolword; //[Number] <- inverter total unit

StateMachineTypedef g_st_StateMachine; //[Number] <- inverter total unit

BrakeStatusTypedef g_st_BrakeStatus;

StatuswordTypedef g_st_Statusword;


