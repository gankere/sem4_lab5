# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\painter_lab_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\painter_lab_autogen.dir\\ParseCache.txt"
  "painter_lab_autogen"
  )
endif()
