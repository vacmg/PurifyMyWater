#include "PrivStoragePartitionManager.h"


esp_err_t StoragePartitionManager::unmount()
{
    ESP_LOGI(STORAGE_PARTITION_MANAGER_COMPONENT_TAG, "Unmounting " CONFIG_STORAGE_PARTITION_LABEL " partition");
    esp_err_t ret = esp_vfs_spiffs_unregister(conf.partition_label);
    if (ret != ESP_OK)
    {
        ESP_LOGE(STORAGE_PARTITION_MANAGER_COMPONENT_TAG, AT"Failed to unmount " CONFIG_STORAGE_PARTITION_LABEL " partition: %s", esp_err_to_name(ret));
    }
    return ret;
}

esp_vfs_spiffs_conf_t StoragePartitionManager::getConf()
{
    return conf;
}

esp_err_t StoragePartitionManager::format()
{
    ESP_LOGI(STORAGE_PARTITION_MANAGER_COMPONENT_TAG, "Formatting " CONFIG_STORAGE_PARTITION_LABEL " partition");
    esp_err_t ret = esp_spiffs_format(conf.partition_label);
    if (ret != ESP_OK)
    {
        ESP_LOGE(STORAGE_PARTITION_MANAGER_COMPONENT_TAG, AT"Failed to format " CONFIG_STORAGE_PARTITION_LABEL " partition: %s", esp_err_to_name(ret));
        return ret;
    }
    return ret;
}


esp_err_t StoragePartitionManager::mount()
{
    ESP_LOGI(STORAGE_PARTITION_MANAGER_COMPONENT_TAG, "Initializing " CONFIG_STORAGE_PARTITION_LABEL " partition");

    // Use settings defined above to initialize and mount SPIFFS filesystem.
    // Note: esp_vfs_spiffs_register is an all-in-one convenience function.
    esp_err_t ret = esp_vfs_spiffs_register(&conf);

    if (ret != ESP_OK)
    {
        if (ret == ESP_FAIL)
        {
            ESP_LOGE(STORAGE_PARTITION_MANAGER_COMPONENT_TAG, AT"Failed to mount or format " CONFIG_STORAGE_PARTITION_LABEL " filesystem");
        }
        else if (ret == ESP_ERR_NOT_FOUND)
        {
            ESP_LOGE(STORAGE_PARTITION_MANAGER_COMPONENT_TAG, AT"Failed to find " CONFIG_STORAGE_PARTITION_LABEL " SPIFFS partition");
        }
        else
        {
            ESP_LOGE(STORAGE_PARTITION_MANAGER_COMPONENT_TAG, AT"Failed to initialize " CONFIG_STORAGE_PARTITION_LABEL " SPIFFS partition: %s", esp_err_to_name(ret));
        }
        return ret;
    }

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(conf.partition_label, &total, &used);
    if (ret != ESP_OK)
    {
        ESP_LOGE(STORAGE_PARTITION_MANAGER_COMPONENT_TAG, AT"Failed to get " CONFIG_STORAGE_PARTITION_LABEL " partition information: %s", esp_err_to_name(ret));
        return ret;
    }
    else
    {
        ESP_LOGI(STORAGE_PARTITION_MANAGER_COMPONENT_TAG, CONFIG_STORAGE_PARTITION_LABEL " partition size: total: %d, used: %d", total, used);
    }

    // Check consistency of reported partition size info.
    if (used > total)
    {
        ESP_LOGW(STORAGE_PARTITION_MANAGER_COMPONENT_TAG, "Number of used bytes cannot be larger than total.");
        ret = check();
        // Could be also used to mend broken files, to clean unreferenced pages, etc.
        // More info at https://github.com/pellepl/spiffs/wiki/FAQ#powerlosses-contd-when-should-i-run-spiffs_check
    }
    return ret;
}

esp_err_t StoragePartitionManager::check()
{
    if(!esp_spiffs_mounted(CONFIG_STORAGE_PARTITION_LABEL))
    {
        ESP_LOGE(STORAGE_PARTITION_MANAGER_COMPONENT_TAG, AT CONFIG_STORAGE_PARTITION_LABEL " SPIFFS partition not mounted");
        return false;
    }

    ESP_LOGI(STORAGE_PARTITION_MANAGER_COMPONENT_TAG, "Performing SPIFFS_check()");
    esp_err_t ret = esp_spiffs_check(conf.partition_label);
    if (ret != ESP_OK)
    {
        ESP_LOGE(STORAGE_PARTITION_MANAGER_COMPONENT_TAG, AT "SPIFFS_check() failed (%s)", esp_err_to_name(ret));
    } else
    {
        ESP_LOGI(STORAGE_PARTITION_MANAGER_COMPONENT_TAG, "SPIFFS_check() successful");
    }
    return ret;
}

