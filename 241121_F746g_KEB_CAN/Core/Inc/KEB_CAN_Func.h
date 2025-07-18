/*
 * KEB_CAN_Func.h
 *
 *  Created on: Nov 22, 2024
 *      Author: LEEMINKOO
 */

#ifndef INC_KEB_CAN_FUNC_HPP_
#define INC_KEB_CAN_FUNC_HPP_

#include <main.h>
void KEB_CAN_Func_32dectohex(int idecvalue, uint8_t* uiarryhex, uint8_t num);

void KEB_CAN_Func_Controlword_dectohex(int idecvalue, uint8_t* uiarryhex);

uint16_t KEB_CAN_Func_hexto16uint(uint8_t* uiarryhex, uint8_t Num);

void KEB_CAN_Func_reverse_array(uint8_t *uiarryhex, uint8_t Num);

int KEB_CAN_Func_hexto32dec(uint8_t* uiarryhex, uint8_t num);

void KEB_CAN_Modes(uint16_t dec, char *StateString);

void KEB_CAN_errorcode(uint8_t dec, char *StateString);

#endif /* INC_KEB_CAN_FUNC_HPP_ */
