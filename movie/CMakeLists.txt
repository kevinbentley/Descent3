set(HEADERS
  movie.h)
set(CPPS
  movie.cpp)

add_library(movie STATIC ${HEADERS} ${CPPS})
target_link_libraries(movie PRIVATE
  ddio
  libmve
  renderer
  grtext
  bitmap
  model
  manage
  dd_video
  2dlib
)

target_include_directories(movie PUBLIC
  $<BUILD_INTERFACE:
    ${PROJECT_SOURCE_DIR}/movie
  >
)

