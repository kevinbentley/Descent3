set(CPPS
  lnxdsound.cpp
  mveasm.cpp
  mvelibl.cpp
  platform.cpp

  # d2x implementation
  decoder8.c
  decoder16.c
  mve_audio.c
  mvelib.c
  mveplay.c
)

add_library(libmve STATIC ${CPPS})
target_link_libraries(libmve PRIVATE SDL2::SDL2)
target_include_directories(libmve PUBLIC
  $<BUILD_INTERFACE:
    ${PROJECT_SOURCE_DIR}/libmve
  >
)
