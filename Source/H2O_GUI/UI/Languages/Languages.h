//
// Created by Victor on 24/07/2022.
//

#ifndef H2O_GUI_LANGUAGES_H
#define H2O_GUI_LANGUAGES_H

#include "../UI.h"

enum StringIDs{Lang_STR = 0, YES_STR, NO_STR, ON_STR, OFF_STR, Previous_STR, Next_STR, Delete_STR, OK_STR, // Utils
    Status_Title_STR, StatusBtn_Error_STR, MenuBtn_STR, // Status
    Menu_Title_STR, HelpBtn_STR, EngineeringBtn_STR, SettingsBtn_STR, ExtraFunctionsBtn, // Menu
    ExtraFunctions_Title_STR, ExtraFunctions_InstallWizard_STR, ExtraFunctions_StartInstallWizard_STR, ExtraFunctions_ACPSU_STR, ExtraFunctions_DCPSU_STR, // ExtraFunctions
    Settings_Title_STR, Settings_ElectricityBtn_STR, Settings_WaterBtn_STR, Settings_TemperatureBtn_STR, Settings_InterfaceBtn_STR, // Settings
    Water_Title_STR, Water_WellPumpMaxTimeON_STR, Water_UVPumpMaxTimeON_STR, Water_EndPumpMaxTimeON_STR, Water_FilterMaxTimeON_STR, Water_UVPumpFlow_STR, // Water
    Temp_Title_STR, Temp_RefreshInterval_STR, Temp_SystemStopTemp_STR, Temp_PSUFanStartTemp_STR, Temp_PSUFanStopTemp_STR, Temp_CaseFanStartTemp_STR, Temp_CaseFanStopTemp_STR, // Temperature
    Interface_Title_STR, Interface_RefreshInterval_STR, Interface_LanguageTitle_STR, Interface_RotationTitle_STR, Interface_RotationLandscape_STR, Interface_RotationInvertedLandscape_STR, Interface_CalibrationTitle_STR, Interface_CalibrationStart_STR, Interface_ResetTitle_STR, Interface_ResetStart_STR, // Interface
    Electricity_Title_STR, Electricity_UVCurrent_STR, Electricity_StartChargingVoltage_STR, Electricity_StopChargingVoltage_STR, Electricity_StartWorkingVoltage_STR, Electricity_StopWorkingVoltage_STR, Electricity_ACInverterFrequency_STR, Electricity_ACAmmeterSensitivity_STR, Electricity_ACAmmeterZero_STR, Electricity_DCAmmeterSensitivity_STR, Electricity_DCAmmeterZero_STR, // Electricity
    Language_Title_STR, // Language
    ScreenNotImplementedError_STR, UpRangeValue_STR,LowRangeValue_STR // Error
};

#include "EN_Lang.h"
#include "ES_Lang.h"
#include "FR_Lang.h"

const char* const* const langs[] PROGMEM = {langEN, langES, langFR}; // Follow the same order as enum Languages (UI.h)

char languageBuff[50] = ""; // Max size of any language string

// Returns the string identified by the id in the language selected by enum Languages LANGUAGE variable
char* getString(enum StringIDs stringId);

// Returns the string identified by the id in the language selected by the specified language
char* getString(enum StringIDs stringId, Languages language);

enum PathIDs{ResetPopup_PATH, UpRange_PATH, LowRange_PATH};

const char* const* const paths[] PROGMEM = {pathEN, pathES, pathFR}; // Follow the same order as enum Languages (UI.h)

// Returns the path to a localized file identified by the id in the language selected by enum Languages LANGUAGE variable
char* getPath(enum PathIDs pathID);

// Returns the path to a localized file identified by the id in the language selected by the specified language
char* getPath(enum PathIDs pathID, Languages language);

#include "Languages.cpp"

#endif //H2O_GUI_LANGUAGES_H
