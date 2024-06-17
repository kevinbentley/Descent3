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
