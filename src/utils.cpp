#include <nvs_flash.h>

void resetSettings()
{
    nvs_flash_erase(); // erase the NVS partition and...
    nvs_flash_init();  // initialize the NVS partition.
}