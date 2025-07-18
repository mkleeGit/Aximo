#include <gui/main_screen/MainView.hpp>
#include <touchgfx/Color.hpp>
#include <math.h>
MainView::MainView() {

}

void MainView::setupScreen() {
	MainViewBase::setupScreen();
	if (g_bPowerstate == true) {
		Popup_PowerState.setVisible(true);
		Popup_PowerState.invalidate();
	} else {
		;
	}
	//TestAdd;
	//GVL_iModevalue = Position;
	//GVLAddnumber = 1;
	u8Screenpage = 1;
	g_s8Mode = 1;

	PosOption.setVisible(true);
	PosOption.invalidate();
	PosScreenBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	PosScreenBox.invalidate();

	HomeOption.setVisible(false);
	HomeOption.invalidate();
	HomeScreenBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
	HomeScreenBox.invalidate();

	PowerOFFBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
	PowerOFFBox.invalidate();
	PowerONBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	PowerONBox.invalidate();

}

void MainView::tearDownScreen() {
	MainViewBase::tearDownScreen();
}

void MainView::List1ButtonOn() {
	/*if (g_bPowerstate == true) {
		Popup_PowerState.setVisible(true);
		Popup_PowerState.invalidate();
	} else {

		//GVLAddnumber = 1;
	}*/
}
void MainView::PowerButtonON(){
	if(g_st_inverter.s8Mode == Position)
	{
		if(g_st_Statusword.ready_to_switch_on == true && g_st_Statusword.switched_on ==  true && g_st_Statusword.switch_on_disabled == false)
				g_st_controlword.enable_operation = 8;//GVL_enable_operation = 8;
	}
}
void MainView::PowerButtonOFF(){
	g_st_controlword.enable_operation = 0;//GVL_enable_operation = 0;
}
void MainView::ComButtonONOFF()
{
	if(GVLComstate == 8)
	{
		GVLComon 		= false;
		GVLComoff 		= true;
	}
	else if(GVLComstate == 0)
	{
		GVLComon 		= true;
		GVLComoff		= false;
	}
}
void MainView::DirectPosUpSetPadShowButton()
{
	Numkeypad.setVisible(true);
	Numkeypad.invalidate();
	Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Direct_input_UpPosvalue);
	Keypadinputvalue.invalidate();
	Numbuttonminus.setVisible(true);
	Numbuttonminus.invalidate();
	Numbuttondot.setVisible(false);
	Numbuttondot.invalidate();
	KeypadMode = KEYPAD_Direct_Up_POS;
}
void MainView::DirectPosDownSetPadShowButton()
{
	if(g_st_Direct.s32DirectActPos <= 0)
	{
		g_s32Direct_input_DownPosvalue = g_s32Direct_input_DownPosvalue -1;
	}
	Numkeypad.setVisible(true);
	Numkeypad.invalidate();
	Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Direct_input_DownPosvalue);
	Keypadinputvalue.invalidate();
	Numbuttonminus.setVisible(true);
	Numbuttonminus.invalidate();
	Numbuttondot.setVisible(false);
	Numbuttondot.invalidate();
	KeypadMode = KEYPAD_Direct_Down_POS;
}
void MainView::DirectHomeSetPadShow()
{
	Numkeypad.setVisible(true);
	Numkeypad.invalidate();
	Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Direct_input_Homevalue);
	Keypadinputvalue.invalidate();
	Numbuttonminus.setVisible(true);
	Numbuttonminus.invalidate();
	Numbuttondot.setVisible(false);
	Numbuttondot.invalidate();
	KeypadMode = KEYPAD_Direct_Home_POS;
}

void MainView::Velrpmpadshow()
{
	Numkeypad.setVisible(true);
	Numkeypad.invalidate();
	Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Vel_input_Rpmvalue);
	Keypadinputvalue.invalidate();
	Numbuttonminus.setVisible(true);
	Numbuttonminus.invalidate();
	Numbuttondot.setVisible(false);
	Numbuttondot.invalidate();
	KeypadMode = KEYPAD_Velocity_RPM;
}

void MainView::Posrpmpadshow()
{
	Numkeypad.setVisible(true);
	Numkeypad.invalidate();
	Unicode:: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Pos_input_Rpmvalue);
	Keypadinputvalue.invalidate();
	Numbuttonminus.setVisible(false);
	Numbuttonminus.invalidate();
	Numbuttondot.setVisible(false);
	Numbuttondot.invalidate();
	KeypadMode = KEYPAD_Position_RPM;
}

void MainView::Pospospadshow()
{
	Numkeypad.setVisible(true);
	Numkeypad.invalidate();
	Unicode:: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Pos_input_Posvalue);
	Keypadinputvalue.invalidate();
	Numbuttonminus.setVisible(true);
	Numbuttonminus.invalidate();
	Numbuttondot.setVisible(false);
	Numbuttondot.invalidate();
	KeypadMode = KEYPAD_Position_POS;
}
void MainView::HomePospadshow()
{
	Numkeypad.setVisible(true);
	Numkeypad.invalidate();
	Unicode:: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Home_input_Posvalue);
	Keypadinputvalue.invalidate();
	Numbuttonminus.setVisible(true);
	Numbuttonminus.invalidate();
	Numbuttondot.setVisible(false);
	Numbuttondot.invalidate();
	KeypadMode = KEYPAD_Home_POS;
}


void MainView::SettingMinposShow()
{
	Numkeypad.setVisible(true);
	Numkeypad.invalidate();
	temp_SetMinPos = 0;
	Unicode::snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMinPos);
	Keypadinputvalue.invalidate();
	Numbuttonminus.setVisible(true);
	Numbuttonminus.invalidate();
	Numbuttondot.setVisible(false);
	Numbuttondot.invalidate();
	KeypadMode = KEYPAD_Setting_Minpos;
}
void MainView::SettingMaxposShow()
{
	Numkeypad.setVisible(true);
	Numkeypad.invalidate();
	temp_SetMaxPos = 0;
	Unicode::snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMaxPos);
	Keypadinputvalue.invalidate();
	Numbuttonminus.setVisible(true);
	Numbuttonminus.invalidate();
	Numbuttondot.setVisible(false);
	Numbuttondot.invalidate();
	KeypadMode = KEYPAD_Setting_Maxpos;
}
void MainView::SettingGearNumShow()
{
	Numkeypad.setVisible(true);
	Numkeypad.invalidate();
	temp_SetGearNum = 0;
	dot_state = false;
	dot_value = 0;
	Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetGearNum);
	Keypadinputvalue.invalidate();
	Numbuttonminus.setVisible(false);
	Numbuttonminus.invalidate();
	Numbuttondot.setVisible(true);
	Numbuttondot.invalidate();
	KeypadMode = KEYPAD_Setting_GearNum;
}
void MainView::SettingGearDenShow()
{
	Numkeypad.setVisible(true);
	Numkeypad.invalidate();
	temp_SetGearDen = 0;
	dot_state = false;
	dot_value = 0;
	Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetGearDen);
	Keypadinputvalue.invalidate();
	Numbuttonminus.setVisible(false);
	Numbuttonminus.invalidate();
	Numbuttondot.setVisible(true);
	Numbuttondot.invalidate();
	KeypadMode = KEYPAD_Setting_GearDen;
}
void MainView::SettingDiameterShow()
{
	Numkeypad.setVisible(true);
	Numkeypad.invalidate();
	temp_SetDiameter = 0;
	dot_state = false;
	dot_value = 0;
	Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetDiameter);
	Keypadinputvalue.invalidate();
	Numbuttonminus.setVisible(false);
	Numbuttonminus.invalidate();
	Numbuttondot.setVisible(true);
	Numbuttondot.invalidate();
	KeypadMode = KEYPAD_Setting_Diameter;
}
void MainView::SettingWireSetPadShow()
{
	Numkeypad.setVisible(true);
	Numkeypad.invalidate();
	temp_SetWire = 0;
	dot_state = false;
	dot_value = 0;
	Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetWire);
	Keypadinputvalue.invalidate();
	Numbuttonminus.setVisible(false);
	Numbuttonminus.invalidate();
	Numbuttondot.setVisible(true);
	Numbuttondot.invalidate();
	KeypadMode = KEYPAD_Wire;
}
void MainView::SettingRpmShow()
{
	Numkeypad.setVisible(true);
	Numkeypad.invalidate();
	temp_SetMinMaxRpm = 0;
	Unicode::snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMinMaxRpm);
	Keypadinputvalue.invalidate();
	Numbuttonminus.setVisible(false);
	Numbuttonminus.invalidate();
	Numbuttondot.setVisible(false);
	Numbuttondot.invalidate();
	KeypadMode = KEYPAD_Setting_MinMaxVel;
}
void MainView::SettingEncPulseSetPadShow()
{
	Numkeypad.setVisible(true);
	Numkeypad.invalidate();
	temp_SetEncPulse = 0;
	Unicode::snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetEncPulse);
	Keypadinputvalue.invalidate();
	Numbuttonminus.setVisible(false);
	Numbuttonminus.invalidate();
	Numbuttondot.setVisible(false);
	Numbuttondot.invalidate();
	KeypadMode = KEYPAD_Enc_Pulse;
}


void MainView::SettingHideButton()
{
	temp_SetMinMaxRpm = 0;
	temp_SetMaxPos = 0;
	temp_SetMinPos = 0;
	temp_SetGearDen = 0;
	temp_SetGearNum = 0;
	temp_SetDiameter = 0;
	temp_SetType = g_s32DriveSettingType;
	temp_SetWire = 0;
	temp_SetYoYo = bool(g_s32YoYo);
	temp_SetEncPulse = 0;
	if(temp_SetYoYo == true)YoYoButton.setSelected(true);
	else YoYoButton.setSelected(false);
	Setting.hide();
}

void MainView::SettingShowButton()
{
	oldtemp_SetMaxPos = g_s32MaxPosValue;
	oldtemp_SetMinPos = g_s32MinPosValue;
	oldtemp_SetGearDen = g_st_Setting.fGearDenominator;
	oldtemp_SetGearNum = g_st_Setting.fGearNumerator;
	oldtemp_SetDiameter = g_st_Setting.fDiameter;
	oldtemp_SetMinMaxRpm = g_st_inverter.minmaxRpmvalue;

	temp_SetType = g_s32DriveSettingType;

	oldtemp_SetWire = g_fWire;
	oldtemp_SetEncPulse = g_st_Direct.u16EncoderPulse;

	temp_SetYoYo = bool(g_s32YoYo);
	if(temp_SetYoYo == true)YoYoButton.setSelected(true);
	else YoYoButton.setSelected(false);
}
void MainView::YoYoSelected()
{
	YoYoButton.setSelected(true);
	temp_SetYoYo = true;
}
void MainView::YoYoDeselected()
{
	YoYoButton.setSelected(false);
	temp_SetYoYo = false;
}
void MainView::Keypadhide()
{
	if(KeypadMode == KEYPAD_Velocity_RPM)g_s32Vel_input_Rpmvalue = 0;
	else if(KeypadMode == KEYPAD_Position_RPM)g_s32Pos_input_Rpmvalue = 0;
	else if(KeypadMode == KEYPAD_Position_POS)g_s32Pos_input_Posvalue = 0;
	else if(KeypadMode == KEYPAD_Setting_Minpos)temp_SetMinPos = 0;
	else if(KeypadMode == KEYPAD_Setting_Maxpos)temp_SetMaxPos = 0;
	else if(KeypadMode == KEYPAD_Setting_GearNum)
	{
		temp_SetGearNum = 0;
		dot_value = 0;
		dot_state = false;
	}
	else if(KeypadMode == KEYPAD_Setting_GearDen)
	{
		temp_SetGearDen = 0;
		dot_value = 0;
		dot_state = false;
	}
	else if(KeypadMode == KEYPAD_Home_POS)g_s32Home_input_Posvalue = 0;
	else if(KeypadMode == KEYPAD_Setting_Diameter)
	{
		temp_SetDiameter = 0;
		dot_value = 0;
		dot_state = false;
	}
	else if(KeypadMode == KEYPAD_Setting_MinMaxVel)temp_SetMinMaxRpm = 0;
	else if(KeypadMode == KEYPAD_Direct_Up_POS)g_s32Direct_input_UpPosvalue = 0;
	else if(KeypadMode == KEYPAD_Direct_Down_POS)g_s32Direct_input_DownPosvalue = 0;
	else if(KeypadMode == KEYPAD_Direct_Home_POS)g_s32Direct_input_Homevalue = 0;
	else if(KeypadMode == KEYPAD_Wire)
	{
		temp_SetWire = 0;
		dot_value = 0;
		dot_state = false;
	}
	else if(KeypadMode == KEYPAD_Enc_Pulse)temp_SetEncPulse = 0;
	Numkeypad.hide();
	//Numkeypad.setVisible(true);
	Numkeypad.invalidate();
}
void MainView::Num1Button()
{
	const int digit = 1; // 현재 버튼에서 입력한 숫자 (Num2Button이므로 2)
	const float fvalue =0.1f;
	const float fvalue2 =0.01f;
	// 정수 입력값을 갱신하는 람다 함수
	auto UpdateInputValue = [&](int32_t& value, int32_t minVal, int32_t maxVal) {
		if (value == 0) {
			value = digit;
		}
		else if (value > 0) {
			value = (value * 10) + digit;
		}
		else {
			value = (value * 10) - digit;
		}

		// 최대/최소 범위 제한
		if (value > maxVal) value = maxVal;
		if (value < minVal) value = minVal;
	};

	// 소수점 입력값을 갱신하는 람다 함수
	auto UpdateFloatInputValue = [&](float& value) {
		if (dot_state) {
			if (dot_value == 0) {
				value = value + fvalue;
				dot_value = 1;
			}
			else if (dot_value == 1) {
				value = value+ fvalue2;
				dot_value = 2;
			}
		}
		else {
			value = (value * 10) + digit;
		}

		if (value > 60000) value = 60000;
	};

	// 문자열 변환 및 디스플레이 업데이트
	auto UpdateKeypadDisplay = [&](float value, bool bDotstate, int Dotvalue) {
		if (bDotstate) {
			if (Dotvalue == 1)
				Unicode::snprintfFloat(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%.1f", value);
			else if (Dotvalue == 2)
				Unicode::snprintfFloat(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%.2f", value);
		}
		else {
			Unicode::snprintf(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%d", static_cast<int>(value));
		}

		Keypadinputvalue.invalidate();
	};

	// KeypadMode에 따른 값 처리
	switch (KeypadMode) {
	case KEYPAD_Velocity_RPM:
		UpdateInputValue(g_s32Vel_input_Rpmvalue, -g_st_inverter.minmaxRpmvalue, g_st_inverter.minmaxRpmvalue);
		UpdateKeypadDisplay(g_s32Vel_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_RPM:
		UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, g_st_inverter.minmaxRpmvalue);
		UpdateKeypadDisplay(g_s32Pos_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_POS:
		UpdateInputValue(g_s32Pos_input_Posvalue, SettingPosmaxLow, SettingPosmaxHigh);
		UpdateKeypadDisplay(g_s32Pos_input_Posvalue, false, 0);
		break;

	case KEYPAD_Setting_Maxpos:
		UpdateInputValue(temp_SetMaxPos, SettingPosmaxLow, SettingPosmaxHigh);
		UpdateKeypadDisplay(temp_SetMaxPos, false, 0);
		break;

	case KEYPAD_Setting_Minpos:
		UpdateInputValue(temp_SetMinPos, SettingPosminLow, SettingPosminHigh);
		UpdateKeypadDisplay(temp_SetMinPos, false, 0);
		break;

	case KEYPAD_Home_POS:
		UpdateInputValue(g_s32Home_input_Posvalue, g_s32MinPosValue, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Home_input_Posvalue, false, 0);
		break;

	case KEYPAD_Setting_GearNum:
		UpdateFloatInputValue(temp_SetGearNum);
		UpdateKeypadDisplay(temp_SetGearNum, dot_state, dot_value);
		break;

	case KEYPAD_Setting_GearDen:
		UpdateFloatInputValue(temp_SetGearDen);
		UpdateKeypadDisplay(temp_SetGearDen, dot_state, dot_value);
		break;

	case KEYPAD_Setting_Diameter:
		UpdateFloatInputValue(temp_SetDiameter);
		UpdateKeypadDisplay(temp_SetDiameter, dot_state, dot_value);
		break;

	case KEYPAD_Setting_MinMaxVel:
		UpdateInputValue(temp_SetMinMaxRpm, 0, SettingPosRpmMinMax);
		UpdateKeypadDisplay(temp_SetMinMaxRpm, false, 0);
		break;

	case KEYPAD_Direct_Up_POS:
		UpdateInputValue(g_s32Direct_input_UpPosvalue, g_st_Direct.s32DirectActPos, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_UpPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Down_POS:
		UpdateInputValue(g_s32Direct_input_DownPosvalue, g_s32MinPosValue, g_st_Direct.s32DirectActPos);
		UpdateKeypadDisplay(g_s32Direct_input_DownPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Home_POS :
		UpdateInputValue(g_s32Direct_input_Homevalue, g_s32MinPosValue, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_Homevalue, false, 0);
		break;

	case KEYPAD_Wire :
		UpdateFloatInputValue(temp_SetWire);
		UpdateKeypadDisplay(temp_SetWire, dot_state, dot_value);
		break;

	case KEYPAD_Enc_Pulse :
		UpdateInputValue(temp_SetEncPulse, 0, 20000);
		UpdateKeypadDisplay(temp_SetEncPulse,false,0);
		break;

	default:
		break;
	}
	/*if(KeypadMode == KEYPAD_Velocity_RPM)
	{
		if (g_s32Vel_input_Rpmvalue == 0){
			g_s32Vel_input_Rpmvalue = 1;
			if(g_s32Vel_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Vel_input_Rpmvalue > 0){
			g_s32Vel_input_Rpmvalue = (g_s32Vel_input_Rpmvalue * 10) + 1;
			if(g_s32Vel_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Vel_input_Rpmvalue < 0){
			g_s32Vel_input_Rpmvalue = (g_s32Vel_input_Rpmvalue * 10) - 1;
			if(g_s32Vel_input_Rpmvalue <= (g_st_inverter.minmaxRpmvalue * -1))
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue * -1;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Vel_input_Rpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_RPM)
	{
		if(g_s32Pos_input_Rpmvalue == 0){
			g_s32Pos_input_Rpmvalue = 1;
			if(g_s32Pos_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Pos_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Pos_input_Rpmvalue > 0){
			g_s32Pos_input_Rpmvalue = (g_s32Pos_input_Rpmvalue * 10) + 1;
			if(g_s32Pos_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Pos_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Pos_input_Rpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_POS)
	{
		if (g_s32Pos_input_Posvalue == 0){
			g_s32Pos_input_Posvalue = 1;
			if(g_s32Pos_input_Posvalue >= SettingPosmaxHigh)
				g_s32Pos_input_Posvalue = SettingPosmaxHigh;
		}
		else if(g_s32Pos_input_Posvalue > 0){
			g_s32Pos_input_Posvalue = (g_s32Pos_input_Posvalue * 10) + 1;
			if(g_s32Pos_input_Posvalue >= SettingPosmaxHigh)
				g_s32Pos_input_Posvalue = SettingPosmaxHigh;
		}
		else if(g_s32Pos_input_Posvalue < 0){
			g_s32Pos_input_Posvalue = (g_s32Pos_input_Posvalue * 10) - 1;
			if(g_s32Pos_input_Posvalue <= SettingPosmaxLow)
				g_s32Pos_input_Posvalue = SettingPosmaxLow;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Pos_input_Posvalue);
	}
	else if(KeypadMode == KEYPAD_Setting_Maxpos)
	{
		if(temp_SetMaxPos == 0)
		{
			temp_SetMaxPos = 1;
			if(temp_SetMaxPos >= SettingPosmaxHigh)
				temp_SetMaxPos = SettingPosmaxHigh;
		}
		else if(temp_SetMaxPos > 0)
		{
			temp_SetMaxPos = (temp_SetMaxPos * 10) + 1;
			if(temp_SetMaxPos >= SettingPosmaxHigh)
				temp_SetMaxPos = SettingPosmaxHigh;
		}
		else if(temp_SetMaxPos < 0)
		{
			temp_SetMaxPos = (temp_SetMaxPos * 10) - 1;
			if(temp_SetMaxPos <= SettingPosmaxLow)
				temp_SetMaxPos = SettingPosmaxLow;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMaxPos);
	}
	else if(KeypadMode == KEYPAD_Setting_Minpos)
	{
		if(temp_SetMinPos == 0)
		{
			temp_SetMinPos = 1;
			if(temp_SetMinPos >= SettingPosminHigh)
				temp_SetMinPos = SettingPosminHigh;
		}
		else if(temp_SetMinPos > 0)
		{
			temp_SetMinPos = (temp_SetMinPos * 10) + 1;
			if(temp_SetMinPos >= SettingPosminHigh)
				temp_SetMinPos = SettingPosminHigh;
		}
		else if(temp_SetMinPos < 0)
		{
			temp_SetMinPos = (temp_SetMinPos * 10) - 1;
			if(temp_SetMinPos <= SettingPosminLow)
				temp_SetMinPos = SettingPosminLow;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMinPos);
	}
	else if(KeypadMode == KEYPAD_Home_POS)
	{
		if (g_s32Home_input_Posvalue == 0){
			g_s32Home_input_Posvalue = 1;
			if(g_s32Home_input_Posvalue >= g_s32MaxPosValue)
				g_s32Home_input_Posvalue = g_s32MaxPosValue;
		}
		else if(g_s32Home_input_Posvalue > 0){
			g_s32Home_input_Posvalue = (g_s32Home_input_Posvalue * 10) + 1;
			if(g_s32Home_input_Posvalue >= g_s32MaxPosValue)
				g_s32Home_input_Posvalue = g_s32MaxPosValue;
		}
		else if(g_s32Home_input_Posvalue < 0){
			g_s32Home_input_Posvalue = (g_s32Home_input_Posvalue * 10) - 1;
			if(g_s32Home_input_Posvalue <= (g_s32MinPosValue))
				g_s32Home_input_Posvalue = g_s32MinPosValue;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Home_input_Posvalue);
	}
	else if(KeypadMode == KEYPAD_Setting_GearNum)
	{
		if(temp_SetGearNum == 0 && dot_state == false){
			temp_SetGearNum = 1;
			if(temp_SetGearNum >= 60000)
				temp_SetGearNum = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearNum);
		}
		else if(temp_SetGearNum > 0 && dot_state == false){
			temp_SetGearNum = (temp_SetGearNum * 10) + 1;
			if(temp_SetGearNum >= 60000)
				temp_SetGearNum = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearNum);
		}
		else if(temp_SetGearNum == 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearNum = temp_SetGearNum + 0.1;
				dot_value = 1;
			}
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearNum);
		}
		else if(temp_SetGearNum > 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearNum = temp_SetGearNum + 0.1;
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearNum);
			}
			else if(dot_value == 1){
				temp_SetGearNum = temp_SetGearNum + 0.01;
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetGearNum);
			}
		}

	}
	else if(KeypadMode == KEYPAD_Setting_GearDen)
	{
		if(temp_SetGearDen == 0 && dot_state == false){
			temp_SetGearDen = 1;
			if(temp_SetGearDen >= 60000)
				temp_SetGearDen = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearDen);
		}
		else if(temp_SetGearDen > 0 && dot_state == false){
			temp_SetGearDen = (temp_SetGearDen * 10) + 1;
			if(temp_SetGearDen >= 60000)
				temp_SetGearDen = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearDen);
		}
		else if(temp_SetGearDen == 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearDen = temp_SetGearDen + 0.1;
				dot_value = 1;
				Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearDen);
			}
		}
		else if(temp_SetGearDen > 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearDen = temp_SetGearDen + 0.1;
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearDen);
			}
			else if(dot_value == 1){
				temp_SetGearDen = temp_SetGearDen + 0.01;
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetGearDen);
			}
		}
	}
	else if(KeypadMode == KEYPAD_Setting_Diameter)
	{
		if(temp_SetDiameter == 0 && dot_state == false){
			temp_SetDiameter = 1;
			if(temp_SetDiameter >= 60000)
				temp_SetDiameter = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetDiameter);
		}
		else if(temp_SetDiameter > 0 && dot_state == false){
			temp_SetDiameter = (temp_SetDiameter * 10) + 1;
			if(temp_SetDiameter >= 60000)
				temp_SetDiameter = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetDiameter);
		}
		else if(temp_SetDiameter == 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetDiameter = temp_SetDiameter + 0.1;
				dot_value = 1;
				Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetDiameter);
			}
		}
		else if(temp_SetDiameter > 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetDiameter = temp_SetDiameter + 0.1;
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetDiameter);
			}
			else if(dot_value == 1){
				temp_SetDiameter = temp_SetDiameter + 0.01;
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetDiameter);
			}
		}
	}
	else if(KeypadMode == KEYPAD_Setting_MinMaxVel)
	{
		if(temp_SetMinMaxRpm == 0)
		{
			temp_SetMinMaxRpm = 1;
			if(temp_SetMinMaxRpm >= SettingPosRpmMinMax)
				temp_SetMinMaxRpm = SettingPosRpmMinMax;
		}
		else if(temp_SetMinMaxRpm > 0)
		{
			temp_SetMinMaxRpm = (temp_SetMinMaxRpm * 10) + 1;
			if(temp_SetMinMaxRpm >= SettingPosRpmMinMax)
				temp_SetMinMaxRpm = SettingPosRpmMinMax;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMinMaxRpm);
	}
	else if(KeypadMode == KEYPAD_Direct_Up_POS)
	{
		if (g_s32Direct_input_UpPosvalue == 0){
			g_s32Direct_input_UpPosvalue = 1;
			if(g_s32Direct_input_UpPosvalue >= g_s32MaxPosValue)
				g_s32Direct_input_UpPosvalue = g_s32MaxPosValue;
		}
		else if(g_s32Direct_input_UpPosvalue > 0){
			g_s32Direct_input_UpPosvalue = (g_s32Direct_input_UpPosvalue * 10) + 1;
			if(g_s32Direct_input_UpPosvalue >= g_s32MaxPosValue)
				g_s32Direct_input_UpPosvalue = g_s32MaxPosValue;
		}
		else if(g_s32Direct_input_UpPosvalue < 0){
			g_s32Direct_input_UpPosvalue = (g_s32Direct_input_UpPosvalue * 10) - 1;
			if(g_s32Direct_input_UpPosvalue <= (g_s32MinPosValue))
				g_s32Direct_input_UpPosvalue = g_s32MinPosValue;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Direct_input_UpPosvalue);
	}
	Keypadinputvalue.invalidate();*/
}
void MainView::Num2Button()
{
	const int digit = 2; // 현재 버튼에서 입력한 숫자 (Num2Button이므로 2)
	const float fvalue =0.2f;
	const float fvalue2 =0.02f;
	// 정수 입력값을 갱신하는 람다 함수
	auto UpdateInputValue = [&](int32_t& value, int32_t minVal, int32_t maxVal) {
		if (value == 0) {
			value = digit;
		}
		else if (value > 0) {
			value = (value * 10) + digit;
		}
		else {
			value = (value * 10) - digit;
		}

		// 최대/최소 범위 제한
		if (value > maxVal) value = maxVal;
		if (value < minVal) value = minVal;
	};

	// 소수점 입력값을 갱신하는 람다 함수
	auto UpdateFloatInputValue = [&](float& value) {
		if (dot_state) {
			if (dot_value == 0) {
				value = value + fvalue;
				dot_value = 1;
			}
			else if (dot_value == 1) {
				value = value+ fvalue2;
				dot_value = 2;
			}
		}
		else {
			value = (value * 10) + digit;
		}

		if (value > 60000) value = 60000;
	};

	// 문자열 변환 및 디스플레이 업데이트
	auto UpdateKeypadDisplay = [&](float value, bool bDotstate, int Dotvalue) {
		if (bDotstate) {
			if (Dotvalue == 1)
				Unicode::snprintfFloat(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%.1f", value);
			else if (Dotvalue == 2)
				Unicode::snprintfFloat(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%.2f", value);
		}
		else {
			Unicode::snprintf(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%d", static_cast<int>(value));
		}

		Keypadinputvalue.invalidate();
	};

	// KeypadMode에 따른 값 처리
	switch (KeypadMode) {
	case KEYPAD_Velocity_RPM:
		UpdateInputValue(g_s32Vel_input_Rpmvalue, -g_st_inverter.minmaxRpmvalue, g_st_inverter.minmaxRpmvalue);
		UpdateKeypadDisplay(g_s32Vel_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_RPM:
		UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, g_st_inverter.minmaxRpmvalue);
		UpdateKeypadDisplay(g_s32Pos_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_POS:
		UpdateInputValue(g_s32Pos_input_Posvalue, SettingPosmaxLow, SettingPosmaxHigh);
		UpdateKeypadDisplay(g_s32Pos_input_Posvalue, false, 0);
		break;

	case KEYPAD_Setting_Maxpos:
		UpdateInputValue(temp_SetMaxPos, SettingPosmaxLow, SettingPosmaxHigh);
		UpdateKeypadDisplay(temp_SetMaxPos, false, 0);
		break;

	case KEYPAD_Setting_Minpos:
		UpdateInputValue(temp_SetMinPos, SettingPosminLow, SettingPosminHigh);
		UpdateKeypadDisplay(temp_SetMinPos, false, 0);
		break;

	case KEYPAD_Home_POS:
		UpdateInputValue(g_s32Home_input_Posvalue, g_s32MinPosValue, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Home_input_Posvalue, false, 0);
		break;

	case KEYPAD_Setting_GearNum:
		UpdateFloatInputValue(temp_SetGearNum);
		UpdateKeypadDisplay(temp_SetGearNum, dot_state, dot_value);
		break;

	case KEYPAD_Setting_GearDen:
		UpdateFloatInputValue(temp_SetGearDen);
		UpdateKeypadDisplay(temp_SetGearDen, dot_state, dot_value);
		break;

	case KEYPAD_Setting_Diameter:
		UpdateFloatInputValue(temp_SetDiameter);
		UpdateKeypadDisplay(temp_SetDiameter, dot_state, dot_value);
		break;

	case KEYPAD_Setting_MinMaxVel:
		UpdateInputValue(temp_SetMinMaxRpm, 0, SettingPosRpmMinMax);
		UpdateKeypadDisplay(temp_SetMinMaxRpm, false, 0);
		break;

	case KEYPAD_Direct_Up_POS:
		UpdateInputValue(g_s32Direct_input_UpPosvalue, g_st_Direct.s32DirectActPos, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_UpPosvalue, false, 0);
		break;
	case KEYPAD_Direct_Down_POS:
		UpdateInputValue(g_s32Direct_input_DownPosvalue, g_s32MinPosValue, g_st_Direct.s32DirectActPos);
		UpdateKeypadDisplay(g_s32Direct_input_DownPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Home_POS :
		UpdateInputValue(g_s32Direct_input_Homevalue, g_s32MinPosValue, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_Homevalue, false, 0);
		break;

	case KEYPAD_Wire :
		UpdateFloatInputValue(temp_SetWire);
		UpdateKeypadDisplay(temp_SetWire, dot_state, dot_value);
		break;

	case KEYPAD_Enc_Pulse :
		UpdateInputValue(temp_SetEncPulse,0,20000);
		UpdateKeypadDisplay(temp_SetEncPulse,false,0);
		break;
	default:
		break;
	}
	/*if(KeypadMode == KEYPAD_Velocity_RPM)
	{
		if (g_s32Vel_input_Rpmvalue == 0){
			g_s32Vel_input_Rpmvalue = 2;
			if(g_s32Vel_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Vel_input_Rpmvalue > 0){
			g_s32Vel_input_Rpmvalue = (g_s32Vel_input_Rpmvalue * 10) + 2;
			if(g_s32Vel_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Vel_input_Rpmvalue < 0){
			g_s32Vel_input_Rpmvalue = (g_s32Vel_input_Rpmvalue * 10) - 2;
			if(g_s32Vel_input_Rpmvalue <= (g_st_inverter.minmaxRpmvalue * -1))
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue * -1;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Vel_input_Rpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_RPM)
	{
		if(g_s32Pos_input_Rpmvalue == 0){
			g_s32Pos_input_Rpmvalue = 2;
			if(g_s32Pos_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Pos_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Pos_input_Rpmvalue > 0){
			g_s32Pos_input_Rpmvalue = (g_s32Pos_input_Rpmvalue * 10) + 2;
			if(g_s32Pos_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Pos_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Pos_input_Rpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_POS)
	{
		if (g_s32Pos_input_Posvalue == 0){
			g_s32Pos_input_Posvalue = 2;
			if(g_s32Pos_input_Posvalue >= SettingPosmaxHigh)
				g_s32Pos_input_Posvalue = SettingPosmaxHigh;
		}
		else if(g_s32Pos_input_Posvalue > 0){
			g_s32Pos_input_Posvalue = (g_s32Pos_input_Posvalue * 10) + 2;
			if(g_s32Pos_input_Posvalue >= SettingPosmaxHigh)
				g_s32Pos_input_Posvalue = SettingPosmaxHigh;
		}
		else if(g_s32Pos_input_Posvalue < 0){
			g_s32Pos_input_Posvalue = (g_s32Pos_input_Posvalue * 10) - 2;
			if(g_s32Pos_input_Posvalue <= SettingPosmaxLow)
				g_s32Pos_input_Posvalue = SettingPosmaxLow;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Pos_input_Posvalue);
	}
	else if(KeypadMode == KEYPAD_Setting_Maxpos)
	{
		if(temp_SetMaxPos == 0)
		{
			temp_SetMaxPos = 2;
			if(temp_SetMaxPos >= SettingPosmaxHigh)
				temp_SetMaxPos = SettingPosmaxHigh;
		}
		else if(temp_SetMaxPos > 0)
		{
			temp_SetMaxPos = (temp_SetMaxPos * 10) + 2;
			if(temp_SetMaxPos >= SettingPosmaxHigh)
				temp_SetMaxPos = SettingPosmaxHigh;
		}
		else if(temp_SetMaxPos < 0)
		{
			temp_SetMaxPos = (temp_SetMaxPos * 10) - 2;
			if(temp_SetMaxPos <= SettingPosmaxLow)
				temp_SetMaxPos = SettingPosmaxLow;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMaxPos);
	}
	else if(KeypadMode == KEYPAD_Setting_Minpos)
	{
		if(temp_SetMinPos == 0)
		{
			temp_SetMinPos = 2;
			if(temp_SetMinPos >= SettingPosminHigh)
				temp_SetMinPos = SettingPosminHigh;
		}
		else if(temp_SetMinPos > 0)
		{
			temp_SetMinPos = (temp_SetMinPos * 10) + 2;
			if(temp_SetMinPos >= SettingPosminHigh)
				temp_SetMinPos = SettingPosminHigh;
		}
		else if(temp_SetMinPos < 0)
		{
			temp_SetMinPos = (temp_SetMinPos * 10) - 2;
			if(temp_SetMinPos <= SettingPosminLow)
				temp_SetMinPos = SettingPosminLow;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMinPos);
	}
	else if(KeypadMode == KEYPAD_Home_POS)
	{
		if (g_s32Home_input_Posvalue == 0){
			g_s32Home_input_Posvalue = 2;
			if(g_s32Home_input_Posvalue >= g_s32MaxPosValue)
				g_s32Home_input_Posvalue = g_s32MaxPosValue;
		}
		else if(g_s32Home_input_Posvalue > 0){
			g_s32Home_input_Posvalue = (g_s32Home_input_Posvalue * 10) + 2;
			if(g_s32Home_input_Posvalue >= g_s32MaxPosValue)
				g_s32Home_input_Posvalue = g_s32MaxPosValue;
		}
		else if(g_s32Home_input_Posvalue < 0){
			g_s32Home_input_Posvalue = (g_s32Home_input_Posvalue * 10) - 2;
			if(g_s32Home_input_Posvalue <= (g_s32MinPosValue))
				g_s32Home_input_Posvalue = g_s32MinPosValue;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Home_input_Posvalue);
	}
	else if(KeypadMode == KEYPAD_Setting_GearNum)
	{
		if(temp_SetGearNum == 0 && dot_state == false){
			temp_SetGearNum = 2;
			if(temp_SetGearNum >= 60000)
				temp_SetGearNum = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearNum);
		}
		else if(temp_SetGearNum > 0 && dot_state == false){
			temp_SetGearNum = (temp_SetGearNum * 10) + 2;
			if(temp_SetGearNum >= 60000)
				temp_SetGearNum = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearNum);
		}
		else if(temp_SetGearNum == 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearNum = temp_SetGearNum + 0.2;
				dot_value = 1;
			}
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearNum);
		}
		else if(temp_SetGearNum > 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearNum = temp_SetGearNum + 0.2;
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearNum);
			}
			else if(dot_value == 1){
				temp_SetGearNum = temp_SetGearNum + 0.02;
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetGearNum);
			}
		}
	}
	else if(KeypadMode == KEYPAD_Setting_GearDen)
	{
		if(temp_SetGearDen == 0 && dot_state == false){
			temp_SetGearDen = 2;
			if(temp_SetGearDen >= 60000)
				temp_SetGearDen = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearDen);
		}
		else if(temp_SetGearDen > 0 && dot_state == false){
			temp_SetGearDen = (temp_SetGearDen * 10) + 2;
			if(temp_SetGearDen >= 60000)
				temp_SetGearDen = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearDen);
		}
		else if(temp_SetGearDen == 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearDen = temp_SetGearDen + 0.2;
				dot_value = 1;
				Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearDen);
			}
		}
		else if(temp_SetGearDen > 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearDen = temp_SetGearDen + 0.2;
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearDen);
			}
			else if(dot_value == 1){
				temp_SetGearDen = temp_SetGearDen + 0.02;
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetGearDen);
			}
		}
	}
	else if(KeypadMode == KEYPAD_Setting_Diameter)
	{
		if(temp_SetDiameter == 0 && dot_state == false){
			temp_SetDiameter = 2;
			if(temp_SetDiameter >= 60000)
				temp_SetDiameter = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetDiameter);
		}
		else if(temp_SetDiameter > 0 && dot_state == false){
			temp_SetDiameter = (temp_SetDiameter * 10) + 2;
			if(temp_SetDiameter >= 60000)
				temp_SetDiameter = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetDiameter);
		}
		else if(temp_SetDiameter == 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetDiameter = temp_SetDiameter + 0.2;
				dot_value = 1;
				Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetDiameter);
			}
		}
		else if(temp_SetDiameter > 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetDiameter = temp_SetDiameter + 0.2;
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetDiameter);
			}
			else if(dot_value == 1){
				temp_SetDiameter = temp_SetDiameter + 0.02;
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetDiameter);
			}
		}
	}
	else if(KeypadMode == KEYPAD_Setting_MinMaxVel)
	{
		if(temp_SetMinMaxRpm == 0)
		{
			temp_SetMinMaxRpm = 2;
			if(temp_SetMinMaxRpm >= SettingPosRpmMinMax)
				temp_SetMinMaxRpm = SettingPosRpmMinMax;
		}
		else if(temp_SetMinMaxRpm > 0)
		{
			temp_SetMinMaxRpm = (temp_SetMinMaxRpm * 10) + 2;
			if(temp_SetMinMaxRpm >= SettingPosRpmMinMax)
				temp_SetMinMaxRpm = SettingPosRpmMinMax;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMinMaxRpm);
	}
	else if(KeypadMode == KEYPAD_Direct_Up_POS)
	{
		if (g_s32Direct_input_UpPosvalue == 0){
			g_s32Direct_input_UpPosvalue = 2;
			if(g_s32Direct_input_UpPosvalue >= g_s32MaxPosValue)
				g_s32Direct_input_UpPosvalue = g_s32MaxPosValue;
		}
		else if(g_s32Direct_input_UpPosvalue > 0){
			g_s32Direct_input_UpPosvalue = (g_s32Direct_input_UpPosvalue * 10) + 2;
			if(g_s32Direct_input_UpPosvalue >= g_s32MaxPosValue)
				g_s32Direct_input_UpPosvalue = g_s32MaxPosValue;
		}
		else if(g_s32Direct_input_UpPosvalue < 0){
			g_s32Direct_input_UpPosvalue = (g_s32Direct_input_UpPosvalue * 10) - 2;
			if(g_s32Direct_input_UpPosvalue <= (g_s32MinPosValue))
				g_s32Direct_input_UpPosvalue = g_s32MinPosValue;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Direct_input_UpPosvalue);
	}
	Keypadinputvalue.invalidate();*/
}
void MainView::Num3Button()
{
	const int digit = 3; // 현재 버튼에서 입력한 숫자 (Num2Button이므로 2)
	const float fvalue = 0.3f;
	const float fvalue2 = 0.03f;
	// 정수 입력값을 갱신하는 람다 함수
	auto UpdateInputValue = [&](int32_t& value, int32_t minVal, int32_t maxVal) {
		if (value == 0) {
			value = digit;
		}
		else if (value > 0) {
			value = (value * 10) + digit;
		}
		else {
			value = (value * 10) - digit;
		}

		// 최대/최소 범위 제한
		if (value > maxVal) value = maxVal;
		if (value < minVal) value = minVal;
	};

	// 소수점 입력값을 갱신하는 람다 함수
	auto UpdateFloatInputValue = [&](float& value) {
		if (dot_state) {
			if (dot_value == 0) {
				value = value + fvalue;
				dot_value = 1;
			}
			else if (dot_value == 1) {
				value = value+ fvalue2;
				dot_value = 2;
			}
		}
		else {
			value = (value * 10) + digit;
		}

		if (value > 60000) value = 60000;
	};

	// 문자열 변환 및 디스플레이 업데이트
	auto UpdateKeypadDisplay = [&](float value, bool bDotstate, int Dotvalue) {
		if (bDotstate) {
			if (Dotvalue == 1)
				Unicode::snprintfFloat(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%.1f", value);
			else if (Dotvalue == 2)
				Unicode::snprintfFloat(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%.2f", value);
		}
		else {
			Unicode::snprintf(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%d", static_cast<int>(value));
		}

		Keypadinputvalue.invalidate();
	};

	// KeypadMode에 따른 값 처리
	switch (KeypadMode) {
	case KEYPAD_Velocity_RPM:
		UpdateInputValue(g_s32Vel_input_Rpmvalue, -g_st_inverter.minmaxRpmvalue, g_st_inverter.minmaxRpmvalue);
		UpdateKeypadDisplay(g_s32Vel_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_RPM:
		UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, g_st_inverter.minmaxRpmvalue);
		UpdateKeypadDisplay(g_s32Pos_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_POS:
		UpdateInputValue(g_s32Pos_input_Posvalue, SettingPosmaxLow, SettingPosmaxHigh);
		UpdateKeypadDisplay(g_s32Pos_input_Posvalue, false, 0);
		break;

	case KEYPAD_Setting_Maxpos:
		UpdateInputValue(temp_SetMaxPos, SettingPosmaxLow, SettingPosmaxHigh);
		UpdateKeypadDisplay(temp_SetMaxPos, false, 0);
		break;

	case KEYPAD_Setting_Minpos:
		UpdateInputValue(temp_SetMinPos, SettingPosminLow, SettingPosminHigh);
		UpdateKeypadDisplay(temp_SetMinPos, false, 0);
		break;

	case KEYPAD_Home_POS:
		UpdateInputValue(g_s32Home_input_Posvalue, g_s32MinPosValue, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Home_input_Posvalue, false, 0);
		break;

	case KEYPAD_Setting_GearNum:
		UpdateFloatInputValue(temp_SetGearNum);
		UpdateKeypadDisplay(temp_SetGearNum, dot_state, dot_value);
		break;

	case KEYPAD_Setting_GearDen:
		UpdateFloatInputValue(temp_SetGearDen);
		UpdateKeypadDisplay(temp_SetGearDen, dot_state, dot_value);
		break;

	case KEYPAD_Setting_Diameter:
		UpdateFloatInputValue(temp_SetDiameter);
		UpdateKeypadDisplay(temp_SetDiameter, dot_state, dot_value);
		break;

	case KEYPAD_Setting_MinMaxVel:
		UpdateInputValue(temp_SetMinMaxRpm, 0, SettingPosRpmMinMax);
		UpdateKeypadDisplay(temp_SetMinMaxRpm, false, 0);
		break;

	case KEYPAD_Direct_Up_POS:
		UpdateInputValue(g_s32Direct_input_UpPosvalue, g_st_Direct.s32DirectActPos, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_UpPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Down_POS:
		UpdateInputValue(g_s32Direct_input_DownPosvalue, g_s32MinPosValue, g_st_Direct.s32DirectActPos);
		UpdateKeypadDisplay(g_s32Direct_input_DownPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Home_POS :
		UpdateInputValue(g_s32Direct_input_Homevalue, g_s32MinPosValue, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_Homevalue, false, 0);
		break;

	case KEYPAD_Wire :
		UpdateFloatInputValue(temp_SetWire);
		UpdateKeypadDisplay(temp_SetWire, dot_state, dot_value);
		break;
	case KEYPAD_Enc_Pulse :
		UpdateInputValue(temp_SetEncPulse,0,20000);
		UpdateKeypadDisplay(temp_SetEncPulse,false,0);
		break;
	default:
		break;
	}
	/*if(KeypadMode == KEYPAD_Velocity_RPM)
	{
		if (g_s32Vel_input_Rpmvalue == 0){
			g_s32Vel_input_Rpmvalue = 3;
			if(g_s32Vel_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Vel_input_Rpmvalue > 0){
			g_s32Vel_input_Rpmvalue = (g_s32Vel_input_Rpmvalue * 10) + 3;
			if(g_s32Vel_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Vel_input_Rpmvalue < 0){
			g_s32Vel_input_Rpmvalue = (g_s32Vel_input_Rpmvalue * 10) - 3;
			if(g_s32Vel_input_Rpmvalue <= (g_st_inverter.minmaxRpmvalue * -1))
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue * -1;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Vel_input_Rpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_RPM)
	{
		if(g_s32Pos_input_Rpmvalue == 0){
			g_s32Pos_input_Rpmvalue = 3;
			if(g_s32Pos_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Pos_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Pos_input_Rpmvalue > 0){
			g_s32Pos_input_Rpmvalue = (g_s32Pos_input_Rpmvalue * 10) + 3;
			if(g_s32Pos_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Pos_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Pos_input_Rpmvalue);

	}
	else if(KeypadMode == KEYPAD_Position_POS)
	{
		if (g_s32Pos_input_Posvalue == 0){
			g_s32Pos_input_Posvalue = 3;
			if(g_s32Pos_input_Posvalue >= SettingPosmaxHigh)
				g_s32Pos_input_Posvalue = SettingPosmaxHigh;
		}
		else if(g_s32Pos_input_Posvalue > 0){
			g_s32Pos_input_Posvalue = (g_s32Pos_input_Posvalue * 10) + 3;
			if(g_s32Pos_input_Posvalue >= SettingPosmaxHigh)
				g_s32Pos_input_Posvalue = SettingPosmaxHigh;
		}
		else if(g_s32Pos_input_Posvalue < 0){
			g_s32Pos_input_Posvalue = (g_s32Pos_input_Posvalue * 10) - 3;
			if(g_s32Pos_input_Posvalue <= SettingPosmaxLow)
				g_s32Pos_input_Posvalue = SettingPosmaxLow;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Pos_input_Posvalue);
	}
	else if(KeypadMode == KEYPAD_Setting_Maxpos)
	{
		if(temp_SetMaxPos == 0)
		{
			temp_SetMaxPos = 3;
			if(temp_SetMaxPos >= SettingPosmaxHigh)
				temp_SetMaxPos = SettingPosmaxHigh;
		}
		else if(temp_SetMaxPos > 0)
		{
			temp_SetMaxPos = (temp_SetMaxPos * 10) + 3;
			if(temp_SetMaxPos >= SettingPosmaxHigh)
				temp_SetMaxPos = SettingPosmaxHigh;
		}
		else if(temp_SetMaxPos < 0)
		{
			temp_SetMaxPos = (temp_SetMaxPos * 10) - 3;
			if(temp_SetMaxPos <= SettingPosmaxLow)
				temp_SetMaxPos = SettingPosmaxLow;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMaxPos);
	}
	else if(KeypadMode == KEYPAD_Setting_Minpos)
	{
		if(temp_SetMinPos == 0)
		{
			temp_SetMinPos = 3;
			if(temp_SetMinPos >= SettingPosminHigh)
				temp_SetMinPos = SettingPosminHigh;
		}
		else if(temp_SetMinPos > 0)
		{
			temp_SetMinPos = (temp_SetMinPos * 10) + 3;
			if(temp_SetMinPos >= SettingPosminHigh)
				temp_SetMinPos = SettingPosminHigh;
		}
		else if(temp_SetMinPos < 0)
		{
			temp_SetMinPos = (temp_SetMinPos * 10) - 3;
			if(temp_SetMinPos <= SettingPosminLow)
				temp_SetMinPos = SettingPosminLow;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMinPos);
	}
	else if(KeypadMode == KEYPAD_Home_POS)
	{
		if (g_s32Home_input_Posvalue == 0){
			g_s32Home_input_Posvalue = 3;
			if(g_s32Home_input_Posvalue >= g_s32MaxPosValue)
				g_s32Home_input_Posvalue = g_s32MaxPosValue;
		}
		else if(g_s32Home_input_Posvalue > 0){
			g_s32Home_input_Posvalue = (g_s32Home_input_Posvalue * 10) + 3;
			if(g_s32Home_input_Posvalue >= g_s32MaxPosValue)
				g_s32Home_input_Posvalue = g_s32MaxPosValue;
		}
		else if(g_s32Home_input_Posvalue < 0){
			g_s32Home_input_Posvalue = (g_s32Home_input_Posvalue * 10) - 3;
			if(g_s32Home_input_Posvalue <= (g_s32MinPosValue))
				g_s32Home_input_Posvalue = g_s32MinPosValue;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Home_input_Posvalue);
	}
	else if(KeypadMode == KEYPAD_Setting_GearNum)
	{
		if(temp_SetGearNum == 0 && dot_state == false){
			temp_SetGearNum = 3;
			if(temp_SetGearNum >= 60000)
				temp_SetGearNum = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearNum);
		}
		else if(temp_SetGearNum > 0 && dot_state == false){
			temp_SetGearNum = (temp_SetGearNum * 10) + 3;
			if(temp_SetGearNum >= 60000)
				temp_SetGearNum = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearNum);
		}
		else if(temp_SetGearNum == 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearNum = temp_SetGearNum + 0.3;
				dot_value = 1;
			}
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearNum);
		}
		else if(temp_SetGearNum > 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearNum = temp_SetGearNum + 0.3;
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearNum);
			}
			else if(dot_value == 1){
				temp_SetGearNum = temp_SetGearNum + 0.03;
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetGearNum);
			}
		}

	}
	else if(KeypadMode == KEYPAD_Setting_GearDen)
	{
		if(temp_SetGearDen == 0 && dot_state == false){
			temp_SetGearDen = 3;
			if(temp_SetGearDen >= 60000)
				temp_SetGearDen = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearDen);
		}
		else if(temp_SetGearDen > 0 && dot_state == false){
			temp_SetGearDen = (temp_SetGearDen * 10) + 3;
			if(temp_SetGearDen >= 60000)
				temp_SetGearDen = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearDen);
		}
		else if(temp_SetGearDen == 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearDen = temp_SetGearDen + 0.3;
				dot_value = 1;
				Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearDen);
			}
		}
		else if(temp_SetGearDen > 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearDen = temp_SetGearDen + 0.3;
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearDen);
			}
			else if(dot_value == 1){
				temp_SetGearDen = temp_SetGearDen + 0.03;
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetGearDen);
			}
		}
	}
	else if(KeypadMode == KEYPAD_Setting_Diameter)
	{
		if(temp_SetDiameter == 0 && dot_state == false){
			temp_SetDiameter = 3;
			if(temp_SetDiameter >= 60000)
				temp_SetDiameter = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetDiameter);
		}
		else if(temp_SetDiameter > 0 && dot_state == false){
			temp_SetDiameter = (temp_SetDiameter * 10) + 3;
			if(temp_SetDiameter >= 60000)
				temp_SetDiameter = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetDiameter);
		}
		else if(temp_SetDiameter == 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetDiameter = temp_SetDiameter + 0.3;
				dot_value = 1;
				Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetDiameter);
			}
		}
		else if(temp_SetDiameter > 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetDiameter = temp_SetDiameter + 0.3;
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetDiameter);
			}
			else if(dot_value == 1){
				temp_SetDiameter = temp_SetDiameter + 0.03;
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetDiameter);
			}
		}
	}
	else if(KeypadMode == KEYPAD_Setting_MinMaxVel)
	{
		if(temp_SetMinMaxRpm == 0)
		{
			temp_SetMinMaxRpm = 3;
			if(temp_SetMinMaxRpm >= SettingPosRpmMinMax)
				temp_SetMinMaxRpm = SettingPosRpmMinMax;
		}
		else if(temp_SetMinMaxRpm > 0)
		{
			temp_SetMinMaxRpm = (temp_SetMinMaxRpm * 10) + 3;
			if(temp_SetMinMaxRpm >= SettingPosRpmMinMax)
				temp_SetMinMaxRpm = SettingPosRpmMinMax;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMinMaxRpm);
	}
	Keypadinputvalue.invalidate();*/
}
void MainView::Num4Button()
{
	const int digit = 4; // 현재 버튼에서 입력한 숫자 (Num2Button이므로 2)
	const float fvalue =0.4f;
	const float fvalue2 =0.04f;
	// 정수 입력값을 갱신하는 람다 함수
	auto UpdateInputValue = [&](int32_t& value, int32_t minVal, int32_t maxVal) {
		if (value == 0) {
			value = digit;
		}
		else if (value > 0) {
			value = (value * 10) + digit;
		}
		else {
			value = (value * 10) - digit;
		}

		// 최대/최소 범위 제한
		if (value > maxVal) value = maxVal;
		if (value < minVal) value = minVal;
	};

	// 소수점 입력값을 갱신하는 람다 함수
	auto UpdateFloatInputValue = [&](float& value) {
		if (dot_state) {
			if (dot_value == 0) {
				value = value + fvalue;
				dot_value = 1;
			}
			else if (dot_value == 1) {
				value = value+ fvalue2;
				dot_value = 2;
			}
		}
		else {
			value = (value * 10) + digit;
		}

		if (value > 60000) value = 60000;
	};

	// 문자열 변환 및 디스플레이 업데이트
	auto UpdateKeypadDisplay = [&](float value, bool bDotstate, int Dotvalue) {
		if (bDotstate) {
			if (Dotvalue == 1)
				Unicode::snprintfFloat(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%.1f", value);
			else if (Dotvalue == 2)
				Unicode::snprintfFloat(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%.2f", value);
		}
		else {
			Unicode::snprintf(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%d", static_cast<int>(value));
		}

		Keypadinputvalue.invalidate();
	};

	// KeypadMode에 따른 값 처리
	switch (KeypadMode) {
	case KEYPAD_Velocity_RPM:
		UpdateInputValue(g_s32Vel_input_Rpmvalue, -g_st_inverter.minmaxRpmvalue, g_st_inverter.minmaxRpmvalue);
		UpdateKeypadDisplay(g_s32Vel_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_RPM:
		UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, g_st_inverter.minmaxRpmvalue);
		UpdateKeypadDisplay(g_s32Pos_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_POS:
		UpdateInputValue(g_s32Pos_input_Posvalue, SettingPosmaxLow, SettingPosmaxHigh);
		UpdateKeypadDisplay(g_s32Pos_input_Posvalue, false, 0);
		break;

	case KEYPAD_Setting_Maxpos:
		UpdateInputValue(temp_SetMaxPos, SettingPosmaxLow, SettingPosmaxHigh);
		UpdateKeypadDisplay(temp_SetMaxPos, false, 0);
		break;

	case KEYPAD_Setting_Minpos:
		UpdateInputValue(temp_SetMinPos, SettingPosminLow, SettingPosminHigh);
		UpdateKeypadDisplay(temp_SetMinPos, false, 0);
		break;

	case KEYPAD_Home_POS:
		UpdateInputValue(g_s32Home_input_Posvalue, g_s32MinPosValue, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Home_input_Posvalue, false, 0);
		break;

	case KEYPAD_Setting_GearNum:
		UpdateFloatInputValue(temp_SetGearNum);
		UpdateKeypadDisplay(temp_SetGearNum, dot_state, dot_value);
		break;

	case KEYPAD_Setting_GearDen:
		UpdateFloatInputValue(temp_SetGearDen);
		UpdateKeypadDisplay(temp_SetGearDen, dot_state, dot_value);
		break;

	case KEYPAD_Setting_Diameter:
		UpdateFloatInputValue(temp_SetDiameter);
		UpdateKeypadDisplay(temp_SetDiameter, dot_state, dot_value);
		break;

	case KEYPAD_Setting_MinMaxVel:
		UpdateInputValue(temp_SetMinMaxRpm, 0, SettingPosRpmMinMax);
		UpdateKeypadDisplay(temp_SetMinMaxRpm, false, 0);
		break;

	case KEYPAD_Direct_Up_POS:
		UpdateInputValue(g_s32Direct_input_UpPosvalue, g_st_Direct.s32DirectActPos, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_UpPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Down_POS:
		UpdateInputValue(g_s32Direct_input_DownPosvalue, g_s32MinPosValue, g_st_Direct.s32DirectActPos);
		UpdateKeypadDisplay(g_s32Direct_input_DownPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Home_POS :
		UpdateInputValue(g_s32Direct_input_Homevalue, g_s32MinPosValue, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_Homevalue, false, 0);
		break;

	case KEYPAD_Wire :
		UpdateFloatInputValue(temp_SetWire);
		UpdateKeypadDisplay(temp_SetWire, dot_state, dot_value);
		break;
	case KEYPAD_Enc_Pulse :
		UpdateInputValue(temp_SetEncPulse,0,20000);
		UpdateKeypadDisplay(temp_SetEncPulse,false,0);
		break;
	default:
		break;
	}

	/*if(KeypadMode == KEYPAD_Velocity_RPM)
	{
		if (g_s32Vel_input_Rpmvalue == 0){
			g_s32Vel_input_Rpmvalue = 4;
			if(g_s32Vel_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Vel_input_Rpmvalue > 0){
			g_s32Vel_input_Rpmvalue = (g_s32Vel_input_Rpmvalue * 10) + 4;
			if(g_s32Vel_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Vel_input_Rpmvalue < 0){
			g_s32Vel_input_Rpmvalue = (g_s32Vel_input_Rpmvalue * 10) - 4;
			if(g_s32Vel_input_Rpmvalue <= (g_st_inverter.minmaxRpmvalue * -1))
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue * -1;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Vel_input_Rpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_RPM)
	{
		if(g_s32Pos_input_Rpmvalue == 0){
			g_s32Pos_input_Rpmvalue = 4;
			if(g_s32Pos_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Pos_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Pos_input_Rpmvalue > 0){
			g_s32Pos_input_Rpmvalue = (g_s32Pos_input_Rpmvalue * 10) + 4;
			if(g_s32Pos_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Pos_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Pos_input_Rpmvalue);

	}
	else if(KeypadMode == KEYPAD_Position_POS)
	{
		if (g_s32Pos_input_Posvalue == 0){
			g_s32Pos_input_Posvalue = 4;
			if(g_s32Pos_input_Posvalue >= SettingPosmaxHigh)
				g_s32Pos_input_Posvalue = SettingPosmaxHigh;
		}
		else if(g_s32Pos_input_Posvalue > 0){
			g_s32Pos_input_Posvalue = (g_s32Pos_input_Posvalue * 10) + 4;
			if(g_s32Pos_input_Posvalue >= SettingPosmaxHigh)
				g_s32Pos_input_Posvalue = SettingPosmaxHigh;
		}
		else if(g_s32Pos_input_Posvalue < 0){
			g_s32Pos_input_Posvalue = (g_s32Pos_input_Posvalue * 10) - 4;
			if(g_s32Pos_input_Posvalue <= SettingPosmaxLow)
				g_s32Pos_input_Posvalue = SettingPosmaxLow;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Pos_input_Posvalue);
	}
	else if(KeypadMode == KEYPAD_Setting_Maxpos)
	{
		if(temp_SetMaxPos == 0)
		{
			temp_SetMaxPos = 4;
			if(temp_SetMaxPos >= SettingPosmaxHigh)
				temp_SetMaxPos = SettingPosmaxHigh;
		}
		else if(temp_SetMaxPos > 0)
		{
			temp_SetMaxPos = (temp_SetMaxPos * 10) + 4;
			if(temp_SetMaxPos >= SettingPosmaxHigh)
				temp_SetMaxPos = SettingPosmaxHigh;
		}
		else if(temp_SetMaxPos < 0)
		{
			temp_SetMaxPos = (temp_SetMaxPos * 10) - 4;
			if(temp_SetMaxPos <= SettingPosmaxLow)
				temp_SetMaxPos = SettingPosmaxLow;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMaxPos);
	}
	else if(KeypadMode == KEYPAD_Setting_Minpos)
	{
		if(temp_SetMinPos == 0)
		{
			temp_SetMinPos = 4;
			if(temp_SetMinPos >= SettingPosminHigh)
				temp_SetMinPos = SettingPosminHigh;
		}
		else if(temp_SetMinPos > 0)
		{
			temp_SetMinPos = (temp_SetMinPos * 10) + 4;
			if(temp_SetMinPos >= SettingPosminHigh)
				temp_SetMinPos = SettingPosminHigh;
		}
		else if(temp_SetMinPos < 0)
		{
			temp_SetMinPos = (temp_SetMinPos * 10) - 4;
			if(temp_SetMinPos <= SettingPosminLow)
				temp_SetMinPos = SettingPosminLow;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMinPos);
	}
	else if(KeypadMode == KEYPAD_Home_POS)
	{
		if (g_s32Home_input_Posvalue == 0){
			g_s32Home_input_Posvalue = 4;
			if(g_s32Home_input_Posvalue >= g_s32MaxPosValue)
				g_s32Home_input_Posvalue = g_s32MaxPosValue;
		}
		else if(g_s32Home_input_Posvalue > 0){
			g_s32Home_input_Posvalue = (g_s32Home_input_Posvalue * 10) + 4;
			if(g_s32Home_input_Posvalue >= g_s32MaxPosValue)
				g_s32Home_input_Posvalue = g_s32MaxPosValue;
		}
		else if(g_s32Home_input_Posvalue < 0){
			g_s32Home_input_Posvalue = (g_s32Home_input_Posvalue * 10) - 4;
			if(g_s32Home_input_Posvalue <= (g_s32MinPosValue))
				g_s32Home_input_Posvalue = g_s32MinPosValue;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Home_input_Posvalue);
	}
	else if(KeypadMode == KEYPAD_Setting_GearNum)
	{
		if(temp_SetGearNum == 0 && dot_state == false){
			temp_SetGearNum = 4;
			if(temp_SetGearNum >= 60000)
				temp_SetGearNum = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearNum);
		}
		else if(temp_SetGearNum > 0 && dot_state == false){
			temp_SetGearNum = (temp_SetGearNum * 10) + 4;
			if(temp_SetGearNum >= 60000)
				temp_SetGearNum = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearNum);
		}
		else if(temp_SetGearNum == 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearNum = temp_SetGearNum + 0.4;
				dot_value = 1;
			}
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearNum);
		}
		else if(temp_SetGearNum > 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearNum = temp_SetGearNum + 0.4;
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearNum);
			}
			else if(dot_value == 1){
				temp_SetGearNum = temp_SetGearNum + 0.04;
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetGearNum);
			}
		}

	}
	else if(KeypadMode == KEYPAD_Setting_GearDen)
	{
		if(temp_SetGearDen == 0 && dot_state == false){
			temp_SetGearDen = 4;
			if(temp_SetGearDen >= 60000)
				temp_SetGearDen = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearDen);
		}
		else if(temp_SetGearDen > 0 && dot_state == false){
			temp_SetGearDen = (temp_SetGearDen * 10) + 4;
			if(temp_SetGearDen >= 60000)
				temp_SetGearDen = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearDen);
		}
		else if(temp_SetGearDen == 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearDen = temp_SetGearDen + 0.4;
				dot_value = 1;
				Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearDen);
			}
		}
		else if(temp_SetGearDen > 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearDen = temp_SetGearDen + 0.4;
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearDen);
			}
			else if(dot_value == 1){
				temp_SetGearDen = temp_SetGearDen + 0.04;
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetGearDen);
			}
		}
	}
	else if(KeypadMode == KEYPAD_Setting_Diameter)
	{
		if(temp_SetDiameter == 0 && dot_state == false){
			temp_SetDiameter = 4;
			if(temp_SetDiameter >= 60000)
				temp_SetDiameter = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetDiameter);
		}
		else if(temp_SetDiameter > 0 && dot_state == false){
			temp_SetDiameter = (temp_SetDiameter * 10) + 4;
			if(temp_SetDiameter >= 60000)
				temp_SetDiameter = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetDiameter);
		}
		else if(temp_SetDiameter == 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetDiameter = temp_SetDiameter + 0.4;
				dot_value = 1;
				Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetDiameter);
			}
		}
		else if(temp_SetDiameter > 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetDiameter = temp_SetDiameter + 0.4;
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetDiameter);
			}
			else if(dot_value == 1){
				temp_SetDiameter = temp_SetDiameter + 0.04;
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetDiameter);
			}
		}
	}
	else if(KeypadMode == KEYPAD_Setting_MinMaxVel)
	{
		if(temp_SetMinMaxRpm == 0)
		{
			temp_SetMinMaxRpm = 4;
			if(temp_SetMinMaxRpm >= SettingPosRpmMinMax)
				temp_SetMinMaxRpm = SettingPosRpmMinMax;
		}
		else if(temp_SetMinMaxRpm > 0)
		{
			temp_SetMinMaxRpm = (temp_SetMinMaxRpm * 10) + 4;
			if(temp_SetMinMaxRpm >= SettingPosRpmMinMax)
				temp_SetMinMaxRpm = SettingPosRpmMinMax;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMinMaxRpm);
	}
	Keypadinputvalue.invalidate();*/
}
void MainView::Num5Button()
{
	const int digit = 5; // 현재 버튼에서 입력한 숫자 (Num2Button이므로 2)
	const float fvalue = 0.5f;
	const float fvalue2 = 0.05f;
	// 정수 입력값을 갱신하는 람다 함수
	auto UpdateInputValue = [&](int32_t& value, int32_t minVal, int32_t maxVal) {
		if (value == 0) {
			value = digit;
		}
		else if (value > 0) {
			value = (value * 10) + digit;
		}
		else {
			value = (value * 10) - digit;
		}

		// 최대/최소 범위 제한
		if (value > maxVal) value = maxVal;
		if (value < minVal) value = minVal;
	};

	// 소수점 입력값을 갱신하는 람다 함수
	auto UpdateFloatInputValue = [&](float& value) {
		if (dot_state) {
			if (dot_value == 0) {
				value = value + fvalue;
				dot_value = 1;
			}
			else if (dot_value == 1) {
				value = value+ fvalue2;
				dot_value = 2;
			}
		}
		else {
			value = (value * 10) + digit;
		}

		if (value > 60000) value = 60000;
	};

	// 문자열 변환 및 디스플레이 업데이트
	auto UpdateKeypadDisplay = [&](float value, bool bDotstate, int Dotvalue) {
		if (bDotstate) {
			if (Dotvalue == 1)
				Unicode::snprintfFloat(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%.1f", value);
			else if (Dotvalue == 2)
				Unicode::snprintfFloat(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%.2f", value);
		}
		else {
			Unicode::snprintf(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%d", static_cast<int>(value));
		}

		Keypadinputvalue.invalidate();
	};

	// KeypadMode에 따른 값 처리
	switch (KeypadMode) {
	case KEYPAD_Velocity_RPM:
		UpdateInputValue(g_s32Vel_input_Rpmvalue, -g_st_inverter.minmaxRpmvalue, g_st_inverter.minmaxRpmvalue);
		UpdateKeypadDisplay(g_s32Vel_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_RPM:
		UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, g_st_inverter.minmaxRpmvalue);
		UpdateKeypadDisplay(g_s32Pos_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_POS:
		UpdateInputValue(g_s32Pos_input_Posvalue, SettingPosmaxLow, SettingPosmaxHigh);
		UpdateKeypadDisplay(g_s32Pos_input_Posvalue, false, 0);
		break;

	case KEYPAD_Setting_Maxpos:
		UpdateInputValue(temp_SetMaxPos, SettingPosmaxLow, SettingPosmaxHigh);
		UpdateKeypadDisplay(temp_SetMaxPos, false, 0);
		break;

	case KEYPAD_Setting_Minpos:
		UpdateInputValue(temp_SetMinPos, SettingPosminLow, SettingPosminHigh);
		UpdateKeypadDisplay(temp_SetMinPos, false, 0);
		break;

	case KEYPAD_Home_POS:
		UpdateInputValue(g_s32Home_input_Posvalue, g_s32MinPosValue, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Home_input_Posvalue, false, 0);
		break;

	case KEYPAD_Setting_GearNum:
		UpdateFloatInputValue(temp_SetGearNum);
		UpdateKeypadDisplay(temp_SetGearNum, dot_state, dot_value);
		break;

	case KEYPAD_Setting_GearDen:
		UpdateFloatInputValue(temp_SetGearDen);
		UpdateKeypadDisplay(temp_SetGearDen, dot_state, dot_value);
		break;

	case KEYPAD_Setting_Diameter:
		UpdateFloatInputValue(temp_SetDiameter);
		UpdateKeypadDisplay(temp_SetDiameter, dot_state, dot_value);
		break;

	case KEYPAD_Setting_MinMaxVel:
		UpdateInputValue(temp_SetMinMaxRpm, 0, SettingPosRpmMinMax);
		UpdateKeypadDisplay(temp_SetMinMaxRpm, false, 0);
		break;

	case KEYPAD_Direct_Up_POS:
		UpdateInputValue(g_s32Direct_input_UpPosvalue, g_st_Direct.s32DirectActPos, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_UpPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Down_POS:
		UpdateInputValue(g_s32Direct_input_DownPosvalue, g_s32MinPosValue, g_st_Direct.s32DirectActPos);
		UpdateKeypadDisplay(g_s32Direct_input_DownPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Home_POS :
		UpdateInputValue(g_s32Direct_input_Homevalue, g_s32MinPosValue, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_Homevalue, false, 0);
		break;

	case KEYPAD_Wire :
		UpdateFloatInputValue(temp_SetWire);
		UpdateKeypadDisplay(temp_SetWire, dot_state, dot_value);
		break;

	case KEYPAD_Enc_Pulse :
		UpdateInputValue(temp_SetEncPulse,0,20000);
		UpdateKeypadDisplay(temp_SetEncPulse,false,0);
		break;

	default:
		break;
	}

	/*if(KeypadMode == KEYPAD_Velocity_RPM)
	{
		if (g_s32Vel_input_Rpmvalue == 0){
			g_s32Vel_input_Rpmvalue = 5;
			if(g_s32Vel_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Vel_input_Rpmvalue > 0){
			g_s32Vel_input_Rpmvalue = (g_s32Vel_input_Rpmvalue * 10) + 5;
			if(g_s32Vel_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Vel_input_Rpmvalue < 0){
			g_s32Vel_input_Rpmvalue = (g_s32Vel_input_Rpmvalue * 10) - 5;
			if(g_s32Vel_input_Rpmvalue <= (g_st_inverter.minmaxRpmvalue * -1))
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue * -1;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Vel_input_Rpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_RPM)
	{
		if(g_s32Pos_input_Rpmvalue == 0){
			g_s32Pos_input_Rpmvalue = 5;
			if(g_s32Pos_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Pos_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Pos_input_Rpmvalue > 0){
			g_s32Pos_input_Rpmvalue = (g_s32Pos_input_Rpmvalue * 10) + 5;
			if(g_s32Pos_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Pos_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Pos_input_Rpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_POS)
	{
		if (g_s32Pos_input_Posvalue == 0){
			g_s32Pos_input_Posvalue = 5;
			if(g_s32Pos_input_Posvalue >= SettingPosmaxHigh)
				g_s32Pos_input_Posvalue = SettingPosmaxHigh;
		}
		else if(g_s32Pos_input_Posvalue > 0){
			g_s32Pos_input_Posvalue = (g_s32Pos_input_Posvalue * 10) + 5;
			if(g_s32Pos_input_Posvalue >= SettingPosmaxHigh)
				g_s32Pos_input_Posvalue = SettingPosmaxHigh;
		}
		else if(g_s32Pos_input_Posvalue < 0){
			g_s32Pos_input_Posvalue = (g_s32Pos_input_Posvalue * 10) - 5;
			if(g_s32Pos_input_Posvalue <= SettingPosmaxLow)
				g_s32Pos_input_Posvalue = SettingPosmaxLow;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Pos_input_Posvalue);
	}
	else if(KeypadMode == KEYPAD_Setting_Maxpos)
	{
		if(temp_SetMaxPos == 0)
		{
			temp_SetMaxPos = 5;
			if(temp_SetMaxPos >= SettingPosmaxHigh)
				temp_SetMaxPos = SettingPosmaxHigh;
		}
		else if(temp_SetMaxPos > 0)
		{
			temp_SetMaxPos = (temp_SetMaxPos * 10) + 5;
			if(temp_SetMaxPos >= SettingPosmaxHigh)
				temp_SetMaxPos = SettingPosmaxHigh;
		}
		else if(temp_SetMaxPos < 0)
		{
			temp_SetMaxPos = (temp_SetMaxPos * 10) - 5;
			if(temp_SetMaxPos <= SettingPosmaxLow)
				temp_SetMaxPos = SettingPosmaxLow;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMaxPos);
	}
	else if(KeypadMode == KEYPAD_Setting_Minpos)
	{
		if(temp_SetMinPos == 0)
		{
			temp_SetMinPos = 5;
			if(temp_SetMinPos >= SettingPosminHigh)
				temp_SetMinPos = SettingPosminHigh;
		}
		else if(temp_SetMinPos > 0)
		{
			temp_SetMinPos = (temp_SetMinPos * 10) + 5;
			if(temp_SetMinPos >= SettingPosminHigh)
				temp_SetMinPos = SettingPosminHigh;
		}
		else if(temp_SetMinPos < 0)
		{
			temp_SetMinPos = (temp_SetMinPos * 10) - 5;
			if(temp_SetMinPos <= SettingPosminLow)
				temp_SetMinPos = SettingPosminLow;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMinPos);
	}
	else if(KeypadMode == KEYPAD_Home_POS)
	{
		if (g_s32Home_input_Posvalue == 0){
			g_s32Home_input_Posvalue = 1;
			if(g_s32Home_input_Posvalue >= g_s32MaxPosValue)
				g_s32Home_input_Posvalue = g_s32MaxPosValue;
		}
		else if(g_s32Home_input_Posvalue > 0){
			g_s32Home_input_Posvalue = (g_s32Home_input_Posvalue * 10) + 5;
			if(g_s32Home_input_Posvalue >= g_s32MaxPosValue)
				g_s32Home_input_Posvalue = g_s32MaxPosValue;
		}
		else if(g_s32Home_input_Posvalue < 0){
			g_s32Home_input_Posvalue = (g_s32Home_input_Posvalue * 10) - 5;
			if(g_s32Home_input_Posvalue <= (g_s32MinPosValue))
				g_s32Home_input_Posvalue = g_s32MinPosValue;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Home_input_Posvalue);
	}
	else if(KeypadMode == KEYPAD_Setting_GearNum)
	{
		if(temp_SetGearNum == 0 && dot_state == false){
			temp_SetGearNum = 5;
			if(temp_SetGearNum >= 60000)
				temp_SetGearNum = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearNum);
		}
		else if(temp_SetGearNum > 0 && dot_state == false){
			temp_SetGearNum = (temp_SetGearNum * 10) + 5;
			if(temp_SetGearNum >= 60000)
				temp_SetGearNum = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearNum);
		}
		else if(temp_SetGearNum == 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearNum = temp_SetGearNum + 0.5;
				dot_value = 1;
			}
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearNum);
		}
		else if(temp_SetGearNum > 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearNum = temp_SetGearNum + 0.5;
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearNum);
			}
			else if(dot_value == 1){
				temp_SetGearNum = temp_SetGearNum + 0.05;
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetGearNum);
			}
		}
	}
	else if(KeypadMode == KEYPAD_Setting_GearDen)
	{
		if(temp_SetGearDen == 0 && dot_state == false){
			temp_SetGearDen = 5;
			if(temp_SetGearDen >= 60000)
				temp_SetGearDen = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearDen);
		}
		else if(temp_SetGearDen > 0 && dot_state == false){
			temp_SetGearDen = (temp_SetGearDen * 10) + 5;
			if(temp_SetGearDen >= 60000)
				temp_SetGearDen = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearDen);
		}
		else if(temp_SetGearDen == 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearDen = temp_SetGearDen + 0.5;
				dot_value = 1;
				Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearDen);
			}
		}
		else if(temp_SetGearDen > 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearDen = temp_SetGearDen + 0.5;
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearDen);
			}
			else if(dot_value == 1){
				temp_SetGearDen = temp_SetGearDen + 0.05;
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetGearDen);
			}
		}
	}
	else if(KeypadMode == KEYPAD_Setting_Diameter)
	{
		if(temp_SetDiameter == 0 && dot_state == false){
			temp_SetDiameter = 5;
			if(temp_SetDiameter >= 60000)
				temp_SetDiameter = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetDiameter);
		}
		else if(temp_SetDiameter > 0 && dot_state == false){
			temp_SetDiameter = (temp_SetDiameter * 10) + 5;
			if(temp_SetDiameter >= 60000)
				temp_SetDiameter = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetDiameter);
		}
		else if(temp_SetDiameter == 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetDiameter = temp_SetDiameter + 0.5;
				dot_value = 1;
				Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetDiameter);
			}
		}
		else if(temp_SetDiameter > 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetDiameter = temp_SetDiameter + 0.5;
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetDiameter);
			}
			else if(dot_value == 1){
				temp_SetDiameter = temp_SetDiameter + 0.05;
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetDiameter);
			}
		}
	}
	else if(KeypadMode == KEYPAD_Setting_MinMaxVel)
	{
		if(temp_SetMinMaxRpm == 0)
		{
			temp_SetMinMaxRpm = 5;
			if(temp_SetMinMaxRpm >= SettingPosRpmMinMax)
				temp_SetMinMaxRpm = SettingPosRpmMinMax;
		}
		else if(temp_SetMinMaxRpm > 0)
		{
			temp_SetMinMaxRpm = (temp_SetMinMaxRpm * 10) + 5;
			if(temp_SetMinMaxRpm >= SettingPosRpmMinMax)
				temp_SetMinMaxRpm = SettingPosRpmMinMax;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMinMaxRpm);
	}
	Keypadinputvalue.invalidate();*/
}
void MainView::Num6Button()
{
	const int digit = 6; // 현재 버튼에서 입력한 숫자 (Num2Button이므로 2)
	const float fvalue = 0.6f;
	const float fvalue2 = 0.06f;
	// 정수 입력값을 갱신하는 람다 함수
	auto UpdateInputValue = [&](int32_t& value, int32_t minVal, int32_t maxVal) {
		if (value == 0) {
			value = digit;
		}
		else if (value > 0) {
			value = (value * 10) + digit;
		}
		else {
			value = (value * 10) - digit;
		}

		// 최대/최소 범위 제한
		if (value > maxVal) value = maxVal;
		if (value < minVal) value = minVal;
	};

	// 소수점 입력값을 갱신하는 람다 함수
	auto UpdateFloatInputValue = [&](float& value) {
		if (dot_state) {
			if (dot_value == 0) {
				value = value + fvalue;
				dot_value = 1;
			}
			else if (dot_value == 1) {
				value = value + fvalue2;
				dot_value = 2;
			}
		}
		else {
			value = (value * 10) + digit;
		}

		if (value > 60000) value = 60000;
	};

	// 문자열 변환 및 디스플레이 업데이트
	auto UpdateKeypadDisplay = [&](float value, bool bDotstate, int Dotvalue) {
		if (bDotstate) {
			if (Dotvalue == 1)
				Unicode::snprintfFloat(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%.1f", value);
			else if (Dotvalue == 2)
				Unicode::snprintfFloat(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%.2f", value);
		}
		else {
			Unicode::snprintf(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%d", static_cast<int>(value));
		}

		Keypadinputvalue.invalidate();
	};

	// KeypadMode에 따른 값 처리
	switch (KeypadMode) {
	case KEYPAD_Velocity_RPM:
		UpdateInputValue(g_s32Vel_input_Rpmvalue, -g_st_inverter.minmaxRpmvalue, g_st_inverter.minmaxRpmvalue);
		UpdateKeypadDisplay(g_s32Vel_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_RPM:
		UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, g_st_inverter.minmaxRpmvalue);
		UpdateKeypadDisplay(g_s32Pos_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_POS:
		UpdateInputValue(g_s32Pos_input_Posvalue, SettingPosmaxLow, SettingPosmaxHigh);
		UpdateKeypadDisplay(g_s32Pos_input_Posvalue, false, 0);
		break;

	case KEYPAD_Setting_Maxpos:
		UpdateInputValue(temp_SetMaxPos, SettingPosmaxLow, SettingPosmaxHigh);
		UpdateKeypadDisplay(temp_SetMaxPos, false, 0);
		break;

	case KEYPAD_Setting_Minpos:
		UpdateInputValue(temp_SetMinPos, SettingPosminLow, SettingPosminHigh);
		UpdateKeypadDisplay(temp_SetMinPos, false, 0);
		break;

	case KEYPAD_Home_POS:
		UpdateInputValue(g_s32Home_input_Posvalue, g_s32MinPosValue, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Home_input_Posvalue, false, 0);
		break;

	case KEYPAD_Setting_GearNum:
		UpdateFloatInputValue(temp_SetGearNum);
		UpdateKeypadDisplay(temp_SetGearNum, dot_state, dot_value);
		break;

	case KEYPAD_Setting_GearDen:
		UpdateFloatInputValue(temp_SetGearDen);
		UpdateKeypadDisplay(temp_SetGearDen, dot_state, dot_value);
		break;

	case KEYPAD_Setting_Diameter:
		UpdateFloatInputValue(temp_SetDiameter);
		UpdateKeypadDisplay(temp_SetDiameter, dot_state, dot_value);
		break;

	case KEYPAD_Setting_MinMaxVel:
		UpdateInputValue(temp_SetMinMaxRpm, 0, SettingPosRpmMinMax);
		UpdateKeypadDisplay(temp_SetMinMaxRpm, false, 0);
		break;

	case KEYPAD_Direct_Up_POS:
		UpdateInputValue(g_s32Direct_input_UpPosvalue, g_st_Direct.s32DirectActPos, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_UpPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Down_POS:
		UpdateInputValue(g_s32Direct_input_DownPosvalue, g_s32MinPosValue, g_st_Direct.s32DirectActPos);
		UpdateKeypadDisplay(g_s32Direct_input_DownPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Home_POS :
		UpdateInputValue(g_s32Direct_input_Homevalue, g_s32MinPosValue, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_Homevalue, false, 0);
		break;

	case KEYPAD_Wire :
		UpdateFloatInputValue(temp_SetWire);
		UpdateKeypadDisplay(temp_SetWire, dot_state, dot_value);
		break;

	case KEYPAD_Enc_Pulse :
		UpdateInputValue(temp_SetEncPulse,0,20000);
		UpdateKeypadDisplay(temp_SetEncPulse,false,0);
		break;

	default:
		break;
	}
	/*if(KeypadMode == KEYPAD_Velocity_RPM)
	{
		if (g_s32Vel_input_Rpmvalue == 0){
			g_s32Vel_input_Rpmvalue = 6;
			if(g_s32Vel_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Vel_input_Rpmvalue > 0){
			g_s32Vel_input_Rpmvalue = (g_s32Vel_input_Rpmvalue * 10) + 6;
			if(g_s32Vel_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Vel_input_Rpmvalue < 0){
			g_s32Vel_input_Rpmvalue = (g_s32Vel_input_Rpmvalue * 10) - 6;
			if(g_s32Vel_input_Rpmvalue <= (g_st_inverter.minmaxRpmvalue * -1))
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue * -1;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Vel_input_Rpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_RPM)
	{
		if(g_s32Pos_input_Rpmvalue == 0){
			g_s32Pos_input_Rpmvalue = 6;
			if(g_s32Pos_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Pos_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Pos_input_Rpmvalue > 0){
			g_s32Pos_input_Rpmvalue = (g_s32Pos_input_Rpmvalue * 10) + 6;
			if(g_s32Pos_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Pos_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Pos_input_Rpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_POS)
	{
		if (g_s32Pos_input_Posvalue == 0){
			g_s32Pos_input_Posvalue = 6;
			if(g_s32Pos_input_Posvalue >= SettingPosmaxHigh)
				g_s32Pos_input_Posvalue = SettingPosmaxHigh;
		}
		else if(g_s32Pos_input_Posvalue > 0){
			g_s32Pos_input_Posvalue = (g_s32Pos_input_Posvalue * 10) + 6;
			if(g_s32Pos_input_Posvalue >= SettingPosmaxHigh)
				g_s32Pos_input_Posvalue = SettingPosmaxHigh;
		}
		else if(g_s32Pos_input_Posvalue < 0){
			g_s32Pos_input_Posvalue = (g_s32Pos_input_Posvalue * 10) - 6;
			if(g_s32Pos_input_Posvalue <= SettingPosmaxLow)
				g_s32Pos_input_Posvalue = SettingPosmaxLow;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Pos_input_Posvalue);
	}
	else if(KeypadMode == KEYPAD_Setting_Maxpos)
	{
		if(temp_SetMaxPos == 0)
		{
			temp_SetMaxPos = 6;
			if(temp_SetMaxPos >= SettingPosmaxHigh)
				temp_SetMaxPos = SettingPosmaxHigh;
		}
		else if(temp_SetMaxPos > 0)
		{
			temp_SetMaxPos = (temp_SetMaxPos * 10) + 6;
			if(temp_SetMaxPos >= SettingPosmaxHigh)
				temp_SetMaxPos = SettingPosmaxHigh;
		}
		else if(temp_SetMaxPos < 0)
		{
			temp_SetMaxPos = (temp_SetMaxPos * 10) - 6;
			if(temp_SetMaxPos <= SettingPosmaxLow)
				temp_SetMaxPos = SettingPosmaxLow;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMaxPos);
	}
	else if(KeypadMode == KEYPAD_Setting_Minpos)
	{
		if(temp_SetMinPos == 0)
		{
			temp_SetMinPos = 6;
			if(temp_SetMinPos >= SettingPosminHigh)
				temp_SetMinPos = SettingPosminHigh;
		}
		else if(temp_SetMinPos > 0)
		{
			temp_SetMinPos = (temp_SetMinPos * 10) + 6;
			if(temp_SetMinPos >= SettingPosminHigh)
				temp_SetMinPos = SettingPosminHigh;
		}
		else if(temp_SetMinPos < 0)
		{
			temp_SetMinPos = (temp_SetMinPos * 10) - 6;
			if(temp_SetMinPos <= SettingPosminLow)
				temp_SetMinPos = SettingPosminLow;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMinPos);
	}
	else if(KeypadMode == KEYPAD_Home_POS)
	{
		if (g_s32Home_input_Posvalue == 0){
			g_s32Home_input_Posvalue = 6;
			if(g_s32Home_input_Posvalue >= g_s32MaxPosValue)
				g_s32Home_input_Posvalue = g_s32MaxPosValue;
		}
		else if(g_s32Home_input_Posvalue > 0){
			g_s32Home_input_Posvalue = (g_s32Home_input_Posvalue * 10) + 6;
			if(g_s32Home_input_Posvalue >= g_s32MaxPosValue)
				g_s32Home_input_Posvalue = g_s32MaxPosValue;
		}
		else if(g_s32Home_input_Posvalue < 0){
			g_s32Home_input_Posvalue = (g_s32Home_input_Posvalue * 10) - 6;
			if(g_s32Home_input_Posvalue <= (g_s32MinPosValue))
				g_s32Home_input_Posvalue = g_s32MinPosValue;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Home_input_Posvalue);
	}
	else if(KeypadMode == KEYPAD_Setting_GearNum)
	{
		if(temp_SetGearNum == 0 && dot_state == false){
			temp_SetGearNum = 6;
			if(temp_SetGearNum >= 60000)
				temp_SetGearNum = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearNum);
		}
		else if(temp_SetGearNum > 0 && dot_state == false){
			temp_SetGearNum = (temp_SetGearNum * 10) + 6;
			if(temp_SetGearNum >= 60000)
				temp_SetGearNum = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearNum);
		}
		else if(temp_SetGearNum == 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearNum = temp_SetGearNum + 0.6;
				dot_value = 1;
			}
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearNum);
		}
		else if(temp_SetGearNum > 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearNum = temp_SetGearNum + 0.6;
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearNum);
			}
			else if(dot_value == 1){
				temp_SetGearNum = temp_SetGearNum + 0.06;
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetGearNum);
			}
		}

	}
	else if(KeypadMode == KEYPAD_Setting_GearDen)
	{
		if(temp_SetGearDen == 0 && dot_state == false){
			temp_SetGearDen = 6;
			if(temp_SetGearDen >= 60000)
				temp_SetGearDen = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearDen);
		}
		else if(temp_SetGearDen > 0 && dot_state == false){
			temp_SetGearDen = (temp_SetGearDen * 10) + 6;
			if(temp_SetGearDen >= 60000)
				temp_SetGearDen = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearDen);
		}
		else if(temp_SetGearDen == 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearDen = temp_SetGearDen + 0.6;
				dot_value = 1;
				Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearDen);
			}
		}
		else if(temp_SetGearDen > 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearDen = temp_SetGearDen + 0.6;
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearDen);
			}
			else if(dot_value == 1){
				temp_SetGearDen = temp_SetGearDen + 0.06;
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetGearDen);
			}
		}
	}
	else if(KeypadMode == KEYPAD_Setting_Diameter)
	{
		if(temp_SetDiameter == 0 && dot_state == false){
			temp_SetDiameter = 6;
			if(temp_SetDiameter >= 60000)
				temp_SetDiameter = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetDiameter);
		}
		else if(temp_SetDiameter > 0 && dot_state == false){
			temp_SetDiameter = (temp_SetDiameter * 10) + 6;
			if(temp_SetDiameter >= 60000)
				temp_SetDiameter = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetDiameter);
		}
		else if(temp_SetDiameter == 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetDiameter = temp_SetDiameter + 0.6;
				dot_value = 1;
				Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetDiameter);
			}
		}
		else if(temp_SetDiameter > 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetDiameter = temp_SetDiameter + 0.6;
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetDiameter);
			}
			else if(dot_value == 1){
				temp_SetDiameter = temp_SetDiameter + 0.06;
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetDiameter);
			}
		}
	}
	else if(KeypadMode == KEYPAD_Setting_MinMaxVel)
	{
		if(temp_SetMinMaxRpm == 0)
		{
			temp_SetMinMaxRpm = 6;
			if(temp_SetMinMaxRpm >= SettingPosRpmMinMax)
				temp_SetMinMaxRpm = SettingPosRpmMinMax;
		}
		else if(temp_SetMinMaxRpm > 0)
		{
			temp_SetMinMaxRpm = (temp_SetMinMaxRpm * 10) + 6;
			if(temp_SetMinMaxRpm >= SettingPosRpmMinMax)
				temp_SetMinMaxRpm = SettingPosRpmMinMax;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMinMaxRpm);
	}
	Keypadinputvalue.invalidate();*/
}
void MainView::Num7Button()
{
	const int digit = 7; // 현재 버튼에서 입력한 숫자 (Num2Button이므로 2)
	const float fvalue = 0.7f;
	const float fvalue2 = 0.07f;
	// 정수 입력값을 갱신하는 람다 함수
	auto UpdateInputValue = [&](int32_t& value, int32_t minVal, int32_t maxVal) {
		if (value == 0) {
			value = digit;
		}
		else if (value > 0) {
			value = (value * 10) + digit;
		}
		else {
			value = (value * 10) - digit;
		}

		// 최대/최소 범위 제한
		if (value > maxVal) value = maxVal;
		if (value < minVal) value = minVal;
	};

	// 소수점 입력값을 갱신하는 람다 함수
	auto UpdateFloatInputValue = [&](float& value) {
		if (dot_state) {
			if (dot_value == 0) {
				value = value + fvalue;
				dot_value = 1;
			}
			else if (dot_value == 1) {
				value = value+ fvalue2;
				dot_value = 2;
			}
		}
		else {
			value = (value * 10) + digit;
		}

		if (value > 60000) value = 60000;
	};

	// 문자열 변환 및 디스플레이 업데이트
	auto UpdateKeypadDisplay = [&](float value, bool bDotstate, int Dotvalue) {
		if (bDotstate) {
			if (Dotvalue == 1)
				Unicode::snprintfFloat(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%.1f", value);
			else if (Dotvalue == 2)
				Unicode::snprintfFloat(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%.2f", value);
		}
		else {
			Unicode::snprintf(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%d", static_cast<int>(value));
		}

		Keypadinputvalue.invalidate();
	};

	// KeypadMode에 따른 값 처리
	switch (KeypadMode) {
	case KEYPAD_Velocity_RPM:
		UpdateInputValue(g_s32Vel_input_Rpmvalue, -g_st_inverter.minmaxRpmvalue, g_st_inverter.minmaxRpmvalue);
		UpdateKeypadDisplay(g_s32Vel_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_RPM:
		UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, g_st_inverter.minmaxRpmvalue);
		UpdateKeypadDisplay(g_s32Pos_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_POS:
		UpdateInputValue(g_s32Pos_input_Posvalue, SettingPosmaxLow, SettingPosmaxHigh);
		UpdateKeypadDisplay(g_s32Pos_input_Posvalue, false, 0);
		break;

	case KEYPAD_Setting_Maxpos:
		UpdateInputValue(temp_SetMaxPos, SettingPosmaxLow, SettingPosmaxHigh);
		UpdateKeypadDisplay(temp_SetMaxPos, false, 0);
		break;

	case KEYPAD_Setting_Minpos:
		UpdateInputValue(temp_SetMinPos, SettingPosminLow, SettingPosminHigh);
		UpdateKeypadDisplay(temp_SetMinPos, false, 0);
		break;

	case KEYPAD_Home_POS:
		UpdateInputValue(g_s32Home_input_Posvalue, g_s32MinPosValue, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Home_input_Posvalue, false, 0);
		break;

	case KEYPAD_Setting_GearNum:
		UpdateFloatInputValue(temp_SetGearNum);
		UpdateKeypadDisplay(temp_SetGearNum, dot_state, dot_value);
		break;

	case KEYPAD_Setting_GearDen:
		UpdateFloatInputValue(temp_SetGearDen);
		UpdateKeypadDisplay(temp_SetGearDen, dot_state, dot_value);
		break;

	case KEYPAD_Setting_Diameter:
		UpdateFloatInputValue(temp_SetDiameter);
		UpdateKeypadDisplay(temp_SetDiameter, dot_state, dot_value);
		break;

	case KEYPAD_Setting_MinMaxVel:
		UpdateInputValue(temp_SetMinMaxRpm, 0, SettingPosRpmMinMax);
		UpdateKeypadDisplay(temp_SetMinMaxRpm, false, 0);
		break;

	case KEYPAD_Direct_Up_POS:
		UpdateInputValue(g_s32Direct_input_UpPosvalue, g_st_Direct.s32DirectActPos, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_UpPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Down_POS:
		UpdateInputValue(g_s32Direct_input_DownPosvalue, g_s32MinPosValue, g_st_Direct.s32DirectActPos);
		UpdateKeypadDisplay(g_s32Direct_input_DownPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Home_POS :
		UpdateInputValue(g_s32Direct_input_Homevalue, g_s32MinPosValue, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_Homevalue, false, 0);
		break;

	case KEYPAD_Wire :
		UpdateFloatInputValue(temp_SetWire);
		UpdateKeypadDisplay(temp_SetWire, dot_state, dot_value);
		break;

	case KEYPAD_Enc_Pulse :
		UpdateInputValue(temp_SetEncPulse,0,20000);
		UpdateKeypadDisplay(temp_SetEncPulse,false,0);
		break;

	default:
		break;
	}
	/*if(KeypadMode == KEYPAD_Velocity_RPM)
	{
		if (g_s32Vel_input_Rpmvalue == 0){
			g_s32Vel_input_Rpmvalue = 7;
			if(g_s32Vel_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Vel_input_Rpmvalue > 0){
			g_s32Vel_input_Rpmvalue = (g_s32Vel_input_Rpmvalue * 10) + 7;
			if(g_s32Vel_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Vel_input_Rpmvalue < 0){
			g_s32Vel_input_Rpmvalue = (g_s32Vel_input_Rpmvalue * 10) - 7;
			if(g_s32Vel_input_Rpmvalue <= (g_st_inverter.minmaxRpmvalue * -1))
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue * -1;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Vel_input_Rpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_RPM)
	{
		if(g_s32Pos_input_Rpmvalue == 0){
			g_s32Pos_input_Rpmvalue = 7;
			if(g_s32Pos_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Pos_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Pos_input_Rpmvalue > 0){
			g_s32Pos_input_Rpmvalue = (g_s32Pos_input_Rpmvalue * 10) + 7;
			if(g_s32Pos_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Pos_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Pos_input_Rpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_POS)
	{
		if (g_s32Pos_input_Posvalue == 0){
			g_s32Pos_input_Posvalue = 7;
			if(g_s32Pos_input_Posvalue >= SettingPosmaxHigh)
				g_s32Pos_input_Posvalue = SettingPosmaxHigh;
		}
		else if(g_s32Pos_input_Posvalue > 0){
			g_s32Pos_input_Posvalue = (g_s32Pos_input_Posvalue * 10) + 7;
			if(g_s32Pos_input_Posvalue >= SettingPosmaxHigh)
				g_s32Pos_input_Posvalue = SettingPosmaxHigh;
		}
		else if(g_s32Pos_input_Posvalue < 0){
			g_s32Pos_input_Posvalue = (g_s32Pos_input_Posvalue * 10) - 7;
			if(g_s32Pos_input_Posvalue <= SettingPosmaxLow)
				g_s32Pos_input_Posvalue = SettingPosmaxLow;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Pos_input_Posvalue);
	}
	else if(KeypadMode == KEYPAD_Setting_Maxpos)
	{
		if(temp_SetMaxPos == 0)
		{
			temp_SetMaxPos = 7;
			if(temp_SetMaxPos >= SettingPosmaxHigh)
				temp_SetMaxPos = SettingPosmaxHigh;
		}
		else if(temp_SetMaxPos > 0)
		{
			temp_SetMaxPos = (temp_SetMaxPos * 10) + 7;
			if(temp_SetMaxPos >= SettingPosmaxHigh)
				temp_SetMaxPos = SettingPosmaxHigh;
		}
		else if(temp_SetMaxPos < 0)
		{
			temp_SetMaxPos = (temp_SetMaxPos * 10) - 7;
			if(temp_SetMaxPos <= SettingPosmaxLow)
				temp_SetMaxPos = SettingPosmaxLow;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMaxPos);
	}
	else if(KeypadMode == KEYPAD_Setting_Minpos)
	{
		if(temp_SetMinPos == 0)
		{
			temp_SetMinPos = 7;
			if(temp_SetMinPos >= SettingPosminHigh)
				temp_SetMinPos = SettingPosminHigh;
		}
		else if(temp_SetMinPos > 0)
		{
			temp_SetMinPos = (temp_SetMinPos * 10) + 7;
			if(temp_SetMinPos >= SettingPosminHigh)
				temp_SetMinPos = SettingPosminHigh;
		}
		else if(temp_SetMinPos < 0)
		{
			temp_SetMinPos = (temp_SetMinPos * 10) - 7;
			if(temp_SetMinPos <= SettingPosminLow)
				temp_SetMinPos = SettingPosminLow;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMinPos);
	}
	else if(KeypadMode == KEYPAD_Home_POS)
	{
		if (g_s32Home_input_Posvalue == 0){
			g_s32Home_input_Posvalue = 7;
			if(g_s32Home_input_Posvalue >= g_s32MaxPosValue)
				g_s32Home_input_Posvalue = g_s32MaxPosValue;
		}
		else if(g_s32Home_input_Posvalue > 0){
			g_s32Home_input_Posvalue = (g_s32Home_input_Posvalue * 10) + 7;
			if(g_s32Home_input_Posvalue >= g_s32MaxPosValue)
				g_s32Home_input_Posvalue = g_s32MaxPosValue;
		}
		else if(g_s32Home_input_Posvalue < 0){
			g_s32Home_input_Posvalue = (g_s32Home_input_Posvalue * 10) - 7;
			if(g_s32Home_input_Posvalue <= (g_s32MinPosValue))
				g_s32Home_input_Posvalue = g_s32MinPosValue;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Home_input_Posvalue);
	}
	else if(KeypadMode == KEYPAD_Setting_GearNum)
	{
		if(temp_SetGearNum == 0 && dot_state == false){
			temp_SetGearNum = 7;
			if(temp_SetGearNum >= 60000)
				temp_SetGearNum = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearNum);
		}
		else if(temp_SetGearNum > 0 && dot_state == false){
			temp_SetGearNum = (temp_SetGearNum * 10) + 7;
			if(temp_SetGearNum >= 60000)
				temp_SetGearNum = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearNum);
		}
		else if(temp_SetGearNum == 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearNum = temp_SetGearNum + 0.7;
				dot_value = 1;
			}
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearNum);
		}
		else if(temp_SetGearNum > 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearNum = temp_SetGearNum + 0.7;
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearNum);
			}
			else if(dot_value == 1){
				temp_SetGearNum = temp_SetGearNum + 0.07;
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetGearNum);
			}
		}

	}
	else if(KeypadMode == KEYPAD_Setting_GearDen)
	{
		if(temp_SetGearDen == 0 && dot_state == false){
			temp_SetGearDen = 7;
			if(temp_SetGearDen >= 60000)
				temp_SetGearDen = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearDen);
		}
		else if(temp_SetGearDen > 0 && dot_state == false){
			temp_SetGearDen = (temp_SetGearDen * 10) + 7;
			if(temp_SetGearDen >= 60000)
				temp_SetGearDen = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearDen);
		}
		else if(temp_SetGearDen == 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearDen = temp_SetGearDen + 0.7;
				dot_value = 1;
				Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearDen);
			}
		}
		else if(temp_SetGearDen > 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearDen = temp_SetGearDen + 0.7;
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearDen);
			}
			else if(dot_value == 1){
				temp_SetGearDen = temp_SetGearDen + 0.07;
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetGearDen);
			}
		}
	}
	else if(KeypadMode == KEYPAD_Setting_Diameter)
	{
		if(temp_SetDiameter == 0 && dot_state == false){
			temp_SetDiameter = 7;
			if(temp_SetDiameter >= 60000)
				temp_SetDiameter = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetDiameter);
		}
		else if(temp_SetDiameter > 0 && dot_state == false){
			temp_SetDiameter = (temp_SetDiameter * 10) + 7;
			if(temp_SetDiameter >= 60000)
				temp_SetDiameter = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetDiameter);
		}
		else if(temp_SetDiameter == 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetDiameter = temp_SetDiameter + 0.7;
				dot_value = 1;
				Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetDiameter);
			}
		}
		else if(temp_SetDiameter > 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetDiameter = temp_SetDiameter + 0.7;
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetDiameter);
			}
			else if(dot_value == 1){
				temp_SetDiameter = temp_SetDiameter + 0.07;
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetDiameter);
			}
		}
	}
	else if(KeypadMode == KEYPAD_Setting_MinMaxVel)
	{
		if(temp_SetMinMaxRpm == 0)
		{
			temp_SetMinMaxRpm = 7;
			if(temp_SetMinMaxRpm >= SettingPosRpmMinMax)
				temp_SetMinMaxRpm = SettingPosRpmMinMax;
		}
		else if(temp_SetMinMaxRpm > 0)
		{
			temp_SetMinMaxRpm = (temp_SetMinMaxRpm * 10) + 7;
			if(temp_SetMinMaxRpm >= SettingPosRpmMinMax)
				temp_SetMinMaxRpm = SettingPosRpmMinMax;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMinMaxRpm);
	}
	Keypadinputvalue.invalidate();*/
}
void MainView::Num8Button()
{
	const int digit = 8; // 현재 버튼에서 입력한 숫자 (Num2Button이므로 2)
	const float fvalue = 0.8f;
	const float fvalue2 = 0.08f;
	// 정수 입력값을 갱신하는 람다 함수
	auto UpdateInputValue = [&](int32_t& value, int32_t minVal, int32_t maxVal) {
		if (value == 0) {
			value = digit;
		}
		else if (value > 0) {
			value = (value * 10) + digit;
		}
		else {
			value = (value * 10) - digit;
		}

		// 최대/최소 범위 제한
		if (value > maxVal) value = maxVal;
		if (value < minVal) value = minVal;
	};

	// 소수점 입력값을 갱신하는 람다 함수
	auto UpdateFloatInputValue = [&](float& value) {
		if (dot_state) {
			if (dot_value == 0) {
				value = value + fvalue;
				dot_value = 1;
			}
			else if (dot_value == 1) {
				value = value+ fvalue2;
				dot_value = 2;
			}
		}
		else {
			value = (value * 10) + digit;
		}

		if (value > 60000) value = 60000;
	};

	// 문자열 변환 및 디스플레이 업데이트
	auto UpdateKeypadDisplay = [&](float value, bool bDotstate, int Dotvalue) {
		if (bDotstate) {
			if (Dotvalue == 1)
				Unicode::snprintfFloat(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%.1f", value);
			else if (Dotvalue == 2)
				Unicode::snprintfFloat(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%.2f", value);
		}
		else {
			Unicode::snprintf(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%d", static_cast<int>(value));
		}

		Keypadinputvalue.invalidate();
	};

	// KeypadMode에 따른 값 처리
	switch (KeypadMode) {
	case KEYPAD_Velocity_RPM:
		UpdateInputValue(g_s32Vel_input_Rpmvalue, -g_st_inverter.minmaxRpmvalue, g_st_inverter.minmaxRpmvalue);
		UpdateKeypadDisplay(g_s32Vel_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_RPM:
		UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, g_st_inverter.minmaxRpmvalue);
		UpdateKeypadDisplay(g_s32Pos_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_POS:
		UpdateInputValue(g_s32Pos_input_Posvalue, SettingPosmaxLow, SettingPosmaxHigh);
		UpdateKeypadDisplay(g_s32Pos_input_Posvalue, false, 0);
		break;

	case KEYPAD_Setting_Maxpos:
		UpdateInputValue(temp_SetMaxPos, SettingPosmaxLow, SettingPosmaxHigh);
		UpdateKeypadDisplay(temp_SetMaxPos, false, 0);
		break;

	case KEYPAD_Setting_Minpos:
		UpdateInputValue(temp_SetMinPos, SettingPosminLow, SettingPosminHigh);
		UpdateKeypadDisplay(temp_SetMinPos, false, 0);
		break;

	case KEYPAD_Home_POS:
		UpdateInputValue(g_s32Home_input_Posvalue, g_s32MinPosValue, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Home_input_Posvalue, false, 0);
		break;

	case KEYPAD_Setting_GearNum:
		UpdateFloatInputValue(temp_SetGearNum);
		UpdateKeypadDisplay(temp_SetGearNum, dot_state, dot_value);
		break;

	case KEYPAD_Setting_GearDen:
		UpdateFloatInputValue(temp_SetGearDen);
		UpdateKeypadDisplay(temp_SetGearDen, dot_state, dot_value);
		break;

	case KEYPAD_Setting_Diameter:
		UpdateFloatInputValue(temp_SetDiameter);
		UpdateKeypadDisplay(temp_SetDiameter, dot_state, dot_value);
		break;

	case KEYPAD_Setting_MinMaxVel:
		UpdateInputValue(temp_SetMinMaxRpm, 0, SettingPosRpmMinMax);
		UpdateKeypadDisplay(temp_SetMinMaxRpm, false, 0);
		break;

	case KEYPAD_Direct_Up_POS:
		UpdateInputValue(g_s32Direct_input_UpPosvalue, g_st_Direct.s32DirectActPos, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_UpPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Down_POS:
		UpdateInputValue(g_s32Direct_input_DownPosvalue, g_s32MinPosValue, g_st_Direct.s32DirectActPos);
		UpdateKeypadDisplay(g_s32Direct_input_DownPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Home_POS :
		UpdateInputValue(g_s32Direct_input_Homevalue, g_s32MinPosValue, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_Homevalue, false, 0);
		break;

	case KEYPAD_Wire :
		UpdateFloatInputValue(temp_SetWire);
		UpdateKeypadDisplay(temp_SetWire, dot_state, dot_value);
		break;

	case KEYPAD_Enc_Pulse :
		UpdateInputValue(temp_SetEncPulse,0,20000);
		UpdateKeypadDisplay(temp_SetEncPulse,false,0);
		break;

	default:
		break;
	}
	/*if(KeypadMode == KEYPAD_Velocity_RPM)
	{
		if (g_s32Vel_input_Rpmvalue == 0){
			g_s32Vel_input_Rpmvalue = 8;
			if(g_s32Vel_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Vel_input_Rpmvalue > 0){
			g_s32Vel_input_Rpmvalue = (g_s32Vel_input_Rpmvalue * 10) + 8;
			if(g_s32Vel_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Vel_input_Rpmvalue < 0){
			g_s32Vel_input_Rpmvalue = (g_s32Vel_input_Rpmvalue * 10) - 8;
			if(g_s32Vel_input_Rpmvalue <= (g_st_inverter.minmaxRpmvalue * -1))
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue * -1;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Vel_input_Rpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_RPM)
	{
		if(g_s32Pos_input_Rpmvalue == 0){
			g_s32Pos_input_Rpmvalue = 8;
			if(g_s32Pos_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Pos_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Pos_input_Rpmvalue > 0){
			g_s32Pos_input_Rpmvalue = (g_s32Pos_input_Rpmvalue * 10) + 8;
			if(g_s32Pos_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Pos_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Pos_input_Rpmvalue);

	}
	else if(KeypadMode == KEYPAD_Position_POS)
	{
		if (g_s32Pos_input_Posvalue == 0){
			g_s32Pos_input_Posvalue = 8;
			if(g_s32Pos_input_Posvalue >= SettingPosmaxHigh)
				g_s32Pos_input_Posvalue = SettingPosmaxHigh;
		}
		else if(g_s32Pos_input_Posvalue > 0){
			g_s32Pos_input_Posvalue = (g_s32Pos_input_Posvalue * 10) + 8;
			if(g_s32Pos_input_Posvalue >= SettingPosmaxHigh)
				g_s32Pos_input_Posvalue = SettingPosmaxHigh;
		}
		else if(g_s32Pos_input_Posvalue < 0){
			g_s32Pos_input_Posvalue = (g_s32Pos_input_Posvalue * 10) - 8;
			if(g_s32Pos_input_Posvalue <= SettingPosmaxLow)
				g_s32Pos_input_Posvalue = SettingPosmaxLow;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Pos_input_Posvalue);
	}
	else if(KeypadMode == KEYPAD_Setting_Maxpos)
	{
		if(temp_SetMaxPos == 0)
		{
			temp_SetMaxPos = 1;
			if(temp_SetMaxPos >= SettingPosmaxHigh)
				temp_SetMaxPos = SettingPosmaxHigh;
		}
		else if(temp_SetMaxPos > 0)
		{
			temp_SetMaxPos = (temp_SetMaxPos * 10) + 8;
			if(temp_SetMaxPos >= SettingPosmaxHigh)
				temp_SetMaxPos = SettingPosmaxHigh;
		}
		else if(temp_SetMaxPos < 0)
		{
			temp_SetMaxPos = (temp_SetMaxPos * 10) - 8;
			if(temp_SetMaxPos <= SettingPosmaxLow)
				temp_SetMaxPos = SettingPosmaxLow;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMaxPos);
	}
	else if(KeypadMode == KEYPAD_Setting_Minpos)
	{
		if(temp_SetMinPos == 0)
		{
			temp_SetMinPos = 1;
			if(temp_SetMinPos >= SettingPosminHigh)
				temp_SetMinPos = SettingPosminHigh;
		}
		else if(temp_SetMinPos > 0)
		{
			temp_SetMinPos = (temp_SetMinPos * 10) + 8;
			if(temp_SetMinPos >= SettingPosminHigh)
				temp_SetMinPos = SettingPosminHigh;
		}
		else if(temp_SetMinPos < 0)
		{
			temp_SetMinPos = (temp_SetMinPos * 10) - 8;
			if(temp_SetMinPos <= SettingPosminLow)
				temp_SetMinPos = SettingPosminLow;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMinPos);
	}
	else if(KeypadMode == KEYPAD_Home_POS)
	{
		if (g_s32Home_input_Posvalue == 0){
			g_s32Home_input_Posvalue = 8;
			if(g_s32Home_input_Posvalue >= g_s32MaxPosValue)
				g_s32Home_input_Posvalue = g_s32MaxPosValue;
		}
		else if(g_s32Home_input_Posvalue > 0){
			g_s32Home_input_Posvalue = (g_s32Home_input_Posvalue * 10) + 8;
			if(g_s32Home_input_Posvalue >= g_s32MaxPosValue)
				g_s32Home_input_Posvalue = g_s32MaxPosValue;
		}
		else if(g_s32Home_input_Posvalue < 0){
			g_s32Home_input_Posvalue = (g_s32Home_input_Posvalue * 10) - 8;
			if(g_s32Home_input_Posvalue <= (g_s32MinPosValue))
				g_s32Home_input_Posvalue = g_s32MinPosValue;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Home_input_Posvalue);
	}
	else if(KeypadMode == KEYPAD_Setting_GearNum)
	{
		if(temp_SetGearNum == 0 && dot_state == false){
			temp_SetGearNum = 8;
			if(temp_SetGearNum >= 60000)
				temp_SetGearNum = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearNum);
		}
		else if(temp_SetGearNum > 0 && dot_state == false){
			temp_SetGearNum = (temp_SetGearNum * 10) + 8;
			if(temp_SetGearNum >= 60000)
				temp_SetGearNum = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearNum);
		}
		else if(temp_SetGearNum == 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearNum = temp_SetGearNum + 0.8;
				dot_value = 1;
			}
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearNum);
		}
		else if(temp_SetGearNum > 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearNum = temp_SetGearNum + 0.8;
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearNum);
			}
			else if(dot_value == 1){
				temp_SetGearNum = temp_SetGearNum + 0.08;
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetGearNum);
			}
		}

	}
	else if(KeypadMode == KEYPAD_Setting_GearDen)
	{
		if(temp_SetGearDen == 0 && dot_state == false){
			temp_SetGearDen = 8;
			if(temp_SetGearDen >= 60000)
				temp_SetGearDen = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearDen);
		}
		else if(temp_SetGearDen > 0 && dot_state == false){
			temp_SetGearDen = (temp_SetGearDen * 10) + 8;
			if(temp_SetGearDen >= 60000)
				temp_SetGearDen = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearDen);
		}
		else if(temp_SetGearDen == 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearDen = temp_SetGearDen + 0.8;
				dot_value = 1;
				Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearDen);
			}
		}
		else if(temp_SetGearDen > 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearDen = temp_SetGearDen + 0.8;
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearDen);
			}
			else if(dot_value == 1){
				temp_SetGearDen = temp_SetGearDen + 0.08;
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetGearDen);
			}
		}
	}
	else if(KeypadMode == KEYPAD_Setting_Diameter)
	{
		if(temp_SetDiameter == 0 && dot_state == false){
			temp_SetDiameter = 8;
			if(temp_SetDiameter >= 60000)
				temp_SetDiameter = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetDiameter);
		}
		else if(temp_SetDiameter > 0 && dot_state == false){
			temp_SetDiameter = (temp_SetDiameter * 10) + 8;
			if(temp_SetDiameter >= 60000)
				temp_SetDiameter = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetDiameter);
		}
		else if(temp_SetDiameter == 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetDiameter = temp_SetDiameter + 0.8;
				dot_value = 1;
				Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetDiameter);
			}
		}
		else if(temp_SetDiameter > 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetDiameter = temp_SetDiameter + 0.8;
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetDiameter);
			}
			else if(dot_value == 1){
				temp_SetDiameter = temp_SetDiameter + 0.08;
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetDiameter);
			}
		}
	}
	else if(KeypadMode == KEYPAD_Setting_MinMaxVel)
	{
		if(temp_SetMinMaxRpm == 0)
		{
			temp_SetMinMaxRpm = 8;
			if(temp_SetMinMaxRpm >= SettingPosRpmMinMax)
				temp_SetMinMaxRpm = SettingPosRpmMinMax;
		}
		else if(temp_SetMinMaxRpm > 0)
		{
			temp_SetMinMaxRpm = (temp_SetMinMaxRpm * 10) + 8;
			if(temp_SetMinMaxRpm >= SettingPosRpmMinMax)
				temp_SetMinMaxRpm = SettingPosRpmMinMax;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMinMaxRpm);
	}
	Keypadinputvalue.invalidate();*/
}
void MainView::Num9Button()
{
	const int digit = 9; // 현재 버튼에서 입력한 숫자 (Num2Button이므로 2)
	const float fvalue = 0.9f;
	const float fvalue2 = 0.09f;
	// 정수 입력값을 갱신하는 람다 함수
	auto UpdateInputValue = [&](int32_t& value, int32_t minVal, int32_t maxVal) {
		if (value == 0) {
			value = digit;
		}
		else if (value > 0) {
			value = (value * 10) + digit;
		}
		else {
			value = (value * 10) - digit;
		}

		// 최대/최소 범위 제한
		if (value > maxVal) value = maxVal;
		if (value < minVal) value = minVal;
	};

	// 소수점 입력값을 갱신하는 람다 함수
	auto UpdateFloatInputValue = [&](float& value) {
		if (dot_state) {
			if (dot_value == 0) {
				value = value + 0.9f;
				dot_value = 1;
			}
			else if (dot_value == 1) {
				value = value+ 0.09f;
				dot_value = 2;
			}
		}
		else {
			value = (value * 10) + digit;
		}

		if (value > 60000) value = 60000;
	};

	// 문자열 변환 및 디스플레이 업데이트
	auto UpdateKeypadDisplay = [&](float value, bool bDotstate, int Dotvalue) {
		if (bDotstate) {
			if (Dotvalue == 1)
				Unicode::snprintfFloat(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%.1f", value);
			else if (Dotvalue == 2)
				Unicode::snprintfFloat(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%.2f", value);
		}
		else {
			Unicode::snprintf(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%d", static_cast<int>(value));
		}

		Keypadinputvalue.invalidate();
	};

	// KeypadMode에 따른 값 처리
	switch (KeypadMode) {
	case KEYPAD_Velocity_RPM:
		UpdateInputValue(g_s32Vel_input_Rpmvalue, -g_st_inverter.minmaxRpmvalue, g_st_inverter.minmaxRpmvalue);
		UpdateKeypadDisplay(g_s32Vel_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_RPM:
		UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, g_st_inverter.minmaxRpmvalue);
		UpdateKeypadDisplay(g_s32Pos_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_POS:
		UpdateInputValue(g_s32Pos_input_Posvalue, SettingPosmaxLow, SettingPosmaxHigh);
		UpdateKeypadDisplay(g_s32Pos_input_Posvalue, false, 0);
		break;

	case KEYPAD_Setting_Maxpos:
		UpdateInputValue(temp_SetMaxPos, SettingPosmaxLow, SettingPosmaxHigh);
		UpdateKeypadDisplay(temp_SetMaxPos, false, 0);
		break;

	case KEYPAD_Setting_Minpos:
		UpdateInputValue(temp_SetMinPos, SettingPosminLow, SettingPosminHigh);
		UpdateKeypadDisplay(temp_SetMinPos, false, 0);
		break;

	case KEYPAD_Home_POS:
		UpdateInputValue(g_s32Home_input_Posvalue, g_s32MinPosValue, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Home_input_Posvalue, false, 0);
		break;

	case KEYPAD_Setting_GearNum:
		UpdateFloatInputValue(temp_SetGearNum);
		UpdateKeypadDisplay(temp_SetGearNum, dot_state, dot_value);
		break;

	case KEYPAD_Setting_GearDen:
		UpdateFloatInputValue(temp_SetGearDen);
		UpdateKeypadDisplay(temp_SetGearDen, dot_state, dot_value);
		break;

	case KEYPAD_Setting_Diameter:
		UpdateFloatInputValue(temp_SetDiameter);
		UpdateKeypadDisplay(temp_SetDiameter, dot_state, dot_value);
		break;

	case KEYPAD_Setting_MinMaxVel:
		UpdateInputValue(temp_SetMinMaxRpm, 0, SettingPosRpmMinMax);
		UpdateKeypadDisplay(temp_SetMinMaxRpm, false, 0);
		break;

	case KEYPAD_Direct_Up_POS:
		UpdateInputValue(g_s32Direct_input_UpPosvalue, g_s32MinPosValue, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_UpPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Down_POS:
		UpdateInputValue(g_s32Direct_input_DownPosvalue, g_s32MinPosValue, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_DownPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Home_POS :
		UpdateInputValue(g_s32Direct_input_Homevalue, g_s32MinPosValue, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_Homevalue, false, 0);
		break;

	case KEYPAD_Wire :
		UpdateFloatInputValue(temp_SetWire);
		UpdateKeypadDisplay(temp_SetWire, dot_state, dot_value);
		break;

	case KEYPAD_Enc_Pulse :
		UpdateInputValue(temp_SetEncPulse,0,20000);
		UpdateKeypadDisplay(temp_SetEncPulse,false,0);
		break;

	default:
		break;
	}
	/*if(KeypadMode == KEYPAD_Velocity_RPM)
	{
		if (g_s32Vel_input_Rpmvalue == 0){
			g_s32Vel_input_Rpmvalue = 9;
			if(g_s32Vel_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Vel_input_Rpmvalue > 0){
			g_s32Vel_input_Rpmvalue = (g_s32Vel_input_Rpmvalue * 10) + 9;
			if(g_s32Vel_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Vel_input_Rpmvalue < 0){
			g_s32Vel_input_Rpmvalue = (g_s32Vel_input_Rpmvalue * 10) - 9;
			if(g_s32Vel_input_Rpmvalue <= (g_st_inverter.minmaxRpmvalue * -1))
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue * -1;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Vel_input_Rpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_RPM)
	{
		if(g_s32Pos_input_Rpmvalue == 0){
			g_s32Pos_input_Rpmvalue = 9;
			if(g_s32Pos_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Pos_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Pos_input_Rpmvalue > 0){
			g_s32Pos_input_Rpmvalue = (g_s32Pos_input_Rpmvalue * 10) + 9;
			if(g_s32Pos_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Pos_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Pos_input_Rpmvalue);

	}
	else if(KeypadMode == KEYPAD_Position_POS)
	{
		if (g_s32Pos_input_Posvalue == 0){
			g_s32Pos_input_Posvalue = 9;
			if(g_s32Pos_input_Posvalue >= SettingPosmaxHigh)
				g_s32Pos_input_Posvalue = SettingPosmaxHigh;
		}
		else if(g_s32Pos_input_Posvalue > 0){
			g_s32Pos_input_Posvalue = (g_s32Pos_input_Posvalue * 10) + 9;
			if(g_s32Pos_input_Posvalue >= SettingPosmaxHigh)
				g_s32Pos_input_Posvalue = SettingPosmaxHigh;
		}
		else if(g_s32Pos_input_Posvalue < 0){
			g_s32Pos_input_Posvalue = (g_s32Pos_input_Posvalue * 10) - 9;
			if(g_s32Pos_input_Posvalue <= SettingPosmaxLow)
				g_s32Pos_input_Posvalue = SettingPosmaxLow;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Pos_input_Posvalue);
	}
	else if(KeypadMode == KEYPAD_Setting_Maxpos)
	{
		if(temp_SetMaxPos == 0)
		{
			temp_SetMaxPos = 1;
			if(temp_SetMaxPos >= SettingPosmaxHigh)
				temp_SetMaxPos = SettingPosmaxHigh;
		}
		else if(temp_SetMaxPos > 0)
		{
			temp_SetMaxPos = (temp_SetMaxPos * 10) + 9;
			if(temp_SetMaxPos >= SettingPosmaxHigh)
				temp_SetMaxPos = SettingPosmaxHigh;
		}
		else if(temp_SetMaxPos < 0)
		{
			temp_SetMaxPos = (temp_SetMaxPos * 10) - 9;
			if(temp_SetMaxPos <= SettingPosmaxLow)
				temp_SetMaxPos = SettingPosmaxLow;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMaxPos);
	}
	else if(KeypadMode == KEYPAD_Setting_Minpos)
	{
		if(temp_SetMinPos == 0)
		{
			temp_SetMinPos = 1;
			if(temp_SetMinPos >= SettingPosminHigh)
				temp_SetMinPos = SettingPosminHigh;
		}
		else if(temp_SetMinPos > 0)
		{
			temp_SetMinPos = (temp_SetMinPos * 10) + 9;
			if(temp_SetMinPos >= SettingPosminHigh)
				temp_SetMinPos = SettingPosminHigh;
		}
		else if(temp_SetMinPos < 0)
		{
			temp_SetMinPos = (temp_SetMinPos * 10) - 9;
			if(temp_SetMinPos <= SettingPosminLow)
				temp_SetMinPos = SettingPosminLow;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMinPos);
	}
	else if(KeypadMode == KEYPAD_Home_POS)
		{
			if (g_s32Home_input_Posvalue == 0){
				g_s32Home_input_Posvalue = 9;
				if(g_s32Home_input_Posvalue >= g_s32MaxPosValue)
					g_s32Home_input_Posvalue = g_s32MaxPosValue;
			}
			else if(g_s32Home_input_Posvalue > 0){
				g_s32Home_input_Posvalue = (g_s32Home_input_Posvalue * 10) + 9;
				if(g_s32Home_input_Posvalue >= g_s32MaxPosValue)
					g_s32Home_input_Posvalue = g_s32MaxPosValue;
			}
			else if(g_s32Home_input_Posvalue < 0){
				g_s32Home_input_Posvalue = (g_s32Home_input_Posvalue * 10) - 9;
				if(g_s32Home_input_Posvalue <= (g_s32MinPosValue))
					g_s32Home_input_Posvalue = g_s32MinPosValue;
			}

			Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Home_input_Posvalue);
		}
	else if(KeypadMode == KEYPAD_Setting_GearNum)
	{
		if(temp_SetGearNum == 0 && dot_state == false){
			temp_SetGearNum = 9;
			if(temp_SetGearNum >= 60000)
				temp_SetGearNum = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearNum);
		}
		else if(temp_SetGearNum > 0 && dot_state == false){
			temp_SetGearNum = (temp_SetGearNum * 10) + 9;
			if(temp_SetGearNum >= 60000)
				temp_SetGearNum = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearNum);
		}
		else if(temp_SetGearNum == 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearNum = temp_SetGearNum + 0.9;
				dot_value = 1;
			}
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearNum);
		}
		else if(temp_SetGearNum > 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearNum = temp_SetGearNum + 0.9;
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearNum);
			}
			else if(dot_value == 1){
				temp_SetGearNum = temp_SetGearNum + 0.09;
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetGearNum);
			}
		}

	}
	else if(KeypadMode == KEYPAD_Setting_GearDen)
	{
		if(temp_SetGearDen == 0 && dot_state == false){
			temp_SetGearDen = 9;
			if(temp_SetGearDen >= 60000)
				temp_SetGearDen = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearDen);
		}
		else if(temp_SetGearDen > 0 && dot_state == false){
			temp_SetGearDen = (temp_SetGearDen * 10) + 9;
			if(temp_SetGearDen >= 60000)
				temp_SetGearDen = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearDen);
		}
		else if(temp_SetGearDen == 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearDen = temp_SetGearDen + 0.9;
				dot_value = 1;
				Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearDen);
			}
		}
		else if(temp_SetGearDen > 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetGearDen = temp_SetGearDen + 0.9;
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearDen);
			}
			else if(dot_value == 1){
				temp_SetGearDen = temp_SetGearDen + 0.09;
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetGearDen);
			}
		}
	}
	else if(KeypadMode == KEYPAD_Setting_Diameter)
	{
		if(temp_SetDiameter == 0 && dot_state == false){
			temp_SetDiameter = 9;
			if(temp_SetDiameter >= 60000)
				temp_SetDiameter = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetDiameter);
		}
		else if(temp_SetDiameter > 0 && dot_state == false){
			temp_SetDiameter = (temp_SetDiameter * 10) + 9;
			if(temp_SetDiameter >= 60000)
				temp_SetDiameter = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetDiameter);
		}
		else if(temp_SetDiameter == 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetDiameter = temp_SetDiameter + 0.9;
				dot_value = 1;
				Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetDiameter);
			}
		}
		else if(temp_SetDiameter > 0 && dot_state == true)
		{
			if(dot_value == 0){
				temp_SetDiameter = temp_SetDiameter + 0.9;
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetDiameter);
			}
			else if(dot_value == 1){
				temp_SetDiameter = temp_SetDiameter + 0.09;
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetDiameter);
			}
		}
	}
	else if(KeypadMode == KEYPAD_Setting_MinMaxVel)
	{
		if(temp_SetMinMaxRpm == 0)
		{
			temp_SetMinMaxRpm = 9;
			if(temp_SetMinMaxRpm >= SettingPosRpmMinMax)
				temp_SetMinMaxRpm = SettingPosRpmMinMax;
		}
		else if(temp_SetMinMaxRpm > 0)
		{
			temp_SetMinMaxRpm = (temp_SetMinMaxRpm * 10) + 9;
			if(temp_SetMinMaxRpm >= SettingPosRpmMinMax)
				temp_SetMinMaxRpm = SettingPosRpmMinMax;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMinMaxRpm);
	}
	Keypadinputvalue.invalidate();*/
}
void MainView::Num0Button()
{
	const int digit = 0; // 현재 버튼에서 입력한 숫자 (Num2Button이므로 2)

	// 정수 입력값을 갱신하는 람다 함수
	auto UpdateInputValue = [&](int32_t& value, int32_t minVal, int32_t maxVal) {
		if (value == 0) {
			value = digit;
		}
		else if (value > 0) {
			value = (value * 10) + digit;
		}
		else {
			value = (value * 10) - digit;
		}

		// 최대/최소 범위 제한
		if (value > maxVal) value = maxVal;
		if (value < minVal) value = minVal;
	};

	// 소수점 입력값을 갱신하는 람다 함수
	auto UpdateFloatInputValue = [&](float& value) {
		if (dot_state) {
			if (dot_value == 0) {
				value = value;
				dot_value = 1;
			}
			else if (dot_value == 1) {
				value = value;
				dot_value = 2;
			}
		}
		else {
			value = (value * 10) + digit;
		}

		if (value > 60000) value = 60000;
	};

	// 문자열 변환 및 디스플레이 업데이트
	auto UpdateKeypadDisplay = [&](float value, bool bDotstate, int Dotvalue) {
		if (bDotstate) {
			if (Dotvalue == 1)
				Unicode::snprintfFloat(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%.1f", value);
			else if (Dotvalue == 2)
				Unicode::snprintfFloat(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%.2f", value);
		}
		else {
			Unicode::snprintf(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%d", static_cast<int>(value));
		}

		Keypadinputvalue.invalidate();
	};

	// KeypadMode에 따른 값 처리
	switch (KeypadMode) {
	case KEYPAD_Velocity_RPM:
		UpdateInputValue(g_s32Vel_input_Rpmvalue, -g_st_inverter.minmaxRpmvalue, g_st_inverter.minmaxRpmvalue);
		UpdateKeypadDisplay(g_s32Vel_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_RPM:
		UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, g_st_inverter.minmaxRpmvalue);
		UpdateKeypadDisplay(g_s32Pos_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_POS:
		UpdateInputValue(g_s32Pos_input_Posvalue, SettingPosmaxLow, SettingPosmaxHigh);
		UpdateKeypadDisplay(g_s32Pos_input_Posvalue, false, 0);
		break;

	case KEYPAD_Setting_Maxpos:
		UpdateInputValue(temp_SetMaxPos, SettingPosmaxLow, SettingPosmaxHigh);
		UpdateKeypadDisplay(temp_SetMaxPos, false, 0);
		break;

	case KEYPAD_Setting_Minpos:
		UpdateInputValue(temp_SetMinPos, SettingPosminLow, SettingPosminHigh);
		UpdateKeypadDisplay(temp_SetMinPos, false, 0);
		break;

	case KEYPAD_Home_POS:
		UpdateInputValue(g_s32Home_input_Posvalue, g_s32MinPosValue, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Home_input_Posvalue, false, 0);
		break;

	case KEYPAD_Setting_GearNum:
		UpdateFloatInputValue(temp_SetGearNum);
		UpdateKeypadDisplay(temp_SetGearNum, dot_state, dot_value);
		break;

	case KEYPAD_Setting_GearDen:
		UpdateFloatInputValue(temp_SetGearDen);
		UpdateKeypadDisplay(temp_SetGearDen, dot_state, dot_value);
		break;

	case KEYPAD_Setting_Diameter:
		UpdateFloatInputValue(temp_SetDiameter);
		UpdateKeypadDisplay(temp_SetDiameter, dot_state, dot_value);
		break;

	case KEYPAD_Setting_MinMaxVel:
		UpdateInputValue(temp_SetMinMaxRpm, 0, SettingPosRpmMinMax);
		UpdateKeypadDisplay(temp_SetMinMaxRpm, false, 0);
		break;

	case KEYPAD_Direct_Up_POS:
		UpdateInputValue(g_s32Direct_input_UpPosvalue, g_s32MinPosValue, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_UpPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Down_POS:
		UpdateInputValue(g_s32Direct_input_DownPosvalue, g_s32MinPosValue, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_DownPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Home_POS :
		UpdateInputValue(g_s32Direct_input_Homevalue, g_s32MinPosValue, g_s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_Homevalue, false, 0);
		break;

	case KEYPAD_Wire :
		UpdateFloatInputValue(temp_SetWire);
		UpdateKeypadDisplay(temp_SetWire, dot_state, dot_value);
		break;

	case KEYPAD_Enc_Pulse :
		UpdateInputValue(temp_SetEncPulse,0,20000);
		UpdateKeypadDisplay(temp_SetEncPulse,false,0);
		break;

	default:
		break;
	}
	/*if(KeypadMode == KEYPAD_Velocity_RPM)
	{
		if (g_s32Vel_input_Rpmvalue == 0){
			g_s32Vel_input_Rpmvalue = 0;
			if(g_s32Vel_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Vel_input_Rpmvalue > 0){
			g_s32Vel_input_Rpmvalue = (g_s32Vel_input_Rpmvalue * 10);
			if(g_s32Vel_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Vel_input_Rpmvalue < 0){
			g_s32Vel_input_Rpmvalue = (g_s32Vel_input_Rpmvalue * 10);
			if(g_s32Vel_input_Rpmvalue <= (g_st_inverter.minmaxRpmvalue * -1))
				g_s32Vel_input_Rpmvalue = g_st_inverter.minmaxRpmvalue * -1;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Vel_input_Rpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_RPM)
	{
		if(g_s32Pos_input_Rpmvalue == 0){
			g_s32Pos_input_Rpmvalue = 0;
			if(g_s32Pos_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Pos_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}
		else if(g_s32Pos_input_Rpmvalue > 0){
			g_s32Pos_input_Rpmvalue = (g_s32Pos_input_Rpmvalue * 10);
			if(g_s32Pos_input_Rpmvalue >= g_st_inverter.minmaxRpmvalue)
				g_s32Pos_input_Rpmvalue = g_st_inverter.minmaxRpmvalue;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Pos_input_Rpmvalue);

	}
	else if(KeypadMode == KEYPAD_Position_POS)
	{
		if (g_s32Pos_input_Posvalue == 0){
			g_s32Pos_input_Posvalue = 0;
			if(g_s32Pos_input_Posvalue >= SettingPosmaxHigh)
				g_s32Pos_input_Posvalue = SettingPosmaxHigh;
		}
		else if(g_s32Pos_input_Posvalue > 0){
			g_s32Pos_input_Posvalue = (g_s32Pos_input_Posvalue * 10);
			if(g_s32Pos_input_Posvalue >= SettingPosmaxHigh)
				g_s32Pos_input_Posvalue = SettingPosmaxHigh;
		}
		else if(g_s32Pos_input_Posvalue < 0){
			g_s32Pos_input_Posvalue = (g_s32Pos_input_Posvalue * 10);
			if(g_s32Pos_input_Posvalue <= SettingPosmaxLow)
				g_s32Pos_input_Posvalue = SettingPosmaxLow;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Pos_input_Posvalue);
	}
	else if(KeypadMode == KEYPAD_Setting_Maxpos)
		{
			if(temp_SetMaxPos == 0)
			{
				temp_SetMaxPos = 0;
				if(temp_SetMaxPos >= SettingPosmaxHigh)
					temp_SetMaxPos = SettingPosmaxHigh;
			}
			else if(temp_SetMaxPos > 0)
			{
				temp_SetMaxPos = (temp_SetMaxPos * 10);
				if(temp_SetMaxPos >= SettingPosmaxHigh)
					temp_SetMaxPos = SettingPosmaxHigh;
			}
			else if(temp_SetMaxPos < 0)
			{
				temp_SetMaxPos = (temp_SetMaxPos * 10);
				if(temp_SetMaxPos <= SettingPosmaxLow)
					temp_SetMaxPos = SettingPosmaxLow;
			}
			Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMaxPos);
		}
		else if(KeypadMode == KEYPAD_Setting_Minpos)
		{
			if(temp_SetMinPos == 0)
			{
				temp_SetMinPos = 0;
				if(temp_SetMinPos >= SettingPosminHigh)
					temp_SetMinPos = SettingPosminHigh;
			}
			else if(temp_SetMinPos > 0)
			{
				temp_SetMinPos = (temp_SetMinPos * 10);
				if(temp_SetMinPos >= SettingPosminHigh)
					temp_SetMinPos = SettingPosminHigh;
			}
			else if(temp_SetMinPos < 0)
			{
				temp_SetMinPos = (temp_SetMinPos * 10);
				if(temp_SetMinPos <= SettingPosminLow)
					temp_SetMinPos = SettingPosminLow;
			}
			Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMinPos);
		}
	else if(KeypadMode == KEYPAD_Home_POS)
		{
			if (g_s32Home_input_Posvalue == 0){
				g_s32Home_input_Posvalue = 0;
				if(g_s32Home_input_Posvalue >= g_s32MaxPosValue)
					g_s32Home_input_Posvalue = g_s32MaxPosValue;
			}
			else if(g_s32Home_input_Posvalue > 0){
				g_s32Home_input_Posvalue = (g_s32Home_input_Posvalue * 10);
				if(g_s32Home_input_Posvalue >= g_s32MaxPosValue)
					g_s32Home_input_Posvalue = g_s32MaxPosValue;
			}
			else if(g_s32Home_input_Posvalue < 0){
				g_s32Home_input_Posvalue = (g_s32Home_input_Posvalue * 10);
				if(g_s32Home_input_Posvalue <= (g_s32MinPosValue))
					g_s32Home_input_Posvalue = g_s32MinPosValue;
			}

			Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Home_input_Posvalue);
		}
	else if(KeypadMode == KEYPAD_Setting_GearNum)
	{
		if(temp_SetGearNum == 0 && dot_state == false){
			temp_SetGearNum = 0;
			if(temp_SetGearNum >= 60000)
				temp_SetGearNum = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearNum);
		}
		else if(temp_SetGearNum > 0 && dot_state == false){
			temp_SetGearNum = (temp_SetGearNum * 10);
			if(temp_SetGearNum >= 60000)
				temp_SetGearNum = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearNum);
		}
		else if(temp_SetGearNum == 0 && dot_state == true)
		{
			if(dot_value == 0){
				dot_value = 1;
			}
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearNum);
		}
		else if(temp_SetGearNum > 0 && dot_state == true)
		{
			if(dot_value == 0){
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearNum);
			}
			else if(dot_value == 1){
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetGearNum);
			}
		}

	}
	else if(KeypadMode == KEYPAD_Setting_GearDen)
	{
		if(temp_SetGearDen == 0 && dot_state == false){
			temp_SetGearDen = 0;
			if(temp_SetGearDen >= 60000)
				temp_SetGearDen = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearDen);
		}
		else if(temp_SetGearDen > 0 && dot_state == false){
			temp_SetGearDen = (temp_SetGearDen * 10);
			if(temp_SetGearDen >= 60000)
				temp_SetGearDen = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearDen);
		}
		else if(temp_SetGearDen == 0 && dot_state == true)
		{
			if(dot_value == 0){
				dot_value = 1;
				Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearDen);
			}
		}
		else if(temp_SetGearDen > 0 && dot_state == true)
		{
			if(dot_value == 0){
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearDen);
			}
			else if(dot_value == 1){
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetGearDen);
			}
		}
	}
	else if(KeypadMode == KEYPAD_Setting_Diameter)
	{
		if(temp_SetDiameter == 0 && dot_state == false){
			temp_SetDiameter = 0;
			if(temp_SetDiameter >= 60000)
				temp_SetDiameter = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetDiameter);
		}
		else if(temp_SetDiameter > 0 && dot_state == false){
			temp_SetDiameter = (temp_SetDiameter * 10);
			if(temp_SetDiameter >= 60000)
				temp_SetDiameter = 60000;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetDiameter);
		}
		else if(temp_SetDiameter == 0 && dot_state == true)
		{
			if(dot_value == 0){
				dot_value = 1;
				Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetDiameter);
			}
		}
		else if(temp_SetDiameter > 0 && dot_state == true)
		{
			if(dot_value == 0){
				dot_value = 1;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetDiameter);
			}
			else if(dot_value == 1){
				dot_value = 2;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.2f", temp_SetDiameter);
			}
		}
	}
	else if(KeypadMode == KEYPAD_Setting_MinMaxVel)
	{
		if(temp_SetMinMaxRpm == 0)
		{
			temp_SetMinMaxRpm = 0;
			if(temp_SetMinMaxRpm >= SettingPosRpmMinMax)
				temp_SetMinMaxRpm = SettingPosRpmMinMax;
		}
		else if(temp_SetMinMaxRpm > 0)
		{
			temp_SetMinMaxRpm = (temp_SetMinMaxRpm * 10);
			if(temp_SetMinMaxRpm >= SettingPosRpmMinMax)
				temp_SetMinMaxRpm = SettingPosRpmMinMax;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMinMaxRpm);
	}
	Keypadinputvalue.invalidate();*/
}
void MainView::MinusButton()
{
    auto ToggleSign = [&](int32_t& value, int32_t minValue) {
        if (value != 0 && (value * -1) >= minValue) {
            value *= -1;
        }
    };
    auto TargetUpDownToggleSign = [&](int32_t& SetPos, int32_t minPos, int32_t ActPos){
    	if (SetPos != 0 &&  (SetPos * -1) >= minPos) {
    		if (ActPos > 0)
    			SetPos *= -1;
    	}
	};
    // 문자열 변환 및 디스플레이 업데이트를 수행하는 람다 함수
    auto UpdateKeypadDisplay = [&](int value) {
        Unicode::snprintf(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%d", value);
        Keypadinputvalue.invalidate();
    };

    // KeypadMode에 따른 값 처리
    switch (KeypadMode) {
        case KEYPAD_Velocity_RPM:
            g_s32Vel_input_Rpmvalue *= -1;
            UpdateKeypadDisplay(g_s32Vel_input_Rpmvalue);
            break;

        case KEYPAD_Position_POS:
            ToggleSign(g_s32Pos_input_Posvalue, g_s32MinPosValue);
            UpdateKeypadDisplay(g_s32Pos_input_Posvalue);
            break;

        case KEYPAD_Setting_Maxpos:
            ToggleSign(temp_SetMaxPos, SettingPosmaxLow);
            UpdateKeypadDisplay(temp_SetMaxPos);
            break;

        case KEYPAD_Setting_Minpos:
            ToggleSign(temp_SetMinPos, SettingPosminLow);
            UpdateKeypadDisplay(temp_SetMinPos);
            break;

        case KEYPAD_Home_POS:
            ToggleSign(g_s32Home_input_Posvalue, g_s32MinPosValue);
            UpdateKeypadDisplay(g_s32Home_input_Posvalue);
            break;

        case KEYPAD_Direct_Up_POS :
        	TargetUpDownToggleSign(g_s32Direct_input_UpPosvalue,g_s32MinPosValue, g_s32MaxPosValue);
        	UpdateKeypadDisplay(g_s32Direct_input_UpPosvalue);
        	break;

        case KEYPAD_Direct_Down_POS :
        	TargetUpDownToggleSign(g_s32Direct_input_DownPosvalue,g_s32MinPosValue, g_s32MaxPosValue);
        	UpdateKeypadDisplay(g_s32Direct_input_DownPosvalue);
        	break;

        case KEYPAD_Direct_Home_POS :
        	ToggleSign(g_s32Direct_input_Homevalue,g_s32MinPosValue);
        	UpdateKeypadDisplay(g_s32Direct_input_Homevalue);
        	break;

        default:
            break;
    }
	/*if(KeypadMode == KEYPAD_Velocity_RPM)
	{
		g_s32Vel_input_Rpmvalue = g_s32Vel_input_Rpmvalue * -1;
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Vel_input_Rpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_POS)
	{
		if(g_s32Pos_input_Posvalue * -1 >= g_s32MinPosValue)
			g_s32Pos_input_Posvalue = g_s32Pos_input_Posvalue * -1;
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Pos_input_Posvalue);
	}
	else if(KeypadMode == KEYPAD_Setting_Maxpos)
	{
		if(temp_SetMaxPos * - 1 >= SettingPosmaxLow)
			temp_SetMaxPos = temp_SetMaxPos * -1;
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMaxPos);
	}
	else if(KeypadMode == KEYPAD_Setting_Minpos)
	{
		if(temp_SetMinPos * -1 >= SettingPosminLow)
			temp_SetMinPos = temp_SetMinPos * -1;
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMinPos);
	}
	else if(KeypadMode == KEYPAD_Home_POS)
	{
		if(g_s32Home_input_Posvalue * -1 >= g_s32MinPosValue)
			g_s32Home_input_Posvalue = g_s32Home_input_Posvalue * -1;
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Home_input_Posvalue);
	}
	Keypadinputvalue.invalidate();*/
}
void MainView::EntButton()
{
    // 값 설정을 수행하는 람다 함수 (최소/최대 범위 체크 포함)
    auto SetValue = [&](int16_t& dest, int32_t& src, int32_t minValue, int32_t maxValue) {
        if (src >= minValue && src <= maxValue) {
            dest = src;
        } else if (src < minValue) {
            dest = minValue;
        } else if (src > maxValue) {
            dest = maxValue;
        }
        src = 0;  // 입력값 초기화
    };

    // KeypadMode에 따른 값 처리
    switch (KeypadMode) {
        case KEYPAD_Velocity_RPM:
            g_st_inverter.VelsetRpmvalue = g_s32Vel_input_Rpmvalue;
            g_s32Vel_input_Rpmvalue = 0;
            break;

        case KEYPAD_Position_RPM:
            g_st_inverter.PosSetRpmvalue = g_s32Pos_input_Rpmvalue;
            g_s32Pos_input_Rpmvalue = 0;
            break;

        case KEYPAD_Position_POS:
            SetValue(g_st_inverter.PosSetPosvalue, g_s32Pos_input_Posvalue, g_s32MinPosValue, g_s32MaxPosValue);
            break;

        case KEYPAD_Setting_Maxpos:
            if (temp_SetMaxPos > oldtemp_SetMinPos)
                oldtemp_SetMaxPos = temp_SetMaxPos;
            break;

        case KEYPAD_Setting_Minpos:
            if (temp_SetMinPos < oldtemp_SetMaxPos)
                oldtemp_SetMinPos = temp_SetMinPos;
            break;

        case KEYPAD_Home_POS:
            SetValue(g_st_inverter.HomeSetPosvalue, g_s32Home_input_Posvalue, g_s32MinPosValue, g_s32MaxPosValue);
            break;

        case KEYPAD_Setting_GearDen:
            if (temp_SetGearDen > 0)
                oldtemp_SetGearDen = temp_SetGearDen;
            else
                oldtemp_SetGearDen = g_st_Setting.fGearDenominator;

            Unicode::snprintfFloat(textGearDeno_valueBuffer, TEXTGEARDENO_VALUE_SIZE, "%.2f", oldtemp_SetGearDen);
            textGearDeno_value.invalidate();
            break;

        case KEYPAD_Setting_GearNum:
            if (temp_SetGearNum > 0)
                oldtemp_SetGearNum = temp_SetGearNum;
            else
                oldtemp_SetGearNum = g_st_Setting.fGearNumerator;

            Unicode::snprintfFloat(textGearNum_valueBuffer, TEXTGEARNUM_VALUE_SIZE, "%.2f", oldtemp_SetGearNum);
            textGearNum_value.invalidate();
            break;

        case KEYPAD_Setting_Diameter:
            if (temp_SetDiameter > 0)
                oldtemp_SetDiameter = temp_SetDiameter;
            else
                oldtemp_SetDiameter = g_st_Setting.fDiameter;

            Unicode::snprintfFloat(textGearDeno_valueBuffer, TEXTGEARDENO_VALUE_SIZE, "%.2f", oldtemp_SetDiameter);
            textGearDeno_value.invalidate();
            break;

        case KEYPAD_Setting_MinMaxVel:
            if (temp_SetMinMaxRpm > 0)
                oldtemp_SetMinMaxRpm = temp_SetMinMaxRpm;
            else
                oldtemp_SetMinMaxRpm = g_st_inverter.minmaxRpmvalue;
            break;

        case KEYPAD_Direct_Up_POS:
        	if (g_s32Direct_input_UpPosvalue <= g_st_Direct.s32DirectActPos)
        		g_st_Direct.s16UpPosSetValue = (int16_t)g_st_Direct.s32DirectActPos;
        	else
        	{
        		if(g_s32Direct_input_UpPosvalue >= g_s32MaxPosValue)
        			g_st_Direct.s16UpPosSetValue = (int16_t)g_s32MaxPosValue;
        		else
        			g_st_Direct.s16UpPosSetValue = (int16_t)g_s32Direct_input_UpPosvalue;
        	}
        	g_s32Direct_input_UpPosvalue = 0;
            break;

        case KEYPAD_Direct_Down_POS:
        	if (g_s32Direct_input_DownPosvalue >= g_st_Direct.s32DirectActPos)
				g_st_Direct.s16DownPosSetValue = (int16_t)g_st_Direct.s32DirectActPos;
			else
			{
				if(g_s32Direct_input_DownPosvalue <= g_s32MinPosValue)
					g_st_Direct.s16DownPosSetValue = (int16_t)g_s32MinPosValue;
				else
					g_st_Direct.s16DownPosSetValue = (int16_t)g_s32Direct_input_DownPosvalue;
			}
        	g_s32Direct_input_DownPosvalue = 0;
        	break;

        case KEYPAD_Direct_Home_POS :
        	SetValue(g_st_Direct.s16HomePosSetValue, g_s32Direct_input_Homevalue, g_s32MinPosValue, g_s32MaxPosValue);
        	break;

        case KEYPAD_Wire :
        	if (temp_SetWire > 0)
				oldtemp_SetWire = temp_SetWire;
			else
				oldtemp_SetWire = g_fWire;
        	Unicode::snprintfFloat(textWirevalueBuffer, TEXTWIREVALUE_SIZE, "%.2f", oldtemp_SetWire);
			textWirevalue.invalidate();
        	break;

        case KEYPAD_Enc_Pulse :
        	if (temp_SetEncPulse > 0)
        		oldtemp_SetEncPulse = temp_SetEncPulse;
        	else
        		oldtemp_SetEncPulse = g_st_Direct.u16EncoderPulse;
        	break;
        default:
            break;
    }

    // 키패드 숨기기
    Numkeypad.hide();
    Numkeypad.invalidate();
	/*
	if(KeypadMode == KEYPAD_Velocity_RPM){
		g_st_inverter.VelsetRpmvalue = g_s32Vel_input_Rpmvalue;
		g_s32Vel_input_Rpmvalue = 0;
	}
	else if(KeypadMode == KEYPAD_Position_RPM){
		g_st_inverter.PossetRpmvalue = g_s32Pos_input_Rpmvalue;
		g_s32Pos_input_Rpmvalue = 0;
	}
	else if(KeypadMode == KEYPAD_Position_POS){
		if(g_s32MinPosValue <= g_s32Pos_input_Posvalue && g_s32Pos_input_Posvalue <= g_s32MaxPosValue)
		{
			g_st_inverter.PosSetPosvalue = g_s32Pos_input_Posvalue;
			g_s32Pos_input_Posvalue = 0;
		}
		else if(g_s32MinPosValue > g_s32Pos_input_Posvalue)
		{
			g_st_inverter.PosSetPosvalue = g_s32MinPosValue;
			g_s32Pos_input_Posvalue = 0;
		}
		else if(g_s32Pos_input_Posvalue > g_s32MaxPosValue)
		{
			g_st_inverter.PosSetPosvalue = g_s32MaxPosValue;
			g_s32Pos_input_Posvalue = 0;
		}
	}
	else if(KeypadMode == KEYPAD_Setting_Maxpos){
		if(temp_SetMaxPos > oldtemp_SetMinPos)
			oldtemp_SetMaxPos = temp_SetMaxPos;
	}
	else if(KeypadMode == KEYPAD_Setting_Minpos){
		if(temp_SetMinPos < oldtemp_SetMaxPos)
			oldtemp_SetMinPos = temp_SetMinPos;
	}
	else if(KeypadMode == KEYPAD_Home_POS){
		if(g_s32MinPosValue <= g_s32Home_input_Posvalue && g_s32Home_input_Posvalue <= g_s32MaxPosValue)
		{
			g_st_inverter.HomeSetPosvalue = g_s32Home_input_Posvalue;
			g_s32Home_input_Posvalue = 0;
		}
		else if(g_s32MinPosValue > g_s32Home_input_Posvalue)
		{
			g_st_inverter.HomeSetPosvalue = g_s32MinPosValue;
			g_s32Home_input_Posvalue = 0;
		}
		else if(g_s32Home_input_Posvalue > g_s32MaxPosValue)
		{
			g_st_inverter.HomeSetPosvalue = g_s32MaxPosValue;
			g_s32Home_input_Posvalue = 0;
		}
	}
	else if(KeypadMode == KEYPAD_Setting_GearDen)
	{
		if(temp_SetGearDen > 0)
			oldtemp_SetGearDen = temp_SetGearDen;
		else if(temp_SetGearDen <= 0)
			oldtemp_SetGearDen = g_st_inverter.iGearDenominator;

		Unicode :: snprintfFloat(textGearDeno_valueBuffer,TEXTGEARDENO_VALUE_SIZE, "%.2f", temp_SetGearDen);
		textGearDeno_value.invalidate();
	}
	else if(KeypadMode == KEYPAD_Setting_GearNum)
	{
		if(temp_SetGearNum > 0)
			oldtemp_SetGearNum = temp_SetGearNum;
		else if(temp_SetGearNum <= 0)
			oldtemp_SetGearNum = g_st_inverter.iGearNumerator;

		Unicode :: snprintfFloat(textGearNum_valueBuffer,TEXTGEARNUM_VALUE_SIZE, "%.2f", temp_SetGearNum);
		textGearNum_value.invalidate();
	}
	else if(KeypadMode == KEYPAD_Setting_Diameter)
	{
		if(temp_SetDiameter > 0)
			oldtemp_SetDiameter = temp_SetDiameter;
		else if(temp_SetDiameter <= 0)
			oldtemp_SetDiameter = g_st_inverter.idiameter;

		Unicode :: snprintfFloat(textGearDeno_valueBuffer,TEXTGEARDENO_VALUE_SIZE, "%.2f", temp_SetDiameter);
		textGearDeno_value.invalidate();
	}
	else if(KeypadMode == KEYPAD_Setting_MinMaxVel)
	{
		if(temp_SetMinMaxRpm > 0)
			oldtemp_SetMinMaxRpm = temp_SetMinMaxRpm;
		else if(temp_SetMinMaxRpm = 0)
			oldtemp_SetMinMaxRpm = g_st_inverter.minmaxRpmvalue;
	}
	else if(KeypadMode == KEYPAD_Direct_Up_POS)
	{
		if(g_s32MinPosValue <= g_s32Direct_input_UpPosvalue && g_s32Direct_input_UpPosvalue <= g_s32MaxPosValue)
		{
			g_st_Direct.s16UpPosSetValue = g_s32Direct_input_UpPosvalue;
			g_s32Direct_input_UpPosvalue = 0;
		}
		else if(g_s32MinPosValue > g_s32Home_input_Posvalue)
		{
			g_st_Direct.s16UpPosSetValue = g_s32MinPosValue;
			g_s32Direct_input_UpPosvalue = 0;
		}
		else if(g_s32Home_input_Posvalue > g_s32MaxPosValue)
		{
			g_st_Direct.s16UpPosSetValue = g_s32MaxPosValue;
			g_s32Direct_input_UpPosvalue = 0;
		}
	}
	Numkeypad.hide();
	Numkeypad.invalidate();*/
}
void MainView::BackspaceButton()
{
	auto BackspaceInt = [&](int32_t& value){
		if(value >= 10 || value <= -10){
			value /= 10;
		}
		else{
			value = 0;
		}
	};
	auto BackspaceFloat = [&](float& value) {
		if (value >= 10.0f) {
			if (dot_state) {
				if (dot_value == 1) {
					value = floor(value);
					dot_value = 0;
					dot_state = false;
				}
				else if (dot_value == 2) {
					value = floor(value * 10.0f) / 10.0f;
					dot_value = 1;
				}
				else {
					value = floor(value);
					dot_value = 0;
					dot_state = false;
				}
			}
			else {
				value = floor(value / 10.0f);
			}
		}
		else if (value < 10.0f && value >= 0.0f){
			if (dot_state) {
				if (dot_value == 1){
					value = floor(value);
					dot_value = 0;
					dot_state = false;
				}
				else if( dot_value == 2) {
					value = floor(value * 10.f) / 10.0f;
					dot_value = 1;
				}
				else{
					value = floor(value);
					dot_value = 0;
					dot_state = false;
				}
			}
			else{
				value = floor(value / 10.0f);
			}
		}
		else {
			value = 0.0f;
			dot_value = 0;
			dot_state = false;
		}
	};
	auto UpdateKeypadDisplay = [&](float value, bool bDotstate, int s32dotvalue){
		if (bDotstate){
			if (s32dotvalue == 1)
				Unicode :: snprintfFloat(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%.1f", value);
			else if (s32dotvalue == 2)
				Unicode :: snprintfFloat(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%.2f", value);
		}
		else{
			Unicode::snprintf(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%d",static_cast<int>(value));
		}
		Keypadinputvalue.invalidate();
	};

	switch(KeypadMode){
		case KEYPAD_Velocity_RPM :
			BackspaceInt(g_s32Vel_input_Rpmvalue);
			UpdateKeypadDisplay(g_s32Vel_input_Rpmvalue, false, 0);
			break;
		case KEYPAD_Position_RPM :
			BackspaceInt(g_s32Pos_input_Rpmvalue);
			UpdateKeypadDisplay(g_s32Pos_input_Rpmvalue, false , 0);
			break;
		case KEYPAD_Position_POS :
			BackspaceInt(g_s32Pos_input_Posvalue);
			UpdateKeypadDisplay(g_s32Pos_input_Posvalue, false, 0);
			break;
		case KEYPAD_Setting_Maxpos :
			BackspaceInt(temp_SetMaxPos);
			UpdateKeypadDisplay(temp_SetMaxPos, false, 0);
			break;
		case KEYPAD_Setting_Minpos :
			BackspaceInt(temp_SetMinPos);
			UpdateKeypadDisplay(temp_SetMinPos, false, 0);
			break;
		case KEYPAD_Home_POS :
			BackspaceInt(g_s32Home_input_Posvalue);
			UpdateKeypadDisplay(g_s32Home_input_Posvalue, false, 0);
			break;
		case KEYPAD_Setting_GearNum :
			BackspaceFloat(temp_SetGearNum);
			UpdateKeypadDisplay(temp_SetGearNum, dot_state, dot_value);
			break;
		case KEYPAD_Setting_GearDen :
			BackspaceFloat(temp_SetGearDen);
			UpdateKeypadDisplay(temp_SetGearDen,dot_state, dot_value);
			break;
		case KEYPAD_Setting_Diameter :
			BackspaceFloat(temp_SetDiameter);
			UpdateKeypadDisplay(temp_SetDiameter, dot_state, dot_value);
			break;
		case KEYPAD_Setting_MinMaxVel :
			BackspaceInt(temp_SetMinMaxRpm);
			UpdateKeypadDisplay(temp_SetMinMaxRpm, dot_state, dot_value);
			break;
		case KEYPAD_Direct_Up_POS:
			BackspaceInt(g_s32Direct_input_UpPosvalue);
			UpdateKeypadDisplay(g_s32Direct_input_UpPosvalue,false, 0);
			break;
		case KEYPAD_Direct_Down_POS:
			BackspaceInt(g_s32Direct_input_DownPosvalue);
			UpdateKeypadDisplay(g_s32Direct_input_DownPosvalue, false, 0);
			break;
		case KEYPAD_Direct_Home_POS :
			BackspaceInt(g_s32Direct_input_Homevalue);
			UpdateKeypadDisplay(g_s32Direct_input_Homevalue, false, 0);
			break;
		case KEYPAD_Wire :
			BackspaceFloat(temp_SetWire);
			UpdateKeypadDisplay(temp_SetWire, dot_state, dot_value);
			break;
		case KEYPAD_Enc_Pulse :
			BackspaceInt(temp_SetEncPulse);
			UpdateKeypadDisplay(temp_SetEncPulse, false, 0);
			break;
	}
	/*
	if(KeypadMode == KEYPAD_Velocity_RPM){
		if(g_s32Vel_input_Rpmvalue >= 10 || g_s32Vel_input_Rpmvalue <= -10)
			g_s32Vel_input_Rpmvalue = (g_s32Vel_input_Rpmvalue / 10);
		else
			g_s32Vel_input_Rpmvalue = 0;
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Vel_input_Rpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_RPM){
		if(g_s32Pos_input_Rpmvalue >= 10 || g_s32Pos_input_Rpmvalue <= -10)
			g_s32Pos_input_Rpmvalue = (g_s32Pos_input_Rpmvalue / 10);
		else
			g_s32Pos_input_Rpmvalue = 0;
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Pos_input_Rpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_POS){
		if(g_s32Pos_input_Posvalue >= 10 || g_s32Pos_input_Posvalue <= -10)
			g_s32Pos_input_Posvalue = (g_s32Pos_input_Posvalue / 10);
		else
			g_s32Pos_input_Posvalue = 0;
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Pos_input_Posvalue);
	}
	else if(KeypadMode == KEYPAD_Setting_Maxpos){
		if(temp_SetMaxPos >= 10 || temp_SetMaxPos <= -10)
			temp_SetMaxPos = (temp_SetMaxPos / 10);
		else
			temp_SetMaxPos = 0;
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMaxPos);
	}
	else if(KeypadMode == KEYPAD_Setting_Minpos){
		if(temp_SetMinPos >= 10 || temp_SetMinPos <= -10)
			temp_SetMinPos = (temp_SetMinPos / 10);
		else
			temp_SetMinPos = 0;
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMinPos);
	}
	else if(KeypadMode == KEYPAD_Home_POS){
		if(g_s32Home_input_Posvalue >= 10 || g_s32Home_input_Posvalue <= -10)
			g_s32Home_input_Posvalue = (g_s32Home_input_Posvalue / 10);
		else
			g_s32Home_input_Posvalue = 0;
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", g_s32Home_input_Posvalue);
	}
	else if(KeypadMode == KEYPAD_Setting_GearNum){
		if(temp_SetGearNum >= 10)
		{
			if(dot_state == true){
				if(dot_value == 1){
					temp_SetGearNum = floor(temp_SetGearNum);
					dot_value = 0;
					dot_state = false;
					Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearNum);
				}
				else if(dot_value == 2){
					temp_SetGearNum = floor(temp_SetGearNum * 10) / 10;
					dot_value = 1;
					Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearNum);
				}
			}
			else{
				temp_SetGearNum = floor(temp_SetGearNum / 10);
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearNum);
			}
		}
		else{
			temp_SetGearNum = 0;
			dot_state = false;
			dot_value = 0;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearNum);
		}
	}
	else if(KeypadMode == KEYPAD_Setting_GearDen){
		if(temp_SetGearDen >= 10)
		{
			if(dot_state == true){
				temp_SetGearDen = floor(temp_SetGearDen);
				dot_value = 0;
				dot_state = false;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearDen);
			}
			else if(dot_value == 2){
				temp_SetGearDen = floor(temp_SetGearDen * 10) / 10;
				dot_value = 1;
				Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearDen);
			}
			else{
				temp_SetGearDen = floor(temp_SetGearDen / 10);
				Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearDen);
			}
		}
		else{
			temp_SetGearDen = 0;
			dot_state = false;
			dot_value = 0;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetGearDen);
		}
	}
	else if(KeypadMode == KEYPAD_Setting_Diameter){
		if(temp_SetDiameter >= 10)
		{
			if(dot_state == true){
				temp_SetDiameter = floor(temp_SetDiameter);
				dot_value = 0;
				dot_state = false;
				Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetDiameter);
			}
			else if(dot_value == 2){
				temp_SetDiameter = floor(temp_SetDiameter * 10) / 10;
				dot_value = 1;
				Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetDiameter);
			}
			else{
				temp_SetDiameter = floor(temp_SetDiameter / 10);
				Unicode::snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetDiameter);
			}
		}
		else{
			temp_SetDiameter = 0;
			dot_state = false;
			dot_value = 0;
			Unicode :: snprintfFloat(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%.f", temp_SetDiameter);
		}
	}
	else if(KeypadMode == KEYPAD_Setting_MinMaxVel){
		if(temp_SetMinMaxRpm >= 10 || temp_SetMinMaxRpm <= -10)
			temp_SetMinMaxRpm = (temp_SetMinMaxRpm / 10);
		else
			temp_SetMinMaxRpm = 0;
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", temp_SetMinMaxRpm);
	}
	Keypadinputvalue.invalidate();*/
}
void MainView::NumdotButton()
{
	if(KeypadMode == KEYPAD_Setting_GearNum)
	{
		if(dot_state == false){
			dot_state = true;
			dot_value = 0;
			Unicode::snprintfFloat(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearNum);
			Keypadinputvalue.invalidate();
		}
	}
	else if(KeypadMode == KEYPAD_Setting_GearDen)
	{
		if(dot_state == false){
			dot_state = true;
			Unicode::snprintfFloat(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetGearDen);
			Keypadinputvalue.invalidate();
		}
	}
	else if(KeypadMode == KEYPAD_Setting_Diameter)
	{
		if(dot_state == false){
			dot_state = true;
			Unicode::snprintfFloat(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetDiameter);
			Keypadinputvalue.invalidate();
		}
	}
	else if(KeypadMode == KEYPAD_Setting_Diameter)
	{
		if(dot_state == false){
			dot_state = true;
			Unicode::snprintfFloat(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE, "%.1f", temp_SetWire);
			Keypadinputvalue.invalidate();
		}
	}
	else if(KeypadMode == KEYPAD_Wire)
	{
		if(dot_state == false){
			dot_state = true;
			Unicode::snprintfFloat(KeypadinputvalueBuffer, KEYPADINPUTVALUE_SIZE,"%.1f", temp_SetWire);
			Keypadinputvalue.invalidate();
		}
	}
}
void MainView::Resetbutton()
{
	g_st_controlword.fault_reset = 128;
}
void MainView::EableButtonOn()
{
	if(g_st_Statusword.ready_to_switch_on == false && g_st_Statusword.switched_on == false && g_st_Statusword.switch_on_disabled == true )
	{
		g_st_controlword.switch_on = 1;
		g_st_controlword.enable_voltage = 2;
		g_st_controlword.no_quick_stop = 4;
	}
	else
	{
		g_st_controlword.switch_on = 0;
		g_st_controlword.enable_voltage = 0;
		g_st_controlword.no_quick_stop = 0;
	}

}
void MainView::ModeButtonOn()
{
	if(u8Screenpage == 1 && g_bLocal == true)
	{
		g_s8Mode = Position;
		g_bModeWrite = true;
	}
	else if(u8Screenpage == 2 && g_bLocal == true)
	{
		g_s8Mode = Home;
		g_bModeWrite = true;
	}
}
void MainView::PositionScreenButton()
{
	u8Screenpage = 1;
	g_s8Mode = Position;
	g_bModeWrite = true;
}
void MainView::HomingScreenButton()
{
	u8Screenpage = 2;
	g_s8Mode = Home;
	g_bModeWrite = true;
}
void MainView::PositionStartButton()
{
	if(g_st_inverter.s8Mode == 1){
		g_st_controlword.op_mode_spec_four = 16;
		g_st_controlword.op_mode_spec_five = 32;
	}
}
void MainView::PositionStopButton()
{
	if(g_st_inverter.s8Mode == 1)
		g_st_controlword.halt = 256;
}
void MainView::HomeSetbutton()
{
	if(g_st_inverter.s8Mode == 6)
		g_st_controlword.op_mode_spec_four = 16;
}
void MainView::SetType_D_Button()
{
	temp_SetType = 1;
}
void MainView::SetType_D_ENC_Button()
{
	temp_SetType = 2;
}
void MainView::SetType_INV_ENC_Button()
{
	temp_SetType = 4;
}
void MainView::SettingSaveButton()
{
	if(oldtemp_SetMaxPos != 0)
	{
		g_u32FlashSaveMaxPos = *(int*)&oldtemp_SetMaxPos;
		g_bFlashWrite = true;
	}
	if(oldtemp_SetMinPos != 0)
	{
		g_u32FlashSaveMinPos = *(int*)&oldtemp_SetMinPos;
		g_bFlashWrite = true;
	}

	if(oldtemp_SetGearDen != 0)
	{
		g_u32FlashSaveDen = *(uint32_t*)&oldtemp_SetGearDen;
		g_bFlashWrite = true;
	}

	if(oldtemp_SetGearNum != 0)
	{
		g_u32FlashSaveNum = *(uint32_t*)&oldtemp_SetGearNum;
		g_bFlashWrite = true;
	}

	if(oldtemp_SetDiameter != 0)
	{
		g_u32FlashSaveDiameter = *(uint32_t*)&oldtemp_SetDiameter;
		g_bFlashWrite = true;
	}

	if(oldtemp_SetMinMaxRpm != 0)
	{
		g_u32FlashSaveMinMaxRpm = *(uint32_t*)&oldtemp_SetMinMaxRpm;
		g_bFlashWrite = true;
	}

	g_u32FlashSaveDriveType = *(uint32_t*)&temp_SetType;
	g_bFlashWrite = true;

	if(oldtemp_SetWire != 0)
	{
		g_u32FlashSaveWire = *(uint32_t*)&oldtemp_SetWire;
		g_bFlashWrite = true;
	}

	g_u32FlashSaveYoYo = *(uint32_t*)&temp_SetYoYo;

	if(oldtemp_SetEncPulse != 0)
	{
		g_u32FlashSaveEncPulse = *(uint32_t*)&oldtemp_SetEncPulse;
		g_bFlashWrite = true;
	}
}
void MainView::MC_ON_Button()
{
	if(g_bMCinputstate == false && g_bMCoutputstate == false)
	{
		g_bMCinput = true;
		g_bMCoutput = true;
	}
	else
	{
		g_bMCinput = false;
		g_bMCoutput = false;
	}
}

void MainView::ServconnectionButton()
{
	GVLTCP_connection = 0;
}

void MainView::DirectMoveUpButton()
{
	//if(g_st_Setting.bPosLimit == true && g_st_Setting.bFinalPosLimit == true)
	//{
		g_st_Direct.bUp = true;
		g_st_Direct.bDown = false;
	/*}
	else
	{
		g_st_Direct.bUp = false;
		g_st_Direct.bDown = false;
	}*/
}
void MainView::DirectMoveDownButton()
{
	//if(g_st_Setting.bNegLimit == true && g_st_Setting.bFinalNegLimit == true)
	//{
		g_st_Direct.bUp = false;
		g_st_Direct.bDown = true;
	/*}
	else
	{
		g_st_Direct.bUp = false;
		g_st_Direct.bDown = false;
	}*/

}
void MainView::DirectMoveStopButton()
{
	g_st_Direct.bUp = false;
	g_st_Direct.bDown = false;
}
void MainView::DirectHomeSetbutton()
{
	if(g_st_Direct.s16UpPosSetValue>= g_st_Direct.s16HomePosSetValue && g_st_Direct.s16HomePosSetValue >= g_st_Direct.s16DownPosSetValue)
	{
		g_st_Direct.s32DirectHomeOffset = g_st_Direct.s16HomePosSetValue;
		g_bDirect_HomeTrig = true;
	}
}

void MainView::handleTickEvent()
{
	if(g_st_inverter.s8Mode == 1)
	{
		PosOption.setVisible(true);
		PosOption.invalidate();
		PosScreenBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		PosScreenBox.invalidate();

		HomeOption.setVisible(false);
		HomeOption.invalidate();
		HomeScreenBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
		HomeScreenBox.invalidate();

	}
	else if(g_st_inverter.s8Mode == 6)
	{
		PosOption.setVisible(false);
		PosOption.invalidate();
		PosScreenBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
		PosScreenBox.invalidate();

		HomeOption.setVisible(true);
		HomeOption.invalidate();
		HomeScreenBox.setColor(touchgfx::Color::getColorFromRGB(255, 225, 255));
		HomeScreenBox.invalidate();
	}
	if(g_bLocal)
	{
		RemoteAlarm.setVisible(false);
		RemoteAlarm.invalidate();
	}
	else{
		RemoteAlarm.setVisible(true);
		RemoteAlarm.invalidate();
	}

	//Gear Denominator, Numberator
	Unicode::snprintfFloat(textGearDeno_valueBuffer,TEXTGEARDENO_VALUE_SIZE, "%.2f", oldtemp_SetGearDen);
	textGearDeno_value.invalidate();

	Unicode::snprintfFloat(textGearNum_valueBuffer,TEXTGEARNUM_VALUE_SIZE, "%.2f", oldtemp_SetGearNum);
	textGearNum_value.invalidate();

	//Diamter
	Unicode::snprintfFloat(textDiametervalueBuffer,TEXTDIAMETERVALUE_SIZE, "%.2f", oldtemp_SetDiameter);
	textDiametervalue.invalidate();

	//Setting display Postion
	Unicode::snprintf(textsettingMaxposvalueBuffer, TEXTSETTINGMAXPOSVALUE_SIZE, "%d", oldtemp_SetMaxPos);
	textsettingMaxposvalue.invalidate();

	Unicode::snprintf(textsettingMinposvalueBuffer, TEXTSETTINGMINPOSVALUE_SIZE, "%d", oldtemp_SetMinPos);
	textsettingMinposvalue.invalidate();

	//Setting minmaxRpm
	Unicode::snprintf(textsettingMaxrpmvalueBuffer, TEXTSETTINGMAXRPMVALUE_SIZE, "%d", oldtemp_SetMinMaxRpm);
	textsettingMaxrpmvalue.invalidate();

	//Setting YoYo

	//Setting Wire
	Unicode::snprintfFloat(textWirevalueBuffer, TEXTWIREVALUE_SIZE, "%.2f", oldtemp_SetWire);
	textWirevalue.invalidate();

	//Direct Encoder TTL Pulse
	Unicode::snprintf(textEncPulsevalueBuffer,TEXTENCPULSEVALUE_SIZE,"%d", oldtemp_SetEncPulse);

	//CAN ReadyState ->STO, Voltage
	Unicode :: snprintf(textReadyStateValueBuffer,TEXTREADYSTATEVALUE_SIZE,g_st_inverter.cReadystate);
	textReadyStateValue.invalidate();

	Unicode :: snprintf(textStateValueBuffer,TEXTSTATEVALUE_SIZE,g_st_inverter.cState);
	textStateValue.invalidate();

	Unicode :: snprintf(textErrorValueBuffer,TEXTERRORVALUE_SIZE,g_st_inverter.cError);
	textErrorValue.invalidate();


	Unicode :: snprintf(textMODEStateBuffer,TEXTMODESTATE_SIZE, g_st_inverter.cMode);
	textMODEState.invalidate();

	//Position mode Set Rpm value
	//Unicode :: snprintf(textPosSetRpmValueBuffer,TEXTPOSSETRPMVALUE_SIZE, "%d", GVLinverter[GVLAddnumber].PossetRpmvalue);
	Unicode :: snprintfFloat(textPosSetRpmValueBuffer,TEXTPOSSETRPMVALUE_SIZE, "%.f%", float(g_st_inverter.PosSetRpmvalue) / g_st_inverter.minmaxRpmvalue * 100);
	textPosSetRpmValue.invalidate();

	//Position mode Actual Rpm value
	//Unicode :: snprintf(textPosActRpmValueBuffer,TEXTPOSACTRPMVALUE_SIZE, "%d", GVLinverter[GVLAddnumber].actRpmvalue);
	Unicode :: snprintfFloat(textPosActRpmValueBuffer,TEXTPOSACTRPMVALUE_SIZE, "%.f%", float(g_st_inverter.actRpmvalue) / g_st_inverter.minmaxRpmvalue * 100);
	textPosActRpmValue.invalidate();

	//Direct Encoder Mode Actual Pos value
	Unicode :: snprintf(textD_PosActValueBuffer, TEXTD_POSACTVALUE_SIZE, "%d",g_st_Direct.s32DirectActPos);
	textD_PosActValue.invalidate();

	//Direct mode Set Home value
	Unicode::snprintf(textD_HomeSetValueBuffer, TEXTD_HOMESETVALUE_SIZE, "%d", g_st_Direct.s16HomePosSetValue);

	//Direct mode Set Pos value
	Unicode::snprintf(textD_PosUpSetValueBuffer, TEXTD_POSUPSETVALUE_SIZE, "%d", g_st_Direct.s16UpPosSetValue);
	textD_PosUpSetValue.invalidate();

	//Direct mode Set Down Pos value
	Unicode::snprintf(textD_PosDownSetValueBuffer, TEXTD_POSDOWNSETVALUE_SIZE, "%d", g_st_Direct.s16DownPosSetValue);
	textD_PosDownSetValue.invalidate();

	//Position mode Actual Pos value
	Unicode :: snprintf(textPosActPosValueBuffer, TEXTPOSACTPOSVALUE_SIZE, "%d", g_st_inverter.PosActPosvalue);
	textPosActPosValue.invalidate();

	//Position mode Set Pos value
	Unicode :: snprintf(textPosSetPosValueBuffer,TEXTPOSSETPOSVALUE_SIZE, "%d", g_st_inverter.PosSetPosvalue);
	textPosSetPosValue.invalidate();

	//Home mode Set Pos value
	Unicode :: snprintf(textHomeSetPosvalueBuffer, TEXTHOMESETPOSVALUE_SIZE, "%d", g_st_inverter.HomeSetPosvalue);
	textHomeSetPosvalue.invalidate();

	//Home mode Actual Pos value
	Unicode :: snprintf(textHomeActPosvalueBuffer, TEXTHOMEACTPOSVALUE_SIZE, "%d", g_st_inverter.PosActPosvalue);
	textHomeActPosvalue.invalidate();

	//IP
	Unicode::snprintf(textIP0Buffer, TEXTIP0_SIZE, "%d", g_st_u8IP[0]);
	textIP0.invalidate();
	Unicode::snprintf(textIP1Buffer, TEXTIP1_SIZE, "%d", g_st_u8IP[1]);
	textIP1.invalidate();
	Unicode::snprintf(textIP2Buffer, TEXTIP2_SIZE, "%d", g_st_u8IP[2]);
	textIP2.invalidate();
	Unicode::snprintf(textIP3Buffer, TEXTIP3_SIZE, "%d", g_st_u8IP[3]);
	textIP3.invalidate();

	/* Direct Up, Down Begin */
	if(g_st_Direct.bUp == true)
	{
		DirectUpBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
		DirectUpBox.invalidate();
	}
	else
	{
		DirectUpBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		DirectUpBox.invalidate();
	}
	if(g_st_Direct.bDown == true)
	{
		DirectDownBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
		DirectDownBox.invalidate();
	}
	else
	{
		DirectDownBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		DirectDownBox.invalidate();
	}
	if(g_st_Direct.bUp == false && g_st_Direct.bDown == false)
	{
		DirectStopBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
		DirectStopBox.invalidate();
	}
	else
	{
		DirectStopBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		DirectStopBox.invalidate();
	}
	/* Direct Up, Down End */


	/*Limit	Begin*/
	//Final Up Limit
	if(g_st_Setting.bFinalPosLimit == true){
		D_FUP_LimitBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
		D_FUP_LimitBox.invalidate();
	}
	else
	{
		D_FUP_LimitBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		D_FUP_LimitBox.invalidate();
	}
	//Up Limit
	if(g_st_Setting.bPosLimit == true){
		D_UP_LimitBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
		D_UP_LimitBox.invalidate();
	}
	else
	{
		D_UP_LimitBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		D_UP_LimitBox.invalidate();
	}
	//Down Limit
	if(g_st_Setting.bNegLimit == true){
		D_DN_LimitBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
		D_DN_LimitBox.invalidate();
	}
	else
	{
		D_DN_LimitBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		D_DN_LimitBox.invalidate();
	}
	//Final Down Limit
	if(g_st_Setting.bFinalNegLimit == true){
		D_FDN_LimitBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
		D_FDN_LimitBox.invalidate();
	}
	else
	{
		D_FDN_LimitBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		D_FDN_LimitBox.invalidate();
	}
	/*Limit	End*/

	//MC State
	if(g_bMCinputstate == true && g_bMCoutputstate == true){
		MC_OnBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
		MC_OnBox.invalidate();
	}
	else{
		MC_OnBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		MC_OnBox.invalidate();
	}

	if(g_st_Statusword.ready_to_switch_on == true && g_st_Statusword.switched_on ==  true && g_st_Statusword.switch_on_disabled == false)
	{
		EnableBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
		EnableBox.invalidate();
	}
	else
	{
		EnableBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		EnableBox.invalidate();
	}

	if(g_st_Statusword.operation_enabled == true)
	{
		g_bPowerstate = true;
		PowerONBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
		PowerONBox.invalidate();
		PowerOFFBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		PowerOFFBox.invalidate();
	}
	else
	{
		g_bPowerstate = false;
		PowerOFFBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
		PowerOFFBox.invalidate();
		PowerONBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		PowerONBox.invalidate();
	}

	if(GVLComstate == 8)
	{
		g_bPoweroff = true;
		g_bPoweron = false;
		Unicode::snprintf(textCom_onoffBuffer, TEXTCOM_ONOFF_SIZE, "EtherCAT");
		textCom_onoff.invalidate();
		Com_onoff_box.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		Com_onoff_box.invalidate();
	}
	else if(GVLComstate == 0)
	{
		Unicode::snprintf(textCom_onoffBuffer, TEXTCOM_ONOFF_SIZE, "SERIAL");
		textCom_onoff.invalidate();
		Com_onoff_box.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
		Com_onoff_box.invalidate();
	}
	if(temp_SetType == 0)
	{
		if(g_s32DriveSettingType == 1)
		{
			TypeD_Box.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
			TypeD_Box.invalidate();
			TypeD_ENCBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
			TypeD_ENCBox.invalidate();
			TypeINV_ENCBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
			TypeINV_ENCBox.invalidate();
		}
		else if(g_s32DriveSettingType == 2)
		{

			TypeD_ENCBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
			TypeD_ENCBox.invalidate();
			TypeD_Box.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
			TypeD_Box.invalidate();
			TypeINV_ENCBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
			TypeINV_ENCBox.invalidate();
		}
		else if(g_s32DriveSettingType == 3)
		{
			;
		}
		else if(g_s32DriveSettingType == 4)
		{
			TypeINV_ENCBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
			TypeINV_ENCBox.invalidate();
			TypeD_ENCBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
			TypeD_ENCBox.invalidate();
			TypeD_Box.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
			TypeD_Box.invalidate();
		}
	}
	else
	{
		if(temp_SetType == 1)
		{
			TypeD_Box.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
			TypeD_Box.invalidate();
			TypeD_ENCBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
			TypeD_ENCBox.invalidate();
			TypeINV_ENCBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
			TypeINV_ENCBox.invalidate();
		}
		else if(temp_SetType == 2)
		{
			TypeD_ENCBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
			TypeD_ENCBox.invalidate();
			TypeD_Box.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
			TypeD_Box.invalidate();
			TypeINV_ENCBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
			TypeINV_ENCBox.invalidate();
		}
		else if(temp_SetType == 4)
		{
			TypeINV_ENCBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
			TypeINV_ENCBox.invalidate();
			TypeD_Box.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
			TypeD_Box.invalidate();
			TypeD_ENCBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
			TypeD_ENCBox.invalidate();
		}
	}

	if(g_s32DriveSettingType == Direct_No_encoder)
	{
		Direct.setVisible(true);
		Direct.invalidate();
		Direct_PosSetting.setVisible(false);
		Direct_PosSetting.invalidate();
		INVERTER.setVisible(false);
		INVERTER.invalidate();
	}
	else if(g_s32DriveSettingType == Direct_encoder)
	{
		Direct.setVisible(true);
		Direct.invalidate();
		Direct_PosSetting.setVisible(true);
		Direct_PosSetting.invalidate();
		INVERTER.setVisible(false);
		INVERTER.invalidate();
	}
	else if (g_s32DriveSettingType == inverter_encoder)
	{
		Direct.setVisible(false);
		Direct.invalidate();
		INVERTER.setVisible(true);
		INVERTER.invalidate();
	}

}
