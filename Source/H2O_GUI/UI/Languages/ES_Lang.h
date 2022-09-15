//
// Created by Victor on 26/07/2022.
//

#ifndef H2O_GUI_ES_LANG_H
#define H2O_GUI_ES_LANG_H

#include "Languages.h"

// TODO translate to Spanish

// Utils
const char ES_LANG_STR[] PROGMEM = "Espanol";
const char ES_YES_STR[] PROGMEM = "YES";
const char ES_NO_STR[] PROGMEM = "NO";
const char ES_ON_STR[] PROGMEM = "ON";
const char ES_OFF_STR[] PROGMEM = "OFF";
const char ES_Previous_STR[] PROGMEM = "Anterior";
const char ES_Next_STR[] PROGMEM = "Siguiente";
const char ES_Delete_STR[] PROGMEM = "Delete";
const char ES_OK_STR[] PROGMEM = "OK";

// Status
const char ES_Status_Title_STR[] PROGMEM = "Status";
const char ES_StatusBtn_Error_STR[] PROGMEM = "FAILURE";
const char ES_MenuBtn_STR[] PROGMEM = "Menu";

// Menu
const char ES_Menu_Title_STR[] PROGMEM = "Menu";
const char ES_HelpBtn_STR[] PROGMEM = "Help";
const char ES_EngineeringBtn_STR[] PROGMEM = "Engineering Mode";
const char ES_SettingsBtn_STR[] PROGMEM = "Settings";
const char ES_ExtraFunctionsBtn[] PROGMEM = "Extra Functions";

// ExtraFunctions
const char ES_ExtraFunctions_Title_STR[] PROGMEM = "Extra Functions";
const char ES_ExtraFunctions_InstallWizard_STR[] PROGMEM = "Install Wizard";
const char ES_ExtraFunctions_StartInstallWizard_STR[] PROGMEM = "Start";
const char ES_ExtraFunctions_ACPSU_STR[] PROGMEM = "AC Power Supply";
const char ES_ExtraFunctions_DCPSU_STR[] PROGMEM = "DC Power Supply";

// Settings
const char ES_Settings_Title_STR[] PROGMEM = "Settings";
const char ES_Settings_ElectricityBtn_STR[] PROGMEM = "Electricity";
const char ES_Settings_WaterBtn_STR[] PROGMEM = "Water";
const char ES_Settings_TemperatureBtn_STR[] PROGMEM = "Temperature";
const char ES_Settings_InterfaceBtn_STR[] PROGMEM = "Interface";

// Water
const char ES_Water_Title_STR[] PROGMEM = "Water";
const char ES_Water_WellPumpMaxTimeON_STR[] PROGMEM = "Well Pump max time ON";
const char ES_Water_UVPumpMaxTimeON_STR[] PROGMEM = "UV Pump max time ON";
const char ES_Water_EndPumpMaxTimeON_STR[] PROGMEM = "End Pump max time ON";
const char ES_Water_FilterMaxTimeON_STR[] PROGMEM = "Filter max time ON";
const char ES_Water_UVPumpFlow_STR[] PROGMEM = "UV Pump flow";

//Temperature
const char ES_Temp_Title_STR[] PROGMEM = "Temperature";
const char ES_Temp_RefreshInterval_STR[] PROGMEM = "Temp. Refresh Interval";
const char ES_Temp_SystemStopTemp_STR[] PROGMEM = "System Stop Temp.";
const char ES_Temp_PSUFanStartTemp_STR[] PROGMEM = "PSU Fan Start Temp.";
const char ES_Temp_PSUFanStopTemp_STR[] PROGMEM = "PSU Fan Stop Temp.";
const char ES_Temp_CaseFanStartTemp_STR[] PROGMEM = "Case Fan Start Temp.";
const char ES_Temp_CaseFanStopTemp_STR[] PROGMEM = "Case Fan Stop Temp.";

// Interface
const char ES_Interface_Title_STR[] PROGMEM = "Interface";
const char ES_Interface_RefreshInterval_STR[] PROGMEM = "Refresh Interval";
const char ES_Interface_LanguageTitle_STR[] PROGMEM = "Language";
const char ES_Interface_RotationTitle_STR[] PROGMEM = "Screen Rotation";
const char ES_Interface_RotationLandscape_STR[] PROGMEM = "Landscape";
const char ES_Interface_RotationInvertedLandscape_STR[] PROGMEM = "Inverted Landscape";
const char ES_Interface_CalibrationTitle_STR[] PROGMEM = "Screen Calibration";
const char ES_Interface_CalibrationStart_STR[] PROGMEM = "Calibrate";
const char ES_Interface_ResetTitle_STR[] PROGMEM = "Reset";
const char ES_Interface_ResetStart_STR[] PROGMEM = "Perform Reset";

// Electricity
const char ES_Electricity_Title_STR[] PROGMEM = "Electricity";
const char ES_Electricity_UVCurrent_STR[] PROGMEM = "UV light est. Current";
const char ES_Electricity_StartChargingVoltage_STR[] PROGMEM = "Start Charging Voltage";
const char ES_Electricity_StopChargingVoltage_STR[] PROGMEM = "Stop Charging Voltage";
const char ES_Electricity_StartWorkingVoltage_STR[] PROGMEM = "Start Working Voltage";
const char ES_Electricity_StopWorkingVoltage_STR[] PROGMEM = "Stop Working Voltage";
const char ES_Electricity_ACInverterFrequency_STR[] PROGMEM = "AC Inverter Frequency";
const char ES_Electricity_ACAmmeterSensitivity_STR[] PROGMEM = "AC Ammeter Sensitivity";
const char ES_Electricity_ACAmmeterZero_STR[] PROGMEM = "AC Ammeter Zero";
const char ES_Electricity_DCAmmeterSensitivity_STR[] PROGMEM = "DC Ammeter Sensitivity";
const char ES_Electricity_DCAmmeterZero_STR[] PROGMEM = "DC Ammeter Zero";

// Language
const char ES_Language_Title_STR[] PROGMEM = "Select a language";

// Error
const char ES_ScreenNotImplementedError_STR[] PROGMEM = "This option is not implemented yet";


const char *const langES[] PROGMEM = {ES_LANG_STR,ES_YES_STR,ES_NO_STR,ES_ON_STR, ES_OFF_STR, ES_Previous_STR, ES_Next_STR,ES_Delete_STR, ES_OK_STR, // Utils
                                      ES_Status_Title_STR, ES_StatusBtn_Error_STR, ES_MenuBtn_STR, // Status
                                      ES_Menu_Title_STR, ES_HelpBtn_STR, ES_EngineeringBtn_STR, ES_SettingsBtn_STR, ES_ExtraFunctionsBtn, // Menu
                                      ES_ExtraFunctions_Title_STR, ES_ExtraFunctions_InstallWizard_STR, ES_ExtraFunctions_StartInstallWizard_STR, ES_ExtraFunctions_ACPSU_STR, ES_ExtraFunctions_DCPSU_STR, // ExtraFunctions
                                      ES_Settings_Title_STR, ES_Settings_ElectricityBtn_STR, ES_Settings_WaterBtn_STR, ES_Settings_TemperatureBtn_STR, ES_Settings_InterfaceBtn_STR, // Settings
                                      ES_Water_Title_STR, ES_Water_WellPumpMaxTimeON_STR, ES_Water_UVPumpMaxTimeON_STR, ES_Water_EndPumpMaxTimeON_STR, ES_Water_FilterMaxTimeON_STR, ES_Water_UVPumpFlow_STR, // Water
                                      ES_Temp_Title_STR, ES_Temp_RefreshInterval_STR, ES_Temp_SystemStopTemp_STR, ES_Temp_PSUFanStartTemp_STR, ES_Temp_PSUFanStopTemp_STR, ES_Temp_CaseFanStartTemp_STR, ES_Temp_CaseFanStopTemp_STR, // Temperature
                                      ES_Interface_Title_STR, ES_Interface_RefreshInterval_STR, ES_Interface_LanguageTitle_STR, ES_Interface_RotationTitle_STR, ES_Interface_RotationLandscape_STR, ES_Interface_RotationInvertedLandscape_STR, ES_Interface_CalibrationTitle_STR, ES_Interface_CalibrationStart_STR, ES_Interface_ResetTitle_STR, ES_Interface_ResetStart_STR, // Interface
                                      ES_Electricity_Title_STR, ES_Electricity_UVCurrent_STR, ES_Electricity_StartChargingVoltage_STR, ES_Electricity_StopChargingVoltage_STR, ES_Electricity_StartWorkingVoltage_STR, ES_Electricity_StopWorkingVoltage_STR, ES_Electricity_ACInverterFrequency_STR, ES_Electricity_ACAmmeterSensitivity_STR, ES_Electricity_ACAmmeterZero_STR, ES_Electricity_DCAmmeterSensitivity_STR, ES_Electricity_DCAmmeterZero_STR, // Electricity
                                      ES_Language_Title_STR, // Language
                                      ES_ScreenNotImplementedError_STR // Error

}; // Follow the same order as enum StringIDs (Languages.h)


// const char ES_XXX_PATH[] PROGMEM = "xxxx";

const char ES_HelpTopic1_PATH[] PROGMEM = "/ES/Help/Topic1.txt";
const char ES_HelpTopic2_PATH[] PROGMEM = "/ES/Help/Topic2.txt";
const char ES_HelpTopic3_PATH[] PROGMEM = "/ES/Help/Topic3.txt";
const char ES_HelpTopic4_PATH[] PROGMEM = "/ES/Help/Topic4.txt";
const char ES_HelpTopic5_PATH[] PROGMEM = "/ES/Help/Topic5.txt";
const char ES_HelpTopic6_PATH[] PROGMEM = "/ES/Help/Topic6.txt";

const char ES_ResetPopUp_PATH[] PROGMEM = "/ES/Reset/PopUp.txt";

const char *const pathES[] PROGMEM = { ES_HelpTopic1_PATH,ES_HelpTopic2_PATH,ES_HelpTopic3_PATH,ES_HelpTopic4_PATH,ES_HelpTopic5_PATH,ES_HelpTopic6_PATH,ES_ResetPopUp_PATH}; // Follow the same order as enum PathIDs (Languages.h)

#endif //H2O_GUI_ES_LANG_H
