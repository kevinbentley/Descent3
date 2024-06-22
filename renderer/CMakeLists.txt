set(HEADERS
  3d.h
  dyna_gl.h
  HardwareInternal.h
  lnxscreenmode.h
  rend_d3d.h
  renderer.h
  rend_opengl.h
)
set(CPPS
  HardwareClipper.cpp
  HardwareDraw.cpp
  HardwareGlobalVars.cpp
  HardwareInstance.cpp
  HardwareOpenGL.cpp
  HardwareBaseGPU.cpp
  HardwarePoints.cpp
  HardwareSetup.cpp
  HardwareTransforms.cpp
)

if(UNIX)
  list(APPEND HEADERS lnxscreenmode.h)
  list(APPEND CPPS lnxscreenmode.cpp)
endif()

# These are excluded.
#opengl.cpp
#renderer.cpp
#Direct3D.cpp

add_library(renderer STATIC ${HEADERS} ${CPPS})
target_link_libraries(renderer PRIVATE
  bitmap
  ddio
  mem
  rtperformance
  module
  2dlib
  $<$<PLATFORM_ID:Linux,Darwin>:
    linux
  >
  $<$<PLATFORM_ID:Windows>:
    win32
  >
)

target_include_directories(renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
