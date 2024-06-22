set(HEADERS
  polymodel_external.h
  polymodel.h)

set(CPPS
  newstyle.cpp
  polymodel.cpp)

add_library(model STATIC ${HEADERS} ${CPPS})
target_link_libraries(model PRIVATE
  ddio
  mem
  bitmap
  renderer
  networking
  physics
  manage
  2dlib
)

target_include_directories(model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
