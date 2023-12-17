# Module Design: Settings Storage Idea

## Description

This document shows the idea to develop for the settings storage module

## Keywords

Configuration, Storage, Settings

## Description of the idea

When creating a complex system such as the water treatment plant, we will certainly find the need to have parameters that, depending on their value, will modify the behavior of the system, i.e., we will have parameters to adjust, a configuration.

Therefore, we need to create a persistent storage for those parameters, so that it is not necessary to recompile the program to update a value, but that the adjusted values persist reboots or absence of power.

Our goal is to create all the necessary mechanisms to be able to save, modify and retrieve all configuration parameters from a persistent store.


## Requirement list
### R1: Persistence
- Persistent configuration storage
    - Description: Being able to store data that could persist reboots or power outages
	- Distinguish if the configuration is corrupted and restore to default if that occurs
    - Description: Having a way to check if the data stored has been corrupted or if it is valid, and have some counter measures if the integrity cannot be guaranteed.

### R2: API
- Read configuration at any time
    - Description: Ensure the availability of the data stored in this module.
- Modify configuration at any time
    - Description: Ensure the data stored in this module is available for writing
- Restore to a default configuration of one or all parameters
    - Description: Be able to restore each individual setting to a default, or all settings at once

### R3: Concurrency
- Ensure concurrent operation when several processes access the settings system
    - Description: Ensure there are no race conditions, and other issues derivated from accessing and modifying the settings from different places at the same time

