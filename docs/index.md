# Welcome to PurifyMyWater
Here you can read about the hardware & software used to bring to the world the first DIY water purifying system which can be assembled without spending lots of resources in expensive components.

## About us
This project is being developed by [**@vacmg**](https://github.com/vacmg) with the support of the [**ALUMNOS SOLIDARIOS**](https://www.joyfe.es/gente-joyfe/alumnos-solidarios/) initiative of JOYFE's school in Madrid.

Currently, we are developing and testing a prototype which will be deployed in the Kanhankro school and will supply arround **1500L** of clean water per day to the school and the surrounding area.

Our project was included in an UNICEF [video](http://www.youtube.com/watch?v=UPMDZqc1k5A&t=4m5s) about solidarity and was selected by [Juan José Marquez's foundation](https://fundacionjjmarquez.org/) to bring water to a school located in Kahankro, in Ivory Coast.

![Prototype](https://github.com/vacmg/PurifyMyWater/raw/master/docs/media/20180611_103633_HDR.jpg) | ![Control Unit](https://github.com/vacmg/PurifyMyWater/raw/master/docs/media/20180802_202004.jpg)
------------ | -------------
This is an image of the protoytpe | This is the inside of the control unit

## Hardware
The main idea of this project is to use cheap items to create a robust machine that is almost self-sufficient and easily scalable. To achieve that, we have split the system into the control unit, and some peripherals. With little or no change to the control unit and the code, our solution can be expanded to purify more water if required.

- #### How it works?

![System scheme](https://raw.githubusercontent.com/vacmg/PurifyMyWater/master/Schematics/Scan.jpg)

Firstly, a pump gets water from the well and puts it in a surface tank. Then, the sand filter separates the clean water from the soil, and sends it to an UV tank.
The next step is to destroy any organism using an UV lamp and then pump the water to a tank which is higher than the rest of the installation.
From that tank, the water is distributed to where it is needed.

- #### Energy management

This system gets all its energy from a **solar panel**. for better performance, its rated power should be at least 50% higher than the periphral that needs more power. This is to ensure that if the day is not sunny, the system will work as well.

Instead of accumulating the energy in a battery, which lifespan is around 2 years, we use supercapacitors, which accumulate less energy (still enough to drive high loads for a short period of time), but last millions of charge and discharge cycles. With that hardware configuration, our system will not work at night, but even though, our reference design which cleans 180L per hour is capable of cleaning 1500L in a day if it just works 8-9 hours a day.

Our components use direct current but also alternative current, so we need to have a transformer to give the correct DC voltage (12V) and an inverter to provide us AC energy at the european standard voltage (230V). To carefully manage the electricity used in the system, we have an overvoltage control board for the capacitors and a few voltage and ampere meters in addition to a solid state relay that manages the energy input.

- #### Control unit

Our control unit packages all the electronics needed to control and supply energy to all pumps and components used in the system. It has an arduino MEGA 2560 inside which is the main controller. In adition, we are developing 2 versions of the control unit: one with a touchscreen module and another one which doesn´t. The touchscreen will be used to monitor the system, check for errors and tune its parameters to adapt to your necesities. Moreover, it will be used to toggle additional features such as an AC power supply, an USB phone charger and more!

To use some of the additional features included in the touchscreen version, it will be possible to edit the configuration file, which is placed inside a microSD card in JSON format.

## Software
Currently, our development team is developing and testing a rework of the code which will work with the hardware revision that it is also being developed now. This rework will include the support of the touchscreen and lots of extra funcionalities.

The code is being developed in Arduino language, a slightly modified version of c++ which emulates processing main methods: setup and loop.
