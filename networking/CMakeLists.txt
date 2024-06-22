set(HEADERS
  networking.h
  $<$<PLATFORM_ID:Windows>:
    directplay.h
  >
)
set(CPPS
  networking.cpp
  $<$<PLATFORM_ID:Windows>:
    directplay.cpp
  >
)

add_library(networking STATIC ${HEADERS} ${CPPS})
target_link_libraries(networking PRIVATE
  ddio
  mem
  renderer
  bitmap
  manage
  module
  ddio
  2dlib
  model
)

target_include_directories(networking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
