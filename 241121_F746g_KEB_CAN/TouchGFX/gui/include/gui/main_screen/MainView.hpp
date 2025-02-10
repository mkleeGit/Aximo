#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include "global.h"

class MainView : public MainViewBase
{
public:
    MainView();
    virtual ~MainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void List1ButtonOn();
    virtual void List2ButtonOn();
    virtual void List3ButtonOn();
    virtual void List4ButtonOn();
    virtual void List5ButtonOn();
    virtual void List6ButtonOn();
    virtual void PowerButtonON();
    virtual void PowerButtonOFF();
    virtual void ComButtonONOFF();
    virtual void Velrpmpadshow();
    virtual void Keypadhide();
    virtual void Num1Button();
    virtual void Num2Button();
    virtual void Num3Button();
    virtual void Num4Button();
    virtual void Num5Button();
    virtual void Num6Button();
    virtual void Num7Button();
    virtual void Num8Button();
    virtual void Num9Button();
    virtual void Num0Button();
    virtual void NumdotButton();
    virtual void MinusButton();
    virtual void EntButton();
    virtual void BackspaceButton();
    virtual void VelSettingRpmButton();
    virtual void Resetbutton();
    virtual void EableButtonOn();
    virtual void ModeButtonOn();
    virtual void PositionScreenButton();
    virtual void PositionStartButton();
    virtual void PositionStopButton();
    virtual void Posrpmpadshow();
    virtual void PosRpmSettingButton();
    virtual void Pospospadshow();
    virtual void PosPosSettingButton();
    virtual void SettingMinposShow();
    virtual void SettingMaxposShow();
    virtual void SettingGearNumShow();
    virtual void SettingGearDenShow();
    virtual void SetttingShowButton();
    virtual void SettingSaveButton();
    virtual void MC_ON_Button();
    virtual void Vel_SettingCWButton();
    virtual void Vel_SettingCCWButton();
    virtual void HomingScreenButton();
    virtual void HomePospadshow();
	virtual void HomeSettingPosButton();
	virtual void HomeSetbutton();
	virtual void ServconnectionButton();
	virtual void SettingHideButton();
	virtual void SettingDiameterShow();
	virtual void SettingRpmShow();
    virtual void handleTickEvent();
protected:
    typedef enum NumpadModeTypedef{
    	KEYPAD_Velocity_RPM = 1,
    	KEYPAD_Position_RPM = 2,
    	KEYPAD_Position_POS = 3,
		KEYPAD_Setting_Minpos = 4,
		KEYPAD_Setting_Maxpos = 5,
		KEYPAD_Setting_GearNum = 6,
		KEYPAD_Setting_GearDen = 7,
		KEYPAD_Home_POS = 8,
		KEYPAD_Setting_Diameter = 9,
		KEYPAD_Setting_MinMaxVel
    }NumpadModeTypedef;

    int KeypadMode;

    bool dot_state;
    int dot_value;

    //Setting Rpm Keypad
    int temp_SetMinMaxRpm;
    int oldtemp_SetMinMaxRpm;

    //Setting Pos Keypad
    int temp_SetMaxPos;
    int temp_SetMinPos;

    int oldtemp_SetMaxPos;
    int oldtemp_SetMinPos;

    //Setting Gear Keypad
    float temp_SetGearNum;
    float temp_SetGearDen;

    float oldtemp_SetGearNum;
    float oldtemp_SetGearDen;

    //Setting Diameter Keypad
    float temp_SetDiameter;

    float oldtemp_SetDiameter;

    int SettingPosmaxHigh = 99999;
    int SettingPosmaxLow = -99998;

    int SettingPosminHigh = SettingPosmaxHigh - 1;
    int SettingPosminLow = SettingPosmaxLow - 1;

    int SettingPosRpmMinMax = 10000;
};

#endif // MAINVIEW_HPP
