set(HEADERS
  music.h
  musiclib.h)

set(CPPS
  omflex.cpp
  sequencer.cpp
  streamer.cpp
  tracklist.cpp)

add_library(music STATIC ${HEADERS} ${CPPS})
target_link_libraries(music PRIVATE
  cfile
  ddio
  mem
  sndlib
  stream_audio
  libacm
  manage
  bitmap
)

target_include_directories(music PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
