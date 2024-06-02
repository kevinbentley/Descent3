set(HEADERS)
set(CPPS
  mem.cpp)

add_library(mem STATIC ${HEADERS} ${CPPS})

target_include_directories(mem PUBLIC
  $<BUILD_INTERFACE:
    ${PROJECT_SOURCE_DIR}/mem
  >
)
