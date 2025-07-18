/*
 * KEB_CAN_Func.c
 *
 *  Created on: Nov 22, 2024
 *      Author: LEEMINKOO
 */

#include <KEB_CAN_Func_Copy.hpp>

void KEB_CAN_FUNC::KEB_CAN_Func_32dectohex(int idecvalue, uint8_t* uiarryhex, uint8_t num)
{
	uint8_t i;
	for(i = 0; i < num; i++)
	{
		uiarryhex[i] = (idecvalue >> ((num - 1 - i) * 8)) & 0xFF;
	}
}

void KEB_CAN_FUNC::KEB_CAN_Func_Controlword_dectohex(int idecvalue, uint8_t* uiarryhex)
{
	uiarryhex[0] = (idecvalue >> 8) & 0xFF;
	uiarryhex[1] = idecvalue & 0xFF;
}


uint16_t KEB_CAN_FUNC::KEB_CAN_Func_hexto16uint(uint8_t* uiarryhex, uint8_t num)
{

	uint16_t dec = 0;
	uint8_t i = 0;

	for(i = 0; i < num ; i++)
	{
		dec |= (uiarryhex[i] << ((num - 1 - i) * 8));
	}
	return dec;
}

void KEB_CAN_FUNC::KEB_CAN_Func_reverse_array(uint8_t *uiarryhex, uint8_t Num)
{
	uint8_t temp = 0;//uint8_t *temp = 0;
	uint8_t cnt;
	if(Num == 0 && (Num % 2  != 0))
	{
		return;
	}
	else
		cnt = Num / 2;
	for (uint8_t i = 0; i < cnt; i++)
	{
		temp = uiarryhex[i];
		uiarryhex[i] = uiarryhex[Num - 1];
		uiarryhex[Num - 1] = temp;
		Num = Num - 1;
	}
}

int KEB_CAN_FUNC::KEB_CAN_Func_hexto32dec(uint8_t* uiarryhex, uint8_t num)
{
	int dec = 0;
	uint8_t i = 0;
	//dec = uiarryhex[0] << 24 | uiarryhex[1] << 16 | uiarryhex[2] << 8 | uiarryhex[3];
	for(i = 0; i < num ; i++)
	{
		dec |= (uiarryhex[i] << ((num - 1 - i) * 8));
	}
	return dec;
}
void KEB_CAN_FUNC::KEB_CAN_Stateword(uint16_t u16dec, char *StateString)
{
	strcpy(StateString, "");

	bool first = true;

    auto append = [&](const char *text) {
        if (!first) strcat(StateString, "+");
        strcat(StateString, text);
        first = false;
    };

	if (u16dec & (1 << 0)) append("RSO");//"[Ready to switch on] ");
	if (u16dec & (1 << 1)) append("SO");//"[Switched on] ");
	if (u16dec & (1 << 2)) append("OE");//"[Operation enabled] ");
	if (u16dec & (1 << 3)) append("F");//"[Fault] ");
	if (u16dec & (1 << 4)) append("V");//"[Voltage enabled] ");
	if (!(u16dec & (1 << 5))) append("Q"); //"[Quick stop active] "); // 0이면 Quick Stop Active
	if (u16dec & (1 << 6)) append("SW");//"[Switch on disabled] ");
	if (u16dec & (1 << 7)) append("W");//"[Warning] ");
	if (u16dec & (1 << 8)) append("SY");//"[Synchronous] ");
	if (u16dec & (1 << 10)) append("TR");//"[Target reached] ");
	if (u16dec & (1 << 11)) append("L");//"[Internal limit active] ");
	if (u16dec & (1 << 12)) append("O12");//"[Op. mode spec 12] ");
	if (u16dec & (1 << 13)) append("O13");//"[Op. mode spec 13] ");
	if (u16dec & (1 << 14)) append("M14");//"[Manufacturer spec 14] ");
	if (u16dec & (1 << 15)) append("BS");//"[Braking state] ");

	if (strlen(StateString) == 0) {
		strcpy(StateString, "Unknown state");
	}
}

void KEB_CAN_FUNC::KEB_CAN_ModeState(uint16_t dec, char *StateString)
{
	if(dec == 0)
		strcpy(StateString, "NO MODE");
	else if(dec == 1)
		strcpy(StateString, "POSITION");
	else if(dec == 2)
		strcpy(StateString, "VELOCITY");
	else if(dec == 6)
		strcpy(StateString, "HOMING");
	else if(dec == 8)
		strcpy(StateString, "CYCL,SYNC POS");
	else if(dec == 8)
		strcpy(StateString, "CYCL,SYNC VEL");
	else if(dec == 8)
		strcpy(StateString, "CYCL,SYNC TOR");
}

void KEB_CAN_FUNC::KEB_CAN_errorcode(uint8_t dec, char *StateString)
{
	if (dec == 0)		// 0
		strcpy(StateString, "no exception");
	else if (dec == 3)// 3
		strcpy(StateString, "overcurrent PU");
	else if (dec == 4)// 4
		strcpy(StateString, "overcurrent analog");
	else if (dec == 5)// 5
		strcpy(StateString,"over potential");
	else if (dec == 6)// 6
		strcpy(StateString, "under potential");
	else if (dec == 7)// 7
		strcpy(StateString, "overload");
	else if (dec == 8)// 8
		strcpy(StateString, "reset E. overload");
	else if (dec == 9)// 9
		strcpy(StateString, "overload 2");
	else if (dec == 10)// 10
		strcpy(StateString, "overheat powmod.");
	else if (dec == 11)// 11
		strcpy(StateString, "reset E overheat pmod.");
	else if (dec == 12)// 12
		strcpy(StateString, "overheat internal PU");
	else if (dec == 13)// 13
		strcpy(StateString, "reset E. overheat intern PU");
	else if (dec == 14)// 14
		strcpy(StateString, "motorprotection");
	else if (dec == 15)// 15
		strcpy(StateString, "reset E. motorprotection");
	else if (dec == 16)// 16
		strcpy(StateString, "drive overheat");
	else if (dec == 17)// 17
		strcpy(StateString, "reset ERROR drive overheat");
	else if (dec == 18)// 18
		strcpy(StateString, "overspeed");
	else if (dec == 20)// 20
		strcpy(StateString, "drive data");
	else if (dec == 21)// 21
		strcpy(StateString, "motordata not stored ");
	else if (dec == 22)// 22
		strcpy(StateString, " ident ");
	else if (dec == 23)// 23
		strcpy(StateString, "ERROR speed diff");
	else if (dec == 24)// 24
		strcpy(StateString, "fieldbus memory");
	else if (dec == 25)// 38
		strcpy(StateString, "memory size");
	else if (dec == 40)// 40
		strcpy(StateString, "FPGA conf.");
	else if (dec == 41)// 41
		strcpy(StateString, "safety module SACB comm");
	else if (dec == 42)// 42
		strcpy(StateString, "power unit SACB comm ");
	else if (dec == 43)// 43
		strcpy(StateString, "enc.intf. SACB comm.");
	else if (dec == 44)// 44
		strcpy(StateString, "invalid power unit data");
	else if (dec == 47)// 47
		strcpy(StateString, "power unit flash");
	else if (dec == 52)// 52
		strcpy(StateString, "undervoltage phase");
	else if (dec == 55)// 55
		strcpy(StateString, "ERROR safety");
	else if (dec == 56)// 56
		strcpy(StateString, "software switch left");
	else if (dec == 57)// 57
		strcpy(StateString, "software switch right");
	else if (dec == 58)//58
		strcpy(StateString, "fieldbus watchdog");
	else if (dec == 59)//59
		strcpy(StateString, "prg. input");
	else if (dec == 60)//60
		strcpy(StateString, "safety module type changed");
	else if (dec == 61)//61
		strcpy(StateString, "safety module changed");
	else if (dec == 62)//62
		strcpy(StateString, "Power unit changed");
	else if (dec == 63)//63
		strcpy(StateString, "enc. intf. changed");
	else if (dec == 64)//64
		strcpy(StateString, "power unit type changed");
	else if (dec == 65)//65
		strcpy(StateString, "enc. intf. version");
	else if (dec == 66)//66
		strcpy(StateString, "overcurrent PU");
	else if (dec == 67)//67
		strcpy(StateString, "max acc/dec");
	else if (dec == 68)//68
		strcpy(StateString, "overcurrent Brake");
	else if (dec == 83)//83
		strcpy(StateString, "Limit Switch Forward");
	else if (dec == 84)//84
		strcpy(StateString, "Limit Switch Reverse");
	else if (dec == 85)//85
		strcpy(StateString, "Override Limit Switch For￾ward");
	else if (dec == 86)//86
		strcpy(StateString, "Override Limit Switch Re￾verse");
	else if (dec == 87)//87
		strcpy(StateString, "Limit Switch");
	else if (dec == 89)//89
		strcpy(StateString, "at encoder type change");
	else if (dec == 90)//90
		strcpy(StateString, "enc.intf.fast comm.");
	else if (dec == 91)//91
		strcpy(StateString, "encoder interface");
	else if (dec == 92)//92
		strcpy(StateString, "encoder A");
	else if (dec == 93)//93
		strcpy(StateString, "encoder B");
	else if (dec == 94)//94
		strcpy(StateString, "init encoder A");
	else if (dec == 95)//95
		strcpy(StateString, "init encoder B");
	else if (dec == 96)//96
		strcpy(StateString, "encoder missing");
	else if (dec == 97)//97
		strcpy(StateString, "overspeed (EMF)");
	else if (dec == 98)//98
		strcpy(StateString, "encoder A changed");
	else if (dec == 99)//99
		strcpy(StateString, "encoder B changed");
	else if (dec == 100)//100
		strcpy(StateString, "overcurrent out1");
	else if (dec == 101)//101
		strcpy(StateString, "overcurrent out2");
	else if (dec == 102)//102
		strcpy(StateString, "overcurrent out3");
	else if (dec == 103)//103
		strcpy(StateString, "overcurrent out4");
	else if (dec == 105)//105
		strcpy(StateString, "overcurrent encoder");
	else if (dec == 106)//106
		strcpy(StateString, "overcurrent 24V");
	else if (dec == 107)//107
		strcpy(StateString, "over frequency");
	else if (dec == 108)//108
		strcpy(StateString, "reset E. overheat intern CB");
	else if (dec == 109)//109
		strcpy(StateString, "overheat internal CB ");
	else if (dec == 110)//110
		strcpy(StateString, "OH ramp");
	else if (dec == 111)//111
		strcpy(StateString, "OHI ramp");
	else if (dec == 112)//112
		strcpy(StateString, "24V supply low");
	else if (dec == 115)//115
		strcpy(StateString, "GTR7 always OFF");
	else if (dec == 116)//116
		strcpy(StateString, "GTR7 OC");
	else if (dec == 117)//117
		strcpy(StateString, "GTR7 always ON");
	else if (dec == 118)//118
		strcpy(StateString, "OC at 5V diag");
	else if (dec == 119)//119
		strcpy(StateString, "extreme overpotential");
	else if (dec == 120)//120
		strcpy(StateString, "DC capacitor damaged");
	else if (dec == 121)//121
		strcpy(StateString, "runtime");
	else if (dec == 122)//122
		strcpy(StateString, "UP2");
	else if (dec == 123)//123
		strcpy(StateString, "LT ready");
	else if (dec == 124)//124
		strcpy(StateString, "General Fielbus Error");
	else if (dec == 125)//125
		strcpy(StateString, "fieldbus type changed");
	else if (dec == 126)//126
		strcpy(StateString, "overheat 2 powmod.");
	else if (dec == 127)//127
		strcpy(StateString, "reset E. overheat 2 pmod.");
	else if (dec == 128)//128
		strcpy(StateString, "overheat 3 powmod.");
	else if (dec == 129)//129
		strcpy(StateString, "reset E. overheat 3 pmod.");
	else if (dec == 130)//130
		strcpy(StateString, "overheat 2 internal");
	else if (dec == 131)//131
		strcpy(StateString, "reset E. overheat 2 intern");
	else if (dec == 132)//132
		strcpy(StateString, "overheat 3 internal");
	else if (dec == 133)//133
		strcpy(StateString, "reset E. overheat 3 intern");
	else if (dec == 134)//134
		strcpy(StateString, "Safety Stop");
	else if (dec == 135)//135
		strcpy(StateString, "File Code");
	else if (dec == 136)//136
		strcpy(StateString, "blockade detected");
	else if (dec == 139)//139
		strcpy(StateString, "STO");
	else if (dec == 140)//140
		strcpy(StateString, "Fail Safe");
	else if (dec == 141)//141
		strcpy(StateString, "Control hardware type");
	else if (dec == 142)//142
		strcpy(StateString, "142 ERROR");
	else if (dec == 144)//144
		strcpy(StateString, "overheat braking resistor");
	else if (dec == 145)//145
		strcpy(StateString, "invalid resistor data");
	else if (dec == 146)//146
		strcpy(StateString, "analog input 4..20mA");
	else if (dec == 147)//147
		strcpy(StateString, "147 ERROR");
	else if (dec == 148)//148
		strcpy(StateString, "phase check");
}

void KEB_CAN_FUNC::KEB_CAN_ModeChange(bool& u8ModeWrite, int8_t& s8TouchMode, int8_t& s8RPDOMode,int8_t& s8InvModeState)
{
	static uint8_t u8Modestep = 0;

	switch(u8Modestep)
	{
	case 0://Touchgfx에서 화면전환 및 모드 버튼 클릭시 step : 10, IPC,COMBIVIS에서 Mode 바꿀씨 Step : 20
		if(u8ModeWrite == true)
			u8Modestep = 10;
		else if((s8InvModeState != s8TouchMode) && (u8ModeWrite == false))
			u8Modestep = 20;
		break;
	case 10:
		s8RPDOMode = s8TouchMode;
		if(s8InvModeState == s8RPDOMode)
		{
			u8ModeWrite = false;
			u8Modestep = 0;
		}
		break;
	case 20:
		s8TouchMode = s8InvModeState;
		s8RPDOMode = s8TouchMode;
		u8Modestep = 21;
		break;
	case 21:
		if(s8InvModeState == s8RPDOMode)
			u8Modestep = 0;
		else
			u8Modestep = 20;
		break;
	}
}

