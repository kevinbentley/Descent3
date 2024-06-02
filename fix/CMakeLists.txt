set(HEADERS
  fix.h)
set(CPPS
  fix.cpp)

add_library(fix STATIC ${HEADERS} ${CPPS})
target_include_directories(fix PUBLIC
  $<BUILD_INTERFACE:
    ${PROJECT_SOURCE_DIR}/fix
  >
)
