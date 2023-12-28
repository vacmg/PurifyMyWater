idf_component_register(SRCS "main.cpp" "utils/deviceInfo.cpp"
                    INCLUDE_DIRS "." "utils"
                    REQUIRES fmt app_update spi_flash SettingsStorage StoragePartitionManager)
