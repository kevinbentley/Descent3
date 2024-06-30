set(CPPS
  error.cpp
  logfile.cpp
  log.cpp
  psglob.cpp
  psrand.cpp
  pstring.cpp
)

add_library(misc STATIC ${CPPS})
target_link_libraries(misc PRIVATE
  ddebug
  SDL2::SDL2
)
target_include_directories(misc PUBLIC
  $<BUILD_INTERFACE:
    ${PROJECT_SOURCE_DIR}/misc
  >
)

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
