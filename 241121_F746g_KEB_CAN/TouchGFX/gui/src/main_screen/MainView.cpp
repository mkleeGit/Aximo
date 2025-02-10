#include <gui/main_screen/MainView.hpp>
#include <touchgfx/Color.hpp>
#include <math.h>
MainView::MainView() {

}

void MainView::setupScreen() {
	MainViewBase::setupScreen();
	if (GVLPowerstate == true) {
		Popup_PowerState.setVisible(true);
		Popup_PowerState.invalidate();
	} else {
		;
	}

	GVLiMode = Position;
	GVLAddnumber = 1;


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
	if (GVLPowerstate == true) {
		Popup_PowerState.setVisible(true);
		Popup_PowerState.invalidate();
	} else {

		GVLAddnumber = 1;
	}
}
void MainView::List2ButtonOn() {
	if (GVLPowerstate == true) {
		Popup_PowerState.setVisible(true);
		Popup_PowerState.invalidate();
	} else {

		GVLAddnumber = 2;
	}
}
void MainView::List3ButtonOn() {
	if (GVLPowerstate == true) {
		Popup_PowerState.setVisible(true);
		Popup_PowerState.invalidate();
	} else {

		GVLAddnumber = 3;
	}
}
void MainView::List4ButtonOn() {
	if (GVLPowerstate == true) {
		Popup_PowerState.setVisible(true);
		Popup_PowerState.invalidate();
	} else {

		GVLAddnumber = 4;
	}
}
void MainView::List5ButtonOn() {
	if (GVLPowerstate == true) {
		Popup_PowerState.setVisible(true);
		Popup_PowerState.invalidate();
	} else {
		GVLAddnumber = 5;
	}
}
void MainView::List6ButtonOn() {
	if (GVLPowerstate == true) {
		Popup_PowerState.setVisible(true);
		Popup_PowerState.invalidate();
	} else {
		GVLAddnumber = 6;
	}
}
void MainView::PowerButtonON(){
	if(GVLinverter[GVLAddnumber].iMode == Position)
	{
		if(GVLStatusword.ready_to_switch_on == true && GVLStatusword.switched_on ==  true && GVLStatusword.switch_on_disabled == false)
				GVL_enable_operation = 8;
	}
}
void MainView::PowerButtonOFF(){
	GVL_enable_operation = 0;
}
void MainView::ComButtonONOFF()
{
	if(GVLComstate == 8)
	{
		GVLComon 		= false;
		GVLComoff 		= true;
		GVLWriteon		= true;
	}
	else if(GVLComstate == 0)
	{
		GVLComon 		= true;
		GVLComoff		= false;
		GVLWriteon		= true;
	}
}
void MainView::Velrpmpadshow()
{
	Numkeypad.setVisible(true);
	Numkeypad.invalidate();
	Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Vel_input_iRpmvalue);
	Keypadinputvalue.invalidate();
	Numbuttonminus.setVisible(true);
	Numbuttonminus.invalidate();
	Numbuttondot.setVisible(false);
	Numbuttondot.invalidate();
	KeypadMode = KEYPAD_Velocity_RPM;
	//GVLiMode = Velocity;
}

void MainView::Posrpmpadshow()
{
	Numkeypad.setVisible(true);
	Numkeypad.invalidate();
	Unicode:: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Pos_input_iRpmvalue);
	Keypadinputvalue.invalidate();
	Numbuttonminus.setVisible(false);
	Numbuttonminus.invalidate();
	Numbuttondot.setVisible(false);
	Numbuttondot.invalidate();
	KeypadMode = KEYPAD_Position_RPM;
	//GVLiMode = Position;
}

void MainView::Pospospadshow()
{
	Numkeypad.setVisible(true);
	Numkeypad.invalidate();
	Unicode:: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Pos_input_iPosvalue);
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
	Unicode:: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Home_input_iPosvalue);
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
void MainView::SettingHideButton()
{
	temp_SetMinMaxRpm = 0;
	temp_SetMaxPos = 0;
	temp_SetMinPos = 0;
	temp_SetGearDen = 0;
	temp_SetGearNum = 0;
	temp_SetDiameter = 0;
	Setting.hide();
}

void MainView::SetttingShowButton()
{
	oldtemp_SetMaxPos = GVLinverter[GVLAddnumber].maxPosvalue;
	oldtemp_SetMinPos = GVLinverter[GVLAddnumber].minPosvalue;
	oldtemp_SetGearDen = GVLinverter[GVLAddnumber].iGearDenominator;
	oldtemp_SetGearNum = GVLinverter[GVLAddnumber].iGearNumerator;
	oldtemp_SetDiameter = GVLinverter[GVLAddnumber].idiameter;
	oldtemp_SetMinMaxRpm = GVLinverter[GVLAddnumber].minmaxRpmvalue;
}

void MainView::Keypadhide()
{
	//if(GVLiMode == Velocity)
	if(KeypadMode == KEYPAD_Velocity_RPM)
		GVL_Vel_input_iRpmvalue = 0;
	else if(KeypadMode == KEYPAD_Position_RPM)
		GVL_Pos_input_iRpmvalue = 0;
	else if(KeypadMode == KEYPAD_Position_POS)
		GVL_Pos_input_iPosvalue = 0;
	else if(KeypadMode == KEYPAD_Setting_Minpos)
		temp_SetMinPos = 0;
	else if(KeypadMode == KEYPAD_Setting_Maxpos)
		temp_SetMaxPos = 0;
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
	else if(KeypadMode == KEYPAD_Home_POS)
	{
		GVL_Home_input_iPosvalue = 0;
	}
	else if(KeypadMode == KEYPAD_Setting_Diameter)
	{
		temp_SetDiameter = 0;
		dot_value = 0;
		dot_state = false;
	}
	else if(KeypadMode == KEYPAD_Setting_MinMaxVel)
	{
		temp_SetMinMaxRpm = 0;
	}
	Numkeypad.hide();
	//Numkeypad.setVisible(true);
	Numkeypad.invalidate();
}
void MainView::Num1Button()
{
	if(KeypadMode == KEYPAD_Velocity_RPM)
	{
		if (GVL_Vel_input_iRpmvalue == 0){
			GVL_Vel_input_iRpmvalue = 1;
			if(GVL_Vel_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Vel_input_iRpmvalue > 0){
			GVL_Vel_input_iRpmvalue = (GVL_Vel_input_iRpmvalue * 10) + 1;
			if(GVL_Vel_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Vel_input_iRpmvalue < 0){
			GVL_Vel_input_iRpmvalue = (GVL_Vel_input_iRpmvalue * 10) - 1;
			if(GVL_Vel_input_iRpmvalue <= (GVLinverter[GVLAddnumber].minmaxRpmvalue * -1))
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue * -1;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Vel_input_iRpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_RPM)
	{
		if(GVL_Pos_input_iRpmvalue == 0){
			GVL_Pos_input_iRpmvalue = 1;
			if(GVL_Pos_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Pos_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Pos_input_iRpmvalue > 0){
			GVL_Pos_input_iRpmvalue = (GVL_Pos_input_iRpmvalue * 10) + 1;
			if(GVL_Pos_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Pos_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Pos_input_iRpmvalue);

	}
	else if(KeypadMode == KEYPAD_Position_POS)
	{
		if (GVL_Pos_input_iPosvalue == 0){
			GVL_Pos_input_iPosvalue = 1;
			if(GVL_Pos_input_iPosvalue >= SettingPosmaxHigh)
				GVL_Pos_input_iPosvalue = SettingPosmaxHigh;
		}
		else if(GVL_Pos_input_iPosvalue > 0){
			GVL_Pos_input_iPosvalue = (GVL_Pos_input_iPosvalue * 10) + 1;
			if(GVL_Pos_input_iPosvalue >= SettingPosmaxHigh)
				GVL_Pos_input_iPosvalue = SettingPosmaxHigh;
		}
		else if(GVL_Pos_input_iPosvalue < 0){
			GVL_Pos_input_iPosvalue = (GVL_Pos_input_iPosvalue * 10) - 1;
			if(GVL_Pos_input_iPosvalue <= SettingPosmaxLow)
				GVL_Pos_input_iPosvalue = SettingPosmaxLow;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Pos_input_iPosvalue);
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
		if (GVL_Home_input_iPosvalue == 0){
			GVL_Home_input_iPosvalue = 1;
			if(GVL_Home_input_iPosvalue >= GVLinverter[GVLAddnumber].maxPosvalue)
				GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].maxPosvalue;
		}
		else if(GVL_Home_input_iPosvalue > 0){
			GVL_Home_input_iPosvalue = (GVL_Home_input_iPosvalue * 10) + 1;
			if(GVL_Home_input_iPosvalue >= GVLinverter[GVLAddnumber].maxPosvalue)
				GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].maxPosvalue;
		}
		else if(GVL_Home_input_iPosvalue < 0){
			GVL_Home_input_iPosvalue = (GVL_Home_input_iPosvalue * 10) - 1;
			if(GVL_Home_input_iPosvalue <= (GVLinverter[GVLAddnumber].minPosvalue))
				GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].minPosvalue;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Home_input_iPosvalue);
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
	Keypadinputvalue.invalidate();
}
void MainView::Num2Button()
{
	if(KeypadMode == KEYPAD_Velocity_RPM)
	{
		if (GVL_Vel_input_iRpmvalue == 0){
			GVL_Vel_input_iRpmvalue = 2;
			if(GVL_Vel_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Vel_input_iRpmvalue > 0){
			GVL_Vel_input_iRpmvalue = (GVL_Vel_input_iRpmvalue * 10) + 2;
			if(GVL_Vel_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Vel_input_iRpmvalue < 0){
			GVL_Vel_input_iRpmvalue = (GVL_Vel_input_iRpmvalue * 10) - 2;
			if(GVL_Vel_input_iRpmvalue <= (GVLinverter[GVLAddnumber].minmaxRpmvalue * -1))
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue * -1;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Vel_input_iRpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_RPM)
	{
		if(GVL_Pos_input_iRpmvalue == 0){
			GVL_Pos_input_iRpmvalue = 2;
			if(GVL_Pos_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Pos_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Pos_input_iRpmvalue > 0){
			GVL_Pos_input_iRpmvalue = (GVL_Pos_input_iRpmvalue * 10) + 2;
			if(GVL_Pos_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Pos_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Pos_input_iRpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_POS)
	{
		if (GVL_Pos_input_iPosvalue == 0){
			GVL_Pos_input_iPosvalue = 2;
			if(GVL_Pos_input_iPosvalue >= SettingPosmaxHigh)
				GVL_Pos_input_iPosvalue = SettingPosmaxHigh;
		}
		else if(GVL_Pos_input_iPosvalue > 0){
			GVL_Pos_input_iPosvalue = (GVL_Pos_input_iPosvalue * 10) + 2;
			if(GVL_Pos_input_iPosvalue >= SettingPosmaxHigh)
				GVL_Pos_input_iPosvalue = SettingPosmaxHigh;
		}
		else if(GVL_Pos_input_iPosvalue < 0){
			GVL_Pos_input_iPosvalue = (GVL_Pos_input_iPosvalue * 10) - 2;
			if(GVL_Pos_input_iPosvalue <= SettingPosmaxLow)
				GVL_Pos_input_iPosvalue = SettingPosmaxLow;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Pos_input_iPosvalue);
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
		if (GVL_Home_input_iPosvalue == 0){
			GVL_Home_input_iPosvalue = 2;
			if(GVL_Home_input_iPosvalue >= GVLinverter[GVLAddnumber].maxPosvalue)
				GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].maxPosvalue;
		}
		else if(GVL_Home_input_iPosvalue > 0){
			GVL_Home_input_iPosvalue = (GVL_Home_input_iPosvalue * 10) + 2;
			if(GVL_Home_input_iPosvalue >= GVLinverter[GVLAddnumber].maxPosvalue)
				GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].maxPosvalue;
		}
		else if(GVL_Home_input_iPosvalue < 0){
			GVL_Home_input_iPosvalue = (GVL_Home_input_iPosvalue * 10) - 2;
			if(GVL_Home_input_iPosvalue <= (GVLinverter[GVLAddnumber].minPosvalue))
				GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].minPosvalue;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Home_input_iPosvalue);
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
	Keypadinputvalue.invalidate();
}
void MainView::Num3Button()
{
	if(KeypadMode == KEYPAD_Velocity_RPM)
	{
		if (GVL_Vel_input_iRpmvalue == 0){
			GVL_Vel_input_iRpmvalue = 3;
			if(GVL_Vel_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Vel_input_iRpmvalue > 0){
			GVL_Vel_input_iRpmvalue = (GVL_Vel_input_iRpmvalue * 10) + 3;
			if(GVL_Vel_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Vel_input_iRpmvalue < 0){
			GVL_Vel_input_iRpmvalue = (GVL_Vel_input_iRpmvalue * 10) - 3;
			if(GVL_Vel_input_iRpmvalue <= (GVLinverter[GVLAddnumber].minmaxRpmvalue * -1))
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue * -1;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Vel_input_iRpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_RPM)
	{
		if(GVL_Pos_input_iRpmvalue == 0){
			GVL_Pos_input_iRpmvalue = 3;
			if(GVL_Pos_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Pos_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Pos_input_iRpmvalue > 0){
			GVL_Pos_input_iRpmvalue = (GVL_Pos_input_iRpmvalue * 10) + 3;
			if(GVL_Pos_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Pos_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Pos_input_iRpmvalue);

	}
	else if(KeypadMode == KEYPAD_Position_POS)
	{
		if (GVL_Pos_input_iPosvalue == 0){
			GVL_Pos_input_iPosvalue = 3;
			if(GVL_Pos_input_iPosvalue >= SettingPosmaxHigh)
				GVL_Pos_input_iPosvalue = SettingPosmaxHigh;
		}
		else if(GVL_Pos_input_iPosvalue > 0){
			GVL_Pos_input_iPosvalue = (GVL_Pos_input_iPosvalue * 10) + 3;
			if(GVL_Pos_input_iPosvalue >= SettingPosmaxHigh)
				GVL_Pos_input_iPosvalue = SettingPosmaxHigh;
		}
		else if(GVL_Pos_input_iPosvalue < 0){
			GVL_Pos_input_iPosvalue = (GVL_Pos_input_iPosvalue * 10) - 3;
			if(GVL_Pos_input_iPosvalue <= SettingPosmaxLow)
				GVL_Pos_input_iPosvalue = SettingPosmaxLow;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Pos_input_iPosvalue);
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
		if (GVL_Home_input_iPosvalue == 0){
			GVL_Home_input_iPosvalue = 3;
			if(GVL_Home_input_iPosvalue >= GVLinverter[GVLAddnumber].maxPosvalue)
				GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].maxPosvalue;
		}
		else if(GVL_Home_input_iPosvalue > 0){
			GVL_Home_input_iPosvalue = (GVL_Home_input_iPosvalue * 10) + 3;
			if(GVL_Home_input_iPosvalue >= GVLinverter[GVLAddnumber].maxPosvalue)
				GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].maxPosvalue;
		}
		else if(GVL_Home_input_iPosvalue < 0){
			GVL_Home_input_iPosvalue = (GVL_Home_input_iPosvalue * 10) - 3;
			if(GVL_Home_input_iPosvalue <= (GVLinverter[GVLAddnumber].minPosvalue))
				GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].minPosvalue;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Home_input_iPosvalue);
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
	Keypadinputvalue.invalidate();
}
void MainView::Num4Button()
{
	if(KeypadMode == KEYPAD_Velocity_RPM)
	{
		if (GVL_Vel_input_iRpmvalue == 0){
			GVL_Vel_input_iRpmvalue = 4;
			if(GVL_Vel_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Vel_input_iRpmvalue > 0){
			GVL_Vel_input_iRpmvalue = (GVL_Vel_input_iRpmvalue * 10) + 4;
			if(GVL_Vel_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Vel_input_iRpmvalue < 0){
			GVL_Vel_input_iRpmvalue = (GVL_Vel_input_iRpmvalue * 10) - 4;
			if(GVL_Vel_input_iRpmvalue <= (GVLinverter[GVLAddnumber].minmaxRpmvalue * -1))
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue * -1;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Vel_input_iRpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_RPM)
	{
		if(GVL_Pos_input_iRpmvalue == 0){
			GVL_Pos_input_iRpmvalue = 4;
			if(GVL_Pos_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Pos_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Pos_input_iRpmvalue > 0){
			GVL_Pos_input_iRpmvalue = (GVL_Pos_input_iRpmvalue * 10) + 4;
			if(GVL_Pos_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Pos_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Pos_input_iRpmvalue);

	}
	else if(KeypadMode == KEYPAD_Position_POS)
	{
		if (GVL_Pos_input_iPosvalue == 0){
			GVL_Pos_input_iPosvalue = 4;
			if(GVL_Pos_input_iPosvalue >= SettingPosmaxHigh)
				GVL_Pos_input_iPosvalue = SettingPosmaxHigh;
		}
		else if(GVL_Pos_input_iPosvalue > 0){
			GVL_Pos_input_iPosvalue = (GVL_Pos_input_iPosvalue * 10) + 4;
			if(GVL_Pos_input_iPosvalue >= SettingPosmaxHigh)
				GVL_Pos_input_iPosvalue = SettingPosmaxHigh;
		}
		else if(GVL_Pos_input_iPosvalue < 0){
			GVL_Pos_input_iPosvalue = (GVL_Pos_input_iPosvalue * 10) - 4;
			if(GVL_Pos_input_iPosvalue <= SettingPosmaxLow)
				GVL_Pos_input_iPosvalue = SettingPosmaxLow;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Pos_input_iPosvalue);
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
		if (GVL_Home_input_iPosvalue == 0){
			GVL_Home_input_iPosvalue = 4;
			if(GVL_Home_input_iPosvalue >= GVLinverter[GVLAddnumber].maxPosvalue)
				GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].maxPosvalue;
		}
		else if(GVL_Home_input_iPosvalue > 0){
			GVL_Home_input_iPosvalue = (GVL_Home_input_iPosvalue * 10) + 4;
			if(GVL_Home_input_iPosvalue >= GVLinverter[GVLAddnumber].maxPosvalue)
				GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].maxPosvalue;
		}
		else if(GVL_Home_input_iPosvalue < 0){
			GVL_Home_input_iPosvalue = (GVL_Home_input_iPosvalue * 10) - 4;
			if(GVL_Home_input_iPosvalue <= (GVLinverter[GVLAddnumber].minPosvalue))
				GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].minPosvalue;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Home_input_iPosvalue);
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
	Keypadinputvalue.invalidate();
}
void MainView::Num5Button()
{
	if(KeypadMode == KEYPAD_Velocity_RPM)
	{
		if (GVL_Vel_input_iRpmvalue == 0){
			GVL_Vel_input_iRpmvalue = 5;
			if(GVL_Vel_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Vel_input_iRpmvalue > 0){
			GVL_Vel_input_iRpmvalue = (GVL_Vel_input_iRpmvalue * 10) + 5;
			if(GVL_Vel_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Vel_input_iRpmvalue < 0){
			GVL_Vel_input_iRpmvalue = (GVL_Vel_input_iRpmvalue * 10) - 5;
			if(GVL_Vel_input_iRpmvalue <= (GVLinverter[GVLAddnumber].minmaxRpmvalue * -1))
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue * -1;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Vel_input_iRpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_RPM)
	{
		if(GVL_Pos_input_iRpmvalue == 0){
			GVL_Pos_input_iRpmvalue = 5;
			if(GVL_Pos_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Pos_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Pos_input_iRpmvalue > 0){
			GVL_Pos_input_iRpmvalue = (GVL_Pos_input_iRpmvalue * 10) + 5;
			if(GVL_Pos_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Pos_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Pos_input_iRpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_POS)
	{
		if (GVL_Pos_input_iPosvalue == 0){
			GVL_Pos_input_iPosvalue = 5;
			if(GVL_Pos_input_iPosvalue >= SettingPosmaxHigh)
				GVL_Pos_input_iPosvalue = SettingPosmaxHigh;
		}
		else if(GVL_Pos_input_iPosvalue > 0){
			GVL_Pos_input_iPosvalue = (GVL_Pos_input_iPosvalue * 10) + 5;
			if(GVL_Pos_input_iPosvalue >= SettingPosmaxHigh)
				GVL_Pos_input_iPosvalue = SettingPosmaxHigh;
		}
		else if(GVL_Pos_input_iPosvalue < 0){
			GVL_Pos_input_iPosvalue = (GVL_Pos_input_iPosvalue * 10) - 5;
			if(GVL_Pos_input_iPosvalue <= SettingPosmaxLow)
				GVL_Pos_input_iPosvalue = SettingPosmaxLow;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Pos_input_iPosvalue);
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
		if (GVL_Home_input_iPosvalue == 0){
			GVL_Home_input_iPosvalue = 1;
			if(GVL_Home_input_iPosvalue >= GVLinverter[GVLAddnumber].maxPosvalue)
				GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].maxPosvalue;
		}
		else if(GVL_Home_input_iPosvalue > 0){
			GVL_Home_input_iPosvalue = (GVL_Home_input_iPosvalue * 10) + 5;
			if(GVL_Home_input_iPosvalue >= GVLinverter[GVLAddnumber].maxPosvalue)
				GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].maxPosvalue;
		}
		else if(GVL_Home_input_iPosvalue < 0){
			GVL_Home_input_iPosvalue = (GVL_Home_input_iPosvalue * 10) - 5;
			if(GVL_Home_input_iPosvalue <= (GVLinverter[GVLAddnumber].minPosvalue))
				GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].minPosvalue;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Home_input_iPosvalue);
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
	Keypadinputvalue.invalidate();
}
void MainView::Num6Button()
{
	if(KeypadMode == KEYPAD_Velocity_RPM)
	{
		if (GVL_Vel_input_iRpmvalue == 0){
			GVL_Vel_input_iRpmvalue = 6;
			if(GVL_Vel_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Vel_input_iRpmvalue > 0){
			GVL_Vel_input_iRpmvalue = (GVL_Vel_input_iRpmvalue * 10) + 6;
			if(GVL_Vel_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Vel_input_iRpmvalue < 0){
			GVL_Vel_input_iRpmvalue = (GVL_Vel_input_iRpmvalue * 10) - 6;
			if(GVL_Vel_input_iRpmvalue <= (GVLinverter[GVLAddnumber].minmaxRpmvalue * -1))
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue * -1;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Vel_input_iRpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_RPM)
	{
		if(GVL_Pos_input_iRpmvalue == 0){
			GVL_Pos_input_iRpmvalue = 6;
			if(GVL_Pos_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Pos_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Pos_input_iRpmvalue > 0){
			GVL_Pos_input_iRpmvalue = (GVL_Pos_input_iRpmvalue * 10) + 6;
			if(GVL_Pos_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Pos_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Pos_input_iRpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_POS)
	{
		if (GVL_Pos_input_iPosvalue == 0){
			GVL_Pos_input_iPosvalue = 6;
			if(GVL_Pos_input_iPosvalue >= SettingPosmaxHigh)
				GVL_Pos_input_iPosvalue = SettingPosmaxHigh;
		}
		else if(GVL_Pos_input_iPosvalue > 0){
			GVL_Pos_input_iPosvalue = (GVL_Pos_input_iPosvalue * 10) + 6;
			if(GVL_Pos_input_iPosvalue >= SettingPosmaxHigh)
				GVL_Pos_input_iPosvalue = SettingPosmaxHigh;
		}
		else if(GVL_Pos_input_iPosvalue < 0){
			GVL_Pos_input_iPosvalue = (GVL_Pos_input_iPosvalue * 10) - 6;
			if(GVL_Pos_input_iPosvalue <= SettingPosmaxLow)
				GVL_Pos_input_iPosvalue = SettingPosmaxLow;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Pos_input_iPosvalue);
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
		if (GVL_Home_input_iPosvalue == 0){
			GVL_Home_input_iPosvalue = 6;
			if(GVL_Home_input_iPosvalue >= GVLinverter[GVLAddnumber].maxPosvalue)
				GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].maxPosvalue;
		}
		else if(GVL_Home_input_iPosvalue > 0){
			GVL_Home_input_iPosvalue = (GVL_Home_input_iPosvalue * 10) + 6;
			if(GVL_Home_input_iPosvalue >= GVLinverter[GVLAddnumber].maxPosvalue)
				GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].maxPosvalue;
		}
		else if(GVL_Home_input_iPosvalue < 0){
			GVL_Home_input_iPosvalue = (GVL_Home_input_iPosvalue * 10) - 6;
			if(GVL_Home_input_iPosvalue <= (GVLinverter[GVLAddnumber].minPosvalue))
				GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].minPosvalue;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Home_input_iPosvalue);
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
	Keypadinputvalue.invalidate();
}
void MainView::Num7Button()
{
	if(KeypadMode == KEYPAD_Velocity_RPM)
	{
		if (GVL_Vel_input_iRpmvalue == 0){
			GVL_Vel_input_iRpmvalue = 7;
			if(GVL_Vel_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Vel_input_iRpmvalue > 0){
			GVL_Vel_input_iRpmvalue = (GVL_Vel_input_iRpmvalue * 10) + 7;
			if(GVL_Vel_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Vel_input_iRpmvalue < 0){
			GVL_Vel_input_iRpmvalue = (GVL_Vel_input_iRpmvalue * 10) - 7;
			if(GVL_Vel_input_iRpmvalue <= (GVLinverter[GVLAddnumber].minmaxRpmvalue * -1))
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue * -1;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Vel_input_iRpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_RPM)
	{
		if(GVL_Pos_input_iRpmvalue == 0){
			GVL_Pos_input_iRpmvalue = 7;
			if(GVL_Pos_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Pos_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Pos_input_iRpmvalue > 0){
			GVL_Pos_input_iRpmvalue = (GVL_Pos_input_iRpmvalue * 10) + 7;
			if(GVL_Pos_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Pos_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Pos_input_iRpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_POS)
	{
		if (GVL_Pos_input_iPosvalue == 0){
			GVL_Pos_input_iPosvalue = 7;
			if(GVL_Pos_input_iPosvalue >= SettingPosmaxHigh)
				GVL_Pos_input_iPosvalue = SettingPosmaxHigh;
		}
		else if(GVL_Pos_input_iPosvalue > 0){
			GVL_Pos_input_iPosvalue = (GVL_Pos_input_iPosvalue * 10) + 7;
			if(GVL_Pos_input_iPosvalue >= SettingPosmaxHigh)
				GVL_Pos_input_iPosvalue = SettingPosmaxHigh;
		}
		else if(GVL_Pos_input_iPosvalue < 0){
			GVL_Pos_input_iPosvalue = (GVL_Pos_input_iPosvalue * 10) - 7;
			if(GVL_Pos_input_iPosvalue <= SettingPosmaxLow)
				GVL_Pos_input_iPosvalue = SettingPosmaxLow;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Pos_input_iPosvalue);
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
		if (GVL_Home_input_iPosvalue == 0){
			GVL_Home_input_iPosvalue = 7;
			if(GVL_Home_input_iPosvalue >= GVLinverter[GVLAddnumber].maxPosvalue)
				GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].maxPosvalue;
		}
		else if(GVL_Home_input_iPosvalue > 0){
			GVL_Home_input_iPosvalue = (GVL_Home_input_iPosvalue * 10) + 7;
			if(GVL_Home_input_iPosvalue >= GVLinverter[GVLAddnumber].maxPosvalue)
				GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].maxPosvalue;
		}
		else if(GVL_Home_input_iPosvalue < 0){
			GVL_Home_input_iPosvalue = (GVL_Home_input_iPosvalue * 10) - 7;
			if(GVL_Home_input_iPosvalue <= (GVLinverter[GVLAddnumber].minPosvalue))
				GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].minPosvalue;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Home_input_iPosvalue);
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
	Keypadinputvalue.invalidate();
}
void MainView::Num8Button()
{
	if(KeypadMode == KEYPAD_Velocity_RPM)
	{
		if (GVL_Vel_input_iRpmvalue == 0){
			GVL_Vel_input_iRpmvalue = 8;
			if(GVL_Vel_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Vel_input_iRpmvalue > 0){
			GVL_Vel_input_iRpmvalue = (GVL_Vel_input_iRpmvalue * 10) + 8;
			if(GVL_Vel_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Vel_input_iRpmvalue < 0){
			GVL_Vel_input_iRpmvalue = (GVL_Vel_input_iRpmvalue * 10) - 8;
			if(GVL_Vel_input_iRpmvalue <= (GVLinverter[GVLAddnumber].minmaxRpmvalue * -1))
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue * -1;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Vel_input_iRpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_RPM)
	{
		if(GVL_Pos_input_iRpmvalue == 0){
			GVL_Pos_input_iRpmvalue = 8;
			if(GVL_Pos_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Pos_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Pos_input_iRpmvalue > 0){
			GVL_Pos_input_iRpmvalue = (GVL_Pos_input_iRpmvalue * 10) + 8;
			if(GVL_Pos_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Pos_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Pos_input_iRpmvalue);

	}
	else if(KeypadMode == KEYPAD_Position_POS)
	{
		if (GVL_Pos_input_iPosvalue == 0){
			GVL_Pos_input_iPosvalue = 8;
			if(GVL_Pos_input_iPosvalue >= SettingPosmaxHigh)
				GVL_Pos_input_iPosvalue = SettingPosmaxHigh;
		}
		else if(GVL_Pos_input_iPosvalue > 0){
			GVL_Pos_input_iPosvalue = (GVL_Pos_input_iPosvalue * 10) + 8;
			if(GVL_Pos_input_iPosvalue >= SettingPosmaxHigh)
				GVL_Pos_input_iPosvalue = SettingPosmaxHigh;
		}
		else if(GVL_Pos_input_iPosvalue < 0){
			GVL_Pos_input_iPosvalue = (GVL_Pos_input_iPosvalue * 10) - 8;
			if(GVL_Pos_input_iPosvalue <= SettingPosmaxLow)
				GVL_Pos_input_iPosvalue = SettingPosmaxLow;
		}
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Pos_input_iPosvalue);
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
		if (GVL_Home_input_iPosvalue == 0){
			GVL_Home_input_iPosvalue = 8;
			if(GVL_Home_input_iPosvalue >= GVLinverter[GVLAddnumber].maxPosvalue)
				GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].maxPosvalue;
		}
		else if(GVL_Home_input_iPosvalue > 0){
			GVL_Home_input_iPosvalue = (GVL_Home_input_iPosvalue * 10) + 8;
			if(GVL_Home_input_iPosvalue >= GVLinverter[GVLAddnumber].maxPosvalue)
				GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].maxPosvalue;
		}
		else if(GVL_Home_input_iPosvalue < 0){
			GVL_Home_input_iPosvalue = (GVL_Home_input_iPosvalue * 10) - 8;
			if(GVL_Home_input_iPosvalue <= (GVLinverter[GVLAddnumber].minPosvalue))
				GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].minPosvalue;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Home_input_iPosvalue);
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
	Keypadinputvalue.invalidate();
}
void MainView::Num9Button()
{
	if(KeypadMode == KEYPAD_Velocity_RPM)
	{
		if (GVL_Vel_input_iRpmvalue == 0){
			GVL_Vel_input_iRpmvalue = 9;
			if(GVL_Vel_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Vel_input_iRpmvalue > 0){
			GVL_Vel_input_iRpmvalue = (GVL_Vel_input_iRpmvalue * 10) + 9;
			if(GVL_Vel_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Vel_input_iRpmvalue < 0){
			GVL_Vel_input_iRpmvalue = (GVL_Vel_input_iRpmvalue * 10) - 9;
			if(GVL_Vel_input_iRpmvalue <= (GVLinverter[GVLAddnumber].minmaxRpmvalue * -1))
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue * -1;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Vel_input_iRpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_RPM)
	{
		if(GVL_Pos_input_iRpmvalue == 0){
			GVL_Pos_input_iRpmvalue = 9;
			if(GVL_Pos_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Pos_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Pos_input_iRpmvalue > 0){
			GVL_Pos_input_iRpmvalue = (GVL_Pos_input_iRpmvalue * 10) + 9;
			if(GVL_Pos_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Pos_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Pos_input_iRpmvalue);

	}
	else if(KeypadMode == KEYPAD_Position_POS)
	{
		if (GVL_Pos_input_iPosvalue == 0){
			GVL_Pos_input_iPosvalue = 9;
			if(GVL_Pos_input_iPosvalue >= SettingPosmaxHigh)
				GVL_Pos_input_iPosvalue = SettingPosmaxHigh;
		}
		else if(GVL_Pos_input_iPosvalue > 0){
			GVL_Pos_input_iPosvalue = (GVL_Pos_input_iPosvalue * 10) + 9;
			if(GVL_Pos_input_iPosvalue >= SettingPosmaxHigh)
				GVL_Pos_input_iPosvalue = SettingPosmaxHigh;
		}
		else if(GVL_Pos_input_iPosvalue < 0){
			GVL_Pos_input_iPosvalue = (GVL_Pos_input_iPosvalue * 10) - 9;
			if(GVL_Pos_input_iPosvalue <= SettingPosmaxLow)
				GVL_Pos_input_iPosvalue = SettingPosmaxLow;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Pos_input_iPosvalue);
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
			if (GVL_Home_input_iPosvalue == 0){
				GVL_Home_input_iPosvalue = 9;
				if(GVL_Home_input_iPosvalue >= GVLinverter[GVLAddnumber].maxPosvalue)
					GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].maxPosvalue;
			}
			else if(GVL_Home_input_iPosvalue > 0){
				GVL_Home_input_iPosvalue = (GVL_Home_input_iPosvalue * 10) + 9;
				if(GVL_Home_input_iPosvalue >= GVLinverter[GVLAddnumber].maxPosvalue)
					GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].maxPosvalue;
			}
			else if(GVL_Home_input_iPosvalue < 0){
				GVL_Home_input_iPosvalue = (GVL_Home_input_iPosvalue * 10) - 9;
				if(GVL_Home_input_iPosvalue <= (GVLinverter[GVLAddnumber].minPosvalue))
					GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].minPosvalue;
			}

			Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Home_input_iPosvalue);
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
	Keypadinputvalue.invalidate();
}
void MainView::Num0Button()
{
	if(KeypadMode == KEYPAD_Velocity_RPM)
	{
		if (GVL_Vel_input_iRpmvalue == 0){
			GVL_Vel_input_iRpmvalue = 0;
			if(GVL_Vel_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Vel_input_iRpmvalue > 0){
			GVL_Vel_input_iRpmvalue = (GVL_Vel_input_iRpmvalue * 10);
			if(GVL_Vel_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Vel_input_iRpmvalue < 0){
			GVL_Vel_input_iRpmvalue = (GVL_Vel_input_iRpmvalue * 10);
			if(GVL_Vel_input_iRpmvalue <= (GVLinverter[GVLAddnumber].minmaxRpmvalue * -1))
				GVL_Vel_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue * -1;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Vel_input_iRpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_RPM)
	{
		if(GVL_Pos_input_iRpmvalue == 0){
			GVL_Pos_input_iRpmvalue = 0;
			if(GVL_Pos_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Pos_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}
		else if(GVL_Pos_input_iRpmvalue > 0){
			GVL_Pos_input_iRpmvalue = (GVL_Pos_input_iRpmvalue * 10);
			if(GVL_Pos_input_iRpmvalue >= GVLinverter[GVLAddnumber].minmaxRpmvalue)
				GVL_Pos_input_iRpmvalue = GVLinverter[GVLAddnumber].minmaxRpmvalue;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Pos_input_iRpmvalue);

	}
	else if(KeypadMode == KEYPAD_Position_POS)
	{
		if (GVL_Pos_input_iPosvalue == 0){
			GVL_Pos_input_iPosvalue = 0;
			if(GVL_Pos_input_iPosvalue >= SettingPosmaxHigh)
				GVL_Pos_input_iPosvalue = SettingPosmaxHigh;
		}
		else if(GVL_Pos_input_iPosvalue > 0){
			GVL_Pos_input_iPosvalue = (GVL_Pos_input_iPosvalue * 10);
			if(GVL_Pos_input_iPosvalue >= SettingPosmaxHigh)
				GVL_Pos_input_iPosvalue = SettingPosmaxHigh;
		}
		else if(GVL_Pos_input_iPosvalue < 0){
			GVL_Pos_input_iPosvalue = (GVL_Pos_input_iPosvalue * 10);
			if(GVL_Pos_input_iPosvalue <= SettingPosmaxLow)
				GVL_Pos_input_iPosvalue = SettingPosmaxLow;
		}

		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Pos_input_iPosvalue);
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
			if (GVL_Home_input_iPosvalue == 0){
				GVL_Home_input_iPosvalue = 0;
				if(GVL_Home_input_iPosvalue >= GVLinverter[GVLAddnumber].maxPosvalue)
					GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].maxPosvalue;
			}
			else if(GVL_Home_input_iPosvalue > 0){
				GVL_Home_input_iPosvalue = (GVL_Home_input_iPosvalue * 10);
				if(GVL_Home_input_iPosvalue >= GVLinverter[GVLAddnumber].maxPosvalue)
					GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].maxPosvalue;
			}
			else if(GVL_Home_input_iPosvalue < 0){
				GVL_Home_input_iPosvalue = (GVL_Home_input_iPosvalue * 10);
				if(GVL_Home_input_iPosvalue <= (GVLinverter[GVLAddnumber].minPosvalue))
					GVL_Home_input_iPosvalue = GVLinverter[GVLAddnumber].minPosvalue;
			}

			Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Home_input_iPosvalue);
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
	Keypadinputvalue.invalidate();
}
void MainView::MinusButton()
{
	if(KeypadMode == KEYPAD_Velocity_RPM)
	{
		GVL_Vel_input_iRpmvalue = GVL_Vel_input_iRpmvalue * -1;
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Vel_input_iRpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_POS)
	{
		if(GVL_Pos_input_iPosvalue * -1 >= GVLinverter[GVLAddnumber].minPosvalue)
			GVL_Pos_input_iPosvalue = GVL_Pos_input_iPosvalue * -1;
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Pos_input_iPosvalue);
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
		if(GVL_Home_input_iPosvalue * -1 >= GVLinverter[GVLAddnumber].minPosvalue)
			GVL_Home_input_iPosvalue = GVL_Home_input_iPosvalue * -1;
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Home_input_iPosvalue);
	}
	Keypadinputvalue.invalidate();
}
void MainView::EntButton()
{
	if(KeypadMode == KEYPAD_Velocity_RPM){
		GVLinverter[GVLAddnumber].VelsetRpmvalue = GVL_Vel_input_iRpmvalue;
		GVL_Vel_input_iRpmvalue = 0;
	}
	else if(KeypadMode == KEYPAD_Position_RPM){
		GVLinverter[GVLAddnumber].PossetRpmvalue = GVL_Pos_input_iRpmvalue;
		GVL_Pos_input_iRpmvalue = 0;
	}
	else if(KeypadMode == KEYPAD_Position_POS){
		if(GVLinverter[GVLAddnumber].minPosvalue <= GVL_Pos_input_iPosvalue && GVL_Pos_input_iPosvalue <= GVLinverter[GVLAddnumber].maxPosvalue)
		{
			GVLinverter[GVLAddnumber].PosSetPosvalue = GVL_Pos_input_iPosvalue;
			GVL_Pos_input_iPosvalue = 0;
		}
		else if(GVLinverter[GVLAddnumber].minPosvalue > GVL_Pos_input_iPosvalue)
		{
			GVLinverter[GVLAddnumber].PosSetPosvalue = GVLinverter[GVLAddnumber].minPosvalue;
			GVL_Pos_input_iPosvalue = 0;
		}
		else if(GVL_Pos_input_iPosvalue > GVLinverter[GVLAddnumber].maxPosvalue)
		{
			GVLinverter[GVLAddnumber].PosSetPosvalue = GVLinverter[GVLAddnumber].maxPosvalue;
			GVL_Pos_input_iPosvalue = 0;
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
		if(GVLinverter[GVLAddnumber].minPosvalue <= GVL_Home_input_iPosvalue && GVL_Home_input_iPosvalue <= GVLinverter[GVLAddnumber].maxPosvalue)
		{
			GVLinverter[GVLAddnumber].HomeSetPosvalue = GVL_Home_input_iPosvalue;
			GVL_Home_input_iPosvalue = 0;
		}
		else if(GVLinverter[GVLAddnumber].minPosvalue > GVL_Home_input_iPosvalue)
		{
			GVLinverter[GVLAddnumber].HomeSetPosvalue = GVLinverter[GVLAddnumber].minPosvalue;
			GVL_Home_input_iPosvalue = 0;
		}
		else if(GVL_Home_input_iPosvalue > GVLinverter[GVLAddnumber].maxPosvalue)
		{
			GVLinverter[GVLAddnumber].HomeTargetPosvalue = GVLinverter[GVLAddnumber].maxPosvalue;
			GVL_Home_input_iPosvalue = 0;
		}
	}
	else if(KeypadMode == KEYPAD_Setting_GearDen)
	{
		if(temp_SetGearDen > 0)
			oldtemp_SetGearDen = temp_SetGearDen;
		else if(temp_SetGearDen <= 0)
			oldtemp_SetGearDen = GVLinverter[GVLAddnumber].iGearDenominator;

		Unicode :: snprintfFloat(textGearDeno_valueBuffer,TEXTGEARDENO_VALUE_SIZE, "%.2f", temp_SetGearDen);
		textGearDeno_value.invalidate();
	}
	else if(KeypadMode == KEYPAD_Setting_GearNum)
	{
		if(temp_SetGearNum > 0)
			oldtemp_SetGearNum = temp_SetGearNum;
		else if(temp_SetGearNum <= 0)
			oldtemp_SetGearNum = GVLinverter[GVLAddnumber].iGearNumerator;

		Unicode :: snprintfFloat(textGearNum_valueBuffer,TEXTGEARNUM_VALUE_SIZE, "%.2f", temp_SetGearNum);
		textGearNum_value.invalidate();
	}
	else if(KeypadMode == KEYPAD_Setting_Diameter)
	{
		if(temp_SetDiameter > 0)
			oldtemp_SetDiameter = temp_SetDiameter;
		else if(temp_SetDiameter <= 0)
			oldtemp_SetDiameter = GVLinverter[GVLAddnumber].idiameter;

		Unicode :: snprintfFloat(textGearDeno_valueBuffer,TEXTGEARDENO_VALUE_SIZE, "%.2f", temp_SetDiameter);
		textGearDeno_value.invalidate();
	}
	else if(KeypadMode == KEYPAD_Setting_MinMaxVel)
	{
		if(temp_SetMinMaxRpm > 0)
			oldtemp_SetMinMaxRpm = temp_SetMinMaxRpm;
		else if(temp_SetMinMaxRpm = 0)
			oldtemp_SetMinMaxRpm = GVLinverter[GVLAddnumber].minmaxRpmvalue;
	}
	Numkeypad.hide();
	Numkeypad.invalidate();
}
void MainView::BackspaceButton()
{
	if(KeypadMode == KEYPAD_Velocity_RPM){
		if(GVL_Vel_input_iRpmvalue >= 10 || GVL_Vel_input_iRpmvalue <= -10)
			GVL_Vel_input_iRpmvalue = (GVL_Vel_input_iRpmvalue / 10);
		else
			GVL_Vel_input_iRpmvalue = 0;
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Vel_input_iRpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_RPM){
		if(GVL_Pos_input_iRpmvalue >= 10 || GVL_Pos_input_iRpmvalue <= -10)
			GVL_Pos_input_iRpmvalue = (GVL_Pos_input_iRpmvalue / 10);
		else
			GVL_Pos_input_iRpmvalue = 0;
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Pos_input_iRpmvalue);
	}
	else if(KeypadMode == KEYPAD_Position_POS){
		if(GVL_Pos_input_iPosvalue >= 10 || GVL_Pos_input_iPosvalue <= -10)
			GVL_Pos_input_iPosvalue = (GVL_Pos_input_iPosvalue / 10);
		else
			GVL_Pos_input_iPosvalue = 0;
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Pos_input_iPosvalue);
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
		if(GVL_Home_input_iPosvalue >= 10 || GVL_Home_input_iPosvalue <= -10)
			GVL_Home_input_iPosvalue = (GVL_Home_input_iPosvalue / 10);
		else
			GVL_Home_input_iPosvalue = 0;
		Unicode :: snprintf(KeypadinputvalueBuffer,KEYPADINPUTVALUE_SIZE, "%d", GVL_Home_input_iPosvalue);
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
	Keypadinputvalue.invalidate();
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
}
//Velocity Mode Set RPM ENT Button
void MainView::VelSettingRpmButton()
{
	if(GVLinverter[GVLAddnumber].iMode == 2){
		GVLVelRpmset = true;
		GVLWriteon = true;
	}
}
//Position Mode Set RPM ENT Button
void MainView::PosRpmSettingButton()
{
	if(GVLinverter[GVLAddnumber].iMode == 1){
		GVLPosRpmset = true;
		GVLWriteon = true;
	}
}
//Position Mode Set Pos ENT Button
void MainView::PosPosSettingButton()
{
	if(GVLinverter[GVLAddnumber].iMode == 1){
		GVLPosposset = true;
		GVLWriteon = true;
	}
}
//Home Mode Set Pos ENT Button
void MainView::HomeSettingPosButton()
{
	if(GVLinverter[GVLAddnumber].iMode == 6){
		GVLHomeposset = true;
		GVLWriteon = true;
	}
}
void MainView::Resetbutton()
{
	GVL_fault_reset = 128;
}
void MainView::EableButtonOn()
{
	/*if(GVLinverter[GVLAddnumber].iMode == 1 || GVLinverter[GVLAddnumber].iMode == 2 || GVLinverter[GVLAddnumber].iMode == 6){
		if(GVLStatecontrolword[GVLAddnumber].switch_on == true && GVLStatecontrolword[GVLAddnumber].enable_voltage == true && GVLStatecontrolword[GVLAddnumber].no_quick_stop == true)
			GVLinverterenable = false;
		else
			GVLinverterenable = true;
		GVLsendControlword = true;
		GVLWriteon = true;
	}*/
	if(GVLStatusword.ready_to_switch_on == false && GVLStatusword.switched_on == false && GVLStatusword.switch_on_disabled == true )
	{
		GVL_switch_on = 1;
		GVL_enable_voltage = 2;
		GVL_no_quick_stop = 4;
	}
	else
	{
		GVL_switch_on = 0;
		GVL_enable_voltage = 0;
		GVL_no_quick_stop = 0;
	}

}
void MainView::ModeButtonOn()
{
	/*if(GVLiMode == Velocity)
		GVL_iModevalue = 2;
	else if(GVLiMode == Position)
		GVL_iModevalue = 1;		//
	else if(GVLiMode == Home)
		GVL_iModevalue = 6;
	GVLsendMode = true;
	GVLWriteon = true;*/
	if(GVLiMode == Position && GVLinverter[GVLAddnumber].iMode == Cycl_Sync_Pos && GVL_iModevalue == Position)
		GVL_iModevalue = Nomode;
	else if(GVLiMode == Home && GVLinverter[GVLAddnumber].iMode == Cycl_Sync_Pos && GVL_iModevalue == Home)
		GVL_iModevalue = Nomode;
	else if(GVLiMode == Position)
		GVL_iModevalue = Position;	//co01 modes of operation 1: profile position mode
	else if(GVLiMode == Home)
		GVL_iModevalue = Home;		//co01 modes of operation 2:velocity mode
}
void MainView::PositionScreenButton()
{
	GVLiMode = Position;
	GVL_iModevalue = Position;
}
void MainView::HomingScreenButton()
{
	GVLiMode = Home;
	GVL_iModevalue = Home;
}
void MainView::PositionStartButton()
{
	if(GVLinverter[GVLAddnumber].iMode == 1){
		GVL_op_mode_spec_four = 16;
		GVL_op_mode_spec_five = 32;
	}
}
void MainView::PositionStopButton()
{
	if(GVLinverter[GVLAddnumber].iMode == 1)
		GVL_halt = 256;
}
void MainView::HomeSetbutton()
{
	if(GVLinverter[GVLAddnumber].iMode == 6)
		GVL_op_mode_spec_four = 16;
}
void MainView::SettingSaveButton()
{
	if(oldtemp_SetMaxPos != 0)
	{
		GVLFlash_TempSaveMaxPos = *(int*)&oldtemp_SetMaxPos;
		GVLFlash_Write = true;
	}
	if(oldtemp_SetMinPos != 0)
	{
		GVLFlash_TempSaveMinPos = *(int*)&oldtemp_SetMinPos;
		GVLFlash_Write = true;
	}

	if(oldtemp_SetGearDen != 0)
	{
		//GVLinverter[GVLAddnumber].iGearDenominator = temp_SetGearDen;
		GVLFlash_TempSaveDen = *(uint32_t*)&oldtemp_SetGearDen;
		GVLFlash_Write = true;
	}

	if(oldtemp_SetGearNum != 0)
	{
		//GVLinverter[GVLAddnumber].iGearNumerator = temp_SetGearNum;
		GVLFlash_TempSaveNum = *(uint32_t*)&oldtemp_SetGearNum;
		GVLFlash_Write = true;
	}

	if(oldtemp_SetDiameter != 0)
	{
		GVLFlash_TempSaveDiameter = *(uint32_t*)&oldtemp_SetDiameter;
		GVLFlash_Write = true;
	}

	if(oldtemp_SetMinMaxRpm != 0)
	{
		GVLFlash_TempSaveMinMaxRpm = *(uint32_t*)&oldtemp_SetMinMaxRpm;
		GVLFlash_Write = true;
	}
}
void MainView::MC_ON_Button()
{
	if(GVLMCinputstate == false && GVLMCoutputstate == false)
	{
		GVLMCinput = true;
		GVLMCoutput = true;
	}
	else
	{
		GVLMCinput = false;
		GVLMCoutput = false;
	}
}
void MainView::Vel_SettingCWButton()
{
	GVLVel_RPM_direction = false;
}
void MainView::Vel_SettingCCWButton()
{
	GVLVel_RPM_direction = true;
}
void MainView::ServconnectionButton()
{
	GVLTCP_connection = 0;
}
void MainView::handleTickEvent()
{
	if(GVLinverter[GVLAddnumber].iMode == 1)
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
	else if(GVLinverter[GVLAddnumber].iMode == 6)
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
	if(GVLLocal)
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

	//CAN ReadyState ->STO, Voltage
	Unicode :: snprintf(textReadyStateValueBuffer,TEXTREADYSTATEVALUE_SIZE,GVLinverter[GVLAddnumber].cReadystate);
	textReadyStateValue.invalidate();

	Unicode :: snprintf(textErrorValueBuffer,TEXTERRORVALUE_SIZE,GVLinverter[GVLAddnumber].cError);
	textErrorValue.invalidate();


	Unicode :: snprintf(textMODEStateBuffer,TEXTMODESTATE_SIZE, GVLinverter[GVLAddnumber].cMode);
	textMODEState.invalidate();

	//Position mode Set Rpm value
	//Unicode :: snprintf(textPosSetRpmValueBuffer,TEXTPOSSETRPMVALUE_SIZE, "%d", GVLinverter[GVLAddnumber].PossetRpmvalue);
	Unicode :: snprintfFloat(textPosSetRpmValueBuffer,TEXTPOSSETRPMVALUE_SIZE, "%.f%", float(GVLinverter[GVLAddnumber].PossetRpmvalue) / GVLinverter[GVLAddnumber].minmaxRpmvalue * 100);
	textPosSetRpmValue.invalidate();

	//Position mode Actual Rpm value
	//Unicode :: snprintf(textPosActRpmValueBuffer,TEXTPOSACTRPMVALUE_SIZE, "%d", GVLinverter[GVLAddnumber].actRpmvalue);
	Unicode :: snprintfFloat(textPosActRpmValueBuffer,TEXTPOSACTRPMVALUE_SIZE, "%.f%", float(GVLinverter[GVLAddnumber].actRpmvalue) / GVLinverter[GVLAddnumber].minmaxRpmvalue * 100);
	textPosActRpmValue.invalidate();

	//Position mode Target Rpm value

	Unicode :: snprintf(textPosActPosValueBuffer, TEXTPOSACTPOSVALUE_SIZE, "%d", GVLinverter[GVLAddnumber].PosActPosvalue);
	textPosActPosValue.invalidate();

	Unicode :: snprintf(textPosSetPosValueBuffer,TEXTPOSSETPOSVALUE_SIZE, "%d", GVLinverter[GVLAddnumber].PosSetPosvalue);
	textPosSetPosValue.invalidate();

	//Home mode Set Pos value
	Unicode :: snprintf(textHomeSetPosvalueBuffer, TEXTHOMESETPOSVALUE_SIZE, "%d", GVLinverter[GVLAddnumber].HomeSetPosvalue);
	textHomeSetPosvalue.invalidate();

	//Home mode Actual Pos value
	Unicode :: snprintf(textHomeActPosvalueBuffer, TEXTHOMEACTPOSVALUE_SIZE, "%d", GVLinverter[GVLAddnumber].PosActPosvalue);
	textHomeActPosvalue.invalidate();

	//IP
	Unicode::snprintf(textIP0Buffer, TEXTIP0_SIZE, "%d", GVL_IP[0]);
	textIP0.invalidate();
	Unicode::snprintf(textIP1Buffer, TEXTIP1_SIZE, "%d", GVL_IP[1]);
	textIP1.invalidate();
	Unicode::snprintf(textIP2Buffer, TEXTIP2_SIZE, "%d", GVL_IP[2]);
	textIP2.invalidate();
	Unicode::snprintf(textIP3Buffer, TEXTIP3_SIZE, "%d", GVL_IP[3]);
	textIP3.invalidate();

	if(GVLMCinputstate == true && GVLMCoutputstate == true){
		MC_OnBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
		MC_OnBox.invalidate();
	}
	else{
		MC_OnBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		MC_OnBox.invalidate();
	}

	if(GVLStatusword.ready_to_switch_on == true && GVLStatusword.switched_on ==  true && GVLStatusword.switch_on_disabled == false)
	{
		EnableBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
		EnableBox.invalidate();
	}
	else
	{
		EnableBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		EnableBox.invalidate();
	}

	if(GVLStatusword.operation_enabled == true)
	{
		GVLPowerstate = true;
		PowerONBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
		PowerONBox.invalidate();
		PowerOFFBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		PowerOFFBox.invalidate();
	}
	else
	{
		GVLPowerstate = false;
		PowerOFFBox.setColor(touchgfx::Color::getColorFromRGB(41, 119, 255));
		PowerOFFBox.invalidate();
		PowerONBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		PowerONBox.invalidate();
	}

	if(GVLComstate == 8)
	{
		GVLPoweroff = true;
		GVLPoweron = false;
		GVLinverterenable = false;
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
}
