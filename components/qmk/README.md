This wraps a forked version of QMK in an esp-idf component, using
cmake's ExternalProject_add to drive the QMK build.

Both sides are able to reference functions in the other side. See the
comments for idf_component_register in CMakeLists.txt for more info.

The specific keyboard and layout to build are set via the QMK_KEYBOARD
and QMK_LAYOUT variables. These can be set in the top level CMakeLists.txt
for the project. Currently, only keyboards that specify the new esp32s2 MCU
can be used.

QMK has been modified to spit out a static .a file for the new ESP32 platform,
instead of the typical .bin or .hex firmware file. This .a file is then
consumed by the cmake-based esp-idf build, and linked in with the final
firmware image.