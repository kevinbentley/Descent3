set(HEADERS
  debugbreak.h
  debug.h
  mono.h
)

set(CPPS
  debug.cpp
  $<$<PLATFORM_ID:Darwin,Linux>:
    lnxdebug.cpp
    lnxmono.cpp
  >
  $<$<PLATFORM_ID:Windows>:
    windebug.cpp
    winmono.cpp
  >
)

add_library(ddebug STATIC ${HEADERS} ${CPPS})
add_dependencies(ddebug get_git_hash)

target_link_libraries(ddebug PRIVATE
  networking
)
target_include_directories(ddebug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}/lib   # For d3_version.h
)
target_link_libraries(ddebug PRIVATE
  mem
)
