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
  platform.cpp)

set(PLATFORM_CPPS)

if(UNIX)
  set(PLATFORM_CPPS "lnxdsound.cpp")
endif()

add_library(libmve STATIC ${HEADERS} ${CPPS} ${PLATFORM_CPPS})

target_include_directories(libmve PUBLIC
  $<BUILD_INTERFACE:
    ${PROJECT_SOURCE_DIR}/libmve
  >
)
