set(HEADERS
  auddev.h
  ddsndgeometry.h
  ds3dlib.h
  ds3dlib_internal.h
  eax2.h
  eax.h
  hlsoundlib.h
  mixer.h
  sdlsound.h
  sndrender.h
  soundload.h
  ssl_lib.h
  vmanpset.h
)

set(CPPS
  hlsoundlib.cpp
  sndrender.cpp
  soundload.cpp
  ddsoundload.cpp
  ssl_lib.cpp
  $<$<PLATFORM_ID:Windows>:
    ds3dlib.cpp
    ds3dgeometry.cpp
    dsound3d.cpp
    eax.cpp
  >
  $<$<PLATFORM_ID:Darwin,Linux>:
    mixer.cpp
    sdlgeometry.cpp
    sdlsound.cpp
  >
)

add_library(sndlib STATIC ${HEADERS} ${CPPS})
target_link_libraries(sndlib PRIVATE
  cfile
  ddio
  mem
  networking
  bitmap
  renderer
  manage
  model
  physics
  2dlib
  stream_audio
  libacm
  $<$<PLATFORM_ID:Windows>: win32 >
  $<$<PLATFORM_ID:Darwin,Linux>: linux >
)

target_include_directories(sndlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
