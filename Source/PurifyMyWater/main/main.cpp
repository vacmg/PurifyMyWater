/**
 *
 */

#include "LogUtils.h"
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
    setComponentsDefaultLogLevel();

    ESP_LOGE(COMPONENT_TAG_BOOT,"Starting PurifyMyWater Modules");
    ESP_LOGI(COMPONENT_TAG_BOOT,"\n%s",device_info().c_str());

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

    ESP_LOGE(COMPONENT_TAG_BOOT,"PurifyMyWater Modules Successfully Started");


    StoragePartitionManager::unmount();
    vTaskSuspend(nullptr);
}
