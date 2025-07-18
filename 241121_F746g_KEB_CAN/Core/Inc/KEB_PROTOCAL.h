/*
 * KEB_PROTOCAL.h
 *
 *  Created on: Mar 12, 2024
 *      Author: Lee
 */

#ifndef INC_KEB_PROTOCAL_HPP_
#define INC_KEB_PROTOCAL_HPP_

#include <main.h>
#include <stdbool.h>

/* USER CODE BEGIN PFP */
uint8_t KEB_BccXOR(uint8_t* ParaAdd, uint8_t* ParaData, uint8_t BccStep, uint8_t IID, uint8_t Service);
uint8_t* KEB_WriteParameterData(uint16_t usiData);
uint8_t* KEB_ReadTrasmitdata(uint8_t* cReadAddress, uint8_t* cReadParaAddress, uint8_t ReadTransStep);
uint8_t* KEB_WriteTransmitData(uint8_t* cWriteAddress, uint8_t* cWriteParaAddress, uint8_t* cWriteParadata, uint8_t WriteTransStep);
void KEB_StateBuf(uint8_t* uiBuffer,uint16_t uiBufsize, uint8_t* StateString);
void KEB_ErrorBuf(uint8_t* uiBuffer,uint16_t uiBufsize, uint8_t* StateString);
void KEB_ModeBuf(uint8_t* uiBuffer,uint16_t uiBufsize, uint8_t* StateString);
void KEB_SupplyBuf(uint8_t* uiBuffer,uint16_t uiBufsize, uint8_t* StateString);
void KEB_STOBuf(uint8_t* uiBuffer,uint16_t uiBufsize, uint8_t* StateString);

void KEB_StateMachineDisplay(uint8_t* uiBuffer, uint16_t uiBufsize, char* StateString);
void KEB_errorcode(uint8_t* uiBuffer, uint16_t uiBufsize, char *StateString);
void KEB_Modestate(uint8_t* uiBuffer, uint16_t uiBufsize, char *StateString);

void KEB_Supplystate(uint8_t* uiBuffer, uint16_t uiBufsize, char *StateString);
void KEB_STOstate(uint8_t* uiBuffer, uint16_t uiBufsize, char *StateString);
void KEB_HWLimit(uint8_t* uiBuffer, uint16_t uiBufsize, bool* HWPoslimit, bool* HWNeglimit);

int KEB_BrakeCtrlStatus(uint8_t* uiBuffer, uint16_t uiBufsize);
int KEB_Readcontrolword(uint8_t* uiBuffer, uint16_t uiBufsize);
int KEB_ReadStateMachine(uint8_t* uiBuffer, uint16_t uiBufsize);

int KEB_EthercatComOnOff(uint8_t* uiBuffer, uint16_t uiBufsize);

void KEB_dectohex(int idecvalue,uint8_t* uiarryhex);
void KEB_dec32tohex(int idecvalue, uint8_t* uiarryhex);

int KEB_hextodec(uint8_t* uiarryhex);
int32_t KEB_hextodec32(uint8_t* uiarryhex);

int KEB_TargetRpmVelocitydisplay(uint8_t* uiBuffer, uint16_t uiBufsize);
int KEB_TargetRpmPositiondisplay(uint8_t* uiBuffer, uint16_t uiBufsize);
int KEB_ActVelocitydisplay(uint8_t* uiBuffer, uint16_t uiBufsize);

int32_t KEB_ActPositiondisplay(uint8_t* uiBuffer, uint16_t uiBufsize);
int32_t KEB_TgtPositiondisplay(uint8_t* uiBuffer, uint16_t uiBufsize);

int32_t KEB_TgtHomePositiondisplay(uint8_t* uiBuffer, uint16_t uiBufsize);


void KEB_Systemcounter(uint8_t* uiBuffer, uint16_t uiBufsize, char* systime);

//function for TCP communication
int KEB_ModeNum(uint8_t* uiBuffer, uint16_t uiBufsize);
int KEB_StateNum(uint8_t* uiBuffer, uint16_t uiBufsize);
int KEB_ErrorNum(uint8_t* uiBuffer, uint16_t uiBufsize);
int KEB_STOstateNum(uint8_t* uiBuffer, uint16_t uiBufsize);
int KEB_HWLimitNum(uint8_t* uiBuffer, uint16_t uiBufsize);
int KEB_SupplystateNum(uint8_t* uiBuffer, uint16_t uiBufsize);

/* USER CODE END PFP */

#endif /* INC_KEB_PROTOCAL_HPP_ */
