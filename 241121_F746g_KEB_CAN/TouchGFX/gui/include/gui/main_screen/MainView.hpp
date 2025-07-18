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
    virtual void Resetbutton();
    virtual void EableButtonOn();
    virtual void ModeButtonOn();
    virtual void PositionScreenButton();
    virtual void PositionStartButton();
    virtual void PositionStopButton();
    virtual void Posrpmpadshow();
    virtual void Pospospadshow();
    virtual void SettingMinposShow();
    virtual void SettingMaxposShow();
    virtual void SettingGearNumShow();
    virtual void SettingGearDenShow();
    virtual void SettingShowButton();
    virtual void SettingSaveButton();
    virtual void MC_ON_Button();
    virtual void HomingScreenButton();
    virtual void HomePospadshow();
	virtual void HomeSetbutton();
	virtual void ServconnectionButton();
	virtual void SettingHideButton();
	virtual void SettingDiameterShow();
	virtual void SettingRpmShow();
	virtual void SettingWireSetPadShow();
	//Setting
	virtual void SetType_D_Button();
	virtual void SetType_D_ENC_Button();
	virtual void SetType_INV_ENC_Button();
	virtual void YoYoSelected();
	virtual void YoYoDeselected();
	virtual void SettingEncPulseSetPadShow();

	//Direct
	virtual void DirectMoveUpButton();
	virtual void DirectMoveDownButton();
	virtual void DirectMoveStopButton();

	virtual void DirectHomeSetbutton();
	virtual void DirectPosUpSetPadShowButton();
	virtual void DirectPosDownSetPadShowButton();
	virtual void DirectHomeSetPadShow();




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
		KEYPAD_Setting_MinMaxVel = 10,
		KEYPAD_Direct_Up_POS = 11,
    	KEYPAD_Direct_Down_POS = 12,
		KEYPAD_Direct_Home_POS = 13,
		KEYPAD_Wire = 14,
		KEYPAD_Enc_Pulse
    }NumpadModeTypedef;

    uint8_t u8Screenpage; // 1 : Position 2: Home

    int KeypadMode;

    bool dot_state;
    int dot_value;

    //Setting Rpm Keypad
    int32_t temp_SetMinMaxRpm;
    int oldtemp_SetMinMaxRpm;

    //Setting Pos Keypad
    int32_t temp_SetMaxPos;
    int32_t temp_SetMinPos;

    int oldtemp_SetMaxPos;
    int oldtemp_SetMinPos;

    //Setting Gear Keypad
    float temp_SetGearNum;
    float temp_SetGearDen;

    float oldtemp_SetGearNum;
    float oldtemp_SetGearDen;

    //Setting Type
    int temp_SetType;
    int oldtemp_SetType;

    //Setting Diameter Keypad
    float temp_SetDiameter;
    float oldtemp_SetDiameter;

    //Setting Wire
    float temp_SetWire;
	float oldtemp_SetWire;

	//Setting YoYo
	bool temp_SetYoYo;

	//Setting Encoder Pulse
	int32_t temp_SetEncPulse;
	int oldtemp_SetEncPulse;


    int SettingPosmaxHigh = 99999;
    int SettingPosmaxLow = -99998;

    int SettingPosminHigh = SettingPosmaxHigh - 1;
    int SettingPosminLow = SettingPosmaxLow - 1;

    int SettingPosRpmMinMax = 10000;
};

#endif // MAINVIEW_HPP
