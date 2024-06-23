set(HEADERS iff.h)
set(CPPS
  NewBitmap.cpp
  NewBitmap.h

  bitmain.cpp
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
  mem
  stb
)
target_include_directories(bitmap PUBLIC
  $<BUILD_INTERFACE:
    ${PROJECT_SOURCE_DIR}/bitmap
  >
)
