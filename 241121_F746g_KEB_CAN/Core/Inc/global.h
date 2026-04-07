/*
 * global.h
 *
 *  Created on: Feb 3, 2024
 *      Author: Lee
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include <main.h>
#include "stdbool.h"
#include "stm32f7xx_hal.h"

//Serial Number
#define TCP_SERIAL_NUMBER_DEFAULT "C224404491"//"C241701976"
//Version
#define FirmwareVersion "1.0.0.1"

typedef enum TcpPingPongTypdef{
	Disconnect = 0,
	Ping = 1,
	Pong = 2
}TcpPingPongTypdef;

//typedef enum
typedef enum DriveTypeTypedef{
	No_Type = 0,
	Direct_No_Enc = 1,
	Direct_INC = 2,
	Direct_ABS = 3,
	Inverter_No_Enc = 4,
	Inverter_INC = 5,
	Inverter_ABS = 6
}DriveTypeTypedef;


typedef enum WriteModeTypedef{
	Nomode = 0,
	Position = 1,
	Velocity = 2,
	Home	= 6,
	Cycl_Sync_Pos = 8
}WriteModeTypedef;

typedef enum ErrorIdTypedef{
	ErrControlWord7 = 10000,//Power Controlword 7로 안바뀜
	ErrNoPosMode = 10001,	//Position Mode가 아님
	ErrVoltage = 10002,//인버터 3상 인가 확인 필요
	ErrHomingfault = 10003, //Home설정 안됨
	ErrNoHomeMode = 10004, // Home Mode가 아님
	ErrEMG	= 10005,
	ErrMCCB = 10006,
	ErrEmgBrake = 10007,
	ErrWireOut = 10008,
	ErrBrakeCheck = 10009
}ErrorIdTypedef;
typedef enum ErrorTypedef{
	NO_ERROR = 0,
	INVERTER = 1,
	EMERGENCY = 2,
	NORMAL = 3,
	MOTOR = 4,
	PLC = 5,
	LIMIT_ALARM = 6,
	EOCR_TRIP = 7,
	POWER_ALARM = 8,
	ENCODER = 9,
	CURRENT = 10,
	POTENTIAL = 11,
	OVERLOAD = 12,
	OVERHEAT = 13
}ErrorTypedef;

extern bool g_bError;
extern uint16_t g_u16Errorcode;
extern uint8_t g_u8ErrorType;


//Board 관련 Digital I/O
//switch
extern bool g_bIO_Input[15];
extern bool g_bIO_Output[10];

//Touchgfx

extern int32_t g_s32Addnumber; //g_s32Address

extern bool g_bPowerstate;
extern bool g_bPoweroff;
extern bool g_bPoweron;

extern bool GVLComon;
extern bool GVLComoff;

//extern int GVLComstate;

//TCP
extern uint8_t g_st_u8IP[4];
extern bool g_bEthernet_ConnectionStatus ;
extern uint8_t g_u8Ethernet_TcpStatus;




typedef struct PDOBufferTypedef{
	//TPDO
	uint8_t u8TPDO3statusword[2];
	uint8_t u8TPDO3Modes;
	uint8_t u8TPDO3Errorcode;
	uint8_t u8TPDO3DigitalInput[2];

	uint8_t u8TPDO4PositionAct[4];
	uint8_t u8TPDO4VelocityAct[4];

	//RPDO
	uint8_t u8RPDOControlword[2];
	int8_t s8RPDOModeSelect;
	uint8_t u8RPDOHomeoffset[4];
	uint8_t u8RPDOTargetPos[4];
	uint8_t u8RPDOTargetVel[4];

	uint16_t u16Controlword;
}PDOBufferTypdef;


//Flash Memory
typedef struct FlashMemoryTypedef{
	uint32_t u32FlashSaveMaxPos;					//Memory Save Max Position
	uint32_t u32FlashSaveMinPos;					//Memory Save Min Position
	uint32_t u32FlashSaveDen;						//Memory Save Min Gear
	uint32_t u32FlashSaveNum;
	uint32_t u32FlashSaveDiameter;
	uint32_t u32FlashSaveMinMaxRpm;
	uint32_t u32FlashSaveDriveType;
	uint32_t u32FlashSaveWire;
	uint32_t u32FlashSaveYoYo;
	uint32_t u32FlashSaveParking;
	uint32_t u32FlashSaveWireOut;
	uint32_t u32FlashSaveEmgBrake;
	uint32_t u32FlashSaveEncPulse;
	bool bFlashWrite;
}FlashMemoryTypedef;


//typedef struct
typedef struct InputOutputTypedef{
	// IO INPUT
	bool IN_Local;					//Remote<->Local			Pin 1
	bool IN_EMG;					// Emergency switch			Pin 2
	bool IN_FinalPosLimit;			// Final Positive Limit		Pin 3
	bool IN_PosLimit;					// Positive Limit		Pin 4
	bool IN_NegLimit;					// Negative Limit		Pin 5
	bool IN_FinalNegLimit;			// Final Negative Limit		Pin 6
	bool IN_MCCB;						// MAIN MCCB ON/OFF     Pin 7
	bool IN_McIn;						// MC IN ON/OFF			Pin 8
	bool IN_McOut;						// MC OUT ON/OFF		Pin 9
	bool IN_EOCR;						// EOCR					Pin 10
	bool IN_Brake;						// Brake				Pin 11
	bool IN_DoubleBrake;					// 2NDBrake				pin 12
	bool IN_WireOut;					// Wire Out				Pin 13
	bool IN_EmgBrake;					// Emergency Brake		Pin 14
	bool IN_Parking;						// Parking				Pin 15
	//bool IN_MCInOut;					// McInOut On/Off		Pin 15


	// IO OUTPUT
	bool OUT_InvSTO;					// Inverter STO									Pin 1
	bool OUT_Local;						// 로컬전환신호 switch Remote = false, Local = true	Pin 2
	bool OUT_McIn;						// Inverter Mc In								Pin 3
	bool OUT_McOut;						// Inverter Mc Out								Pin 4
	bool OUT_DoubleBrake;				// Double brake									Pin 5
	bool OUT_DirectUp;					// Direct Mc Up									Pin 6
	bool OUT_DirectDown;				// Direct Mc Down								Pin 7
	bool OUT_PDOoff;					// Inverter PDO Off								Pin 8
	bool OUT_PDOon;						// Inverter PDO On;								Pin 9

	bool ICError;
}InputOutputTypedef;

//typedef struct
typedef struct SettingTypedef{
	float fWire;	//Wire length
	int s32YoYo;	//YoYo Type
	int s32Parking; // Parking
	int s32WireOut;		//WireOut
	int s32EmgBrake;	// EmgBrake

	//DriveType
	int s32DriveSettingType;	//드라이브 타입 설정

	//Gear
	float fGearNumerator;
	float fGearDenominator;

	float fDiameter;

	//Min, Max Pos
	int32_t s32MaxPosValue;			// Max Position setting value
	int32_t s32MinPosValue;			// Min Position Setting value

	int32_t minmaxRpmvalue;			// Min, Max Rpm Setting value

	bool bUsingMCCB;
	bool bUsingMcIn;
	bool bUsingMcOut;
	bool bUsingBrake;
	bool bUsingDoubleBrake;
	bool bUsingEOCR;

}SettingTypedef;

typedef struct DirectTypedef{
	int16_t s16UpPosSetValue;			//Set Up Position value

	int16_t s16DownPosSetValue;			//Set Down Position value

	int16_t s16HomePosSetValue;			//Set Home Position value

	uint16_t u16EncoderPulse;			//TTL Setting Pulse value ex) TTL 1024, 2048 ...

	int32_t s32EncodercountValue;		//TTL Actual Count value

	int32_t s32DirectActPos;			//Direct Actual Position

	int32_t s32DirectHomeOffset;		//TTL Encoder Home off set

	bool bEncTTLZero;					//TTL Pulse Zero Setting

	float fActrotate;					//

	float fIncrements;

	bool bUp;							//Direct Up Sisgnal
	bool bDown;							//Direct Down Signal
	bool bHoming;						//Direct Homing Signal

	bool bTouchgfxUpButton;				//Touchgfx Up Button Signal
	bool bTouchgfxDownButton;			//Touchgfx Down Button Signal
	//bool bStop;						//Direct Stop signal

	//Direct Home
	float fHomerated;					//Direct Homerated
	float fHomePoscount;				//Direct Position count
	float fHomeFeedconstant;			//Direct Feedconstant
	int32_t s32HomeCountvalue;			//Direct Home Count

	char cErrorStringDisplay[25];
}DirectTypedef;

typedef struct inverterTypedef{
	char cName[20];						//Inverter Name

	int VelsetRpmvalue;					//Inverter Velocity Mode Set Rpm value(Input Keypad Velocity Rpm)
	int VelTargetRpmvalue;				//Inverter Velocity Mode Set Target Rpm value

	int PosSetRpmvalue;					//Inverter Position Mode Set Rpm value(Input Keypad Position Rpm)
	int PosTargetRpmvalue;				//Inverter Position Mode Set Target Rpm value

	int16_t PosSetPosvalue;				//Inverter Position Meode Set Position value

	int16_t HomeSetPosvalue;			//Inverter Home Mode Set Position value

	int ActRpmvalue;					//Inverter Actual Rpm Value
	int32_t MinMaxRpmvalue;				// Struct inverter -> Sturct Setting

	char cStateStringDisplay[25];
	char cErrorStringDisplay[25];
	char cReadystate[15];
	char cModeStringDisplay[25]; // Mode StringDisplay

	int8_t s8CurrentMode;	// Currently Selected Mode

	int8_t s8TouchgfxMode;// TouchMode
	bool bTouchgfxModeWrite; // TouchMode signal


	char cSupplystate[15];
	char cSTOstate[15];
	int iControlwordstate;

	int PosActPosvalue;
	int PosActPoscount;
	float increments;//double increments;
	float iActrotate;
	float iTgtrotate;

	bool bTouchgfx_PowerButton;
	bool bTouchgfx_HomingButton;
	bool bTouchgfx_StartButton;
	bool bTouchgfx_StopButton;
	//float iGearNumerator;
	//float iGearDenominator;
	//float idiameter;
}inverterTypedef;

typedef struct StatuswordTypedef{
	bool manufacturer_spec_15;
	bool special_function;
	bool op_mode_spec_13;
	bool op_mode_spec_12;
	bool internal_limit_active;
	bool target_reached;
	bool remote;
	bool synchron;
	bool warning ;
	bool switch_on_disabled;
	bool no_quick_stop;
	bool voltage_enabled;
	bool fault;
	bool operation_enabled;
	bool switched_on;
	bool ready_to_switch_on;

}StatuswordTypedef;

typedef struct InvDigitalInputTypedef{
	bool bI1;
	bool bI2;
	bool bI3;
	bool bI4;
	bool bI5;
	bool bI6;
	bool bI7;
	bool bI8;
	bool bIA;
	bool bIB;
	bool bIC;
	bool bID;
	bool bCW1;
	bool bCW2;
	bool bSTO1;
	bool bSTO2;
}InvDigitalInputTypedef;

typedef struct controlwordTypedef{
	uint16_t switch_on;//1
	uint16_t enable_voltage;//2
	uint16_t no_quick_stop;//4
	uint16_t enable_operation;//8
	uint16_t op_mode_spec_four;//16
	uint16_t op_mode_spec_five;//32
	uint16_t op_mode_spec_six;//64
	uint16_t fault_reset;//128
	uint16_t halt;//256
	uint16_t op_mode_spec_nine;//512
	uint16_t reserved;//1024
	uint16_t manufacturer_spec_11;//2048
	uint16_t manufacturer_spec_12;//4096
	uint16_t manufacturer_spec_13;//8192
	uint16_t manufacturer_spec_14;//16384
	uint16_t brake_ctrl_15;//32768
}controlwordTypedef;

/*(typedef struct StatecontrolwordTypedef{
	bool switch_on;//1
	bool enable_voltage;//2
	bool no_quick_stop;//4
	bool enable_operation;//8
	bool op_mode_spec_four;//16
	bool op_mode_spec_five;//32
	bool op_mode_spec_six;//64
	bool fault_reset;//128
	bool halt;//256
	bool op_mode_spec_nine;//512
	bool reserved;//1024
	bool manufacturer_spec_11;//2048
	bool manufacturer_spec_12;//4096
	bool manufacturer_spec_13;//8192
	bool manufacturer_spec_14;//16384
	bool brake_ctrl_15;//32768
}StatecontrolwordTypedef;*/

/*typedef struct StateMachineTypedef{
	bool Initialization;		//0
	bool not_ready_to_switch_on;//1
	bool switch_on_disable;		//2
	bool ready_to_switch_on;	//3
	bool switched_on;			//4
	bool operation_enabled;		//5
	bool Quick_stop_active;		//6
	bool fault_reaction_active; //7
	bool fault;					//8
	bool Shutdown_active;		//9
	bool disable_operation_active;	// 10
	bool start_operation_active;	//11
	bool mod_off_pause_active;		//12
	bool power_Off;				//13
	bool protection_time_active;//14
	bool protection_time_end;	//15
	bool endless_protection_time;	//16
	bool suppressed_error;		//17
}StateMachineTypedef;*/

typedef struct BrakeStatusTypedef{
	bool BrakeCtrlVal;
	bool BrakeCtrlSigal;
	bool BrakeCtrlRef;
	bool Reserved_3;
	bool State_closed;
	bool State_open_delay;
	bool State_opening;
	bool State_open;
	bool State_close_delay;
	bool State_closing;
	bool Reserved_8;
	bool Reserved_9;
	bool Reserved_10;
	bool Reserved_11;
	bool Reserved_12;
	bool Reserved_13;
	bool Reserved_14;
	bool Reserved_15;
}BrakeStatusTypedef;

extern PDOBufferTypdef g_st_PDOBuffer;

extern FlashMemoryTypedef g_st_FlashMemory;

extern InputOutputTypedef g_st_IO;

extern SettingTypedef g_st_Setting;

extern DirectTypedef g_st_Direct;

extern inverterTypedef g_st_inverter;	//[Number] <- inverter total unit

extern controlwordTypedef g_st_controlword;

//extern StatecontrolwordTypedef g_st_Statecontrolword; //[Number] <- inverter total unit

//extern StateMachineTypedef g_st_StateMachine; //[Number] <- inverter total unit

extern BrakeStatusTypedef g_st_BrakeStatus; //[Number] <- inverter total unit

extern StatuswordTypedef g_st_Statusword;

extern InvDigitalInputTypedef g_st_InvDigitalInput;

//extern NumpadTypdef GVLNum;
//extern char GVLcRpmvalue[4];
//extern uint8_t GVLCount;


extern int32_t g_s32Vel_input_Rpmvalue;
extern uint8_t g_u8bufVel_input_Rpmvalue[4];

extern int32_t g_s32Pos_input_Rpmvalue;
extern uint8_t g_u8bufPos_input_Rpmvalue[4];

extern int32_t g_s32Pos_input_Posvalue;
extern uint8_t g_u8bufPos_input_Posvalue[8];

extern int32_t g_s32Home_input_Posvalue;
extern uint8_t g_u8bufHome_input_Posvalue[8];

extern int32_t g_s32Direct_input_UpPosvalue;

extern int32_t g_s32Direct_input_DownPosvalue;

extern int32_t g_s32Direct_input_Homevalue;


//extern int32_t GVL_iModevalue;
extern uint8_t GVL_cModevalue[4]; // Serial Mode

//Tcp Drive Status
extern bool g_Tcp_STM_RemoteEnable;
extern bool g_Tcp_InvPower;
extern bool g_Tcp_InvStart;
extern bool g_Tcp_InvStop;
extern bool g_Tcp_Reset;
extern bool g_Tcp_McOn;
extern bool g_Tcp_HomeSet;
extern int g_Tcp_Speed;
extern int g_Tcp_TargetPos;
extern int g_Tcp_HomeSetPos;
extern bool g_Tcp_DirectUp;
extern bool g_Tcp_DirectDown;
extern bool g_Tcp_DirectStop;
extern bool g_Tcp_ConsoleEMG;
extern uint8_t g_Tcp_DriveType;
extern long long g_Tcp_Timestamp;

extern bool g_Tcp_LocalCtrlOn;
extern bool g_Tcp_ParkingStatus;
extern bool g_Tcp_PowerStatus;
extern int g_Tcp_ActPos;
extern uint16_t g_Tcp_RepeatCnt;
extern float g_Tcp_EstTime;
extern float g_Tcp_LeftTime;
extern bool g_Tcp_IsDoorClose;
extern bool g_Tcp_IsRunning;
extern bool g_Tcp_IsArrived;
extern bool g_Tcp_IsFirstFinish;
extern bool g_Tcp_IsSecondFinish;
extern bool g_Tcp_IsCannotGo;
extern bool g_Tcp_IsCannotBack;
extern bool g_Tcp_LimitFF;
extern bool g_Tcp_LimitF;
extern bool g_Tcp_LimitR;
extern bool g_Tcp_LimitFR;
extern bool g_Tcp_WireOut;
extern bool g_Tcp_EmgBrake;
extern bool g_Tcp_IsError;
extern uint16_t g_Tcp_ErrorCode;
extern uint8_t g_Tcp_ErrorType;
extern uint16_t g_Tcp_MaxSpeed;
extern int16_t g_Tcp_ActWeight;

//Tcp Drive Operation
extern bool g_Tcp_IsSelected;
extern uint8_t g_Tcp_ButtonOperation;
extern uint8_t g_Tcp_DeadDirectionType;
extern int g_Tcp_DeadUp;
extern int g_Tcp_DeadDown;
extern int g_Tcp_TargetPos;
extern int16_t g_Tcp_Jerk;
extern int16_t g_Tcp_AccRatio;
extern int16_t g_Tcp_DecRatio;
extern int g_Tcp_MoveMode;
extern int g_Tcp_MovingSpeed;
extern int16_t g_Tcp_MovingTime;
extern uint8_t g_Tcp_RepeatTotalCnt;
extern uint8_t g_Tcp_DelayMode;
extern float g_Tcp_DelayTime;
extern int16_t g_Tcp_DriveNumber;
extern uint16_t g_Tcp_DrivePosition;
extern uint8_t g_Tcp_FunctionType;
extern bool g_Tcp_IsFreeRun;
extern bool g_Tcp_IsErrorSync;
extern bool g_Tcp_IsMaster;
extern uint8_t g_Tcp_CrossDriection;
extern uint16_t g_Tcp_CrossDriveNumber;
extern int16_t g_Tcp_SecondSpeed;
extern int16_t g_Tcp_SecondPos;
extern int16_t g_Tcp_ThirdSpeed;
extern int16_t g_Tcp_ThirdPos;
extern uint8_t g_Tcp_ClientIndex;
extern int g_Tcp_JoystickNo;
extern int g_Tcp_GroupNumber;
extern bool g_Tcp_IsGroup;

//Tcp Drive Setting
extern char g_Tcp_FWversion[16];
extern char g_Tcp_SerialNumber[11];
extern int g_Tcp_MaxPos;
extern int g_Tcp_MinPos;
extern int g_Tcp_HomePos;
extern int g_Tcp_MaxWeight;
extern bool g_Tcp_IsHwLimitOn;
extern bool g_Tcp_IsParked;
extern bool g_Tcp_IsMcOn;
extern bool g_Tcp_IsIgnored;
extern bool g_Tcp_IsReset;
extern bool g_Tcp_IsHomeSet;
extern bool g_Tcp_IsWeightcheck;
extern bool g_Tcp_BypassNum;

//Drive Joystick
extern bool g_Tcp_Uplamp;
extern bool g_Tcp_Downlamp;


#endif /* INC_GLOBAL_H_ */
