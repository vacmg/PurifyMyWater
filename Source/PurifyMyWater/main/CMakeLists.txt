idf_component_register(SRCS "main.cpp"
                    INCLUDE_DIRS "." "devices" "module_Configurations"
                                 "utils"
                    REQUIRES LovyanGFX lvgl fmt app_update)
