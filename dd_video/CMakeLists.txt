set(CPPS
    video_lnx.cpp
)

add_library(dd_video STATIC ${CPPS})
target_link_libraries(dd_video PRIVATE
  $<$<PLATFORM_ID:Linux,Darwin>:
    linux
  >
  $<$<PLATFORM_ID:Windows>:
    misc
  >
)
