set(HEADERS)

set(CPPS
  CFtp.cpp
  Chttpget.cpp
  inetgetfile.cpp)

add_library(inetfile STATIC ${HEADERS} ${CPPS})
target_link_libraries(inetfile PRIVATE
  mem
)
