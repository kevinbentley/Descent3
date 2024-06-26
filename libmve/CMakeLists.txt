set(HEADERS
  mvegfx.h
  mvelibi.h
  mvelibl.h
  platform.h
  snd8to16.h
  SystemInterfaces.h)

set(CPPS
  mveasm.cpp
  mvelibl.cpp
  platform.cpp
  lnxdsound.cpp)

add_library(libmve STATIC ${HEADERS} ${CPPS} ${PLATFORM_CPPS})
target_link_libraries(libmve PRIVATE SDL2::SDL2)
