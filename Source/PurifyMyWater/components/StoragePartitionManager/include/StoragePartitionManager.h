#ifndef PURIFYMYWATER_STORAGEPARTITIONMANAGER_H
#define PURIFYMYWATER_STORAGEPARTITIONMANAGER_H


#include "esp_err.h"
#include "esp_log.h"
#include "esp_spiffs.h"


class StoragePartitionManager
{
        public:
        static esp_err_t mount();
        static esp_err_t check();
        static esp_err_t format();
        static esp_err_t unmount();
        static esp_vfs_spiffs_conf_t getConf();
        private:
        static constexpr esp_vfs_spiffs_conf_t conf = {
            .base_path = "/storage",
            .partition_label = CONFIG_STORAGE_PARTITION_LABEL,
            .max_files = 5,
            .format_if_mount_failed = false
        };
};


#endif //PURIFYMYWATER_STORAGEPARTITIONMANAGER_H