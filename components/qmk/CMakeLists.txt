set(QMK_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/qmk)

# If you need to access some esp-idf component from qmk, you can
# add it as a REQUIRES here, and the appropriate include directory
# will be passed to the qmk build.
#
# If some esp-idf component needs to access something in qmk, you can
# add the appropriate include directory in INCLUDE_DIRS here, and then
# any component that REQUIRES this component will get the include
# directory.
idf_component_register(INCLUDE_DIRS ${QMK_ROOT}/tmk_core/common
                       REQUIRES fatfs freertos)

string(REPLACE "/" "_" FLATTENED_KEYBOARD ${QMK_KEYBOARD})
set(QMK_STATIC_LIBRARY ${QMK_ROOT}/${FLATTENED_KEYBOARD}_${QMK_LAYOUT}.a)

idf_component_get_property(
    FREERTOS_ORIG_INCLUDE_PATH freertos ORIG_INCLUDE_PATH)

target_include_directories(${COMPONENT_TARGET} INTERFACE "${FREERTOS_ORIG_INCLUDE_PATH}")

# Call the qmk build, passing in all of the include directories that have been configured
# for this esp-idf component.
ExternalProject_Add(qmk_external
   SOURCE_DIR ${QMK_ROOT}
   CONFIGURE_COMMAND ""
   BUILD_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/qmk_build.sh "$<TARGET_PROPERTY:${COMPONENT_LIB},INTERFACE_INCLUDE_DIRECTORIES>" ${QMK_KEYBOARD} ${QMK_LAYOUT}
   BUILD_BYPRODUCTS ${QMK_STATIC_LIBRARY}
   BUILD_IN_SOURCE true
   BUILD_ALWAYS true
   INSTALL_COMMAND ""
)

add_library(qmk_lib INTERFACE)
target_link_libraries(qmk_lib INTERFACE ${QMK_STATIC_LIBRARY})

add_dependencies(${COMPONENT_LIB} qmk_external)

target_link_libraries(${COMPONENT_LIB} INTERFACE qmk_lib)