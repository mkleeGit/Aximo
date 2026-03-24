/*
 * SerialCom.c
 *
 *  Created on: Mar 15, 2024
 *      Author: LEEMINKOO
 */
#include "SerialCom.h"

typedef enum _Writetype{
	Controlword	= 1,
	Mode 		= 2,
	Vel_RPM		= 3,
	Ethercat 	= 4,
	Serial	 	= 5,
	Pos_RPM		= 6,
	Pos_POS		= 7,
	Home_Pos
}Writetype;

Writetype writetype;

uint8_t ReadDataSendStep;
uint8_t WriteDataSendStep;
bool	bReadstate;
bool	bWritestate;

uint8_t uiSerialinit;
uint8_t cAddress[2];
uint8_t cParaAdd[4];
uint8_t cParaData[8];
uint8_t Writeselectnum;

uint8_t* cpReadreturn;
uint8_t* cpWritereturn;

void Addresscalculation()
{
	if((g_s32Addnumber > 0) && (g_s32Addnumber < 10))
	{
		cAddress[0] = 0x30;
		cAddress[1] = (char)(g_s32Addnumber + '0');
	}
	else if (g_s32Addnumber >= 10 && g_s32Addnumber < 100)
	{
		cAddress[0] = (char)((g_s32Addnumber / 10) + '0');
		cAddress[1] = (char)((g_s32Addnumber % 10) + '0');
	}
}

void Serialinit()
{
	;
}

uint8_t* SerialWriteTx(uint8_t x)
{
	Addresscalculation();
	writetype = x;
	if(writetype == Controlword)
	{
		cParaAdd[0] = 0x32;
		cParaAdd[1] = 0x35;
		cParaAdd[2] = 0x30;
		cParaAdd[3] = 0x30;
		cParaData[0] = g_st_PDOBuffer.u8RPDOControlword[0];
		cParaData[1] = g_st_PDOBuffer.u8RPDOControlword[1];
		cParaData[2] = g_st_PDOBuffer.u8RPDOControlword[2];
		cParaData[3] = g_st_PDOBuffer.u8RPDOControlword[3];
		cParaData[4] = 0;
		cParaData[5] = 0;
		cParaData[6] = 0;
		cParaData[7] = 0;
		Writeselectnum = 1;
	}
	else if(writetype == Mode) // Mode.		Users can change the mode
	{
		cParaAdd[0] = 0x32;
		cParaAdd[1] = 0x35;
		cParaAdd[2] = 0x30;
		cParaAdd[3] = 0x31;
		cParaData[0] = GVL_cModevalue[0];
		cParaData[1] = GVL_cModevalue[1];
		cParaData[2] = GVL_cModevalue[2];
		cParaData[3] = GVL_cModevalue[3];
		cParaData[4] = 0;
		cParaData[5] = 0;
		cParaData[6] = 0;
		cParaData[7] = 0;
		Writeselectnum = 1;
	}
	else if(writetype == Vel_RPM) // Velocity Mode. Set Velocity RPM
	{
		cParaAdd[0] = 0x32;
		cParaAdd[1] = 0x33;
		cParaAdd[2] = 0x31;
		cParaAdd[3] = 0x34;
		cParaData[0] = g_u8bufVel_input_Rpmvalue[0];
		cParaData[1] = g_u8bufVel_input_Rpmvalue[1];
		cParaData[2] = g_u8bufVel_input_Rpmvalue[2];
		cParaData[3] = g_u8bufVel_input_Rpmvalue[3];
		cParaData[4] = 0;
		cParaData[5] = 0;
		cParaData[6] = 0;
		cParaData[7] = 0;
		Writeselectnum = 1;
	}
	else if(writetype == Ethercat) // Communication Mode change Ehtercat
	{
		cParaAdd[0] = 0x31;
		cParaAdd[1] = 0x36;
		cParaAdd[2] = 0x30;
		cParaAdd[3] = 0x30;
		cParaData[0] = 0x30;
		cParaData[1] = 0x30;
		cParaData[2] = 0x30;
		cParaData[3] = 0x30;
		cParaData[4] = 0x30;
		cParaData[5] = 0x30;
		cParaData[6] = 0x30;
		cParaData[7] = 0x38;
		Writeselectnum = 14;
	}
	else if(writetype == Serial)	//Communication Mode change Serial
	{
		cParaAdd[0] = 0x31;
		cParaAdd[1] = 0x36;
		cParaAdd[2] = 0x30;
		cParaAdd[3] = 0x30;
		cParaData[0] = 0x30;
		cParaData[1] = 0x30;
		cParaData[2] = 0x30;
		cParaData[3] = 0x30;
		cParaData[4] = 0x30;
		cParaData[5] = 0x30;
		cParaData[6] = 0x30;
		cParaData[7] = 0x30;
		Writeselectnum = 14;
	}
	else if(writetype == Pos_RPM) // Position Mode. Set rpm
	{
		cParaAdd[0] = 0x32;
		cParaAdd[1] = 0x45;
		cParaAdd[2] = 0x31;
		cParaAdd[3] = 0x45;
		cParaData[0] = g_u8bufPos_input_Rpmvalue[0];
		cParaData[1] = g_u8bufPos_input_Rpmvalue[1];
		cParaData[2] = g_u8bufPos_input_Rpmvalue[2];
		cParaData[3] = g_u8bufPos_input_Rpmvalue[3];
		cParaData[4] = 0x30;
		cParaData[5] = 0x30;
		cParaData[6] = 0x30;
		cParaData[7] = 0x30;
		Writeselectnum = 1;
	}
	else if(writetype == Pos_POS) // Position Mode.  Set Position
	{
		cParaAdd[0] = 0x32;
		cParaAdd[1] = 0x35;
		cParaAdd[2] = 0x31;
		cParaAdd[3] = 0x33;
		cParaData[0] = g_u8bufPos_input_Posvalue[0];
		cParaData[1] = g_u8bufPos_input_Posvalue[1];
		cParaData[2] = g_u8bufPos_input_Posvalue[2];
		cParaData[3] = g_u8bufPos_input_Posvalue[3];
		cParaData[4] = g_u8bufPos_input_Posvalue[4];
		cParaData[5] = g_u8bufPos_input_Posvalue[5];
		cParaData[6] = g_u8bufPos_input_Posvalue[6];
		cParaData[7] = g_u8bufPos_input_Posvalue[7];
		Writeselectnum = 2;
	}
	else if(writetype == Home_Pos) // Home Mode. Set position
	{
		cParaAdd[0] = 0x33;
		cParaAdd[1] = 0x31;
		cParaAdd[2] = 0x30;
		cParaAdd[3] = 0x30;
		cParaData[0] = g_u8bufHome_input_Posvalue[0];
		cParaData[1] = g_u8bufHome_input_Posvalue[1];
		cParaData[2] = g_u8bufHome_input_Posvalue[2];
		cParaData[3] = g_u8bufHome_input_Posvalue[3];
		cParaData[4] = g_u8bufHome_input_Posvalue[4];
		cParaData[5] = g_u8bufHome_input_Posvalue[5];
		cParaData[6] = g_u8bufHome_input_Posvalue[6];
		cParaData[7] = g_u8bufHome_input_Posvalue[7];
		Writeselectnum = 2;
	}
	cpWritereturn = KEB_WriteTransmitData(cAddress, cParaAdd, cParaData, Writeselectnum);
	return cpWritereturn;
}

uint8_t* SerialReadTx(uint8_t ReadDataSendStep)
{
	uint8_t keb_Readstep;
	Addresscalculation();
	switch(ReadDataSendStep)
	{

		case 0://st02 mode of operation display
			cParaAdd[0] = 0x32;
			cParaAdd[1] = 0x31;
			cParaAdd[2] = 0x30;
			cParaAdd[3] = 0x32;
			keb_Readstep = 1;
			break;
		case 1://st03 act velocity				//use Vel Mode
			cParaAdd[0] = 0x32;
			cParaAdd[1] = 0x31;
			cParaAdd[2] = 0x30;
			cParaAdd[3] = 0x33;
			keb_Readstep = 1;
			break;
		case 2://st12 state code				//use both Vel and Pos mode
			cParaAdd[0] = 0x32;
			cParaAdd[1] = 0x31;
			cParaAdd[2] = 0x30;
			cParaAdd[3] = 0x43;
			keb_Readstep = 1;
			break;
		case 3://st33 position actual value		//Position mode
			cParaAdd[0] = 0x32;
			cParaAdd[1] = 0x31;
			cParaAdd[2] = 0x32;
			cParaAdd[3] = 0x31;
			keb_Readstep = 2;
			break;
		case 4://st35 system count				//use both Pos and Vel Mode
			cParaAdd[0] = 0x32;
			cParaAdd[1] = 0x31;
			cParaAdd[2] = 0x32;
			cParaAdd[3] = 0x33;
			keb_Readstep = 1;
			break;
		case 5://ru01 error code				//use both Vel and Pos Mode
			cParaAdd[0] = 0x32;
			cParaAdd[1] = 0x43;
			cParaAdd[2] = 0x30;
			cParaAdd[3] = 0x31;
			keb_Readstep = 1;
			break;

		case 6: // ru04 supply unit state
			cParaAdd[0] = 0x32;
			cParaAdd[1] = 0x43;
			cParaAdd[2] = 0x30;
			cParaAdd[3] = 0x34;
			keb_Readstep = 1;
			break;

		case 7: // ru18 dig.input state
			cParaAdd[0] = 0x32;
			cParaAdd[1] = 0x43;
			cParaAdd[2] = 0x31;
			cParaAdd[3] = 0x32;
			keb_Readstep = 1;
			break;

		case 8://vl20 Target velocity(set value)	//use Vel Mode
			cParaAdd[0] = 0x32;
			cParaAdd[1] = 0x33;
			cParaAdd[2] = 0x31;
			cParaAdd[3] = 0x34;
			keb_Readstep = 1;
			break;

		case 9://ps30 profile velocity (set value)	//Position mode
			cParaAdd[0] = 0x32;
			cParaAdd[1] = 0x45;
			cParaAdd[2] = 0x31;
			cParaAdd[3] = 0x45;
			keb_Readstep = 1;
			break;

		case 10://co19 target position				//Position mode
			cParaAdd[0] = 0x32;
			cParaAdd[1] = 0x35;
			cParaAdd[2] = 0x31;
			cParaAdd[3] = 0x33;
			keb_Readstep = 3;
			break;

		case 11://pr 1st receive PDO maapping(count)
			cParaAdd[0] = 0x31;
			cParaAdd[1] = 0x36;
			cParaAdd[2] = 0x30;
			cParaAdd[3] = 0x30;
			keb_Readstep = 15;
			break;

		case 12://hm05 digital inputs(Limit witch)
			cParaAdd[0] = 0x33;
			cParaAdd[1] = 0x31;
			cParaAdd[2] = 0x30;
			cParaAdd[3] = 0x35;
			keb_Readstep = 1;
			break;

		case 13: //st14 active controlword
			cParaAdd[0] = 0x32;
			cParaAdd[1] = 0x31;
			cParaAdd[2] = 0x30;
			cParaAdd[3] = 0x45;
			keb_Readstep = 1;
			break;

		case 14: //hm00 home offset
			cParaAdd[0] = 0x33;
			cParaAdd[1] = 0x31;
			cParaAdd[2] = 0x30;
			cParaAdd[3] = 0x30;
			keb_Readstep = 3;
			break;
		case 15: //st04 brkae ctrl status
			cParaAdd[0] = 0x32;
			cParaAdd[1] = 0x31;
			cParaAdd[2] = 0x30;
			cParaAdd[3] = 0x34;
			keb_Readstep = 1;

	}
	cpReadreturn = KEB_ReadTrasmitdata(cAddress, cParaAdd, keb_Readstep);
	return cpReadreturn;
}



