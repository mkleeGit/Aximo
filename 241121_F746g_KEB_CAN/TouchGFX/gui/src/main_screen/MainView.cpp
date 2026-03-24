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
	//GVL_iModevalue = Position;
	//GVLAddnumber = 1;
	u8Screenpage = 1;
	g_st_inverter.s8TouchgfxMode = Position;

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

void MainView::List1ButtonOn() {//Not use
	/*if (g_bPowerstate == true) {
		Popup_PowerState.setVisible(true);
		Popup_PowerState.invalidate();
	} else {

		//GVLAddnumber = 1;
	}*/
}
void MainView::PowerButtonON(){
	if(g_st_inverter.bTouchgfx_PowerButton == true)
		g_st_inverter.bTouchgfx_PowerButton = false;
	else
		//if(g_st_IO.IN_MCCB == true && g_st_IO.OUT_McIn == true && g_st_IO.OUT_McOut == true && g_st_Statusword.voltage_enabled == true)
		if(g_st_Statusword.voltage_enabled == true)
			g_st_inverter.bTouchgfx_PowerButton = true;
		else
		{
			Popup_PowerState.setVisible(true);
			Popup_PowerState.invalidate();
		}
	/*
	if(g_st_inverter.s8Mode == Position)
	{
		if(g_st_Statusword.ready_to_switch_on == true && g_st_Statusword.switched_on ==  true && g_st_Statusword.switch_on_disabled == false)
				g_st_controlword.enable_operation = 8;//GVL_enable_operation = 8;
	}*/
}
void MainView::PowerButtonOFF(){//Not use
	//g_st_controlword.enable_operation = 0;//GVL_enable_operation = 0;
}
void MainView::ComButtonONOFF()// Not use
{
	/*if(GVLComstate == 8)
	{
		GVLComon 		= false;
		GVLComoff 		= true;
	}
	else if(GVLComstate == 0)
	{
		GVLComon 		= true;
		GVLComoff		= false;
	}*/
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
	temp_SetType = g_st_Setting.s32DriveSettingType;
	temp_SetWire = 0;
	temp_SetYoYo = bool(g_st_Setting.s32YoYo);
	temp_SetParking = bool(g_st_Setting.s32Parking);
	temp_SetWireOut = bool(g_st_Setting.s32WireOut);
	temp_SetEmgBrake = bool(g_st_Setting.s32EmgBrake);
	temp_SetEncPulse = 0;

	if(temp_SetYoYo == true)YoYoButton.setSelected(true);
	else YoYoButton.setSelected(false);
	if(temp_SetParking == true)ParkingButton.setSelected(true);
	else ParkingButton.setSelected(false);
	if(temp_SetWireOut == true)WireOutButton.setSelected(true);
	else WireOutButton.setSelected(false);
	if(temp_SetEmgBrake == true)EmgBrakeButton.setSelected(true);
	else EmgBrakeButton.setSelected(false);

	Setting.hide();
}

void MainView::SettingShowButton()
{
	oldtemp_SetMaxPos = g_st_Setting.s32MaxPosValue;
	oldtemp_SetMinPos = g_st_Setting.s32MinPosValue;
	oldtemp_SetGearDen = g_st_Setting.fGearDenominator;
	oldtemp_SetGearNum = g_st_Setting.fGearNumerator;
	oldtemp_SetDiameter = g_st_Setting.fDiameter;
	oldtemp_SetMinMaxRpm = g_st_inverter.MinMaxRpmvalue;

	temp_SetType = g_st_Setting.s32DriveSettingType;

	oldtemp_SetWire = g_st_Setting.fWire;
	oldtemp_SetEncPulse = g_st_Direct.u16EncoderPulse;

	temp_SetYoYo = bool(g_st_Setting.s32YoYo);
	temp_SetParking = bool(g_st_Setting.s32Parking);
	temp_SetWireOut = bool(g_st_Setting.s32WireOut);
	temp_SetEmgBrake = bool(g_st_Setting.s32EmgBrake);

	if(temp_SetYoYo == true)YoYoButton.setSelected(true);
	else YoYoButton.setSelected(false);
	if(temp_SetParking == true)ParkingButton.setSelected(true);
	else ParkingButton.setSelected(false);
	if(temp_SetWireOut == true)WireOutButton.setSelected(true);
	else WireOutButton.setSelected(false);
	if(temp_SetEmgBrake == true)EmgBrakeButton.setSelected(true);
	else EmgBrakeButton.setSelected(false);
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
void MainView::EmgBrakeSelected()
{
	EmgBrakeButton.setSelected(true);
	temp_SetEmgBrake = true;
}
void MainView::EmgBrakeDeselected()
{
	EmgBrakeButton.setSelected(false);
	temp_SetEmgBrake = false;
}
void MainView::WireOutSelected()
{
	WireOutButton.setSelected(true);
	temp_SetWireOut = true;
}
void MainView::WireOutDeselected()
{
	WireOutButton.setSelected(false);
	temp_SetWireOut = false;
}
void MainView::ParkingSelected()
{
	ParkingButton.setSelected(true);
	temp_SetParking = true;
}
void MainView::ParkingDeselected()
{
	ParkingButton.setSelected(false);
	temp_SetParking = false;
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
		//UpdateInputValue(g_s32Vel_input_Rpmvalue, -g_st_inverter.MinMaxRpmvalue, g_st_inverter.MinMaxRpmvalue);
		UpdateInputValue(g_s32Vel_input_Rpmvalue, -100, 100);
		UpdateKeypadDisplay(g_s32Vel_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_RPM:
		//UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, g_st_inverter.MinMaxRpmvalue);
		UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, 100);
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
		UpdateInputValue(g_s32Home_input_Posvalue, g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
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
		UpdateInputValue(g_s32Direct_input_UpPosvalue, g_st_Direct.s32DirectActPos, g_st_Setting.s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_UpPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Down_POS:
		UpdateInputValue(g_s32Direct_input_DownPosvalue, g_st_Setting.s32MinPosValue, g_st_Direct.s32DirectActPos);
		UpdateKeypadDisplay(g_s32Direct_input_DownPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Home_POS :
		UpdateInputValue(g_s32Direct_input_Homevalue, g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
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
		//UpdateInputValue(g_s32Vel_input_Rpmvalue, -g_st_inverter.MinMaxRpmvalue, g_st_inverter.MinMaxRpmvalue);
		UpdateInputValue(g_s32Vel_input_Rpmvalue, -100, 100);
		UpdateKeypadDisplay(g_s32Vel_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_RPM:
		//UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, g_st_inverter.MinMaxRpmvalue);
		UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, 100);
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
		UpdateInputValue(g_s32Home_input_Posvalue, g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
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
		UpdateInputValue(g_s32Direct_input_UpPosvalue, g_st_Direct.s32DirectActPos, g_st_Setting.s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_UpPosvalue, false, 0);
		break;
	case KEYPAD_Direct_Down_POS:
		UpdateInputValue(g_s32Direct_input_DownPosvalue, g_st_Setting.s32MinPosValue, g_st_Direct.s32DirectActPos);
		UpdateKeypadDisplay(g_s32Direct_input_DownPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Home_POS :
		UpdateInputValue(g_s32Direct_input_Homevalue, g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
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
		//UpdateInputValue(g_s32Vel_input_Rpmvalue, -g_st_inverter.MinMaxRpmvalue, g_st_inverter.MinMaxRpmvalue);
		UpdateInputValue(g_s32Vel_input_Rpmvalue, -100, 100);
		UpdateKeypadDisplay(g_s32Vel_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_RPM:
		//UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, g_st_inverter.MinMaxRpmvalue);
		UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, 100);
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
		UpdateInputValue(g_s32Home_input_Posvalue, g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
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
		UpdateInputValue(g_s32Direct_input_UpPosvalue, g_st_Direct.s32DirectActPos, g_st_Setting.s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_UpPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Down_POS:
		UpdateInputValue(g_s32Direct_input_DownPosvalue, g_st_Setting.s32MinPosValue, g_st_Direct.s32DirectActPos);
		UpdateKeypadDisplay(g_s32Direct_input_DownPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Home_POS :
		UpdateInputValue(g_s32Direct_input_Homevalue, g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
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
		UpdateInputValue(g_s32Vel_input_Rpmvalue, -100, 100);
		UpdateKeypadDisplay(g_s32Vel_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_RPM:
		UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, 100);
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
		UpdateInputValue(g_s32Home_input_Posvalue, g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
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
		UpdateInputValue(g_s32Direct_input_UpPosvalue, g_st_Direct.s32DirectActPos, g_st_Setting.s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_UpPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Down_POS:
		UpdateInputValue(g_s32Direct_input_DownPosvalue, g_st_Setting.s32MinPosValue, g_st_Direct.s32DirectActPos);
		UpdateKeypadDisplay(g_s32Direct_input_DownPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Home_POS :
		UpdateInputValue(g_s32Direct_input_Homevalue, g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
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
		//UpdateInputValue(g_s32Vel_input_Rpmvalue, -g_st_inverter.MinMaxRpmvalue, g_st_inverter.MinMaxRpmvalue);
		UpdateInputValue(g_s32Vel_input_Rpmvalue, -100, 100);
		UpdateKeypadDisplay(g_s32Vel_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_RPM:
		//UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, g_st_inverter.MinMaxRpmvalue);
		UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, 100);
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
		UpdateInputValue(g_s32Home_input_Posvalue, g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
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
		UpdateInputValue(g_s32Direct_input_UpPosvalue, g_st_Direct.s32DirectActPos, g_st_Setting.s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_UpPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Down_POS:
		UpdateInputValue(g_s32Direct_input_DownPosvalue, g_st_Setting.s32MinPosValue, g_st_Direct.s32DirectActPos);
		UpdateKeypadDisplay(g_s32Direct_input_DownPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Home_POS :
		UpdateInputValue(g_s32Direct_input_Homevalue, g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
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
		//UpdateInputValue(g_s32Vel_input_Rpmvalue, -g_st_inverter.MinMaxRpmvalue, g_st_inverter.MinMaxRpmvalue);
		UpdateInputValue(g_s32Vel_input_Rpmvalue, -100, 100);
		UpdateKeypadDisplay(g_s32Vel_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_RPM:
		//UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, g_st_inverter.MinMaxRpmvalue);
		UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, 100);
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
		UpdateInputValue(g_s32Home_input_Posvalue, g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
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
		UpdateInputValue(g_s32Direct_input_UpPosvalue, g_st_Direct.s32DirectActPos, g_st_Setting.s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_UpPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Down_POS:
		UpdateInputValue(g_s32Direct_input_DownPosvalue, g_st_Setting.s32MinPosValue, g_st_Direct.s32DirectActPos);
		UpdateKeypadDisplay(g_s32Direct_input_DownPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Home_POS :
		UpdateInputValue(g_s32Direct_input_Homevalue, g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
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
		//UpdateInputValue(g_s32Vel_input_Rpmvalue, -g_st_inverter.MinMaxRpmvalue, g_st_inverter.MinMaxRpmvalue);
		UpdateInputValue(g_s32Vel_input_Rpmvalue, -100, 100);
		UpdateKeypadDisplay(g_s32Vel_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_RPM:
//		UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, g_st_inverter.MinMaxRpmvalue);
		UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, 100);
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
		UpdateInputValue(g_s32Home_input_Posvalue, g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
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
		UpdateInputValue(g_s32Direct_input_UpPosvalue, g_st_Direct.s32DirectActPos, g_st_Setting.s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_UpPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Down_POS:
		UpdateInputValue(g_s32Direct_input_DownPosvalue, g_st_Setting.s32MinPosValue, g_st_Direct.s32DirectActPos);
		UpdateKeypadDisplay(g_s32Direct_input_DownPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Home_POS :
		UpdateInputValue(g_s32Direct_input_Homevalue, g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
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
		//UpdateInputValue(g_s32Vel_input_Rpmvalue, -g_st_inverter.MinMaxRpmvalue, g_st_inverter.MinMaxRpmvalue);
		UpdateInputValue(g_s32Vel_input_Rpmvalue, -100, 100);
		UpdateKeypadDisplay(g_s32Vel_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_RPM:
		//UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, g_st_inverter.MinMaxRpmvalue);
		UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, 100);
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
		UpdateInputValue(g_s32Home_input_Posvalue, g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
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
		UpdateInputValue(g_s32Direct_input_UpPosvalue, g_st_Direct.s32DirectActPos, g_st_Setting.s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_UpPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Down_POS:
		UpdateInputValue(g_s32Direct_input_DownPosvalue, g_st_Setting.s32MinPosValue, g_st_Direct.s32DirectActPos);
		UpdateKeypadDisplay(g_s32Direct_input_DownPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Home_POS :
		UpdateInputValue(g_s32Direct_input_Homevalue, g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
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
		//UpdateInputValue(g_s32Vel_input_Rpmvalue, -g_st_inverter.MinMaxRpmvalue, g_st_inverter.MinMaxRpmvalue);
		UpdateInputValue(g_s32Vel_input_Rpmvalue, -100, 100);
		UpdateKeypadDisplay(g_s32Vel_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_RPM:
		//UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, g_st_inverter.MinMaxRpmvalue);
		UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, 100);
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
		UpdateInputValue(g_s32Home_input_Posvalue, g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
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
		UpdateInputValue(g_s32Direct_input_UpPosvalue, g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_UpPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Down_POS:
		UpdateInputValue(g_s32Direct_input_DownPosvalue, g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_DownPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Home_POS :
		UpdateInputValue(g_s32Direct_input_Homevalue, g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
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
				value = value + 0.0f;
				dot_value = 1;
			}
			/*else if (dot_value == 1) {
				value = value + 0.00f;
				dot_value = 2;
			}*/
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
		//UpdateInputValue(g_s32Vel_input_Rpmvalue, -g_st_inverter.MinMaxRpmvalue, g_st_inverter.MinMaxRpmvalue);
		UpdateInputValue(g_s32Vel_input_Rpmvalue, -100, 100);
		UpdateKeypadDisplay(g_s32Vel_input_Rpmvalue, false, 0);
		break;

	case KEYPAD_Position_RPM:
		//UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, g_st_inverter.MinMaxRpmvalue);
		UpdateInputValue(g_s32Pos_input_Rpmvalue, 0, 100);
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
		UpdateInputValue(g_s32Home_input_Posvalue, g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
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
		UpdateInputValue(g_s32Direct_input_UpPosvalue, g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_UpPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Down_POS:
		UpdateInputValue(g_s32Direct_input_DownPosvalue, g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
		UpdateKeypadDisplay(g_s32Direct_input_DownPosvalue, false, 0);
		break;

	case KEYPAD_Direct_Home_POS :
		UpdateInputValue(g_s32Direct_input_Homevalue, g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
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
            ToggleSign(g_s32Pos_input_Posvalue, g_st_Setting.s32MinPosValue);
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
            ToggleSign(g_s32Home_input_Posvalue, g_st_Setting.s32MinPosValue);
            UpdateKeypadDisplay(g_s32Home_input_Posvalue);
            break;

        case KEYPAD_Direct_Up_POS :
        	TargetUpDownToggleSign(g_s32Direct_input_UpPosvalue,g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
        	UpdateKeypadDisplay(g_s32Direct_input_UpPosvalue);
        	break;

        case KEYPAD_Direct_Down_POS :
        	TargetUpDownToggleSign(g_s32Direct_input_DownPosvalue,g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
        	UpdateKeypadDisplay(g_s32Direct_input_DownPosvalue);
        	break;

        case KEYPAD_Direct_Home_POS :
        	ToggleSign(g_s32Direct_input_Homevalue,g_st_Setting.s32MinPosValue);
        	UpdateKeypadDisplay(g_s32Direct_input_Homevalue);
        	break;

        default:
            break;
    }
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
            g_st_inverter.PosSetRpmvalue = (int)(((float)g_s32Pos_input_Rpmvalue / 100) * g_st_inverter.MinMaxRpmvalue);
            g_s32Pos_input_Rpmvalue = 0;
            break;

        case KEYPAD_Position_POS:
            SetValue(g_st_inverter.PosSetPosvalue, g_s32Pos_input_Posvalue, g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
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
            SetValue(g_st_inverter.HomeSetPosvalue, g_s32Home_input_Posvalue, g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
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
                oldtemp_SetMinMaxRpm = g_st_inverter.MinMaxRpmvalue;
            break;

        case KEYPAD_Direct_Up_POS:
        	if (g_s32Direct_input_UpPosvalue <= g_st_Direct.s32DirectActPos)
        		g_st_Direct.s16UpPosSetValue = (int16_t)g_st_Direct.s32DirectActPos;
        	else
        	{
        		if(g_s32Direct_input_UpPosvalue >= g_st_Setting.s32MaxPosValue)
        			g_st_Direct.s16UpPosSetValue = (int16_t)g_st_Setting.s32MaxPosValue;
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
				if(g_s32Direct_input_DownPosvalue <= g_st_Setting.s32MinPosValue)
					g_st_Direct.s16DownPosSetValue = (int16_t)g_st_Setting.s32MinPosValue;
				else
					g_st_Direct.s16DownPosSetValue = (int16_t)g_s32Direct_input_DownPosvalue;
			}
        	g_s32Direct_input_DownPosvalue = 0;
        	break;

        case KEYPAD_Direct_Home_POS :
        	SetValue(g_st_Direct.s16HomePosSetValue, g_s32Direct_input_Homevalue, g_st_Setting.s32MinPosValue, g_st_Setting.s32MaxPosValue);
        	break;

        case KEYPAD_Wire :
        	if (temp_SetWire > 0)
				oldtemp_SetWire = temp_SetWire;
			else
				oldtemp_SetWire = g_st_Setting.fWire;
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
	g_u16Errorcode = 0;
	g_st_IO.OUTError = false;
}
void MainView::EableButtonOn()
{
	/*if(g_st_Statusword.ready_to_switch_on == false && g_st_Statusword.switched_on == false && g_st_Statusword.switch_on_disabled == true )
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
	}*/
}
void MainView::ModeButtonOn()
{
	if(u8Screenpage == 1 && g_st_IO.IN_Local == true)
	{
		g_st_inverter.s8TouchgfxMode = Position;
		g_st_inverter.bTouchgfxModeWrite = true;
	}
	else if(u8Screenpage == 2 && g_st_IO.IN_Local == true)
	{
		g_st_inverter.s8TouchgfxMode = Home;
		g_st_inverter.bTouchgfxModeWrite = true;
	}
}
void MainView::PositionScreenButton()
{
	u8Screenpage = 1;
	g_st_inverter.s8TouchgfxMode = Position;
	g_st_inverter.bTouchgfxModeWrite = true;
}
void MainView::HomingScreenButton()
{
	u8Screenpage = 2;
	g_st_inverter.s8TouchgfxMode = Home;
	g_st_inverter.bTouchgfxModeWrite = true;
}
void MainView::PositionStartButton()
{
	if(g_st_inverter.s8CurrentMode == Position)
		g_st_inverter.bTouchgfx_StartButton = true;
}
void MainView::PositionStopButton()
{
	if(g_st_inverter.s8CurrentMode == Position)
		g_st_inverter.bTouchgfx_StopButton = true;
}
void MainView::HomeSetbutton()
{
	if(g_st_inverter.s8CurrentMode == Home)
		g_st_inverter.bTouchgfx_HomingButton = true;
}
void MainView::SetType_D_Button()
{
	temp_SetType = Direct_No_Enc;
}
void MainView::SetType_D_INC_Button()
{
	temp_SetType = Direct_INC;
}
void MainView::SetType_INV_ABS_Button()
{
	temp_SetType = Inverter_ABS;
}
void MainView::SettingSaveButton()
{
	if(oldtemp_SetMaxPos != 0)
	{
		g_st_FlashMemory.u32FlashSaveMaxPos = *(int*)&oldtemp_SetMaxPos;
		g_st_FlashMemory.bFlashWrite = true;
	}
	if(oldtemp_SetMinPos != 0)
	{
		g_st_FlashMemory.u32FlashSaveMinPos = *(int*)&oldtemp_SetMinPos;
		g_st_FlashMemory.bFlashWrite = true;
	}

	if(oldtemp_SetGearDen != 0)
	{
		g_st_FlashMemory.u32FlashSaveDen = *(uint32_t*)&oldtemp_SetGearDen;
		g_st_FlashMemory.bFlashWrite = true;
	}

	if(oldtemp_SetGearNum != 0)
	{
		g_st_FlashMemory.u32FlashSaveNum = *(uint32_t*)&oldtemp_SetGearNum;
		g_st_FlashMemory.bFlashWrite = true;
	}

	if(oldtemp_SetDiameter != 0)
	{
		g_st_FlashMemory.u32FlashSaveDiameter = *(uint32_t*)&oldtemp_SetDiameter;
		g_st_FlashMemory.bFlashWrite = true;
	}

	if(oldtemp_SetMinMaxRpm != 0)
	{
		g_st_FlashMemory.u32FlashSaveMinMaxRpm = *(uint32_t*)&oldtemp_SetMinMaxRpm;
		g_st_FlashMemory.bFlashWrite = true;
	}

	g_st_FlashMemory.u32FlashSaveDriveType = *(uint32_t*)&temp_SetType;
	g_st_FlashMemory.bFlashWrite = true;

	if(oldtemp_SetWire != 0)
	{
		g_st_FlashMemory.u32FlashSaveWire = *(uint32_t*)&oldtemp_SetWire;
		g_st_FlashMemory.bFlashWrite = true;
	}

	g_st_FlashMemory.u32FlashSaveYoYo = 0x0000000000000000 | temp_SetYoYo;//*(uint32_t*)&temp_SetYoYo;
	g_st_FlashMemory.u32FlashSaveParking = 0x0000000000000000 | temp_SetParking;//*(uint32_t*)&temp_SetSecondBrake;
	g_st_FlashMemory.u32FlashSaveWireOut = 0x0000000000000000 | temp_SetWireOut;//*(uint32_t*)&temp_SetWireOut;
	g_st_FlashMemory.u32FlashSaveEmgBrake = 0x0000000000000000 | temp_SetEmgBrake;//*(uint32_t*)&temp_SetEmgBrake;

	if(oldtemp_SetEncPulse != 0)
	{
		g_st_FlashMemory.u32FlashSaveEncPulse = *(uint32_t*)&oldtemp_SetEncPulse;
		g_st_FlashMemory.bFlashWrite = true;
	}
}
void MainView::MC_ON_Button()
{
	if(g_st_IO.IN_McIn == false && g_st_IO.IN_McOut == false)
	{
		g_st_IO.OUT_McIn = true;
		g_st_IO.OUT_McOut = true;
	}
	else
	{
		g_st_IO.OUT_McIn = false;
		g_st_IO.OUT_McOut = false;
	}
}

void MainView::ServconnectionButton()
{
	g_u8Ethernet_TcpStatus = 0;
}
void MainView::IOStateShowButton()
{
	IOState.show();
	bIOPageShowButton = true;
}

void MainView::IOStateHidButton()
{
	IOState.hide();
	bIOPageShowButton = false;
}


void MainView::DirectMoveUpButton()
{
	if(g_st_Setting.s32DriveSettingType == Direct_No_Enc || g_st_Setting.s32DriveSettingType == Direct_INC)
	{
		g_st_Direct.bTouchgfxUpButton = true;
		g_st_Direct.bTouchgfxDownButton = false;
	}
	else
	{
		g_st_Direct.bTouchgfxUpButton = false;
		g_st_Direct.bTouchgfxDownButton = false;
	}
}
void MainView::DirectMoveDownButton()
{
	if(g_st_Setting.s32DriveSettingType == Direct_No_Enc || g_st_Setting.s32DriveSettingType == Direct_INC)
	{
		g_st_Direct.bTouchgfxUpButton = false;
		g_st_Direct.bTouchgfxDownButton = true;
	}
	else
	{
		g_st_Direct.bTouchgfxUpButton = false;
		g_st_Direct.bTouchgfxDownButton = false;

	}
}
void MainView::DirectMoveStopButton()
{
	g_st_Direct.bTouchgfxUpButton = false;
	g_st_Direct.bTouchgfxDownButton = false;
}
void MainView::DirectHomeSetbutton()
{
	if(g_st_Direct.s16UpPosSetValue>= g_st_Direct.s16HomePosSetValue && g_st_Direct.s16HomePosSetValue >= g_st_Direct.s16DownPosSetValue)
	{
		g_st_Direct.s32DirectHomeOffset = g_st_Direct.s16HomePosSetValue;
		g_st_Direct.bHoming = true;
	}
}

void MainView::handleTickEvent()
{
	if(g_st_inverter.s8CurrentMode == Position)
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
	else if(g_st_inverter.s8CurrentMode == Home)
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
	if(g_st_IO.IN_Local == true)
	{
		RemoteAlarm.setVisible(false);
		RemoteAlarm.invalidate();
	}
	else
	{
		RemoteAlarm.setVisible(true);
		RemoteAlarm.invalidate();
	}

	//STM EMERGENCY
	if(g_st_IO.IN_EMG == false)
		STM_EMG.setVisible(true);
	else
		STM_EMG.setVisible(false);
	STM_EMG.invalidate();

	//STM ERROR Box
	if(g_bError == true)
		ResetBox.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
	else
		ResetBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	ResetBox.invalidate();

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

	Unicode :: snprintf(textStateValueBuffer,TEXTSTATEVALUE_SIZE,g_st_inverter.cStateStringDisplay);
	textStateValue.invalidate();

	Unicode :: snprintf(textErrorValueBuffer,TEXTERRORVALUE_SIZE,g_st_inverter.cErrorStringDisplay);
	textErrorValue.invalidate();


	Unicode :: snprintf(textMODEStateBuffer,TEXTMODESTATE_SIZE, g_st_inverter.cModeStringDisplay);
	textMODEState.invalidate();

	//Position mode Set Rpm value
	//Unicode :: snprintfFloat(textPosSetRpmValueBuffer,TEXTPOSSETRPMVALUE_SIZE, "%.f%", float(g_st_inverter.PosSetRpmvalue) / g_st_inverter.MinMaxRpmvalue * 100);
	Unicode :: snprintf(textPosSetRpmValueBuffer,TEXTPOSSETRPMVALUE_SIZE, "%d", int((float)g_st_inverter.PosSetRpmvalue / g_st_inverter.MinMaxRpmvalue * 100));
	textPosSetRpmValue.invalidate();

	//Position mode Actual Rpm value
	//Unicode :: snprintfFloat(textPosActRpmValueBuffer,TEXTPOSACTRPMVALUE_SIZE, "%.f%", float(g_st_inverter.ActRpmvalue) / g_st_inverter.MinMaxRpmvalue * 100);
	Unicode :: snprintf(textPosActRpmValueBuffer,TEXTPOSACTRPMVALUE_SIZE, "%d", int((float)g_st_inverter.ActRpmvalue / g_st_inverter.MinMaxRpmvalue * 100));
	textPosActRpmValue.invalidate();

	//Direct Encoder Mode Actual Pos value
	Unicode :: snprintf(textD_PosActValueBuffer, TEXTD_POSACTVALUE_SIZE, "%d",g_st_Direct.s32DirectActPos);
	textD_PosActValue.invalidate();

	//Direct mode Set Home value
	Unicode::snprintf(textD_HomeSetValueBuffer, TEXTD_HOMESETVALUE_SIZE, "%d", g_st_Direct.s16HomePosSetValue);
	textD_HomeSetValue.invalidate();

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
	if(g_st_IO.IN_FinalPosLimit == true){
		D_FUP_LimitBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
		D_FUP_LimitBox.invalidate();
	}
	else
	{
		D_FUP_LimitBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		D_FUP_LimitBox.invalidate();
	}
	//Up Limit
	if(g_st_IO.IN_PosLimit == true){
		D_UP_LimitBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
		D_UP_LimitBox.invalidate();
	}
	else
	{
		D_UP_LimitBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		D_UP_LimitBox.invalidate();
	}
	//Down Limit
	if(g_st_IO.IN_NegLimit == true){
		D_DN_LimitBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
		D_DN_LimitBox.invalidate();
	}
	else
	{
		D_DN_LimitBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		D_DN_LimitBox.invalidate();
	}
	//Final Down Limit
	if(g_st_IO.IN_FinalNegLimit == true){
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
	if(g_st_IO.IN_McIn == true && g_st_IO.IN_McOut == true){
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

	/*if(GVLComstate == 8)
	{
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
	}*/
	if(temp_SetType == No_Type)
	{
		if(g_st_Setting.s32DriveSettingType == Direct_No_Enc)
		{
			TypeD_Box.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
			TypeD_Box.invalidate();
			TypeD_INCBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
			TypeD_INCBox.invalidate();
			TypeINV_ABSBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
			TypeINV_ABSBox.invalidate();
		}
		else if(g_st_Setting.s32DriveSettingType == Direct_INC)
		{

			TypeD_INCBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
			TypeD_INCBox.invalidate();
			TypeD_Box.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
			TypeD_Box.invalidate();
			TypeINV_ABSBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
			TypeINV_ABSBox.invalidate();
		}
		else if(g_st_Setting.s32DriveSettingType == 3)
		{
			;
		}
		else if(g_st_Setting.s32DriveSettingType == Inverter_ABS)
		{
			TypeINV_ABSBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
			TypeINV_ABSBox.invalidate();
			TypeD_INCBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
			TypeD_INCBox.invalidate();
			TypeD_Box.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
			TypeD_Box.invalidate();
		}
	}
	else
	{
		if(temp_SetType == Direct_No_Enc)
		{
			TypeD_Box.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
			TypeD_Box.invalidate();
			TypeD_INCBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
			TypeD_INCBox.invalidate();
			TypeINV_ABSBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
			TypeINV_ABSBox.invalidate();
		}
		else if(temp_SetType == Direct_INC)
		{
			TypeD_INCBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
			TypeD_INCBox.invalidate();
			TypeD_Box.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
			TypeD_Box.invalidate();
			TypeINV_ABSBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
			TypeINV_ABSBox.invalidate();
		}
		else if(temp_SetType == Inverter_ABS)
		{
			TypeINV_ABSBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
			TypeINV_ABSBox.invalidate();
			TypeD_Box.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
			TypeD_Box.invalidate();
			TypeD_INCBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
			TypeD_INCBox.invalidate();
		}
	}

	if(g_st_Setting.s32DriveSettingType == Direct_No_Enc)
	{
		Direct.setVisible(true);
		Direct.invalidate();
		Direct_PosSetting.setVisible(false);
		Direct_PosSetting.invalidate();
		INVERTER.setVisible(false);
		INVERTER.invalidate();
	}
	else if(g_st_Setting.s32DriveSettingType == Direct_INC)
	{
		Direct.setVisible(true);
		Direct.invalidate();
		Direct_PosSetting.setVisible(true);
		Direct_PosSetting.invalidate();
		INVERTER.setVisible(false);
		INVERTER.invalidate();
	}
	else if (g_st_Setting.s32DriveSettingType == Inverter_ABS)
	{
		Direct.setVisible(false);
		Direct.invalidate();
		INVERTER.setVisible(true);
		INVERTER.invalidate();
	}
	else
	{
		Direct.setVisible(false);
		Direct.invalidate();
		INVERTER.setVisible(false);
		INVERTER.invalidate();
	}


	if(bIOPageShowButton)
	{
		//IOState//
		//Input
		if(g_bIO_Input[0] == true)//Input01
			IO_INPUT_LAMP_Box1.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			IO_INPUT_LAMP_Box1.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		IO_INPUT_LAMP_Box1.invalidate();

		if(g_bIO_Input[1] == true)//Input02
			IO_INPUT_LAMP_Box2.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			IO_INPUT_LAMP_Box2.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		IO_INPUT_LAMP_Box2.invalidate();

		if(g_bIO_Input[2] == true)//Input03
			IO_INPUT_LAMP_Box3.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			IO_INPUT_LAMP_Box3.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		IO_INPUT_LAMP_Box3.invalidate();

		if(g_bIO_Input[3] == true)//Input04
			IO_INPUT_LAMP_Box4.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			IO_INPUT_LAMP_Box4.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		IO_INPUT_LAMP_Box4.invalidate();

		if(g_bIO_Input[4] == true)//Input05
			IO_INPUT_LAMP_Box5.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			IO_INPUT_LAMP_Box5.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		IO_INPUT_LAMP_Box5.invalidate();

		if(g_bIO_Input[5] == true)//Input06
			IO_INPUT_LAMP_Box6.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			IO_INPUT_LAMP_Box6.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		IO_INPUT_LAMP_Box6.invalidate();

		if(g_bIO_Input[6] == true)//Input07
			IO_INPUT_LAMP_Box7.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			IO_INPUT_LAMP_Box7.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		IO_INPUT_LAMP_Box7.invalidate();

		if(g_bIO_Input[7] == true)//Input08
			IO_INPUT_LAMP_Box8.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			IO_INPUT_LAMP_Box8.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		IO_INPUT_LAMP_Box8.invalidate();

		if(g_bIO_Input[8] == true)//Input09
			IO_INPUT_LAMP_Box9.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			IO_INPUT_LAMP_Box9.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		IO_INPUT_LAMP_Box9.invalidate();

		if(g_bIO_Input[9] == true)//Input010
			IO_INPUT_LAMP_Box10.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			IO_INPUT_LAMP_Box10.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		IO_INPUT_LAMP_Box10.invalidate();

		if(g_bIO_Input[10] == true)//Input011
			IO_INPUT_LAMP_Box11.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			IO_INPUT_LAMP_Box11.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		IO_INPUT_LAMP_Box11.invalidate();

		if(g_bIO_Input[11] == true)//Input012
			IO_INPUT_LAMP_Box12.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			IO_INPUT_LAMP_Box12.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		IO_INPUT_LAMP_Box12.invalidate();

		if(g_bIO_Input[12] == true)//Input013
			IO_INPUT_LAMP_Box13.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			IO_INPUT_LAMP_Box13.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		IO_INPUT_LAMP_Box13.invalidate();

		if(g_bIO_Input[13] == true)//Input014
			IO_INPUT_LAMP_Box14.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			IO_INPUT_LAMP_Box14.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		IO_INPUT_LAMP_Box14.invalidate();

		if(g_bIO_Input[14] == true)//Input015
			IO_INPUT_LAMP_Box15.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			IO_INPUT_LAMP_Box15.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		IO_INPUT_LAMP_Box15.invalidate();

		if(g_bIO_Input[15] == true)//Input016
			IO_INPUT_LAMP_Box16.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			IO_INPUT_LAMP_Box16.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		IO_INPUT_LAMP_Box16.invalidate();

		//OUTPUT//
		if(g_bIO_Output[0] == true)//Output01
			IO_OUTPUT_LAMP_Box1.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			IO_OUTPUT_LAMP_Box1.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		IO_OUTPUT_LAMP_Box1.invalidate();
		if(g_bIO_Output[1] == true)//Output02
			IO_OUTPUT_LAMP_Box2.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			IO_OUTPUT_LAMP_Box2.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		IO_OUTPUT_LAMP_Box2.invalidate();

		if(g_bIO_Output[2] == true)//Output03
			IO_OUTPUT_LAMP_Box3.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			IO_OUTPUT_LAMP_Box3.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		IO_OUTPUT_LAMP_Box3.invalidate();

		if(g_bIO_Output[3] == true)//Output04
			IO_OUTPUT_LAMP_Box4.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			IO_OUTPUT_LAMP_Box4.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		IO_OUTPUT_LAMP_Box4.invalidate();

		if(g_bIO_Output[4] == true)//Output05
			IO_OUTPUT_LAMP_Box5.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			IO_OUTPUT_LAMP_Box5.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		IO_OUTPUT_LAMP_Box5.invalidate();

		if(g_bIO_Output[5] == true)//Output06
			IO_OUTPUT_LAMP_Box6.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			IO_OUTPUT_LAMP_Box6.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		IO_OUTPUT_LAMP_Box6.invalidate();

		if(g_bIO_Output[6] == true)//Output7
			IO_OUTPUT_LAMP_Box7.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			IO_OUTPUT_LAMP_Box7.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		IO_OUTPUT_LAMP_Box7.invalidate();

		if(g_bIO_Output[7] == true)//Output8
			IO_OUTPUT_LAMP_Box8.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			IO_OUTPUT_LAMP_Box8.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		IO_OUTPUT_LAMP_Box8.invalidate();

		if(g_bIO_Output[8] == true)//Output09
			IO_OUTPUT_LAMP_Box9.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			IO_OUTPUT_LAMP_Box9.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		IO_OUTPUT_LAMP_Box9.invalidate();

		if(g_bIO_Output[9] == true)//Output10
			IO_OUTPUT_LAMP_Box10.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			IO_OUTPUT_LAMP_Box10.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		IO_OUTPUT_LAMP_Box10.invalidate();
	}

	//Remote Tcp
	if(g_st_IO.IN_Local == false)
	{
		//RemoteEnable
		if(g_Tcp_STM_RemoteEnable)
			TcpSTMRemoteEnablebox.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			TcpSTMRemoteEnablebox.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		TcpSTMRemoteEnablebox.invalidate();
		//ConsoleEmg
		if(g_Tcp_ConsoleEMG)
			TcpSTMConsoleEmgbox.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			TcpSTMConsoleEmgbox.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		TcpSTMConsoleEmgbox.invalidate();

		//McOn
		if(g_Tcp_McOn)
			TcpSTMMcOnbox.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			TcpSTMMcOnbox.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		TcpSTMMcOnbox.invalidate();

		//DriveType
		if(g_Tcp_DriveType == Direct_No_Enc)
		{
			Unicode :: snprintf(textTcpSTMDriveTypeValueBuffer,TEXTTCPSTMDRIVETYPEVALUE_SIZE,"D_NO");
			textTcpErrorCodeValue.invalidate();
		}
		else if(g_Tcp_DriveType == Direct_INC)
		{
			Unicode :: snprintf(textTcpSTMDriveTypeValueBuffer,TEXTTCPSTMDRIVETYPEVALUE_SIZE,"D_INC");
			textTcpErrorCodeValue.invalidate();
		}
		else if(g_Tcp_DriveType == Direct_ABS)
		{
			Unicode :: snprintf(textTcpSTMDriveTypeValueBuffer,TEXTTCPSTMDRIVETYPEVALUE_SIZE,"D_ABS");
			textTcpErrorCodeValue.invalidate();
		}
		else if(g_Tcp_DriveType == Inverter_No_Enc)
		{
			Unicode :: snprintf(textTcpSTMDriveTypeValueBuffer,TEXTTCPSTMDRIVETYPEVALUE_SIZE,"I_NO");
			textTcpErrorCodeValue.invalidate();
		}
		else if(g_Tcp_DriveType == Inverter_INC)
		{
			Unicode :: snprintf(textTcpSTMDriveTypeValueBuffer,TEXTTCPSTMDRIVETYPEVALUE_SIZE,"I_INC");
			textTcpErrorCodeValue.invalidate();
		}
		else if(g_Tcp_DriveType == Inverter_ABS)
		{
			Unicode :: snprintf(textTcpSTMDriveTypeValueBuffer,TEXTTCPSTMDRIVETYPEVALUE_SIZE,"I_ABS");
			textTcpErrorCodeValue.invalidate();
		}
		else if(g_Tcp_DriveType == No_Type)
		{
			Unicode :: snprintf(textTcpSTMDriveTypeValueBuffer,TEXTTCPSTMDRIVETYPEVALUE_SIZE,"NO");
			textTcpErrorCodeValue.invalidate();
		}

		Unicode :: snprintf(textTcpErrorCodeValueBuffer, TEXTTCPERRORCODEVALUE_SIZE, "%d",g_Tcp_ErrorCode);
		textTcpErrorCodeValue.invalidate();

		Unicode :: snprintf(textTcpActPosValueBuffer, TEXTTCPACTPOSVALUE_SIZE, "%d", g_Tcp_ActPos);
		textTcpActPosValue.invalidate();

		Unicode :: snprintf(textTcpSTMTargetPosValueBuffer, TEXTTCPSTMTARGETPOSVALUE_SIZE, "%d", g_Tcp_TargetPos);
		textTcpSTMTargetPosValue.invalidate();

		Unicode :: snprintf(textTcpSTMSpeedValueBuffer, TEXTTCPSTMSPEEDVALUE_SIZE, "%d", g_Tcp_Speed);
		textTcpSTMSpeedValue.invalidate();

		Unicode :: snprintf(textTcpSTMHomeSetPosValueBuffer, TEXTTCPSTMHOMESETPOSVALUE_SIZE, "%d", g_Tcp_HomeSetPos);
		textTcpSTMHomeSetPosValue.invalidate();

		//Tcp Power
		if(g_Tcp_Power)
			TcpSTMPowerbox.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			TcpSTMPowerbox.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		TcpSTMPowerbox.invalidate();
		//Tcp Start
		if(g_Tcp_Start)
			TcpSTMStartbox.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			TcpSTMStartbox.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		TcpSTMStartbox.invalidate();
		//Tcp Stop
		if(g_Tcp_Stop)
			TcpSTMStopbox.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			TcpSTMStopbox.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		TcpSTMStopbox.invalidate();
		//Tcp Reset
		if(g_Tcp_Reset)
			TcpSTMResetbox.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			TcpSTMResetbox.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		TcpSTMResetbox.invalidate();

		if(g_Tcp_HomeSet)
			TcpSTMHomeSetbox.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			TcpSTMHomeSetbox.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		TcpSTMHomeSetbox.invalidate();

		if(g_Tcp_DirectUp)
			TcpSTMDirectUpbox.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			TcpSTMDirectUpbox.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		TcpSTMDirectUpbox.invalidate();

		if(g_Tcp_DirectDown)
			TcpSTMDirectDownbox.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			TcpSTMDirectDownbox.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		TcpSTMDirectDownbox.invalidate();

		if(g_Tcp_DirectStop)
			TcpSTMDirectStopbox.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			TcpSTMDirectStopbox.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		TcpSTMDirectStopbox.invalidate();

		//
		if(g_Tcp_LocalCtrlOn)
			TcpIsLocalCtrlOnbox.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			TcpIsLocalCtrlOnbox.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		TcpIsLocalCtrlOnbox.invalidate();

		if(g_Tcp_PowerStatus)
			TcpIsPowerStatusbox.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			TcpIsPowerStatusbox.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		TcpIsPowerStatusbox.invalidate();

		if(g_Tcp_IsRunning)
			TcpIsRunningbox.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			TcpIsRunningbox.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		TcpIsRunningbox.invalidate();

		if(g_Tcp_Arrived)
			TcpIsArrivedbox.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			TcpIsArrivedbox.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		TcpIsArrivedbox.invalidate();

		if(g_Tcp_IsError)
			TcpIsErrorbox.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			TcpIsErrorbox.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		TcpIsErrorbox.invalidate();

		if(g_Tcp_LimitFF)
			TcpLimitFFbox.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			TcpLimitFFbox.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		TcpLimitFFbox.invalidate();

		if(g_Tcp_LimitF)
			TcpLimitFbox.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			TcpLimitFbox.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		TcpLimitFbox.invalidate();

		if(g_Tcp_LimitR)
			TcpLimitRbox.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			TcpLimitRbox.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		TcpLimitRbox.invalidate();

		if(g_Tcp_LimitFR)
			TcpLimitFRbox.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			TcpLimitFRbox.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		TcpLimitFRbox.invalidate();

		if(g_Tcp_WireOut)
			TcpWireOutbox.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			TcpWireOutbox.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		TcpWireOutbox.invalidate();

		if(g_Tcp_EmgBrake)
			TcpEmgBrakebox.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		else
			TcpEmgBrakebox.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		TcpEmgBrakebox.invalidate();
	}
}
