set(HEADERS
  linux_fix.h
  lnxapp.h
  lnxcontroller.h
  registry.h
)

set(CPPS
  lnxcon.cpp
  lnxcon_raw.cpp
  lnxcontroller.cpp
  lnxapp.cpp
  lnxcon_null.cpp
  lnxdata.cpp
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
target_include_directories(linux PUBLIC
  $<BUILD_INTERFACE:
    ${PROJECT_SOURCE_DIR}/linux
  >
)

