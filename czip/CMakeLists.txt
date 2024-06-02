set(HEADERS CZip.h)
set(CPPS
  BitIO.cpp
  CZip.cpp
  HuffmanAdapt.cpp
  HuffmanBasic.cpp)

add_library(czip STATIC ${HEADERS} ${CPPS})

target_include_directories(czip PUBLIC
  $<BUILD_INTERFACE:
    ${PROJECT_SOURCE_DIR}/czip
  >
)
