set(HEADERS
  dyna_gl.h
  HardwareInternal.h
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
  set(CPPS ${CPPS} lnxscreenmode.cpp)
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
  misc
)
