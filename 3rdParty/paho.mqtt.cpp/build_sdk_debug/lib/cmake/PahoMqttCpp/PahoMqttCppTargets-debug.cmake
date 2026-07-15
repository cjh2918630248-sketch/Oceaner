#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "PahoMqttCpp::paho-mqttpp3-shared" for configuration "Debug"
set_property(TARGET PahoMqttCpp::paho-mqttpp3-shared APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(PahoMqttCpp::paho-mqttpp3-shared PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/paho-mqttpp3.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/paho-mqttpp3.dll"
  )

list(APPEND _cmake_import_check_targets PahoMqttCpp::paho-mqttpp3-shared )
list(APPEND _cmake_import_check_files_for_PahoMqttCpp::paho-mqttpp3-shared "${_IMPORT_PREFIX}/lib/paho-mqttpp3.lib" "${_IMPORT_PREFIX}/bin/paho-mqttpp3.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
