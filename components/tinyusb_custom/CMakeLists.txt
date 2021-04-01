idf_component_register(REQUIRES esp_rom freertos vfs soc)

set(compile_options
    "-DCFG_TUSB_MCU=OPT_MCU_ESP32S2"
    "-DCFG_TUSB_DEBUG=0"
    "-Wno-type-limits" # needed for the vanila tinyusb with turned off classes
)
idf_component_get_property(
    FREERTOS_ORIG_INCLUDE_PATH freertos ORIG_INCLUDE_PATH)
set(includes_private
    "${COMPONENT_DIR}/tinyusb/hw/bsp/"
    "${COMPONENT_DIR}/tinyusb/src/"
    "${COMPONENT_DIR}/tinyusb/src/device"
    "${COMPONENT_DIR}/tinyusb/hw/bsp/esp32s2_saola_1/led_strip/include"
    )

set(includes_public
    "${FREERTOS_ORIG_INCLUDE_PATH}"
    "${COMPONENT_DIR}/tinyusb/hw/"
    "${COMPONENT_DIR}/tinyusb/src/"
    "${COMPONENT_DIR}"
    )
set(srcs
    "${COMPONENT_DIR}/tinyusb/src/portable/espressif/esp32s2/dcd_esp32s2.c"
    "${COMPONENT_DIR}/tinyusb/hw/bsp/esp32s2_saola_1/esp32s2_saola_1.c"
    "${COMPONENT_DIR}/tinyusb/hw/bsp/esp32s2_saola_1/led_strip/src/led_strip_rmt_ws2812.c"
    "${COMPONENT_DIR}/tinyusb/src/class/cdc/cdc_device.c"
    "${COMPONENT_DIR}/tinyusb/src/class/hid/hid_device.c"
    "${COMPONENT_DIR}/tinyusb/src/class/midi/midi_device.c"
    "${COMPONENT_DIR}/tinyusb/src/class/msc/msc_device.c"
    "${COMPONENT_DIR}/tinyusb/src/class/vendor/vendor_device.c"
    "${COMPONENT_DIR}/tinyusb/src/common/tusb_fifo.c"
    "${COMPONENT_DIR}/tinyusb/src/device/usbd_control.c"
    "${COMPONENT_DIR}/tinyusb/src/device/usbd.c"
    "${COMPONENT_DIR}/tinyusb/src/tusb.c")

### tinyusb lib ###
###################
add_library(tinyusb STATIC ${srcs})
target_include_directories(
tinyusb
PUBLIC ${includes_public}
PRIVATE ${includes_private})
target_compile_options(tinyusb PRIVATE ${compile_options})
target_link_libraries(${COMPONENT_TARGET} INTERFACE tinyusb)
