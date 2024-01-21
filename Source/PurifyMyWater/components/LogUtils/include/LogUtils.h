
#ifndef PMW_LOGUTILS_H
#define PMW_LOGUTILS_H

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

/**
 * This macro is used to print the file name and line number of the current position in the code.
 */
#define AT " AT " __FILE__ ":" TOSTRING(__LINE__) ": "

extern const char* COMPONENT_NAME_BOOT;
extern const char* COMPONENT_TAG_BOOT;

extern const char* COMPONENT_NAME_BOOT_GUI;
extern const char* COMPONENT_TAG_BOOT_GUI;

extern const char* COMPONENT_NAME_GUI;
extern const char* COMPONENT_TAG_GUI;

extern const char* COMPONENT_NAME_SETTINGS_STORAGE;
extern const char* COMPONENT_TAG_SETTINGS_STORAGE;

extern const char* COMPONENT_NAME_STORAGE_PARTITION_MANAGER;
extern const char* COMPONENT_TAG_STORAGE_PARTITION_MANAGER;

void setComponentsDefaultLogLevel();

#endif //PMW_LOGUTILS_H
