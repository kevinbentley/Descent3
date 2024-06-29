set(HEADERS)
set(CPPS
  module.cpp)

add_library(module STATIC ${HEADERS} ${CPPS})
target_link_libraries(module PRIVATE
  ddio
  misc
)
