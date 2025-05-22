# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "RelWithDebInfo")
  file(REMOVE_RECURSE
  "CMakeFiles/Programming_Qt_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Programming_Qt_autogen.dir/ParseCache.txt"
  "Programming_Qt_autogen"
  )
endif()
