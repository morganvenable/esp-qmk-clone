# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

# This defines which keyboard and layout will be used when building
# QMK. The keyboard must use one of the supported esp32 MCUs.
set(QMK_KEYBOARD handwired/lalboard)
set(QMK_LAYOUT default)

# I wasn't able to figure out how to get the link order set correctly
# between the qmk static library and some of the esp-idf system components.
# This is a workaround that causes esp-idf to add a --start-group clause
# at the beginning of the link command, which helps avoid these undefined
# references caused by the incorrect link order
set(__PROJECT_GROUP_LINK_COMPONENTS true)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(esp-qmk)
