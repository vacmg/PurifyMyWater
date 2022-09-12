//
// Created by Victor on 26/07/2022.
//

#ifndef H2O_GUI_FR_LANG_H
#define H2O_GUI_FR_LANG_H

#include "Languages.h"

// TODO translate to French

// Utils
const char FR_LANG_STR[] PROGMEM = "Francais";
const char FR_YES_STR[] PROGMEM = "YES";
const char FR_NO_STR[] PROGMEM = "NO";
const char FR_ON_STR[] PROGMEM = "ON";
const char FR_OFF_STR[] PROGMEM = "OFF";
const char FR_Previous_STR[] PROGMEM = "Previous";
const char FR_Next_STR[] PROGMEM = "Next";
const char FR_Delete_STR[] PROGMEM = "Delete";
const char FR_OK_STR[] PROGMEM = "OK";

// Status
const char FR_Status_Title_STR[] PROGMEM = "Status";
const char FR_StatusBtn_Error_STR[] PROGMEM = "FAILURE";
const char FR_MenuBtn_STR[] PROGMEM = "Menu";

// Menu
const char FR_Menu_Title_STR[] PROGMEM = "Menu";
const char FR_HelpBtn_STR[] PROGMEM = "Help";
const char FR_EngineeringBtn_STR[] PROGMEM = "Engineering Mode";
const char FR_SettingsBtn_STR[] PROGMEM = "Settings";
const char FR_ExtraFunctionsBtn[] PROGMEM = "Extra Functions";

// ExtraFunctions
const char FR_ExtraFunctions_Title_STR[] PROGMEM = "Extra Functions";
const char FR_ExtraFunctions_InstallWizard_STR[] PROGMEM = "Install Wizard";
const char FR_ExtraFunctions_StartInstallWizard_STR[] PROGMEM = "Start";
const char FR_ExtraFunctions_ACPSU_STR[] PROGMEM = "AC Power Supply";
const char FR_ExtraFunctions_DCPSU_STR[] PROGMEM = "DC Power Supply";

// Settings
const char FR_Settings_Title_STR[] PROGMEM = "Settings";
const char FR_Settings_ElectricityBtn_STR[] PROGMEM = "Electricity";
const char FR_Settings_WaterBtn_STR[] PROGMEM = "Water";
const char FR_Settings_TemperatureBtn_STR[] PROGMEM = "Temperature";
const char FR_Settings_InterfaceBtn_STR[] PROGMEM = "Interface";

// Water
const char FR_Water_Title_STR[] PROGMEM = "Water";
const char FR_Water_WellPumpMaxTimeON_STR[] PROGMEM = "Well Pump max time ON";
const char FR_Water_UVPumpMaxTimeON_STR[] PROGMEM = "UV Pump max time ON";
const char FR_Water_EndPumpMaxTimeON_STR[] PROGMEM = "End Pump max time ON";
const char FR_Water_FilterMaxTimeON_STR[] PROGMEM = "Filter max time ON";
const char FR_Water_UVPumpFlow_STR[] PROGMEM = "UV Pump flow";

//Temperature
const char FR_Temp_Title_STR[] PROGMEM = "Temperature";
const char FR_Temp_RefreshInterval_STR[] PROGMEM = "Temp. Refresh Interval";
const char FR_Temp_SystemStopTemp_STR[] PROGMEM = "System Stop Temp.";
const char FR_Temp_PSUFanStartTemp_STR[] PROGMEM = "PSU Fan Start Temp.";
const char FR_Temp_PSUFanStopTemp_STR[] PROGMEM = "PSU Fan Stop Temp.";
const char FR_Temp_CaseFanStartTemp_STR[] PROGMEM = "Case Fan Start Temp.";
const char FR_Temp_CaseFanStopTemp_STR[] PROGMEM = "Case Fan Stop Temp.";

// Interface
const char FR_Interface_Title_STR[] PROGMEM = "Interface";
const char FR_Interface_RefreshInterval_STR[] PROGMEM = "Refresh Interval";
const char FR_Interface_LanguageTitle_STR[] PROGMEM = "Language";
const char FR_Interface_RotationTitle_STR[] PROGMEM = "Screen Rotation";
const char FR_Interface_RotationLandscape_STR[] PROGMEM = "Landscape";
const char FR_Interface_RotationInvertedLandscape_STR[] PROGMEM = "Inverted Landscape";
const char FR_Interface_CalibrationTitle_STR[] PROGMEM = "Screen Calibration";
const char FR_Interface_CalibrationStart_STR[] PROGMEM = "Calibrate";
const char FR_Interface_ResetTitle_STR[] PROGMEM = "Reset";
const char FR_Interface_ResetStart_STR[] PROGMEM = "Perform Reset";

// Electricity
const char FR_Electricity_Title_STR[] PROGMEM = "Electricity";
const char FR_Electricity_UVCurrent_STR[] PROGMEM = "UV light est. Current";
const char FR_Electricity_StartChargingVoltage_STR[] PROGMEM = "Start Charging Voltage";
const char FR_Electricity_StopChargingVoltage_STR[] PROGMEM = "Stop Charging Voltage";
const char FR_Electricity_StartWorkingVoltage_STR[] PROGMEM = "Start Working Voltage";
const char FR_Electricity_StopWorkingVoltage_STR[] PROGMEM = "Stop Working Voltage";
const char FR_Electricity_ACInverterFrequency_STR[] PROGMEM = "AC Inverter Frequency";
const char FR_Electricity_ACAmmeterSensitivity_STR[] PROGMEM = "AC Ammeter Sensitivity";
const char FR_Electricity_ACAmmeterZero_STR[] PROGMEM = "AC Ammeter Zero";
const char FR_Electricity_DCAmmeterSensitivity_STR[] PROGMEM = "DC Ammeter Sensitivity";
const char FR_Electricity_DCAmmeterZero_STR[] PROGMEM = "DC Ammeter Zero";

// Language
const char FR_Language_Title_STR[] PROGMEM = "Select a language";

// Error
const char FR_ScreenNotImplementedError_STR[] PROGMEM = "This option is not implemented yet";


const char *const langFR[] PROGMEM = {FR_LANG_STR,FR_YES_STR,FR_NO_STR,FR_ON_STR, FR_OFF_STR, FR_Previous_STR, FR_Next_STR, FR_Delete_STR,FR_OK_STR, // Utils
                                      FR_Status_Title_STR, FR_StatusBtn_Error_STR, FR_MenuBtn_STR, // Status
                                      FR_Menu_Title_STR, FR_HelpBtn_STR, FR_EngineeringBtn_STR, FR_SettingsBtn_STR, FR_ExtraFunctionsBtn, // Menu
                                      FR_ExtraFunctions_Title_STR, FR_ExtraFunctions_InstallWizard_STR, FR_ExtraFunctions_StartInstallWizard_STR, FR_ExtraFunctions_ACPSU_STR, FR_ExtraFunctions_DCPSU_STR, // ExtraFunctions
                                      FR_Settings_Title_STR, FR_Settings_ElectricityBtn_STR, FR_Settings_WaterBtn_STR, FR_Settings_TemperatureBtn_STR, FR_Settings_InterfaceBtn_STR, // Settings
                                      FR_Water_Title_STR, FR_Water_WellPumpMaxTimeON_STR, FR_Water_UVPumpMaxTimeON_STR, FR_Water_EndPumpMaxTimeON_STR, FR_Water_FilterMaxTimeON_STR, FR_Water_UVPumpFlow_STR, // Water
                                      FR_Temp_Title_STR, FR_Temp_RefreshInterval_STR, FR_Temp_SystemStopTemp_STR, FR_Temp_PSUFanStartTemp_STR, FR_Temp_PSUFanStopTemp_STR, FR_Temp_CaseFanStartTemp_STR, FR_Temp_CaseFanStopTemp_STR, // Temperature
                                      FR_Interface_Title_STR, FR_Interface_RefreshInterval_STR, FR_Interface_LanguageTitle_STR, FR_Interface_RotationTitle_STR, FR_Interface_RotationLandscape_STR, FR_Interface_RotationInvertedLandscape_STR, FR_Interface_CalibrationTitle_STR, FR_Interface_CalibrationStart_STR, FR_Interface_ResetTitle_STR, FR_Interface_ResetStart_STR, // Interface
                                      FR_Electricity_Title_STR, FR_Electricity_UVCurrent_STR, FR_Electricity_StartChargingVoltage_STR, FR_Electricity_StopChargingVoltage_STR, FR_Electricity_StartWorkingVoltage_STR, FR_Electricity_StopWorkingVoltage_STR, FR_Electricity_ACInverterFrequency_STR, FR_Electricity_ACAmmeterSensitivity_STR, FR_Electricity_ACAmmeterZero_STR, FR_Electricity_DCAmmeterSensitivity_STR, FR_Electricity_DCAmmeterZero_STR, // Electricity
                                      FR_Language_Title_STR, // Language
                                      FR_ScreenNotImplementedError_STR // Error

}; // Follow the same order as enum StringIDs (Languages.h)


// const char FR_XXX_PATH[] PROGMEM = "xxxx";


const char FR_HelpTopic1_PATH[] PROGMEM = "/FR/Help/Topic1.txt";
const char FR_HelpTopic2_PATH[] PROGMEM = "/FR/Help/Topic2.txt";
const char FR_HelpTopic3_PATH[] PROGMEM = "/FR/Help/Topic3.txt";
const char FR_HelpTopic4_PATH[] PROGMEM = "/FR/Help/Topic4.txt";
const char FR_HelpTopic5_PATH[] PROGMEM = "/FR/Help/Topic5.txt";
const char FR_HelpTopic6_PATH[] PROGMEM = "/FR/Help/Topic6.txt";

const char *const pathFR[] PROGMEM = { FR_HelpTopic1_PATH,FR_HelpTopic2_PATH,FR_HelpTopic3_PATH,FR_HelpTopic4_PATH,FR_HelpTopic5_PATH,FR_HelpTopic6_PATH,}; // Follow the same order as enum PathIDs (Languages.h)


#endif //H2O_GUI_FR_LANG_H
