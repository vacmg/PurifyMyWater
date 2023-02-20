//
// Created by Victor on 11/09/2022.
//

#ifndef H2O_GUI_GUI_COMPILE_FLAGS_H
#define H2O_GUI_GUI_COMPILE_FLAGS_H

#define SCREENHW 35 // Used to set the screen hardware used // 35 --> 3.5INCH / 39 --> 3.95INCH

#define DEBUG true // Used to display debug information messages through Serial port

#define DISABLEUI false  // Used to disable the UI screen module
#define DISABLECOMM true // Used to disable communications module

#define SETDEFAULTSCREENCONFIG true // Used to set the screenConfig to the default screenConfig
#define USEVOLATILECONFIG true // Used to disable EEPROM writes due to saving configuration in the persistent storage

#if !DEBUG && (USEVOLATILECONFIG || SETDEFAULTSCREENCONFIG || DISABLEUI || DISABLECOMM)
#undef DEBUG
#define DEBUG true
#endif

#endif //H2O_GUI_GUI_COMPILE_FLAGS_H
