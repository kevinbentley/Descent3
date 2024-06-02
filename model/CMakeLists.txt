set(HEADERS
  polymodel_external.h
  polymodel.h)

set(CPPS
  newstyle.cpp
  polymodel.cpp)

add_library(model STATIC ${HEADERS} ${CPPS})
target_link_libraries(model PRIVATE
  ddio
  bitmap
  renderer
  networking
  physics
  manage
  2dlib
)

target_include_directories(model PUBLIC
  $<BUILD_INTERFACE:
    ${PROJECT_SOURCE_DIR}/model
  >
)
