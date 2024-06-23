set(HEADERS)
set(CPPS
  Collide.cpp
  FindIntersection.cpp
  newstyle_fi.cpp
  physics.cpp)

add_library(physics STATIC ${HEADERS} ${CPPS})
target_link_libraries(physics PRIVATE
  ddio
  mem
  sndlib
)
