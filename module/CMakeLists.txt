set(HEADERS
  module.h)
set(CPPS
  module.cpp)

add_library(module STATIC ${HEADERS} ${CPPS})
target_link_libraries(module PRIVATE
  ddio
)

target_include_directories(module PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
