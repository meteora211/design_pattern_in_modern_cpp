file(GLOB SOURCE_FILES "*.cc")

foreach(source_file ${SOURCE_FILES})
  get_filename_component(executable_name ${source_file} NAME_WE)
  add_executable(${executable_name} ${source_file})
  set_target_properties(${executable_name} PROPERTIES
      CXX_STANDARD 20
      CXX_STANDARD_REQUIRED YES
      CXX_EXTENSIONS NO
      # COMPILE_FLAGS "-Wall"
  )

  install(TARGETS ${executable_name} DESTINATION ${INSTALL_BIN_DIR})

endforeach()

