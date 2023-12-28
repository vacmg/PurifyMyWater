/**
 *
 */
#include "main.h"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "deviceInfo.h"

#include "Settings.h"
#include "StoragePartitionManager.h"


/**
 * App entry point
 */
extern "C" void app_main(void)
{
    esp_log_level_set(MAIN_COMPONENT_TAG,ESP_LOG_DEBUG);

    ESP_LOGE(MAIN_COMPONENT_TAG,"\n%s",device_info().c_str());

    if(StoragePartitionManager::mount() != ESP_OK)
    {
        // Storage is unusable, GUI assets & config may be lost, fallback to a mode where no assets are in use & try formatting
        // the partition to try to keep settings module working.

        if(StoragePartitionManager::format() != ESP_OK)
        {
            // Storage is 100% unusable. Fallback to default settings & NO settings persistence.
        }
    }
    else
    {
        StoragePartitionManager::check();

        Settings::test(); // Continue boot sequence from here
    }


    StoragePartitionManager::unmount();
    vTaskSuspend(nullptr);
}
