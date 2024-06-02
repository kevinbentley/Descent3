set(HEADERS
  grtext.h
  grtextlib.h)

set(CPPS
  grfont.cpp
  grtext.cpp
  textaux.cpp)

add_library(grtext STATIC ${HEADERS} ${CPPS})
target_link_libraries(grtext PRIVATE
  ddio
  bitmap
  renderer
  dd_video
  2dlib
)

target_include_directories(grtext PUBLIC
  $<BUILD_INTERFACE:
    ${PROJECT_SOURCE_DIR}/grtext
  >
)
