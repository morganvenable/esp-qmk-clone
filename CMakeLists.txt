# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

# This defines which keyboard and layout will be used when building
# QMK. The keyboard must use one of the supported esp32 MCUs.
set(QMK_KEYBOARD handwired/lalboard)
set(QMK_LAYOUT default)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(hello-world)
