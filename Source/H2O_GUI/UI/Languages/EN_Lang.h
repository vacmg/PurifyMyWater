//
// Created by Victor on 26/07/2022.
//

#ifndef H2O_GUI_EN_LANG_H
#define H2O_GUI_EN_LANG_H

#include "Languages.h"

// Utils
const char EN_LANG_STR[] PROGMEM = "English";
const char EN_YES_STR[] PROGMEM = "YES";
const char EN_NO_STR[] PROGMEM = "NO";
const char EN_ON_STR[] PROGMEM = "ON";
const char EN_OFF_STR[] PROGMEM = "OFF";
const char EN_Previous_STR[] PROGMEM = "Previous";
const char EN_Next_STR[] PROGMEM = "Next";
const char EN_Delete_STR[] PROGMEM = "Delete";
const char EN_OK_STR[] PROGMEM = "OK";

// Status
const char EN_Status_Title_STR[] PROGMEM = "Status";
const char EN_StatusBtn_Error_STR[] PROGMEM = "FAILURE";
const char EN_MenuBtn_STR[] PROGMEM = "Menu";

// Menu
const char EN_Menu_Title_STR[] PROGMEM = "Menu";
const char EN_HelpBtn_STR[] PROGMEM = "Help";
const char EN_EngineeringBtn_STR[] PROGMEM = "Engineering Mode";
const char EN_SettingsBtn_STR[] PROGMEM = "Settings";
const char EN_ExtraFunctionsBtn[] PROGMEM = "Extra Functions";

// ExtraFunctions
const char EN_ExtraFunctions_Title_STR[] PROGMEM = "Extra Functions";
const char EN_ExtraFunctions_InstallWizard_STR[] PROGMEM = "Install Wizard";
const char EN_ExtraFunctions_StartInstallWizard_STR[] PROGMEM = "Start";
const char EN_ExtraFunctions_ACPSU_STR[] PROGMEM = "AC Power Supply";
const char EN_ExtraFunctions_DCPSU_STR[] PROGMEM = "DC Power Supply";

// Settings
const char EN_Settings_Title_STR[] PROGMEM = "Settings";
const char EN_Settings_ElectricityBtn_STR[] PROGMEM = "Electricity";
const char EN_Settings_WaterBtn_STR[] PROGMEM = "Water";
const char EN_Settings_TemperatureBtn_STR[] PROGMEM = "Temperature";
const char EN_Settings_InterfaceBtn_STR[] PROGMEM = "Interface";

// Water
const char EN_Water_Title_STR[] PROGMEM = "Water";
const char EN_Water_WellPumpMaxTimeON_STR[] PROGMEM = "Well Pump max time ON";
const char EN_Water_UVPumpMaxTimeON_STR[] PROGMEM = "UV Pump max time ON";
const char EN_Water_EndPumpMaxTimeON_STR[] PROGMEM = "End Pump max time ON";
const char EN_Water_FilterMaxTimeON_STR[] PROGMEM = "Filter max time ON";
const char EN_Water_UVPumpFlow_STR[] PROGMEM = "UV Pump flow";

//Temperature
const char EN_Temp_Title_STR[] PROGMEM = "Temperature";
const char EN_Temp_RefreshInterval_STR[] PROGMEM = "Temp. Refresh Interval";
const char EN_Temp_SystemStopTemp_STR[] PROGMEM = "System Stop Temp.";
const char EN_Temp_PSUFanStartTemp_STR[] PROGMEM = "PSU Fan Start Temp.";
const char EN_Temp_PSUFanStopTemp_STR[] PROGMEM = "PSU Fan Stop Temp.";
const char EN_Temp_CaseFanStartTemp_STR[] PROGMEM = "Case Fan Start Temp.";
const char EN_Temp_CaseFanStopTemp_STR[] PROGMEM = "Case Fan Stop Temp.";

// Interface
const char EN_Interface_Title_STR[] PROGMEM = "Interface";
const char EN_Interface_RefreshInterval_STR[] PROGMEM = "Refresh Interval";
const char EN_Interface_LanguageTitle_STR[] PROGMEM = "Language";
const char EN_Interface_RotationTitle_STR[] PROGMEM = "Screen Rotation";
const char EN_Interface_RotationLandscape_STR[] PROGMEM = "Landscape";
const char EN_Interface_RotationInvertedLandscape_STR[] PROGMEM = "Inverted Landscape";
const char EN_Interface_CalibrationTitle_STR[] PROGMEM = "Screen Calibration";
const char EN_Interface_CalibrationStart_STR[] PROGMEM = "Calibrate";
const char EN_Interface_ResetTitle_STR[] PROGMEM = "Reset";
const char EN_Interface_ResetStart_STR[] PROGMEM = "Perform Reset";

// Electricity
const char EN_Electricity_Title_STR[] PROGMEM = "Electricity";
const char EN_Electricity_UVCurrent_STR[] PROGMEM = "UV light est. Current";
const char EN_Electricity_StartChargingVoltage_STR[] PROGMEM = "Start Charging Voltage";
const char EN_Electricity_StopChargingVoltage_STR[] PROGMEM = "Stop Charging Voltage";
const char EN_Electricity_StartWorkingVoltage_STR[] PROGMEM = "Start Working Voltage";
const char EN_Electricity_StopWorkingVoltage_STR[] PROGMEM = "Stop Working Voltage";
const char EN_Electricity_ACInverterFrequency_STR[] PROGMEM = "AC Inverter Frequency";
const char EN_Electricity_ACAmmeterSensitivity_STR[] PROGMEM = "AC Ammeter Sensitivity";
const char EN_Electricity_ACAmmeterZero_STR[] PROGMEM = "AC Ammeter Zero";
const char EN_Electricity_DCAmmeterSensitivity_STR[] PROGMEM = "DC Ammeter Sensitivity";
const char EN_Electricity_DCAmmeterZero_STR[] PROGMEM = "DC Ammeter Zero";

// Language
const char EN_Language_Title_STR[] PROGMEM = "Select a language";



const char *const langEN[] PROGMEM = {EN_LANG_STR, EN_YES_STR,EN_NO_STR,EN_ON_STR, EN_OFF_STR, EN_Previous_STR, EN_Next_STR,EN_Delete_STR, EN_OK_STR, // Utils
                                      EN_Status_Title_STR, EN_StatusBtn_Error_STR, EN_MenuBtn_STR, // Status
                                      EN_Menu_Title_STR, EN_HelpBtn_STR, EN_EngineeringBtn_STR, EN_SettingsBtn_STR, EN_ExtraFunctionsBtn, // Menu
                                      EN_ExtraFunctions_Title_STR, EN_ExtraFunctions_InstallWizard_STR, EN_ExtraFunctions_StartInstallWizard_STR, EN_ExtraFunctions_ACPSU_STR, EN_ExtraFunctions_DCPSU_STR, // ExtraFunctions
                                      EN_Settings_Title_STR, EN_Settings_ElectricityBtn_STR, EN_Settings_WaterBtn_STR, EN_Settings_TemperatureBtn_STR, EN_Settings_InterfaceBtn_STR, // Settings
                                      EN_Water_Title_STR, EN_Water_WellPumpMaxTimeON_STR, EN_Water_UVPumpMaxTimeON_STR, EN_Water_EndPumpMaxTimeON_STR, EN_Water_FilterMaxTimeON_STR, EN_Water_UVPumpFlow_STR, // Water
                                      EN_Temp_Title_STR, EN_Temp_RefreshInterval_STR, EN_Temp_SystemStopTemp_STR, EN_Temp_PSUFanStartTemp_STR, EN_Temp_PSUFanStopTemp_STR, EN_Temp_CaseFanStartTemp_STR, EN_Temp_CaseFanStopTemp_STR, // Temperature
                                      EN_Interface_Title_STR, EN_Interface_RefreshInterval_STR, EN_Interface_LanguageTitle_STR, EN_Interface_RotationTitle_STR, EN_Interface_RotationLandscape_STR, EN_Interface_RotationInvertedLandscape_STR, EN_Interface_CalibrationTitle_STR, EN_Interface_CalibrationStart_STR, EN_Interface_ResetTitle_STR, EN_Interface_ResetStart_STR, // Interface
                                      EN_Electricity_Title_STR, EN_Electricity_UVCurrent_STR, EN_Electricity_StartChargingVoltage_STR, EN_Electricity_StopChargingVoltage_STR, EN_Electricity_StartWorkingVoltage_STR, EN_Electricity_StopWorkingVoltage_STR, EN_Electricity_ACInverterFrequency_STR, EN_Electricity_ACAmmeterSensitivity_STR, EN_Electricity_ACAmmeterZero_STR, EN_Electricity_DCAmmeterSensitivity_STR, EN_Electricity_DCAmmeterZero_STR, // Electricity
                                      EN_Language_Title_STR // Language

}; // Follow the same order as enum StringIDs (Languages.h)

#endif //H2O_GUI_EN_LANG_H
