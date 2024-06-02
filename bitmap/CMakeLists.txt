set(HEADERS
  bitmap.h
  bumpmap.h
  iff.h
  lightmap.h
  NewBitmap.h)

set(CPPS
  NewBitmap.cpp
  NewBitmap.h
  bitmap.cpp
  bumpmap.cpp
  iff.cpp
  lightmap.cpp
  pcx.cpp
  tga.cpp)

add_library(bitmap STATIC ${HEADERS} ${CPPS})
target_link_libraries(bitmap PRIVATE
  cfile
  ddebug
  ddio
  stb
  renderer
  2dlib
)

target_include_directories(bitmap PUBLIC
  $<BUILD_INTERFACE:
    ${PROJECT_SOURCE_DIR}/bitmap
  >
)
