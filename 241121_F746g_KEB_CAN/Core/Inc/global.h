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



typedef enum DriveTypeTypedef{
	Direct_No_encoder = 1,
	Direct_encoder = 2,
	inverter_No_encoder = 3,
	inverter_encoder
}DriveTypeTypedef;

//Direct Pos
extern int16_t g_s16DirectSetPosvalue;

//Board 관련 Digital I/O



//switch
//INPUT
extern bool g_bEMG;
extern bool g_bLocal;//로컬전환신호 switch 사용

extern bool ResetTest;

//OUTPUT

extern bool g_bBypassSTO;	//Relay 사용
extern bool g_bMCinput;		//인버터 3상 전압 공급 마크네틱 Input
extern bool g_bMCinputstate;//인버터 3상 전압 공급 마그네틱 상태
extern bool g_bMCoutput;	//인버터 3상 출력 마그네틱 output
extern bool g_bMCoutputstate;//인버터 3상 출력 마그네틱 상태

//Buffer
extern int8_t g_s8ModeSelect;
extern bool g_bModeWrite;

extern uint8_t g_u8BufHomeoffset[4];
extern uint8_t g_u8BufPowerStart[2];//delete

extern uint8_t g_u8BufTargetPos[4];
extern uint8_t g_u8BufTargetVel[4];


extern int32_t g_s32Addnumber; //g_s32Address


extern bool g_bDirect_HomeTrig; //Direct Home trig Signal

extern bool g_bPowerstate;
extern bool g_bPoweroff;
extern bool g_bPoweron;

extern bool GVLComon;
extern bool GVLComoff;

extern int GVLComstate;

//TCP
extern uint8_t GVLTCP_connection;
extern int GVLTCP_state;
extern int GVLTCP_Cable_state;
extern uint8_t g_st_u8IP[4];

extern int8_t g_s8Mode;//GVLiMode; inverter Mode

//Min, Max Pos
extern int32_t g_s32MaxPosValue;						//->Struct Setting
extern int32_t g_s32MinPosValue;						//->Struct Setting

extern int g_s32DriveSettingType;	//드라이브 타입 설정		//-> Struct Setting

//Flash Memory
extern uint32_t g_u32FlashSaveMaxPos;					//Memory Save Max Position
extern uint32_t g_u32FlashSaveMinPos;					//Memory Save Min Position
extern uint32_t g_u32FlashSaveDen;						//Memory Save Min Gear
extern uint32_t g_u32FlashSaveNum;
extern uint32_t g_u32FlashSaveDiameter;
extern uint32_t g_u32FlashSaveMinMaxRpm;
extern uint32_t g_u32FlashSaveDriveType;
extern uint32_t g_u32FlashSaveWire;
extern uint32_t g_u32FlashSaveYoYo;
extern uint32_t g_u32FlashSaveEncPulse;
extern bool g_bFlashWrite;

extern float g_fWire;

extern int g_s32YoYo;

//Tcp 보류
typedef struct TcpComdataTypedef{
	char cState[4];
	char cMode[4];
	char cVelocityTgtRPM[4];
	char cVelocityActRPM[4];
	char cPositionTgtRPM[4];
	char cPositionActRPM[4];
	char cPositionTgtPOS[4];
	char cPositionActPOS[4];

}tcpcomdataTypedef;
//

//typedef enum
typedef enum WriteModeTypedef{
	Nomode = 0,
	Position = 1,
	Velocity = 2,
	Home	= 6,
	Cycl_Sync_Pos = 8
}WriteModeTypedef;

//typedef struct
typedef struct SettingTypedef{
	float g_fWrie;	//Wire length
	int g_s32YoYo;	//YoYo Type

	//DriveType
	int g_s32DriveSettingType;	//드라이브 타입 설정

	//Gear
	float fGearNumerator;
	float fGearDenominator;

	float fDiameter;

	//Min, Max Pos
	int32_t g_s32MaxPosValue;		// Max Position setting value
	int32_t g_s32MinPosValue;		// Min Position Setting value

	int32_t g_s32minmaxRpmvalue;	// Min, Max Rpm Setting value

	bool bFinalPosLimit;			// Final Positive Limit
	bool bPosLimit;				// Positive Limit
	bool bNegLimit;					// Negative Limit
	bool bFinalNegLimit;			// Final Negative Limit

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

	bool bUp;							//Direct Up signal
	bool bDown;							//Direct Down signal
	bool bStop;							//Direct Stop signal

	//Direct Home
	float fHomerated;					//Direct Homerated
	float fHomePoscount;				//Direct Position count
	float fHomeFeedconstant;			//Direct Feedconstant
	int32_t s32HomeCountvalue;			//Direct Home Count

}DirectTypedef;

typedef struct inverterTypedef{
	char cName[20];						//Inverter Name

	int VelsetRpmvalue;					//Inverter Velocity Mode Set Rpm value
	int VelTargetRpmvalue;				//Inverter Velocity Mode Set Target Rpm value

	int PosSetRpmvalue;					//Inverter Position Mode Set Rpm value
	int PosTargetRpmvalue;				//Inverter Position Mode Set Target Rpm value

	//int32_t PosTargetPoscount;
	//int16_t PosTargetPosvalue;

	int16_t PosSetPosvalue;

	//int32_t HomeTargetPoscount;
	//int16_t HomeTargetPosvalue;

	int16_t HomeSetPosvalue;

	int actRpmvalue;
	int32_t minmaxRpmvalue;				// Struct inverter -> Sturct Setting

//	int minPosvalue;
//	int maxPosvalue;

	char cState[25];
	char cError[25];
	char systemcounter[4];
	char cMode[25];
	int8_t s8Mode;
	char cSupplystate[15];
	char cSTOstate[15];
	int iControlwordstate;

	char cReadystate[15];

	int16_t PosActPosvalue;
	int64_t PosActPoscount;
	float increments;//double increments;
	float iActrotate;
	float iTgtrotate;
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

typedef struct StatecontrolwordTypedef{
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
}StatecontrolwordTypedef;

typedef struct StateMachineTypedef{
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
}StateMachineTypedef;

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
extern SettingTypedef g_st_Setting;

extern DirectTypedef g_st_Direct;

extern inverterTypedef g_st_inverter;	//[Number] <- inverter total unit

extern controlwordTypedef g_st_controlword;

extern StatecontrolwordTypedef g_st_Statecontrolword; //[Number] <- inverter total unit

extern StateMachineTypedef g_st_StateMachine; //[Number] <- inverter total unit

extern BrakeStatusTypedef g_st_BrakeStatus; //[Number] <- inverter total unit

extern StatuswordTypedef g_st_Statusword;

//extern WriteModeTypedef GVLWrtiemode;
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


extern uint16_t GVL_iControlword;
extern uint8_t GVL_cControlword[2];

//extern int32_t GVL_iModevalue;
extern uint8_t GVL_cModevalue[4]; // Serial Mode



#endif /* INC_GLOBAL_H_ */
