set(HEADERS
  dmfcdllinit.h
  dmfcinputcommands.h
  dmfcinternal.h
  encryption.h)

set(CPPS
  dmfcbase.cpp
  dmfccfg.cpp
  dmfcclient.cpp
  dmfcfunctions.cpp
  dmfchudmessages.cpp
  dmfcinputcommand.cpp
  dmfcmenu.cpp
  dmfcpackets.cpp
  dmfcpinfo.cpp
  dmfcprecord.cpp
  dmfcremote.cpp
  dmfcserver.cpp
  dmfcstats.cpp
  dmfctimer.cpp
  dmfcui.cpp
  dmfcvirtual.cpp
  idmfc.cpp
  encryption.cpp
  dmfcinterface.cpp)

add_definitions(-DOUTRAGE_VERSION)

add_library(dmfc STATIC ${HEADERS} ${CPPS})


target_link_libraries(dmfc PRIVATE
  grtext
  module
  renderer
  bitmap
  networking
  physics
  model
  manage
  ddio
  dd_video
  2dlib
  $<$<PLATFORM_ID:Linux,Darwin>:
    linux
  >
  $<$<PLATFORM_ID:Windows>:
    win32
  >
)

target_include_directories(dmfc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
