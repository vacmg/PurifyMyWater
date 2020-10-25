# Welcome to PurifyMyWater
Here you can read about the hardware & software used to bring to the world the first DIY water purifying system which can be assembled without spending lots of resources in expensive components.

## Overview
`Under development... please be patient`

## About us
This project is being developed by [**@vacmg**](https://github.com/vacmg) with the support of the [**ALUMNOS SOLIDARIOS**](https://www.joyfe.es/gente-joyfe/alumnos-solidarios/) initiative of JOYFE's school in Madrid.

Currently, we are developing and testing a prototype which will be deployed in the Kanhankro school and will supply arround **1500L** of clean water per day to the school and the surrounding area.

## Hardware
The main idea of this project is to use cheap items to create a robust machine that is almost self-sufficient and easily scalable. To achieve that, we have split the system into the control unit, and some peripherals. With little or no change to the control unit and the code, our solution can be expanded to purify more water if required.

- #### How it works?

![System scheme](https://github.com/vacmg/PurifyMyWater/blob/master/Schematics/Scan.jpg)

`Under development... please be patient`

- #### Energy management

This system gets all its energy from a **solar panel**. for better performance, its rated power should be at least 50% higher than the periphral that needs more power. This is to ensure that if the day is not sunny, the system will work as well.

Instead of accumulating the energy in a battery, which lifespan is around 2 years, we use supercapacitors, which accumulate less energy (still enough to drive high loads for a short period of time), but last millions of charge and discharge cycles. With that hardware configuration, our system will not work at night, but even though, our reference design which cleans 180L per hour is capable of cleaning 1500L in a day if it just works 8-9 hours a day.

Our components use direct current but also alternative current, so we need to have a transformer to give the correct DC voltage (12V) and an inverter to provide us AC energy at the european standard voltage (230V). To carefully manage the electricity used in the system, we have an overvoltage control board for the capacitors and a few voltage and ampere meters in addition to a solid state relay that manages the energy input.
