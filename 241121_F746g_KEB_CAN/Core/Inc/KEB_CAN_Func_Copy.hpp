/*
 * KEB_CAN_Func.h
 *
 *  Created on: Nov 22, 2024
 *      Author: LEEMINKOO
 */

#ifndef INC_KEB_CAN_FUNC_HPP_
#define INC_KEB_CAN_FUNC_HPP_

#include <stdint.h>  //
#include <stdio.h>   // C 표준 라이브러리
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"  // C 코드 포함

#ifdef __cplusplus
}
#endif

class KEB_CAN_FUNC{
public :
	void KEB_CAN_Func_32dectohex(int idecvalue, uint8_t* uiarryhex, uint8_t num);

	void KEB_CAN_Func_Controlword_dectohex(int idecvalue, uint8_t* uiarryhex);

	uint16_t KEB_CAN_Func_hexto16uint(uint8_t* uiarryhex, uint8_t Num);

	void KEB_CAN_Func_reverse_array(uint8_t *uiarryhex, uint8_t Num);

	int KEB_CAN_Func_hexto32dec(uint8_t* uiarryhex, uint8_t num);

	void KEB_CAN_Stateword(uint16_t u16dec, char *StateString);

	void KEB_CAN_ModeState(uint16_t dec, char *StateString);

	void KEB_CAN_errorcode(uint8_t dec, char *StateString);

	void KEB_CAN_ModeChange(bool& u8ModeWrite, int8_t& u8TouchMode, int8_t& u8RPDOMode, int8_t& s8InvModeState);
};


#endif /* INC_KEB_CAN_FUNC_HPP_ */
