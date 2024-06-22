set(HEADERS)
set(CPPS
  vector.cpp)

add_library(vecmat STATIC ${HEADERS} ${CPPS})
target_link_libraries(vecmat PRIVATE fix)

target_include_directories(vecmat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
