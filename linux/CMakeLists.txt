set(HEADERS
  linux_fix.h
  lnxapp.h
  lnxcontroller.h
  lnxdatabase.h
  lnxdraw.h
  oelnx_os.h
  registry.h
)

set(CPPS
  lnxcon.cpp
  lnxcon_raw.cpp
  lnxcontroller.cpp
  lnxapp.cpp
  lnxcon_null.cpp
  lnxdatabase.cpp
  registry.cpp
)

add_library(linux STATIC ${HEADERS} ${CPPS})
target_link_libraries(linux PRIVATE
  cfile
  ddio
  networking
  renderer
  model
  manage
  2dlib
  bitmap
)
target_include_directories(linux PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

