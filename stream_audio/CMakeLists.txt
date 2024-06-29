set(HEADERS)
set(CPPS
  osfarchive.cpp
  streamaudio.cpp)

add_library(stream_audio STATIC ${HEADERS} ${CPPS})
target_link_libraries(stream_audio PRIVATE
  ddio
  libacm
  mem
  misc
  sndlib
)
target_include_directories(stream_audio PUBLIC
  $<BUILD_INTERFACE:
  ${PROJECT_SOURCE_DIR}/stream_audio
  >
)
