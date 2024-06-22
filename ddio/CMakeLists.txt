set(CPPS
  chrono_timer.cpp
  ddio.cpp
  file.cpp
  key.cpp
  lnxforcefeedback.cpp
  lnxio.cpp
  sdljoy.cpp
  lnxkey.cpp
  lnxkey_null.cpp
  lnxmouse.cpp
  lnxkey_sdl.cpp
  $<$<PLATFORM_ID:Darwin,Linux,Android>:
    lnxfile.cpp
  >
  $<$<PLATFORM_ID:Windows>:
    winfile.cpp
  >
)
add_library(ddio STATIC ${CPPS})
target_link_libraries(ddio PRIVATE
  ddebug
  mem
  SDL2::SDL2
)
target_include_directories(ddio PUBLIC
  $<BUILD_INTERFACE:
  ${PROJECT_SOURCE_DIR}/ddio
  >
)
