set(HEADERS
  ddsndgeometry.h
  hlsoundlib.h
  sndrender.h
  soundload.h
  ssl_lib.h
  $<$<PLATFORM_ID:Windows>:
    auddev.h
    ds3dlib.h
    ds3dlib_internal.h
    eax2.h
    eax.h
    vmanpset.h
  >
  $<$<PLATFORM_ID:Darwin,Linux>:
    mixer.h
    sdlsound.h
  >
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
  networking
  bitmap
  renderer
  manage
  model
  physics
  2dlib
  stream_audio
  libacm
)

target_include_directories(sndlib PUBLIC
  $<BUILD_INTERFACE:
    ${PROJECT_SOURCE_DIR}/sndlib
  >
)
