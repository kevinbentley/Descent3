set(HEADERS
  ddvid.h
  ddvidlib.h
)

set(CPPS
  $<$<PLATFORM_ID:Windows>:
    video_win32.cpp
    vidWin32FS.cpp
    vidWin32Win.cpp
  >
  $<$<PLATFORM_ID:Linux,Darwin>:
    video_lnx.cpp
  >
)

add_library(dd_video STATIC ${HEADERS} ${CPPS})
target_link_libraries(dd_video PRIVATE
  $<$<PLATFORM_ID:Linux,Darwin>:
    linux
  >
  $<$<PLATFORM_ID:Windows>:
    win32
  >
  ddio
  2dlib
)

target_include_directories(dd_video PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
