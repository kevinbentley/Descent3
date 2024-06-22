set(HEADERS CZip.h)
set(CPPS
  BitIO.cpp
  CZip.cpp
  HuffmanAdapt.cpp
  HuffmanBasic.cpp)

add_library(czip STATIC ${HEADERS} ${CPPS})

target_include_directories(czip PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
