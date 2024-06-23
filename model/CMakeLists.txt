set(HEADERS)
set(CPPS
  newstyle.cpp
  polymodel.cpp)

add_library(model STATIC ${HEADERS} ${CPPS})
target_link_libraries(model PRIVATE
  ddio
  mem
)
