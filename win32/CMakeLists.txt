set(HEADERS
  winapp.h
  windatabase.h
  wincontroller.h
)

set(CPPS
  winapp.cpp
  wincon.cpp
  wincontroller.cpp
  windatabase.cpp
  wintask.cpp
)

add_library(win32 STATIC ${HEADERS} ${CPPS})
add_dependencies(win32 get_git_hash)

target_link_libraries(win32 PRIVATE
  ddio
  2dlib
  bitmap
  manage
  model
  renderer
  networking
)

target_include_directories(win32 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}/lib
)
