set(QMK_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/qmk)

# If you need to access some esp-idf component from qmk, you can
# add it as a REQUIRES here, and the appropriate include directory
# will be passed to the qmk build.

idf_component_register(INCLUDE_DIRS ${QMK_ROOT}/tmk_core/common
                       REQUIRES fatfs)

string(REPLACE "/" "_" FLATTENED_KEYBOARD ${QMK_KEYBOARD})
set(QMK_STATIC_LIBRARY ${QMK_ROOT}/${FLATTENED_KEYBOARD}_${QMK_LAYOUT}.a)

# The following is needed because tinyusb includes some freertos headers without
# the freertos directory prefix. But ORIG_INCLUDE_PATH has the correct include
# directory to use for this case.
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

add_library(qmk_lib IMPORTED STATIC)
add_dependencies(qmk_lib qmk_external)
set_target_properties(qmk_lib PROPERTIES IMPORTED_LOCATION ${QMK_STATIC_LIBRARY})

# The static library for qmk needs to be linked in using the --whole-archive option,
# to ensure that all strong symbols override weak symbols.
target_link_libraries(${COMPONENT_LIB} INTERFACE "-Wl,--whole-archive")
target_link_libraries(${COMPONENT_LIB} INTERFACE qmk_lib)
target_link_libraries(${COMPONENT_LIB} INTERFACE "-Wl,--no-whole-archive")
