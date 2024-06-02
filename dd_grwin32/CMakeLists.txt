set(HEADERS
  ddgrWin32.h
  ddgrWin32DX.h
  ddgrWin32GDI.h)
set(CPPS
  ddgrWin32API.cpp
  ddgrWin32DX.cpp
  ddgrWin32GDI.cpp
  ddgrWin32Init.cpp)

add_library(dd_grwin32 STATIC ${HEADERS} ${CPPS})

target_link_libraries(dd_grwin32
  ddio
  2dlib
  $<$<PLATFORM_ID:Linux,Darwin>:
    linux
  >
  $<$<PLATFORM_ID:Windows>:
    win32
  >
)


target_include_directories(dd_grwin32 PUBLIC .)
