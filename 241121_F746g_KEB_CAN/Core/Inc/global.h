/*
 * global.h
 *
 *  Created on: Feb 3, 2024
 *      Author: Lee
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "stdbool.h"
#include "stm32f7xx_hal.h"

//temp
extern uint8_t TempHomeoffset[4];
extern uint8_t TempPowerStart[2];
extern uint8_t TempModeSelect;
extern uint8_t TempTargetPos[4];
extern uint8_t TempTargetVel[4];
//

extern bool GVLLocal;

extern int GVLAddnumber;
extern bool GVLsendControlword;
extern bool GVLsendMode;

extern bool GVLinverterenable;
extern bool GVLPowerstate;
extern bool GVLPoweroff;
extern bool GVLPoweron;

extern bool GVLComon;
extern bool GVLComoff;

extern int GVLComstate;
extern int GVLBrakestatus;
extern bool GVLVel_RPM_direction;

extern bool GVLVelRpmset;
extern bool GVLPosRpmset;

extern bool GVLPosposset;
extern bool GVLHomeposset;

extern bool GVLReset;
extern bool GVLPosStart;
extern bool GVLPosStop;

extern bool GVLHomeset;

extern uint8_t GVL_IP[4];


extern bool GVLWriteon;

extern uint8_t GVLiMode;

//Relay
extern bool GVLbypassSTO;
extern bool GVLMCinput;
extern bool GVLMCinputstate;
extern bool GVLMCoutput;
extern bool GVLMCoutputstate;
//

//TCP
extern uint8_t GVLTCP_connection;
extern int GVLTCP_state;
extern int GVLTCP_Cable_state;

extern uint8_t GVLTCP_inv_Statebuf[4];
extern uint8_t GVLTCP_inv_Errorbuf[4];
extern uint8_t GVLTCP_inv_Modebuf[4];
extern uint8_t GVLTCP_inv_supplybuf[4];
extern uint8_t GVLTCP_inv_STObuf[4];
//

//Flash
extern uint32_t GVLFlash_TempSaveMaxPos;
extern uint32_t GVLFlash_TempSaveMinPos;
extern uint32_t GVLFlash_TempSaveDen;
extern uint32_t GVLFlash_TempSaveNum;
extern uint32_t GVLFlash_TempSaveDiameter;
extern uint32_t GVLFlash_TempSaveMinMaxRpm;
extern bool GVLFlash_Write;

//

extern uint16_t GVL_switch_on;//1
extern uint16_t GVL_enable_voltage;//2
extern uint16_t GVL_no_quick_stop;//4
extern uint16_t GVL_enable_operation;//8
extern uint16_t GVL_op_mode_spec_four;//16
extern uint16_t GVL_op_mode_spec_five;//32
extern uint16_t GVL_op_mode_spec_six;//64
extern uint16_t GVL_fault_reset;//128
extern uint16_t GVL_halt;//256
extern uint16_t GVL_op_mode_spec_nine;//512
extern uint16_t GVL_reserved;//1024
extern uint16_t GVL_manufacturer_spec_11;//2048
extern uint16_t GVL_manufacturer_spec_12;//4096
extern uint16_t GVL_manufacturer_spec_13;//8192
extern uint16_t GVL_manufacturer_spec_14;//16384
extern uint16_t GVL_brake_ctrl_15;//32768




typedef enum WriteModeTypedef{
	Nomode = 0,
	Position = 1,
	Velocity = 2,
	Home	= 6,
	Cycl_Sync_Pos = 8
}WriteModeTypedef;
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

typedef struct inverterTypedef{
	char cName[20];

	int VelsetRpmvalue;
	int VelTargetRpmvalue;

	int PossetRpmvalue;
	int PosTargetRpmvalue;

	int32_t PosTargetPoscount;
	int16_t PosTargetPosvalue;

	int16_t PosSetPosvalue;

	int32_t HomeTargetPoscount;
	int16_t HomeTargetPosvalue;

	int16_t HomeSetPosvalue;

	int actRpmvalue;
	int minmaxRpmvalue;

	int minPosvalue;
	int maxPosvalue;

	char cState[25];
	char cError[25];
	char systemcounter[4];
	char cMode[25];
	int iMode;
	char cSupplystate[15];
	char cSTOstate[15];
	int iControlwordstate;

	char cReadystate[15];
	bool POSLimit;
	bool NEGLimit;

	int16_t PosActPosvalue;
	int64_t PosActPoscount;
	double increments;
	float iActrotate;
	float iTgtrotate;
	float iGearNumerator;
	float iGearDenominator;
	double idiameter;



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
	uint8_t switch_on;//1
	uint8_t enable_voltage;//2
	uint8_t no_quick_stop;//4
	uint8_t enable_operation;//8
	uint8_t op_mode_spec_four;//16
	uint8_t op_mode_spec_five;//32
	uint8_t op_mode_spec_six;//64
	uint8_t fault_reset;//128
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

extern inverterTypedef GVLinverter[7];	//[Number] <- inverter total unit
extern StatecontrolwordTypedef GVLStatecontrolword[7]; //[Number] <- inverter total unit
extern StateMachineTypedef GVLStateMachine[7]; //[Number] <- inverter total unit
extern BrakeStatusTypedef GVLBrakeStatus[7]; //[Number] <- inverter total unit

extern StatuswordTypedef GVLStatusword;
//extern WriteModeTypedef GVLWrtiemode;
//extern NumpadTypdef GVLNum;
//extern char GVLcRpmvalue[4];
//extern uint8_t GVLCount;
extern int GVL_Vel_input_iRpmvalue;
extern uint8_t GVL_Vel_input_cRpmvalue[4];

extern int GVL_Pos_input_iRpmvalue;
extern uint8_t GVL_Pos_input_cRpmvalue[4];

extern int GVL_Pos_input_iPosvalue;
extern uint8_t GVL_Pos_input_cPosvalue[8];

extern int GVL_Home_input_iPosvalue;
extern uint8_t GVL_Home_input_cPosvalue[8];

extern uint16_t GVL_iControlword;
extern uint8_t GVL_cControlword[2];

extern int GVL_iModevalue;
extern uint8_t GVL_cModevalue[4];



#endif /* INC_GLOBAL_H_ */
