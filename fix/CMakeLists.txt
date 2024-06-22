set(HEADERS
  fix.h)
set(CPPS
  fix.cpp)

add_library(fix STATIC ${HEADERS} ${CPPS})
target_include_directories(fix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
