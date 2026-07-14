# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "RelWithDebInfo")
  file(REMOVE_RECURSE
  "src\\charts\\CMakeFiles\\Charts_autogen.dir\\AutogenUsed.txt"
  "src\\charts\\CMakeFiles\\Charts_autogen.dir\\ParseCache.txt"
  "src\\charts\\Charts_autogen"
  "src\\chartsqml2\\CMakeFiles\\ChartsQml_autogen.dir\\AutogenUsed.txt"
  "src\\chartsqml2\\CMakeFiles\\ChartsQml_autogen.dir\\ParseCache.txt"
  "src\\chartsqml2\\CMakeFiles\\qtchartsqml2_autogen.dir\\AutogenUsed.txt"
  "src\\chartsqml2\\CMakeFiles\\qtchartsqml2_autogen.dir\\ParseCache.txt"
  "src\\chartsqml2\\ChartsQml_autogen"
  "src\\chartsqml2\\qtchartsqml2_autogen"
  )
endif()
