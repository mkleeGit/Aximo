/*
 * KEB_PROTOCAL.c
 *
 *  Created on: Mar 12, 2024
 *      Author: Lee
 */

#include <KEB_PROTOCAL.h>

uint8_t cEOT = 0x04;
uint8_t cSTX = 0x02;
uint8_t cETX = 0x03;
uint8_t cENQ = 0x05;
uint8_t cSubindex[2] = {0x30, 0x30};



uint8_t KEB_BccXOR(uint8_t* ParaAdd, uint8_t* ParaData, uint8_t BccStep, uint8_t IID, uint8_t Service)
{
	int Num = 0;
	static char Data[20];
	char XorData = ' ';
	for(Num = 0; Num < sizeof(Data); Num++)
	{
		Data[Num] = NULL;
	}
	switch(BccStep)
	{
		case 0 :
			break;
		case 1 :
			for(Num = 0; Num < 8; Num++)
			{
				if (Num < 4)
					Data[Num] = ParaAdd[Num];		//Address[0..3]
				else
					Data[Num] = ParaData[Num-4];	//Data[0..3]
			}

			XorData = Data[0] ^ Data[1];

			for(Num = 2; Num <8; Num++)
				XorData = XorData ^ Data[Num];

			XorData = XorData ^ cETX;			// XorData ^ ETX(0x03)

			if (XorData < 0x20)					// XorData < 0x20 경우 	XorData	+ 0x20을 해줘야함  Xordata > 0x20 경우 그대로 리턴
				XorData = XorData + 0x20;

			break;
		case 2 : //Service 0/1 : Reading a parameter value(extended/standard set addressing) BCC CODE
			for(Num = 0; Num < 4; Num++)
			{
				Data[Num] = ParaAdd[Num];		//Address[0..3]
			}
			XorData = Service ^ IID; // Service(0x47) XOR IID '1'(0x31)

			for(Num = 0; Num < 4; Num++)
			{
				XorData = XorData ^ Data[Num];
			}

			XorData = XorData ^ 0x30;//Set ASCII '0'(0x30);
			XorData = XorData ^ 0x31;//Set ASCII '1'(0x31);
			XorData = XorData ^ 0x05;//ENQ 05h(0x05);
			if (XorData < 0x20)		// XorData < 0x20 경우 	XorData	+ 0x20을 해줘야함  Xordata > 0x20 경우 그대로 리턴
				XorData = XorData + 0x20;
			break;

		case 3 : //Service 0/1 : Writing a parameter value
			for(Num = 0; Num < 12; Num++)
			{
				if (Num < 4)
					Data[Num] = ParaAdd[Num];		//Address[0..3]
				else
					Data[Num] = ParaData[Num-4];	//Data[0..7]
			}
			XorData = Service ^ IID; // Service XOR IID

			for(Num = 0; Num < 12; Num++)
			{
				XorData = XorData ^ Data[Num];
			}

			XorData = XorData ^ 0x30;//Set ASCII '0'(0x30);
			XorData = XorData ^ 0x31;//Set ASCII '1'(0x31);
			XorData = XorData ^ 0x03;//ETX 03h(0x03);
			if (XorData < 0x20)		// XorData < 0x20 경우 	XorData	+ 0x20을 해줘야함  Xordata > 0x20 경우 그대로 리턴
				XorData = XorData + 0x20;
			break;

		case 14 :
			for(Num = 0; Num < 16; Num++)
			{
				if(Num == 0)						//Data[0] = 0x55;
					Data[Num] = 0x55;				// Service 'U' <- 0x55
				else if(Num == 1)
					Data[Num] = 0x32;				//IID = '2'
				else if(Num > 1 && Num < 6)				//Data[2] = ParaAdd[0], Data[3] = ParaAdd[1], Data[4] = ParaAdd[2], Data[5] = ParaAdd[3]
					Data[Num] = ParaAdd[Num-2];
				else if(Num >= 6 && Num < 14)				//Data[6] = ParaData[0], Data[7] = ParaData[1], Data[8] = ParaData[2],Data[9] = ParaData[3],
					Data[Num] = ParaData[Num-6];				//Data[10] = ParaData[4], Data[11] = ParaData[5],Data[12] = ParaData[6], Data[13] = ParaData[7]
				else if(Num >= 14 && Num < 16)
					Data[Num] = cSubindex[Num-14];			//Data[14] = Subindex[0], Data[15] = Subindex[1]
			}

			XorData = Data[0] ^ Data[1];

			for(Num = 2; Num < 16; Num++)
				XorData = XorData ^ Data[Num];

			XorData = XorData ^ cETX;			// XorData ^ ETX(0x03)

			if (XorData < 0x20)
				XorData = XorData + 0x20;		// XorData < 0x20 경우 	XorData	+ 0x20을 해줘야함  Xordata > 0x20 경우 그대로 리턴
			break;
		case 15:
			for(Num = 0; Num < 16; Num++)
			{
				if(Num == 0)						//Data[0] = 0x55;
					Data[Num] = 0x55;				// Service 'U' <- 0x55
				else if(Num == 1)
					Data[Num] = 0x31;				//IID = '1'
				else if(Num > 1 && Num < 6)				//Data[2] = ParaAdd[0], Data[3] = ParaAdd[1], Data[4] = ParaAdd[2], Data[5] = ParaAdd[3]
					Data[Num] = ParaAdd[Num-2];
				else if(Num >= 6 && Num < 8)
					Data[Num] = cSubindex[Num-6];			//Data[6] = Subindex[0], Data[7] = Subindex[1]
			}

			XorData = Data[0] ^ Data[1];

			for(Num = 2; Num < 8; Num++)
				XorData = XorData ^ Data[Num];

			XorData = XorData ^ cENQ;			// XorData ^ ENQ(0x05)

			if (XorData < 0x20)
				XorData = XorData + 0x20;		// XorData < 0x20 경우 	XorData	+ 0x20을 해줘야함  Xordata > 0x20 경우 그대로 리턴
			break;
	}

	return XorData;
}

uint8_t* KEB_WriteParameterData(uint16_t usiData)
{
	int Num = ' ';
	static char WriteParaData[4];
	WriteParaData[0] = (usiData >> 12);
	WriteParaData[1] = (usiData >> 8 & 0x0F);
	WriteParaData[2] = (usiData >> 4 & 0x0F);
	WriteParaData[3] = (usiData & 0x0F);
	for(Num = 0; Num <4; Num++)
	{
		if ((WriteParaData[Num] + 0x30) <= 0x39)
			WriteParaData[Num] = WriteParaData[Num] + 0x30;
		else if((WriteParaData[Num] + 0x37) > 0x39)
			WriteParaData[Num] = WriteParaData[Num] + 0x37;
	}
}

uint8_t* KEB_ReadTrasmitdata(uint8_t* cReadAddress, uint8_t* cReadParaAddress, uint8_t ReadTransStep)
 {
	char *BccCode;
	static char ReadTxData[40];
	switch(ReadTransStep)
	{
	case 0:
		break;
	case 1:
		ReadTxData[0] = cEOT;				//EOT
		ReadTxData[1] = cReadAddress[0];		//Address
		ReadTxData[2] = cReadAddress[1];		//Address
		ReadTxData[3] = cReadParaAddress[0];	//PARAMETER |[0]|   |   |   |
		ReadTxData[4] = cReadParaAddress[1];	//PARAMETER |[0]|[1]|   |   |
		ReadTxData[5] = cReadParaAddress[2];	//PARAMETER |[0]|[1]|[2]|   |
		ReadTxData[6] = cReadParaAddress[3];	//PARAMETER |[0]|[1]|[2]|[3]|
		ReadTxData[7] = cENQ;
		break;
	case 2:
		BccCode = KEB_BccXOR(cReadParaAddress, 0, 2, 0x31, 0x47);
		ReadTxData[0] = cEOT;				//EOT
		ReadTxData[1] = cReadAddress[0];	//Address
		ReadTxData[2] = cReadAddress[1];	//Address
		ReadTxData[3] = 0x47;				//Service 'G' <- 0x47 OR Service 'H' <- 0x48
		ReadTxData[4] = 0x31;				// IID = '1' <- 0x31
		ReadTxData[5] = cReadParaAddress[0];
		ReadTxData[6] = cReadParaAddress[1];
		ReadTxData[7] = cReadParaAddress[2];
		ReadTxData[8] = cReadParaAddress[3];
		ReadTxData[9] = 0x30;//Set ASCII;
		ReadTxData[10] = 0x31;//Set ASCII;
		ReadTxData[11] = cENQ;
		ReadTxData[12] = BccCode;
		break;
	case 3:
		BccCode = KEB_BccXOR(cReadParaAddress, 0, 2, 0x31, 0x48);
		ReadTxData[0] = cEOT;				//EOT
		ReadTxData[1] = cReadAddress[0];	//Address
		ReadTxData[2] = cReadAddress[1];	//Address
		ReadTxData[3] = 0x48;				//Service 'G' <- 0x47 OR Service 'H' <- 0x48
		ReadTxData[4] = 0x31;				// IID = '1' <- 0x31
		ReadTxData[5] = cReadParaAddress[0];
		ReadTxData[6] = cReadParaAddress[1];
		ReadTxData[7] = cReadParaAddress[2];
		ReadTxData[8] = cReadParaAddress[3];
		ReadTxData[9] = 0x30;//Set ASCII;
		ReadTxData[10] = 0x31;//Set ASCII;
		ReadTxData[11] = cENQ;
		ReadTxData[12] = BccCode;
		break;
	case 15:
		BccCode = KEB_BccXOR(cReadParaAddress, 0, 15, 0x31, 0x55);
		ReadTxData[0] = cEOT;
		ReadTxData[1] = cReadAddress[0];
		ReadTxData[2] = cReadAddress[1];
		ReadTxData[3] = 0x55;
		ReadTxData[4] = 0x31;
		ReadTxData[5] = cReadParaAddress[0];
		ReadTxData[6] = cReadParaAddress[1];
		ReadTxData[7] = cReadParaAddress[2];
		ReadTxData[8] = cReadParaAddress[3];
		ReadTxData[9] = 0x30;
		ReadTxData[10] = 0x30;
		ReadTxData[11] = cENQ;
		ReadTxData[12] = BccCode;
		break;

	}

	return ReadTxData;
}

uint8_t* KEB_WriteTransmitData(uint8_t* cWriteAddress, uint8_t* cWriteParaAddress, uint8_t* cWriteParadata, uint8_t WriteTransStep)
{
	//char Para_st01[4] = {0x32, 0x31, 0x30, 0x45};	//
	//char Para_ru08[4] = {0x32, 0x43, 0x30, 0x38};	//Read		ActPosition
	//char Para_vl20[4] = {0x32, 0x33, 0x31, 0x34};	//Write		Set Velocity
	//char Para_co01[4] = {0x32, 0x35, 0x30, 0x31};	//
	static char WriteTxData[22];
	bool Normal;
	int Num;
	int step = 0;
	char *BccCode;
	switch(WriteTransStep)
	{
	case 0:
		break;
	case 1:		// Writing a parameter
		BccCode = KEB_BccXOR(cWriteParaAddress, cWriteParadata, 1,0,0);
		WriteTxData[0] = cEOT;				//EOT
		WriteTxData[1] = cWriteAddress[0];		//Address
		WriteTxData[2] = cWriteAddress[1];		//Address
		WriteTxData[3] = cSTX;				//STX
		WriteTxData[4] = cWriteParaAddress[0];	//PARAMETER |[0]|   |   |   |
		WriteTxData[5] = cWriteParaAddress[1];	//PARAMETER |[0]|[1]|   |   |
		WriteTxData[6] = cWriteParaAddress[2];	//PARAMETER |[0]|[1]|[2]|   |
		WriteTxData[7] = cWriteParaAddress[3];	//PARAMETER |[0]|[1]|[2]|[3]|
		WriteTxData[8] = cWriteParadata[0];		//PARA DATA
		WriteTxData[9] = cWriteParadata[1];		//PARA DATA
		WriteTxData[10] = cWriteParadata[2];		//PARA DATA
		WriteTxData[11] = cWriteParadata[3];		//PARA DATA
		WriteTxData[12] = cETX;				//ETX
		WriteTxData[13] = BccCode;			//BCC
		break;
	case 2:	 //Service 0/1 : Writing a parameter value (extended/standard set addressing)
		BccCode = KEB_BccXOR(cWriteParaAddress,cWriteParadata, 3, 0x32, 0x47);
		WriteTxData[0] = cEOT;
		WriteTxData[1] = cWriteAddress[0];
		WriteTxData[2] = cWriteAddress[1];
		WriteTxData[3] = cSTX;
		WriteTxData[4] = 0x47; //Service 'G' <- 0x47 OR Service 'H' <- 0x48
		WriteTxData[5] = 0x32; // IID = '2' <- 0x32
		WriteTxData[6] = cWriteParaAddress[0];
		WriteTxData[7] = cWriteParaAddress[1];
		WriteTxData[8] = cWriteParaAddress[2];
		WriteTxData[9] = cWriteParaAddress[3];
		WriteTxData[10] = cWriteParadata[0];
		WriteTxData[11] = cWriteParadata[1];
		WriteTxData[12] = cWriteParadata[2];
		WriteTxData[13] = cWriteParadata[3];
		WriteTxData[14] = cWriteParadata[4];
		WriteTxData[15] = cWriteParadata[5];
		WriteTxData[16] = cWriteParadata[6];
		WriteTxData[17] = cWriteParadata[7];
		WriteTxData[18] = 0x30;//Set ASCII '0'
		WriteTxData[19] = 0x31;//Set ASCII '1'
		WriteTxData[20] = cETX;
		WriteTxData[21] = BccCode;
		break;
	case 14 :	// Service 14 : Writing a parameter value(suindex addressing)
		BccCode = KEB_BccXOR(cWriteParaAddress, cWriteParadata, 14, 0, 0);
		WriteTxData[0] = cEOT;
		WriteTxData[1] = cWriteAddress[0];
		WriteTxData[2] = cWriteAddress[1];
		WriteTxData[3] = cSTX;
		WriteTxData[4] = 0x55; //Service 'U' <- 0x55
		WriteTxData[5] = 0x32; // IID = '2' <- 0x32
		WriteTxData[6] = cWriteParaAddress[0];
		WriteTxData[7] = cWriteParaAddress[1];
		WriteTxData[8] = cWriteParaAddress[2];
		WriteTxData[9] = cWriteParaAddress[3];
		WriteTxData[10] = cWriteParadata[0];
		WriteTxData[11] = cWriteParadata[1];
		WriteTxData[12] = cWriteParadata[2];
		WriteTxData[13] = cWriteParadata[3];
		WriteTxData[14] = cWriteParadata[4];
		WriteTxData[15] = cWriteParadata[5];
		WriteTxData[16] = cWriteParadata[6];
		WriteTxData[17] = cWriteParadata[7];
		WriteTxData[18] = cSubindex[0];
		WriteTxData[19] = cSubindex[1];
		WriteTxData[20] = cETX;
		WriteTxData[21] = BccCode;
		break;
	}
	return WriteTxData;
}
void KEB_StateBuf(uint8_t* uiBuffer,uint16_t uiBufsize, uint8_t* StateString)
{
	int i = 0;
	for(i = 0; i < uiBufsize; i++)
	{
		if(uiBuffer[i] == 0x02 && uiBuffer[i + 9] == 0x03){
			if (uiBuffer[i+1] == 0x32 && uiBuffer[i+2] == 0x31 && uiBuffer[i+3] == 0x30 && uiBuffer[i+4] == 0x43){
				memcpy(StateString, uiBuffer + (i + 5), 4);
				break;
			}
		}
	}
}
void KEB_ErrorBuf(uint8_t* uiBuffer,uint16_t uiBufsize, uint8_t* StateString)
{
	int i = 0;
	for(i = 0; i < uiBufsize; i++)
	{
		if(uiBuffer[i] == 0x02 && uiBuffer[i + 9] == 0x03){
			if (uiBuffer[i + 1] == 0x32 && uiBuffer[i + 2] == 0x43 && uiBuffer[i + 3] == 0x30 && uiBuffer[i + 4] == 0x31){
				memcpy(StateString, uiBuffer + (i + 5), 4);
				break;
			}
		}
	}
}
void KEB_ModeBuf(uint8_t* uiBuffer,uint16_t uiBufsize, uint8_t* StateString)
{
	int i = 0;
	for(i = 0; i < uiBufsize; i++)
	{
		if(uiBuffer[i] == 0x02 && uiBuffer[i + 9] == 0x03){
			if (uiBuffer[i + 1] == 0x32 && uiBuffer[i + 2] == 0x31 && uiBuffer[i + 3] == 0x30 && uiBuffer[i + 4] == 0x32){
				memcpy(StateString, uiBuffer + (i + 5), 4);
				break;
			}
		}
	}
}
void KEB_SupplyBuf(uint8_t* uiBuffer,uint16_t uiBufsize, uint8_t* StateString)
{
	int i = 0;
	for(i = 0; i < uiBufsize; i++)
	{
		if(uiBuffer[i] == 0x02 && uiBuffer[i + 9] == 0x03){
			if(uiBuffer[i + 1] == 0x32 && uiBuffer[i + 2] == 0x43 && uiBuffer[i + 3] == 0x30 && uiBuffer[i + 4] == 0x34){
				memcpy(StateString, uiBuffer + (i + 5), 4);
				break;
			}
		}
	}
}
void KEB_STOBuf(uint8_t* uiBuffer,uint16_t uiBufsize, uint8_t* StateString)
{
	int i = 0;
	for(i = 0; i < uiBufsize; i++)
	{
		if(uiBuffer[i] == 0x02 && uiBuffer[i + 9] == 0x03){
			if(uiBuffer[i + 1] == 0x32 && uiBuffer[i + 2] == 0x43 && uiBuffer[i + 3] == 0x31 && uiBuffer[i + 4] == 0x32){
				memcpy(StateString, uiBuffer + (i + 5), 4);
				break;
			}
		}
	}
}

void KEB_StateMachineDisplay(uint8_t* uiBuffer, uint16_t uiBufsize, char *StateString)
{
	int i = 0;
	for(i = 0; i < uiBufsize; i++)
	{
		if(uiBuffer[i] == 0x02 && uiBuffer[i + 9] == 0x03){
			if (uiBuffer[i+1] == 0x32 && uiBuffer[i+2] == 0x31 && uiBuffer[i+3] == 0x30 && uiBuffer[i+4] == 0x43)
				break;
		}
	}
	if (uiBuffer[i+1] == 0x32 && uiBuffer[i+2] == 0x31 && uiBuffer[i+3] == 0x30 && uiBuffer[i+4] == 0x43) {
		if (uiBuffer[i+5] == 0x30 && uiBuffer[i+6] == 0x30) {
			if (uiBuffer[i+7] == 0x30 && uiBuffer[i+8] == 0x30)
				strcpy(StateString,"Initialization");
			else if (uiBuffer[i+7] == 0x30 && uiBuffer[i+8] == 0x31)
				strcpy(StateString,"not ready to switch on");
			else if (uiBuffer[i+7] == 0x30 && uiBuffer[i+8] == 0x32)
				strcpy(StateString, "switch on disable");
			else if (uiBuffer[i+7] == 0x30 && uiBuffer[i+8] == 0x33)
				strcpy(StateString, "ready to switch on");
			else if (uiBuffer[i+7] == 0x30 && uiBuffer[i+8] == 0x34)
				strcpy(StateString, "switched on");
			else if (uiBuffer[i+7] == 0x30 && uiBuffer[i+8] == 0x35)
				strcpy(StateString, "operation enabled");
			else if (uiBuffer[i+7] == 0x30 && uiBuffer[i+8] == 0x36)
				strcpy(StateString, "Quick stop active");
			else if (uiBuffer[i+7] == 0x30 && uiBuffer[i+8] == 0x37)
				strcpy(StateString, "fault reaction active");
			else if (uiBuffer[i+7] == 0x30 && uiBuffer[i+8] == 0x38)
				strcpy(StateString,"fault");
			else if (uiBuffer[i+7] == 0x30 && uiBuffer[i+8] == 0x39)
				strcpy(StateString, "Shutdown active");
			else if (uiBuffer[i+7] == 0x31 && uiBuffer[i+8] == 0x30)
				strcpy(StateString, "disable operation active");
			else if (uiBuffer[i+7] == 0x31 && uiBuffer[i+8] == 0x31)
				strcpy(StateString, "start operation active");
			else if (uiBuffer[i+7] == 0x31 && uiBuffer[i+8] == 0x32)
				strcpy(StateString, "mod off pause active");
			else if (uiBuffer[i+7] == 0x31 && uiBuffer[i+8] == 0x33)
				strcpy(StateString, "power Off");
			else if (uiBuffer[i+7] == 0x31 && uiBuffer[i+8] == 0x34)
				strcpy(StateString, "protection time active");
			else if (uiBuffer[i+7] == 0x31 && uiBuffer[i+8] == 0x35)
				strcpy(StateString, "protection time end");
			else if (uiBuffer[i+7] == 0x31 && uiBuffer[i+8] == 0x36)
				strcpy(StateString, "endless protection time");
			else if (uiBuffer[i+7] == 0x31 && uiBuffer[i+8] == 0x37)
				strcpy(StateString, "suppressed error");
		}
	}
}

void KEB_errorcode(uint8_t* uiBuffer, uint16_t uiBufsize, char *StateString)
{
	int i = 0;
	for(i = 0; i < uiBufsize; i++)
	{
		if(uiBuffer[i] == 0x02 && uiBuffer[i + 9] == 0x03){
			if (uiBuffer[i + 1] == 0x32 && uiBuffer[i + 2] == 0x43 && uiBuffer[i + 3] == 0x30 && uiBuffer[i + 4] == 0x31)
				break;
		}
	}
	if (uiBuffer[i + 1] == 0x32 && uiBuffer[i + 2] == 0x43 && uiBuffer[i + 3] == 0x30 && uiBuffer[i + 4] == 0x31) {
		if (uiBuffer[i + 5] == 0x30 && uiBuffer[i + 6] == 0x30) {
			if (uiBuffer[i + 7] == 0x30 && uiBuffer[i + 8] == 0x30)		// 0
				strcpy(StateString, "no exception");
			else if (uiBuffer[i + 7] == 0x30 && uiBuffer[i + 8] == 0x33)// 3
				strcpy(StateString, "overcurrent PU");
			else if (uiBuffer[i + 7] == 0x30 && uiBuffer[i + 8] == 0x34)// 4
				strcpy(StateString, "overcurrent analog");
			else if (uiBuffer[i + 7] == 0x30 && uiBuffer[i + 8] == 0x35)// 5
				strcpy(StateString,"over potential");
			else if (uiBuffer[i + 7] == 0x30 && uiBuffer[i + 8] == 0x36)// 6
				strcpy(StateString, "under potential");
			else if (uiBuffer[i + 7] == 0x30 && uiBuffer[i + 8] == 0x37)// 7
				strcpy(StateString, "overload");
			else if (uiBuffer[i + 7] == 0x30 && uiBuffer[i + 8] == 0x38)// 8
				strcpy(StateString, "reset E. overload");
			else if (uiBuffer[i + 7] == 0x30 && uiBuffer[i + 8] == 0x39)// 9
				strcpy(StateString, "overload 2");
			else if (uiBuffer[i + 7] == 0x30 && uiBuffer[i + 8] == 0x41)// 10
				strcpy(StateString, "overheat powmod.");
			else if (uiBuffer[i + 7] == 0x30 && uiBuffer[i + 8] == 0x42)// 11
				strcpy(StateString, "reset E overheat pmod.");
			else if (uiBuffer[i + 7] == 0x30 && uiBuffer[i + 8] == 0x43)// 12
				strcpy(StateString, "overheat internal PU");
			else if (uiBuffer[i + 7] == 0x30 && uiBuffer[i + 8] == 0x44)// 13
				strcpy(StateString, "reset E. overheat intern PU");
			else if (uiBuffer[i + 7] == 0x30 && uiBuffer[i + 8] == 0x45)// 14
				strcpy(StateString, "motorprotection");
			else if (uiBuffer[i + 7] == 0x30 && uiBuffer[i + 8] == 0x46)// 15
				strcpy(StateString, "reset E. motorprotection");
			else if (uiBuffer[i + 7] == 0x31 && uiBuffer[i + 8] == 0x30)// 16
				strcpy(StateString, "drive overheat");
			else if (uiBuffer[i + 7] == 0x31 && uiBuffer[i + 8] == 0x31)// 17
				strcpy(StateString, "reset ERROR drive overheat");
			else if (uiBuffer[i + 7] == 0x31 && uiBuffer[i + 8] == 0x32)// 18
				strcpy(StateString, "overspeed");
			else if (uiBuffer[i + 7] == 0x31 && uiBuffer[i + 8] == 0x34)// 20
				strcpy(StateString, "drive data");
			else if (uiBuffer[i + 7] == 0x31 && uiBuffer[i + 8] == 0x35)// 21
				strcpy(StateString, "motordata not stored ");
			else if (uiBuffer[i + 7] == 0x31 && uiBuffer[i + 8] == 0x36)// 22
				strcpy(StateString, " ident ");
			else if (uiBuffer[i + 7] == 0x31 && uiBuffer[i + 8] == 0x37)// 23
				strcpy(StateString, "ERROR speed diff");
			else if (uiBuffer[i + 7] == 0x31 && uiBuffer[i + 8] == 0x38)// 24
				strcpy(StateString, "fieldbus memory");
			else if (uiBuffer[i + 7] == 0x32 && uiBuffer[i + 8] == 0x36)// 38
				strcpy(StateString, "memory size");
			else if (uiBuffer[i + 7] == 0x32 && uiBuffer[i + 8] == 0x38)// 40
				strcpy(StateString, "FPGA conf.");
			else if (uiBuffer[i + 7] == 0x32 && uiBuffer[i + 8] == 0x39)// 41
				strcpy(StateString, "safety module SACB comm");
			else if (uiBuffer[i + 7] == 0x32 && uiBuffer[i + 8] == 0x41)// 42
				strcpy(StateString, "power unit SACB comm ");
			else if (uiBuffer[i + 7] == 0x32 && uiBuffer[i + 8] == 0x42)// 43
				strcpy(StateString, "enc.intf. SACB comm.");
			else if (uiBuffer[i + 7] == 0x32 && uiBuffer[i + 8] == 0x43)// 44
				strcpy(StateString, "invalid power unit data");
			else if (uiBuffer[i + 7] == 0x32 && uiBuffer[i + 8] == 0x46)// 47
				strcpy(StateString, "power unit flash");
			else if (uiBuffer[i + 7] == 0x33 && uiBuffer[i + 8] == 0x34)// 52
				strcpy(StateString, "undervoltage phase");
			else if (uiBuffer[i + 7] == 0x33 && uiBuffer[i + 8] == 0x37)// 55
				strcpy(StateString, "ERROR safety");
			else if (uiBuffer[i + 7] == 0x33 && uiBuffer[i + 8] == 0x38)// 56
				strcpy(StateString, "software switch left");
			else if (uiBuffer[i + 7] == 0x33 && uiBuffer[i + 8] == 0x39)// 57
				strcpy(StateString, "software switch right");
			else if (uiBuffer[i + 7] == 0x33 && uiBuffer[i + 8] == 0x41) //58
				strcpy(StateString, "fieldbus watchdog");
			else if (uiBuffer[i + 7] == 0x33 && uiBuffer[i + 8] == 0x42) //59
				strcpy(StateString, "prg. input");
			else if (uiBuffer[i + 7] == 0x33 && uiBuffer[i + 8] == 0x43) //60
				strcpy(StateString, "safety module type changed");
			else if (uiBuffer[i + 7] == 0x33 && uiBuffer[i + 8] == 0x44) //61
				strcpy(StateString, "safety module changed");
			else if (uiBuffer[i + 7] == 0x33 && uiBuffer[i + 8] == 0x45) //62
				strcpy(StateString, "Power unit changed");
			else if (uiBuffer[i + 7] == 0x33 && uiBuffer[i + 8] == 0x46) //63
				strcpy(StateString, "enc. intf. changed");
			else if (uiBuffer[i + 7] == 0x34 && uiBuffer[i + 8] == 0x30) //64
				strcpy(StateString, "power unit type changed");
			else if (uiBuffer[i + 7] == 0x34 && uiBuffer[i + 8] == 0x31) //65
				strcpy(StateString, "enc. intf. version");
			else if (uiBuffer[i + 7] == 0x34 && uiBuffer[i + 8] == 0x32) //66
				strcpy(StateString, "overcurrent PU");
			else if (uiBuffer[i + 7] == 0x34 && uiBuffer[i + 8] == 0x33) //67
				strcpy(StateString, "max acc/dec");
			else if (uiBuffer[i + 7] == 0x34 && uiBuffer[i + 8] == 0x34) //68
				strcpy(StateString, "overcurrent Brake");
			else if (uiBuffer[i + 7] == 0x35 && uiBuffer[i + 8] == 0x33) //83
				strcpy(StateString, "Limit Switch Forward");
			else if (uiBuffer[i + 7] == 0x35 && uiBuffer[i + 8] == 0x34) //84
				strcpy(StateString, "Limit Switch Reverse");
			else if (uiBuffer[i + 7] == 0x35 && uiBuffer[i + 8] == 0x35) //85
				strcpy(StateString, "Override Limit Switch For￾ward");
			else if (uiBuffer[i + 7] == 0x35 && uiBuffer[i + 8] == 0x36) //86
				strcpy(StateString, "Override Limit Switch Re￾verse");
			else if (uiBuffer[i + 7] == 0x35 && uiBuffer[i + 8] == 0x37) //87
				strcpy(StateString, "Limit Switch");
			else if (uiBuffer[i + 7] == 0x35 && uiBuffer[i + 8] == 0x39) //89
				strcpy(StateString, "at encoder type change");
			else if (uiBuffer[i + 7] == 0x35 && uiBuffer[i + 8] == 0x41) //90
				strcpy(StateString, "enc.intf.fast comm.");
			else if (uiBuffer[i + 7] == 0x35 && uiBuffer[i + 8] == 0x42) //91
				strcpy(StateString, "encoder interface");
			else if (uiBuffer[i + 7] == 0x35 && uiBuffer[i + 8] == 0x43) //92
				strcpy(StateString, "encoder A");
			else if (uiBuffer[i + 7] == 0x35 && uiBuffer[i + 8] == 0x44) //93
				strcpy(StateString, "encoder B");
			else if (uiBuffer[i + 7] == 0x35 && uiBuffer[i + 8] == 0x45) //94
				strcpy(StateString, "init encoder A");
			else if (uiBuffer[i + 7] == 0x35 && uiBuffer[i + 8] == 0x46) //95
				strcpy(StateString, "init encoder B");
			else if (uiBuffer[i + 7] == 0x36 && uiBuffer[i + 8] == 0x30) //96
				strcpy(StateString, "encoder missing");
			else if (uiBuffer[i + 7] == 0x36 && uiBuffer[i + 8] == 0x31) //97
				strcpy(StateString, "overspeed (EMF)");
			else if (uiBuffer[i + 7] == 0x36 && uiBuffer[i + 8] == 0x32) //98
				strcpy(StateString, "encoder A changed");
			else if (uiBuffer[i + 7] == 0x36 && uiBuffer[i + 8] == 0x33) //99
				strcpy(StateString, "encoder B changed");
			else if (uiBuffer[i + 7] == 0x36 && uiBuffer[i + 8] == 0x34) //100
				strcpy(StateString, "overcurrent out1");
			else if (uiBuffer[i + 7] == 0x36 && uiBuffer[i + 8] == 0x35) //101
				strcpy(StateString, "overcurrent out2");
			else if (uiBuffer[i + 7] == 0x36 && uiBuffer[i + 8] == 0x36) //102
				strcpy(StateString, "overcurrent out3");
			else if (uiBuffer[i + 7] == 0x36 && uiBuffer[i + 8] == 0x37) //103
				strcpy(StateString, "overcurrent out4");
			else if (uiBuffer[i + 7] == 0x36 && uiBuffer[i + 8] == 0x39) //105
				strcpy(StateString, "overcurrent encoder");
			else if (uiBuffer[i + 7] == 0x36 && uiBuffer[i + 8] == 0x41) //106
				strcpy(StateString, "overcurrent 24V");
			else if (uiBuffer[i + 7] == 0x36 && uiBuffer[i + 8] == 0x42) //107
				strcpy(StateString, "over frequency");
			else if (uiBuffer[i + 7] == 0x36 && uiBuffer[i + 8] == 0x43) //108
				strcpy(StateString, "reset E. overheat intern CB");
			else if (uiBuffer[i + 7] == 0x36 && uiBuffer[i + 8] == 0x44) //109
				strcpy(StateString, "overheat internal CB ");
			else if (uiBuffer[i + 7] == 0x36 && uiBuffer[i + 8] == 0x45) //110
				strcpy(StateString, "OH ramp");
			else if (uiBuffer[i + 7] == 0x36 && uiBuffer[i + 8] == 0x46) //111
				strcpy(StateString, "OHI ramp");
			else if (uiBuffer[i + 7] == 0x37 && uiBuffer[i + 8] == 0x30) //112
				strcpy(StateString, "24V supply low");
			else if (uiBuffer[i + 7] == 0x37 && uiBuffer[i + 8] == 0x33) //115
				strcpy(StateString, "GTR7 always OFF");
			else if (uiBuffer[i + 7] == 0x37 && uiBuffer[i + 8] == 0x34) //116
				strcpy(StateString, "GTR7 OC");
			else if (uiBuffer[i + 7] == 0x37 && uiBuffer[i + 8] == 0x35) //117
				strcpy(StateString, "GTR7 always ON");
			else if (uiBuffer[i + 7] == 0x37 && uiBuffer[i + 8] == 0x36) //118
				strcpy(StateString, "OC at 5V diag");
			else if (uiBuffer[i + 7] == 0x37 && uiBuffer[i + 8] == 0x37) //119
				strcpy(StateString, "extreme overpotential");
			else if (uiBuffer[i + 7] == 0x37 && uiBuffer[i + 8] == 0x38) //120
				strcpy(StateString, "DC capacitor damaged");
			else if (uiBuffer[i + 7] == 0x37 && uiBuffer[i + 8] == 0x39) //121
				strcpy(StateString, "runtime");
			else if (uiBuffer[i + 7] == 0x37 && uiBuffer[i + 8] == 0x41) //122
				strcpy(StateString, "UP2");
			else if (uiBuffer[i + 7] == 0x37 && uiBuffer[i + 8] == 0x42) //123
				strcpy(StateString, "LT ready");
			else if (uiBuffer[i + 7] == 0x37 && uiBuffer[i + 8] == 0x43) //124
				strcpy(StateString, "General Fielbus Error");
			else if (uiBuffer[i + 7] == 0x37 && uiBuffer[i + 8] == 0x44) //125
				strcpy(StateString, "fieldbus type changed");
			else if (uiBuffer[i + 7] == 0x37 && uiBuffer[i + 8] == 0x45) //126
				strcpy(StateString, "overheat 2 powmod.");
			else if (uiBuffer[i + 7] == 0x37 && uiBuffer[i + 8] == 0x46) //127
				strcpy(StateString, "reset E. overheat 2 pmod.");
			else if (uiBuffer[i + 7] == 0x38 && uiBuffer[i + 8] == 0x30) //128
				strcpy(StateString, "overheat 3 powmod.");
			else if (uiBuffer[i + 7] == 0x38 && uiBuffer[i + 8] == 0x31) //129
				strcpy(StateString, "reset E. overheat 3 pmod.");
			else if (uiBuffer[i + 7] == 0x38 && uiBuffer[i + 8] == 0x32) //130
				strcpy(StateString, "overheat 2 internal");
			else if (uiBuffer[i + 7] == 0x38 && uiBuffer[i + 8] == 0x33) //131
				strcpy(StateString, "reset E. overheat 2 intern");
			else if (uiBuffer[i + 7] == 0x38 && uiBuffer[i + 8] == 0x34) //132
				strcpy(StateString, "overheat 3 internal");
			else if (uiBuffer[i + 7] == 0x38 && uiBuffer[i + 8] == 0x35) //133
				strcpy(StateString, "reset E. overheat 3 intern");
			else if (uiBuffer[i + 7] == 0x38 && uiBuffer[i + 8] == 0x36) //134
				strcpy(StateString, "Safety Stop");
			else if (uiBuffer[i + 7] == 0x38 && uiBuffer[i + 8] == 0x37) //135
				strcpy(StateString, "File Code");
			else if (uiBuffer[i + 7] == 0x38 && uiBuffer[i + 8] == 0x38) //136
				strcpy(StateString, "blockade detected");
			else if (uiBuffer[i + 7] == 0x38 && uiBuffer[i + 8] == 0x42) //139
				strcpy(StateString, "STO");
			else if (uiBuffer[i + 7] == 0x38 && uiBuffer[i + 8] == 0x43) //140
				strcpy(StateString, "Fail Safe");
		}
	}
}

void KEB_Modestate(uint8_t* uiBuffer, uint16_t uiBufsize, char *StateString){
	int i = 0;
	for(i = 0; i < uiBufsize; i++)
	{
		if(uiBuffer[i] == 0x02 && uiBuffer[i + 9] == 0x03){
			if (uiBuffer[i+1] == 0x32 && uiBuffer[i+2] == 0x31 && uiBuffer[i+3] == 0x30 && uiBuffer[i+4] == 0x32)
				break;
		}
	}
	if (uiBuffer[i+1] == 0x32 && uiBuffer[i+2] == 0x31 && uiBuffer[i+3] == 0x30 && uiBuffer[i+4] == 0x32) {
		if (uiBuffer[i+5] == 0x30 && uiBuffer[i+6] == 0x30) {
			if (uiBuffer[i+7] == 0x30 && uiBuffer[i+8] == 0x30){
				strcpy(StateString,"no mode change");
			}
			else if (uiBuffer[i+7] == 0x30 && uiBuffer[i+8] == 0x31){
				strcpy(StateString,"profile pos");
			}
			else if (uiBuffer[i+7] == 0x30 && uiBuffer[i+8] == 0x32){
				strcpy(StateString,"velocity");
			}
			else if (uiBuffer[i+7] == 0x30 && uiBuffer[i+8] == 0x36){
				strcpy(StateString,"homing");
			}
			else if (uiBuffer[i+7] == 0x30 && uiBuffer[i+8] == 0x38){
				strcpy(StateString,"cycl.sync pos");
			}
			else if (uiBuffer[i+7] == 0x30 && uiBuffer[i+8] == 0x39){
				strcpy(StateString,"cycl.sync vel");
			}
			else if (uiBuffer[i+7] == 0x30 && uiBuffer[i+8] == 0x41){
				strcpy(StateString,"cycl.sync tor");
			}
		}
		else if(uiBuffer[i+5] == 0x46 && uiBuffer[i+6] == 0x46){
			if (uiBuffer[i+7] == 0x46 && uiBuffer[i+8] == 0x45){
				strcpy(StateString,"jog mode");
			}
		}
	}
}

int KEB_ModeNum(uint8_t* uiBuffer, uint16_t uiBufsize)
{
	int i = 0;
	int StateNumber = 0;
	for(i = 0; i < uiBufsize; i++)
	{
		if(uiBuffer[i] == 0x02 && uiBuffer[i + 9] == 0x03){
			if (uiBuffer[i+1] == 0x32 && uiBuffer[i+2] == 0x31 && uiBuffer[i+3] == 0x30 && uiBuffer[i+4] == 0x32)
				break;
		}
	}
	if (uiBuffer[i+1] == 0x32 && uiBuffer[i+2] == 0x31 && uiBuffer[i+3] == 0x30 && uiBuffer[i+4] == 0x32) {
		if (uiBuffer[i+5] == 0x30 && uiBuffer[i+6] == 0x30) {
			if (uiBuffer[i+7] == 0x30 && uiBuffer[i+8] == 0x30){
				StateNumber = 0;		//"no mode change"
			}
			else if (uiBuffer[i+7] == 0x30 && uiBuffer[i+8] == 0x31){
				StateNumber = 1;		//"profile pos"
			}
			else if (uiBuffer[i+7] == 0x30 && uiBuffer[i+8] == 0x32){
				StateNumber = 2;		//"velocity"
			}
			else if (uiBuffer[i+7] == 0x30 && uiBuffer[i+8] == 0x36){
				StateNumber = 6;		//"homing"
			}
			else if (uiBuffer[i+7] == 0x30 && uiBuffer[i+8] == 0x38){
				StateNumber = 8;		//"cycl.sync pos"
			}
			else if (uiBuffer[i+7] == 0x30 && uiBuffer[i+8] == 0x39){
				StateNumber = 9;		//"cycl.sync vel"
			}
			else if (uiBuffer[i+7] == 0x30 && uiBuffer[i+8] == 0x41){
				StateNumber = 10;	//"cycl.sync tor"
			}
		}
		else if(uiBuffer[i+5] == 0x46 && uiBuffer[i+6] == 0x46){
			if (uiBuffer[i+7] == 0x46 && uiBuffer[i+8] == 0x45){
				StateNumber = -1;	//"jog mode"
			}
		}
	}

	return StateNumber;
}
void KEB_Supplystate(uint8_t* uiBuffer, uint16_t uiBufsize, char *StateString){
	int i = 0;
	for(i = 0; i < uiBufsize; i++)
	{
		if(uiBuffer[i] == 0x02 && uiBuffer[i + 9] == 0x03){
			if(uiBuffer[i+1] == 0x32 && uiBuffer[i+2] == 0x43 && uiBuffer[i+3] == 0x30 && uiBuffer[i+4] == 0x34)
				break;
		}
	}
	if(uiBuffer[i+1] == 0x32 && uiBuffer[i+2] == 0x43 && uiBuffer[i+3] == 0x30 && uiBuffer[i+4] == 0x34){
		if(uiBuffer[i+5] == 0x30 && uiBuffer[i+6] == 0x30){
			if(uiBuffer[i+7] == 0x30 && uiBuffer[i+8] == 0x32)
				strcpy(StateString,"charging");
			else if(uiBuffer[i+7] == 0x30 && uiBuffer[i+8] == 0x34)
				strcpy(StateString,"run");
			else if(uiBuffer[i+7] == 0x30 && uiBuffer[i+8] == 0x35)
				strcpy(StateString,"phase failure");
		}
	}

}

void KEB_STOstate(uint8_t* uiBuffer, uint16_t uiBufsize, char *StateString){
	int i = 0;
	int STO1;
	int STO2;
	char cSTOTemp[4];
	int STOstate;

	for(i = 0; i <= uiBufsize; i++)
	{
		if(uiBuffer[i] == 0x02 && uiBuffer[i + 9] == 0x03){
			if(uiBuffer[i + 1] == 0x32 && uiBuffer[i + 2] == 0x43 && uiBuffer[i + 3] == 0x31 && uiBuffer[i + 4] == 0x32)
			{
				memcpy(cSTOTemp, uiBuffer + (i + 5), 4);
				STOstate = KEB_hextodec(cSTOTemp);
				break;
			}
		}
	}
	if(STOstate < 65536)
	{
		STOstate = STOstate - 32768;
		if(STOstate >= 0 ){
			STO2 = 1;
			STOstate = STOstate - 16384;
			if(STOstate >= 0)
				STO1 = 1;
			else
				STO1 = 0;
		}
		else{
			STO2 = 0;
			STO1 = 0;
		}
	}

	if(STO1 == 1 && STO2 == 1)
		strcpy(StateString,"STO1,2 SET");
	else if(STO1 == 1 && STO2 == 0)
		strcpy(StateString,"STO1 set");
	else if(STO1 == 0 && STO2 == 1)
		strcpy(StateString,"STO2 set");
	else if(STO1 == 0 && STO2 == 0)
		strcpy(StateString,"STO1,2 NOT SET");

}

void KEB_HWLimit(uint8_t* uiBuffer, uint16_t uiBufsize, bool* HWPoslimit, bool* HWNeglimit){
	int i = 0;
	bool Poslimit = false;
	bool Neglimit = false;
	bool Homeswtich = false;
	bool Homingmode = false;
	char diginputTEMP[4];
	int diginputstate = 0;
	for(i = 0; i <= uiBufsize; i++)
	{
		if(uiBuffer[i] == 0x02 && uiBuffer[i + 9] == 0x03){
			if(uiBuffer[i + 1] == 0x33 && uiBuffer[i + 2] == 0x31 && uiBuffer[i + 3] == 0x30 && uiBuffer[i + 4] == 0x35)
			{
				memcpy(diginputTEMP, uiBuffer + (i + 5), 4);
				diginputstate = KEB_hextodec(diginputTEMP);
				break;
			}
		}
	}
	if(diginputstate < 16)
	{
		if((diginputstate - 8) > -1)
		{
			diginputstate = diginputstate - 8;
			Homingmode = true;
		}
		else
			Homingmode = false;

		if((diginputstate - 4) > -1)
		{
			diginputstate = diginputstate - 4;
			Homeswtich = true;
		}
		else
			Homeswtich = false;

		if((diginputstate - 2) > -1)
		{
			diginputstate = diginputstate - 2;
			Poslimit = true;
			*HWPoslimit = Poslimit;
		}
		else{
			Poslimit = false;
			*HWPoslimit = Poslimit;
		}


		if((diginputstate - 1) > -1)
		{
			diginputstate = diginputstate -1;
			Neglimit = true;
			*HWNeglimit = Neglimit;
		}
		else{
			Neglimit = false;
			*HWNeglimit = Neglimit;
		}
	}

}
int KEB_BrakeCtrlStatus(uint8_t* uiBuffer, uint16_t uiBufsize){
	int i = 0;
	int iBrakestatus = 0;
	char temp[4];
	for(i = 0; i <= uiBufsize; i++)
	{
		if(uiBuffer[i] == 0x02 && uiBuffer[i + 9] == 0x03)
		{
			if (uiBuffer[i+1] == 0x32 && uiBuffer[i+2] == 0x31 && uiBuffer[i+3] == 0x30 && uiBuffer[i+4] == 0x34)
			{
				memcpy(temp,uiBuffer + (i + 5), 4);
				iBrakestatus = KEB_hextodec(temp);
				break;
			}
		}
	}
	return iBrakestatus;
}

int KEB_ReadStateMachine(uint8_t* uiBuffer, uint16_t uiBufsize){
	int i = 0;
	int iStateValue = 0;
	char temp[4];
	for(i = 0; i <= uiBufsize; i++)
	{
		if(uiBuffer[i] == 0x02 && uiBuffer[i + 9] == 0x03)
		{
			if (uiBuffer[i+1] == 0x32 && uiBuffer[i+2] == 0x31 && uiBuffer[i+3] == 0x30 && uiBuffer[i+4] == 0x43)
			{
				memcpy(temp,uiBuffer + (i + 5), 4);
				iStateValue = KEB_hextodec(temp);
				break;
			}
		}
	}
	return iStateValue;
}

int KEB_Readcontrolword(uint8_t* uiBuffer, uint16_t uiBufsize){
	int i = 0;
	int iControlword = 0;
	char temp[4];
	for(i = 0; i <= uiBufsize; i++)
	{
		if(uiBuffer[i] == 0x02 && uiBuffer[i + 9] == 0x03){
			if(uiBuffer[i + 1] == 0x32 && uiBuffer[i + 2] == 0x31 && uiBuffer[i + 3] == 0x30 && uiBuffer[i + 4] == 0x45)
			{
				memcpy(temp,uiBuffer + (i + 5), 4);
				iControlword = KEB_hextodec(temp);
				break;
			}
		}
	}
	return iControlword;
}

int KEB_EthercatComOnOff(uint8_t* uiBuffer, uint16_t uiBufsize){
	int i = 0;
	int iComonoff = 0;
	char temp[8];
	for(i = 0; i <= uiBufsize; i++)
	{
		if(uiBuffer[i] == 0x02 && uiBuffer[i + 11] == 0x03){
			if(uiBuffer[i + 1] == 0x55 && uiBuffer[i + 2] == 0x31)
			{
				memcpy(temp,uiBuffer + (i + 3), 8);
				iComonoff = KEB_hextodec32(temp);
				break;
			}
		}
	}
	return iComonoff;
}

int KEB_TargetRpmVelocitydisplay(uint8_t* uiBuffer, uint16_t uiBufsize){
	int i = 0;
	int TargetRpmVelocity = 0;
	char TargetRpmvel[4];
	for(i = 0; i <= uiBufsize; i++)
	{
		if(uiBuffer[i] == 0x02 && uiBuffer[i + 9] == 0x03){
			if(uiBuffer[i + 1] == 0x32 && uiBuffer[i + 2] == 0x33 && uiBuffer[i + 3] == 0x31 && uiBuffer[i + 4] == 0x34)
			{
				memcpy(TargetRpmvel, uiBuffer + (i + 5), 4);
				TargetRpmVelocity = KEB_hextodec(TargetRpmvel);
				break;
			}
		}
	}
	return TargetRpmVelocity;
}

int KEB_TargetRpmPositiondisplay(uint8_t* uiBuffer, uint16_t uiBufsize){
	int i = 0;
	int TargetRpmPosition = 0;
	char TargetRpmPos[4];
	for(i = 0; i <= uiBufsize; i++)
	{
		if(uiBuffer[i] == 0x02 && uiBuffer[i + 9] == 0x03){
			if (uiBuffer[i + 1] == 0x32 && uiBuffer[i + 2] == 0x45 && uiBuffer[i + 3] == 0x31 && uiBuffer[i + 4] == 0x45)
			{
				memcpy(TargetRpmPos, uiBuffer + (i + 5), 4);
				TargetRpmPosition = KEB_hextodec(TargetRpmPos);
				break;
			}
		}
	}
	return TargetRpmPosition;
}

void KEB_Systemcounter(uint8_t* uiBuffer, uint16_t uiBufsize, char* systime){
	int i = 0;
	for(i = 0; i < uiBufsize; i++)
	{
		if(uiBuffer[i] == 0x02 && uiBuffer[i + 9] == 0x03){
			if (uiBuffer[i + 1] == 0x32 && uiBuffer[i + 2] == 0x31 && uiBuffer[i + 3] == 0x32 && uiBuffer[i + 4] == 0x33)
			{
				memcpy(systime, uiBuffer + (i + 5), 4);
				break;
			}
		}
	}
}

int KEB_ActVelocitydisplay(uint8_t* uiBuffer, uint16_t uiBufsize){
	int i = 0;
	int TargetVelocity = 0;
	char Targetvel[4];
	for(i = 0; i < uiBufsize; i++)
	{
		if(uiBuffer[i] == 0x02 && uiBuffer[i + 9] == 0x03){
			if (uiBuffer[i + 1] == 0x32 && uiBuffer[i + 2] == 0x31 && uiBuffer[i + 3] == 0x30 && uiBuffer[i + 4] == 0x33)
			{
				memcpy(Targetvel, uiBuffer + (i + 5), 4);
				TargetVelocity = KEB_hextodec(Targetvel);
				break;
			}
		}
	}
	return TargetVelocity;
}

int32_t KEB_ActPositiondisplay(uint8_t* uiBuffer, uint16_t uiBufsize){
	int i = 0;
	int32_t ActualPosition = 0;
	char ActualPos[8];
	for(i = 0; i < uiBufsize; i++)
	{
		if(uiBuffer[i] == 0x02 && uiBuffer[i + 1] == 0x47 && uiBuffer[i + 2] == 0x31 && uiBuffer[i + 11] == 0x03){
			memcpy(ActualPos, uiBuffer + (i + 3), 8);
			ActualPosition = KEB_hextodec32(ActualPos);
		}
	}
	return ActualPosition;
}

int32_t KEB_TgtPositiondisplay(uint8_t* uiBuffer, uint16_t uiBufsize){
	int i= 0;
	int32_t TargetPosition = 0;
	char TargetPos[8];
	for(i = 0; i < uiBufsize; i++){
		if(uiBuffer[i] == 0x02 && uiBuffer[i + 1] == 0x48 && uiBuffer[i + 2] == 0x31 && uiBuffer[i + 11] == 0x03){
			memcpy(TargetPos, uiBuffer + (i + 3), 8);
			TargetPosition = KEB_hextodec32(TargetPos);
		}
	}
	return TargetPosition;
}
int32_t KEB_TgtHomePositiondisplay(uint8_t* uiBuffer, uint16_t uiBufsize){
	int i = 0;
	int32_t TargetHomePosition = 0;
	char TargetHomePos[8];
	for(i = 0; i < uiBufsize; i++){
		if(uiBuffer[i] == 0x02 && uiBuffer[i + 1] == 0x48 && uiBuffer[i + 2] == 0x31 && uiBuffer[i + 11] == 0x03){
			memcpy(TargetHomePos, uiBuffer + (i + 3), 8);
			TargetHomePosition = KEB_hextodec32(TargetHomePos);
		}
	}
	return TargetHomePosition;
}

int KEB_hextodec(uint8_t* uiarryhex) {
	int result = 0;
	int digitValue = 0;
	int placeValue = 1;
	int isNegative = 0;
	// 음수인 경우 플래그를 설정하고 보수를 취합니다.
	if (uiarryhex[0] == 'F'){
		isNegative = 1;
		for (int i = 3; i >= 0; i--) {
			// 보수를 취합니다.
			if(i == 3)
			{
				if (uiarryhex[i] >= '0' && uiarryhex[i] <= '9') {
					digitValue = 'F' - (uiarryhex[i] + 7 - 1 );
				} else if (uiarryhex[i] >= 'A' && uiarryhex[i] <= 'F') {
					digitValue = 'F' - (uiarryhex[i] - 1);
				} else {
					// 유효하지 않은 16진수 문자
					return - 1;
				}
			}
			else{
				if (uiarryhex[i] >= '0' && uiarryhex[i] <= '9') {
					digitValue = 'F' - (uiarryhex[i] + 7);
				} else if (uiarryhex[i] >= 'A' && uiarryhex[i] <= 'F') {
					digitValue = 'F' - uiarryhex[i];
				} else {
					// 유효하지 않은 16진수 문자
					return - 1;
				}
			}
			result += digitValue * placeValue;
			placeValue *= 16;
		}
	}
	else
	{
		 for (int i = 3; i >= 0; i--) {
			// 16진수를 10진수로 변환합니다.
			if (uiarryhex[i] >= '0' && uiarryhex[i] <= '9') {
				digitValue = uiarryhex[i] - '0';
			} else if (uiarryhex[i] >= 'A' && uiarryhex[i] <= 'F') {
				digitValue = uiarryhex[i] - 'A' + 10;
			} else {
				// 유효하지 않은 16진수 문자
				return - 1;
			}

			// 자릿수에 해당하는 값을 곱하여 결과에 더합니다.
			result += digitValue * placeValue;
			placeValue *= 16;
		}
	}
    // 뒤에서부터 시작하여 각 자릿수의 값을 더합니다.


    if (isNegative) {
		result = result * -1;
	}

    return result;
}
int32_t KEB_hextodec32(uint8_t* uiarryhex)
{
	int32_t result = 0;
	int digitValue = 0;
	int placeValue = 1;
	int isNegative = 0;
	//int mulvalue = 1;
	 for (int i = 7; i >= 0; i--) {
		// 16진수를 10진수로 변환합니다.
		//mulvalue *= 2;
		if (uiarryhex[i] >= '0' && uiarryhex[i] <= '9') {
			digitValue = uiarryhex[i] - '0'; //* mulvalue;
		} else if (uiarryhex[i] >= 'A' && uiarryhex[i] <= 'F') {
			digitValue = uiarryhex[i] - 'A' + 10; // * mulvalue;
		} else {
			// 유효하지 않은 16진수 문자
			return - 1;
		}

		// 자릿수에 해당하는 값을 곱하여 결과에 더합니다.
		result += digitValue * placeValue;
		placeValue *= 16;
	}
	return result;
}



void KEB_dectohex(int idecvalue, uint8_t* uiarryhex) {
	int i = 0;
	int markcheck = 0;
	unsigned int u_dec = idecvalue; // 음수 처리를 위해 부호 없는 정수로 변환

	if (idecvalue < 0) {
		markcheck = idecvalue;
		u_dec = -idecvalue; // 음수면 절댓값 취하기
	}

	// idecvalue를 16진수로 변환하여 uiarrhex에 저장
	do {
		if(markcheck >= 0)
		{
			int remainder = u_dec % 16;
			if (remainder < 10)
				uiarryhex[i++] = 48 + remainder; // '0'부터 '9'까지
			else
				uiarryhex[i++] = 55 + remainder; // 'A'부터 'F'까지
			u_dec = u_dec / 16;
		}
		else
		{
			int remainder = u_dec % 16;
			if (i == 0){
				if (remainder == 0)
					uiarryhex[i] = 0;
				else
					uiarryhex[i] = 16 - remainder;

				if(uiarryhex[i] >= 0 && uiarryhex[i] <= 9)
					uiarryhex[i++] = 48 + uiarryhex[i]; // '0'부터 '9'까지
				else if(uiarryhex[i] >= 10 && uiarryhex[i] <= 15)
					uiarryhex[i++] = 55 + uiarryhex[i]; // 'A'부터 'F'까지
				}
			else{
				if(remainder == 0)
					uiarryhex[i] = 0;
				else{
					if(uiarryhex[i - 1] == 48)
						uiarryhex[i] = 16 - remainder;
					else
						uiarryhex[i] = 15 - remainder;
				}
				if(uiarryhex[i] >= 0 && uiarryhex[i] <=9)
					uiarryhex[i++] = 48 + uiarryhex[i]; // '0'부터 '9'까지
				else if(uiarryhex[i] >= 10 && uiarryhex[i] <= 15)
					uiarryhex[i++] = 55 + uiarryhex[i]; // 'A'부터 'F'까지
			}
			u_dec = u_dec / 16;
		}
	} while (u_dec != 0);

	if (idecvalue < 0) {
		while(i < 4)
			uiarryhex[i++] = 'F';
	}

	// 앞에 빈 자리 0으로 채우기
	while (i < 4) {
		uiarryhex[i++] = '0';
	}

	// 배열을 뒤집기
	int j = 0, k = i - 1;
	while (j < k) {
		uint8_t temp = uiarryhex[j];
		uiarryhex[j] = uiarryhex[k];
		uiarryhex[k] = temp;
		j++;
		k--;
	}
}

void KEB_dec32tohex(int idecvalue, uint8_t* uiarryhex) {
	int i = 0;
	int markcheck = 0;
	unsigned int u_dec = idecvalue; // 음수 처리를 위해 부호 없는 정수로 변환

	if (idecvalue < 0) {
		markcheck = idecvalue;
		u_dec = -idecvalue; // 음수면 절댓값 취하기
	}

	// idecvalue를 16진수로 변환하여 uiarrhex에 저장
	do {
		if(markcheck >= 0)
		{
			int remainder = u_dec % 16;
			if (remainder < 10)
				uiarryhex[i++] = 48 + remainder; // '0'부터 '9'까지
			else
				uiarryhex[i++] = 55 + remainder; // 'A'부터 'F'까지
			u_dec = u_dec / 16;
		}
		else
		{
			int remainder = u_dec % 16;
			if (i == 0){
				if (remainder == 0)
					uiarryhex[i] = 0;
				else
					uiarryhex[i] = 16 - remainder;
				if(uiarryhex[i] >= 0 && uiarryhex[i] <= 9)
					uiarryhex[i++] = 48 + uiarryhex[i]; // '0'부터 '9'까지
				else if(uiarryhex[i] >= 10 && uiarryhex[i] <= 15)
					uiarryhex[i++] = 55 + uiarryhex[i]; // 'A'부터 'F'까지
				}
			else{
				/*if(remainder == 0)
					uiarryhex[i] = 0;
				else{
					if(uiarryhex[i - 1] == 48)
						uiarryhex[i] = 16 - remainder;
					else
						uiarryhex[i] = 15 - remainder;
				}*/
				if(uiarryhex[0] == 0)
					uiarryhex[i] = 16 - remainder;
				else
					uiarryhex[i] = 15 - remainder;

				if(uiarryhex[i] >= 0 && uiarryhex[i] <=9)
					uiarryhex[i++] = 48 + uiarryhex[i]; // '0'부터 '9'까지
				else if(uiarryhex[i] >= 10 && uiarryhex[i] <= 15)
					uiarryhex[i++] = 55 + uiarryhex[i]; // 'A'부터 'F'까지
			}
			u_dec = u_dec / 16;
		}
	} while (u_dec != 0);

	if (idecvalue < 0) {
		while(i < 8)
			uiarryhex[i++] = 'F';
	}

	// 앞에 빈 자리 0으로 채우기
	while (i < 8) {
		uiarryhex[i++] = '0';
	}

	// 배열을 뒤집기
	int j = 0, k = i - 1;
	while (j < k) {
		uint8_t temp = uiarryhex[j];
		uiarryhex[j] = uiarryhex[k];
		uiarryhex[k] = temp;
		j++;
		k--;
	}
}
