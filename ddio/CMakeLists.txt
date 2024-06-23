set(CPPS
  chrono_timer.cpp
  ddio.cpp
  file.cpp
  key.cpp
  $<$<PLATFORM_ID:Darwin,Linux>:
    lnxfile.cpp
    lnxforcefeedback.cpp
    lnxio.cpp
    sdljoy.cpp
    lnxkey.cpp
    lnxkey_null.cpp
    lnxmouse.cpp
    lnxkey_sdl.cpp
  >
  $<$<PLATFORM_ID:Windows>:
    winfile.cpp
    winforcefeedback.cpp
    winio.cpp
    winjoy.cpp
    winkey.cpp
    winmouse.cpp
  >
)
add_library(ddio STATIC ${CPPS})
target_link_libraries(ddio PRIVATE
  ddebug
  mem
)
target_include_directories(ddio PUBLIC
  $<BUILD_INTERFACE:
  ${PROJECT_SOURCE_DIR}/ddio
  >
)
