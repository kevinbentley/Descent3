set(HEADERS
  CFtp.h
  Chttpget.h
  inetgetfile.h)

set(CPPS
  CFtp.cpp
  Chttpget.cpp
  inetgetfile.cpp)

add_library(inetfile STATIC ${HEADERS} ${CPPS})

target_link_libraries(inetfile PRIVATE
  networking
)

target_include_directories(inetfile PUBLIC .)
