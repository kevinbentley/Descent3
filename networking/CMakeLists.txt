set(HEADERS
  networking.h)
set(CPPS
  networking.cpp)

if(WIN32)
  set(HEADERS ${HEADERS} directplay.h)
  set(CPPS ${CPPS} directplay.cpp)
endif()

add_library(networking STATIC ${HEADERS} ${CPPS})
target_link_libraries(networking PRIVATE
  ddio
  renderer
  bitmap
  manage
  module
  ddio
  2dlib
  model
)

target_include_directories(networking PUBLIC
  $<BUILD_INTERFACE:
    ${PROJECT_SOURCE_DIR}/networking
  >
)
