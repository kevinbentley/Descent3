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
  bitmap
)

target_include_directories(cfile PUBLIC
  $<BUILD_INTERFACE:
    ${PROJECT_SOURCE_DIR}/cfile
  >
)
