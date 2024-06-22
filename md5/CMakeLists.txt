set(HEADERS md5.h)
set(CPPS
  md5.cpp)

set(PLATFORMCPPS)

add_library(md5 STATIC ${HEADERS} ${CPPS} ${PLATFORMCPPS})

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()

target_include_directories(md5 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


