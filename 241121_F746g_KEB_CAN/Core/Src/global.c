/*
 * global.c
 *
 *  Created on: Mar 18, 2024
 *      Author: LEEMINKOO
 */
#include "global.h"
#include "stdbool.h"

bool g_bError = false;
uint16_t g_u16Errorcode = 0;
uint8_t g_u16ErrorType;
uint8_t g_u8ErrorType;


//Board 관련 Digital I/O
//switch
bool g_bIO_Input[15] = {false};
bool g_bIO_Output[10] = {false};



int32_t g_s32Addnumber; //g_s32Address

bool g_bPowerstate;

bool GVLComon = false;
bool GVLComoff = false;

int GVLComstate = 0;

//IP Address
uint8_t g_st_u8IP[4];
bool g_bEthernet_ConnectionStatus ;
uint8_t g_u8Ethernet_TcpStatus;



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

//int32_t GVL_iModevalue;
uint8_t GVL_cModevalue[4]; // Serial Mode

bool g_bFlashWrite = false;

//struct
PDOBufferTypdef g_st_PDOBuffer;

FlashMemoryTypedef g_st_FlashMemory;

InputOutputTypedef g_st_IO;

SettingTypedef g_st_Setting;

DirectTypedef g_st_Direct;

inverterTypedef g_st_inverter;

controlwordTypedef g_st_controlword; // controlword

//StatecontrolwordTypedef g_st_Statecontrolword; //[Number] <- inverter total unit

//StateMachineTypedef g_st_StateMachine; //[Number] <- inverter total unit

BrakeStatusTypedef g_st_BrakeStatus;

StatuswordTypedef g_st_Statusword;

InvDigitalInputTypedef g_st_InvDigitalInput;

//Tcp Drive Status
bool g_Tcp_LocalCtrlOn;
bool g_Tcp_ParkingStatus;
bool g_Tcp_PowerStatus;
int g_Tcp_ActPos;
uint16_t g_Tcp_RepeatCnt;
float g_Tcp_EstTime;
float g_Tcp_LeftTime;
bool g_Tcp_IsDoorClose;
bool g_Tcp_IsRunning;
bool g_Tcp_IsArrived;
bool g_Tcp_IsFirstFinish;
bool g_Tcp_IsSecondFinish;
bool g_Tcp_IsCannotGo;
bool g_Tcp_IsCannotBack;
bool g_Tcp_LimitFF = false;
bool g_Tcp_LimitF = false;
bool g_Tcp_LimitR = false;
bool g_Tcp_LimitFR = false;
bool g_Tcp_WireOut = false;
bool g_Tcp_EmgBrake = false;
bool g_Tcp_IsError;
uint16_t g_Tcp_ErrorCode;
uint8_t g_Tcp_ErrorType;
uint16_t g_Tcp_MaxSpeed;
int16_t g_Tcp_ActWeight;

//Tcp Drive Operation
bool g_Tcp_STM_RemoteEnable;
bool g_Tcp_Power;
bool g_Tcp_Start;
bool g_Tcp_Stop;
bool g_Tcp_Reset;
bool g_Tcp_McOn;
bool g_Tcp_HomeSet;
int g_Tcp_Speed;
int g_Tcp_TargetPos;
int g_Tcp_HomeSetPos;
bool g_Tcp_DirectUp;
bool g_Tcp_DirectDown;
bool g_Tcp_DirectStop;
bool g_Tcp_ConsoleEMG;
bool g_Tcp_Running;
bool g_Tcp_Arrived;
uint8_t g_Tcp_DriveType;
long long g_Tcp_Timestamp;

bool g_Tcp_IsSelected;
uint8_t g_Tcp_ButtonOperation;
uint8_t g_Tcp_DeadDirectionType;
int g_Tcp_DeadUp;
int g_Tcp_DeadDown;
int g_Tcp_TargetPos;
int16_t g_Tcp_Jerk;
int16_t g_Tcp_AccRatio;
int16_t g_Tcp_DecRatio;
int g_Tcp_MoveMode;
int g_Tcp_MovingSpeed;
int16_t g_Tcp_MovingTime;
uint8_t g_Tcp_RepeatTotalCnt;
uint8_t g_Tcp_DelayMode;
float g_Tcp_DelayTime;
int16_t g_Tcp_DriveNumber;
uint16_t g_Tcp_DrivePosition;
uint8_t g_Tcp_FunctionType;
bool g_Tcp_IsFreeRun;
bool g_Tcp_IsErrorSync;
bool g_Tcp_IsMaster;
uint8_t g_Tcp_CrossDriection;
uint16_t g_Tcp_CrossDriveNumber;
int16_t g_Tcp_SecondSpeed;
int16_t g_Tcp_SecondPos;
int16_t g_Tcp_ThirdSpeed;
int16_t g_Tcp_ThirdPos;
uint8_t g_Tcp_ClientIndex;
int g_Tcp_JoystickNo;
int g_Tcp_GroupNumber;
bool g_Tcp_IsGroup;

//Tcp Drive Setting
char g_Tcp_FWversion[16];
char g_Tcp_SerialNumber[11];
int g_Tcp_MaxPos;
int g_Tcp_MinPos;
int g_Tcp_HomePos;
int g_Tcp_MaxWeight;
bool g_Tcp_IsHwLimitOn;
bool g_Tcp_IsParked;
bool g_Tcp_IsMcOn;
bool g_Tcp_IsIgnored;
bool g_Tcp_IsReset;
bool g_Tcp_IsHomeSet;
bool g_Tcp_IsWeightcheck;
bool g_Tcp_BypassNum;

//Tcp Drive Joystick
bool g_Tcp_Uplamp;
bool g_Tcp_Downlamp;
