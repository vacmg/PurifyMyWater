idf_component_register(SRCS "StoragePartitionManager.cpp"
                    INCLUDE_DIRS "include"
                    REQUIRES spiffs)

spiffs_create_partition_image(storage "../../storage_spiffs_root" FLASH_IN_PROJECT)
