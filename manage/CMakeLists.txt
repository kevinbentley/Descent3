set(HEADERS
  doorpage.h
  gamefilepage.h
  genericpage.h
  megapage.h
  powerpage.h
  robotpage.h
  shippage.h
  soundpage.h
  texpage.h
  weaponpage.h)
set(CPPS
  doorpage.cpp
  gamefilepage.cpp
  generic.cpp
  manage.cpp
  megapage.cpp
  pagelock.cpp
  shippage.cpp
  soundpage.cpp
  texpage.cpp
  weaponpage.cpp)

add_library(manage STATIC ${HEADERS} ${CPPS})
target_link_libraries(manage PRIVATE
  cfile
  ddio
  mem
  sndlib
  stream_audio
)
