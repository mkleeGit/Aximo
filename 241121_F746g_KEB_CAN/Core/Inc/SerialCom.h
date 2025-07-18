/*
 * SerialCom.h
 *
 *  Created on: Mar 15, 2024
 *      Author: LEEMINKOO
 */
#ifndef INC_SERIALCOM_H_
#define INC_SERIALCOM_H_

#include <KEB_PROTOCAL.h>
#include <stdbool.h>
#include <main.h>
#include "global.h"

//char* SerialReadTx();
uint8_t* SerialReadTx(uint8_t ReadDataSendStep);
uint8_t* SerialWriteTx(uint8_t x);
void Serialinit();
void Addresscalculation();

#endif /* INC_SERIALCOM_H_ */
