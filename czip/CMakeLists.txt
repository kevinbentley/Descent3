set(HEADERS)
set(CPPS
  BitIO.cpp
  CZip.cpp
  HuffmanAdapt.cpp
  HuffmanBasic.cpp)

add_library(czip STATIC ${HEADERS} ${CPPS})
target_link_libraries(czip PRIVATE
  misc
)
