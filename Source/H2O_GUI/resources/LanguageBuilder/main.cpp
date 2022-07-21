#include <iostream>
#include <stdio.h>
#include "ArduinoJson.h"

char data[50000];
char filename[200] = "DEF.lan";
StaticJsonDocument<50000> langs;

void serialize()
{
    ArduinoJson6194_71::serializeJsonPretty(langs,data, sizeof(data));
    std::cout << data << std::endl;
    FILE* file = fopen(filename,"w");
    fwrite(data,sizeof(char), strlen(data),file);
    fclose(file);
    langs.clear();
}



void english()
{
    strcpy(filename,"../EN.lan");

    langs["Utils"]["SwitchStatus"]["ON"] = "ON";
    langs["Utils"]["SwitchStatus"]["OFF"] = "OFF";

    langs["Status"]["Title"] = "Status";
    langs["Status"]["ErrorStatusBtn"]["FAILURE"] = "FAILURE";
    langs["Status"]["MenuBtn"] = "Menu";

    langs["Menu"]["Title"] = "Menu";
    langs["Menu"]["HelpBtn"] = "Help";
    langs["Menu"]["EngineeringBtn"] = "Engineering Mode";
    langs["Menu"]["SettingsBtn"] = "Settings";
    langs["Menu"]["ExtraFunctionsBtn"] = "Extra Functions";

    langs["Menu"]["Settings"]["Title"] = "Settings";
    langs["Menu"]["Settings"]["ElectricityBtn"] = "Electricity";
    langs["Menu"]["Settings"]["WaterBtn"] = "Water";
    langs["Menu"]["Settings"]["InterfaceBtn"] = "Interface";
    langs["Menu"]["Settings"]["TemperatureBtn"] = "Temperature";

    langs["Menu"]["Settings"]["Water"]["Title"] = "Water";
    langs["Menu"]["Settings"]["Water"]["WellPumpMaxTimeON"] = "Well Pump max time ON";
    langs["Menu"]["Settings"]["Water"]["UVPumpMaxTimeON"] = "UV Pump max time ON";
    langs["Menu"]["Settings"]["Water"]["EndPumpMaxTimeON"] = "End Pump max time ON";
    langs["Menu"]["Settings"]["Water"]["FilterMaxTimeON"] = "Filter max time ON";
    langs["Menu"]["Settings"]["Water"]["UVPumpFlow"] = "UV Pump flow";

    langs["Menu"]["Settings"]["Temperature"]["Title"] = "Temperature";
    langs["Menu"]["Settings"]["Temperature"]["RefreshRate"] = "Temp. Refresh Rate";
    langs["Menu"]["Settings"]["Temperature"]["SystemStopTemp"] = "System Stop Temp.";
    langs["Menu"]["Settings"]["Temperature"]["PSUFanStartTemp"] = "PSU Fan Start Temp.";
    langs["Menu"]["Settings"]["Temperature"]["PSUFanStopTemp"] = "PSU Fan Stop Temp.";
    langs["Menu"]["Settings"]["Temperature"]["CaseFanStartTemp"] = "Case Fan Start Temp.";
    langs["Menu"]["Settings"]["Temperature"]["CaseFanStopTemp"] = "Case Fan Stop Temp.";

    langs["Menu"]["Settings"]["Interface"]["Title"] = "Interface";
    langs["Menu"]["Settings"]["Interface"]["Language"]["Title"] = "Language";
    langs["Menu"]["Settings"]["Interface"]["Language"]["English"] = "English";
    langs["Menu"]["Settings"]["Interface"]["Language"]["Spanish"] = "Spanish";
    langs["Menu"]["Settings"]["Interface"]["Language"]["French"] = "French";
    langs["Menu"]["Settings"]["Interface"]["ScreenRotation"]["Title"] = "Screen Rotation";
    langs["Menu"]["Settings"]["Interface"]["ScreenRotation"]["InvertedLandscape"] = "Inverted Landscape";
    langs["Menu"]["Settings"]["Interface"]["ScreenRotation"]["Landscape"] = "Landscape";
    langs["Menu"]["Settings"]["Interface"]["ScreenCalibration"]["Title"] = "Screen Calibration";
    langs["Menu"]["Settings"]["Interface"]["ScreenCalibration"]["StartScreenCalibration"] = "Calibrate";
    langs["Menu"]["Settings"]["Interface"]["RefreshPeriod"] = "Refresh Period";
    langs["Menu"]["Settings"]["Interface"]["Reset"]["Title"] = "Reset";
    langs["Menu"]["Settings"]["Interface"]["Reset"]["StartReset"] = "Perform Reset";

    langs["Menu"]["Settings"]["Electricity"]["Title"] = "Electricity";
    langs["Menu"]["Settings"]["Electricity"]["StartChargingVoltage"] = "Start Charging Voltage";
    langs["Menu"]["Settings"]["Electricity"]["StopChargingVoltage"] = "Stop Charging Voltage";
    langs["Menu"]["Settings"]["Electricity"]["UVCurrent"] = "UV light est. Current";
    langs["Menu"]["Settings"]["Electricity"]["StartWorkingVoltage"] = "Start Working Voltage";
    langs["Menu"]["Settings"]["Electricity"]["StopWorkingVoltage"] = "Stop Working Voltage";
    langs["Menu"]["Settings"]["Electricity"]["ACInverterFrequency"] = "AC Inverter Frequency";
    langs["Menu"]["Settings"]["Electricity"]["ACAmmeterSensitivity"] = "AC Ammeter Sensitivity";
    langs["Menu"]["Settings"]["Electricity"]["ACAmmeterZero"] = "AC Ammeter Zero";
    langs["Menu"]["Settings"]["Electricity"]["DCAmmeterSensitivity"] = "DC Ammeter Sensitivity";
    langs["Menu"]["Settings"]["Electricity"]["DCAmmeterZero"] = "DC Ammeter Zero";

    langs["Menu"]["ExtraFunctions"]["Title"] = "Extra Functions";
    langs["Menu"]["ExtraFunctions"]["InstallWizard"] = "Install Wizard";
    langs["Menu"]["ExtraFunctions"]["StartInstallWizard"] = "Start";
    langs["Menu"]["ExtraFunctions"]["ACPSU"] = "AC Power Supply";
    langs["Menu"]["ExtraFunctions"]["DCPSU"] = "DC Power Supply";

    serialize();
}

int main()
{
    english();

    return 0;
}