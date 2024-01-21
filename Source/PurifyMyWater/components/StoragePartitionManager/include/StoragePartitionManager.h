#ifndef PURIFYMYWATER_STORAGEPARTITIONMANAGER_H
#define PURIFYMYWATER_STORAGEPARTITIONMANAGER_H


#include "esp_err.h"
#include "esp_log.h"
#include "esp_spiffs.h"
#include "LogUtils.h"


/**
 * This class manages the storage partition.
 */
class StoragePartitionManager
{
    public:

    /**
     * This function mounts the storage filesystem and if some inconsistencies are found, it calls StoragePartitionManager::check().
     *
     * @return ESP_OK if success; ESP_ERR_NO_MEM if objects could not be allocated;
     * ESP_ERR_INVALID_STATE if already mounted or partition is encrypted;
     * ESP_ERR_NOT_FOUND if partition for SPIFFS was not found;
     * ESP_FAIL if mount or format fails
     */
    static esp_err_t mount();

    /**
     * This function checks and repairs the storage filesystem.
     *
     * @return ESP_OK if successful;
     * ESP_ERR_INVALID_STATE if not mounted;
     * ESP_FAIL on error
     */
    static esp_err_t check();

    /**
     * This function formats the storage filesystem.
     *
     * @return ESP_OK if successful;
     * ESP_FAIL on error
     */
    static esp_err_t format();

    /**
     * This function unmounts the storage filesystem.
     *
     * @return ESP_OK if successful;
     * ESP_ERR_INVALID_STATE already unregistered
     */
    static esp_err_t unmount();

    /**
     * This function returns the configuration of the storage filesystem.
     *
     * @return the configuration of the storage filesystem
     */
    static esp_vfs_spiffs_conf_t getConf();

    private:

    static constexpr esp_vfs_spiffs_conf_t conf = {
        .base_path = "/" CONFIG_STORAGE_PARTITION_LABEL,
        .partition_label = CONFIG_STORAGE_PARTITION_LABEL,
        .max_files = 5,
        .format_if_mount_failed = false
    };
};


#endif //PURIFYMYWATER_STORAGEPARTITIONMANAGER_H