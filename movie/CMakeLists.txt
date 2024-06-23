set(HEADERS)
set(CPPS
  d3movie.cpp)

add_library(movie STATIC ${HEADERS} ${CPPS})
target_link_libraries(movie PRIVATE
  ddio
  libmve
  mem
)
