set(HEADERS
  musicapi.h)
set(CPPS
  musicapi.cpp)

add_library(d3music STATIC ${HEADERS} ${CPPS})
target_link_libraries(d3music PRIVATE
  music
  stream_audio
  libacm
  sndlib
  manage
  bitmap
)

target_include_directories(d3music PUBLIC
  $<BUILD_INTERFACE:
    ${PROJECT_SOURCE_DIR}/d3music
  >
)
