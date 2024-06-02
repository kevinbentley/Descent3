set(HEADERS unzip.h)
set(CPPS unzip.cpp)

add_library(unzip STATIC ${HEADERS} ${CPPS})

target_link_libraries(unzip ZLIB::ZLIB)

target_include_directories(unzip PUBLIC .)
