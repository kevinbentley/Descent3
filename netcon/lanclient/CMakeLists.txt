set(HEADERS
  lanclient.h
  lanstrings.h)
set(CPPS lanclient.cpp)

add_library(Direct_TCP_IP MODULE ${HEADERS} ${CPPS})
set_target_properties(Direct_TCP_IP PROPERTIES PREFIX "")
set_target_properties(Direct_TCP_IP PROPERTIES CXX_VISIBILITY_PRESET "hidden")
set_target_properties(Direct_TCP_IP PROPERTIES OUTPUT_NAME "Direct TCP~IP")
target_link_libraries(Direct_TCP_IP PRIVATE
  ddio
  inetfile
  networking
  ui
  bitmap
  model
  module
  manage
  renderer
  2dlib
  $<$<PLATFORM_ID:Windows>:
    ws2_32
  >
)

target_include_directories(Direct_TCP_IP PUBLIC .)

add_custom_target(Direct_TCP_IP_Hog
  COMMAND $<TARGET_FILE:HogMaker>
  "$<TARGET_FILE_DIR:Descent3>/online/Direct TCP~IP.d3c"
  "${CMAKE_SOURCE_DIR}/netcon/lanclient/TCP_IP.d3c.txt"
  "${CMAKE_SOURCE_DIR}/scripts/data/fullhog/"
  "$<TARGET_FILE_DIR:Direct_TCP_IP>"

  DEPENDS Direct_TCP_IP HogMaker
  COMMENT "Generate 'Direct TCP~IP.d3c'"
)
install(FILES "$<TARGET_FILE_DIR:Descent3>/online/Direct TCP~IP.d3c" DESTINATION ${CMAKE_INSTALL_DATADIR}/online)

