/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_log.h"

#include "bsp/board.h"

#include "keyboard.h"

#include "gpio.h"


int idf_main(void);

void app_main(void)
{
    //board_init();
    //tud_task();
    idf_main();
}

void blah() {
    board_init();
    tud_task();
}
