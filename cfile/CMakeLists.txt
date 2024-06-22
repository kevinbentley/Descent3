set(HEADERS
  cfile.h
  hogfile.h
  inffile.h
)

set(CPPS
  cfile.cpp
  hogfile.cpp
  inffile.cpp
)

add_library(cfile STATIC ${HEADERS} ${CPPS})
target_link_libraries(cfile PRIVATE
  ddio
  mem
  bitmap
)

target_include_directories(cfile PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
