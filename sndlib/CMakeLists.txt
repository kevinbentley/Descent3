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

add_library(sndlib STATIC ${CPPS})
target_link_libraries(sndlib PRIVATE
  cfile
  ddio
  mem
  misc
  stream_audio
)
target_include_directories(sndlib PUBLIC
  $<BUILD_INTERFACE:
  ${PROJECT_SOURCE_DIR}/sndlib
  >
)
