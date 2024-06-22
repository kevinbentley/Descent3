set(HEADERS
  appconsole.h
  appdatabase.h
  application.h
  chrono_timer.h
  controller.h
  ddio_common.h
  ddio.h
  $<$<PLATFORM_ID:Darwin,Linux>: ddio_lnx.h>
  $<$<PLATFORM_ID:Windows>: ddio_win.h>
  forcefeedback.h
  joystick.h
)

set(CPPS
  chrono_timer.cpp
  ddio.cpp
  key.cpp
  $<$<PLATFORM_ID:Darwin,Linux>:
    lnxfile.cpp
    lnxforcefeedback.cpp
    lnxio.cpp
    lnxkey.cpp
    lnxkey_null.cpp
    lnxkey_sdl.cpp
    lnxmouse.cpp
    sdljoy.cpp
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
add_library(ddio STATIC ${HEADERS} ${CPPS})
target_link_libraries(ddio PRIVATE
  ddebug
  mem
  $<$<PLATFORM_ID:Linux,Darwin>:
    linux
  >
  $<$<PLATFORM_ID:Windows>:
    win32
  >
)

target_include_directories(ddio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
