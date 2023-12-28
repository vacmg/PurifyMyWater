idf_component_register(SRCS "Settings.cpp" "SettingsParser.cpp"
                    INCLUDE_DIRS "include"
	            REQUIRES spiffs json fmt)
