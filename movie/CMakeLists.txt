set(HEADERS
  movie.h)
set(CPPS
  movie.cpp)

add_library(movie STATIC ${HEADERS} ${CPPS})
target_link_libraries(movie PRIVATE
  ddio
  libmve
  mem
  renderer
  grtext
  bitmap
  model
  manage
  dd_video
  2dlib
  $<$<PLATFORM_ID:Linux,Darwin>: linux >
  $<$<PLATFORM_ID:Windows>: win32 >
)

target_include_directories(movie PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

