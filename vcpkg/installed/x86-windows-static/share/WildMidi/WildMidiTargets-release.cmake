#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "WildMidi::libwildmidi-static" for configuration "Release"
set_property(TARGET WildMidi::libwildmidi-static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(WildMidi::libwildmidi-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libWildMidi-static.lib"
  )

list(APPEND _cmake_import_check_targets WildMidi::libwildmidi-static )
list(APPEND _cmake_import_check_files_for_WildMidi::libwildmidi-static "${_IMPORT_PREFIX}/lib/libWildMidi-static.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
