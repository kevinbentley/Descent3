set(HEADERS)
set(CPPS
  error.cpp
  logfile.cpp
  log.cpp
  psglob.cpp
  psrand.cpp
  pstring.cpp)

add_library(misc STATIC ${HEADERS} ${CPPS})

target_link_libraries(misc PRIVATE
  ddebug
  ddio
  $<$<PLATFORM_ID:Linux,Darwin>:
    linux
  >
  $<$<PLATFORM_ID:Windows>:
    win32
  >
)

target_include_directories(misc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
