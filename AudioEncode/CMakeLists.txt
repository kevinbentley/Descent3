set(HEADERS
  audio_encode.h)
set(CPPS
  audio_encode.cpp)

add_library(AudioEncode STATIC ${HEADERS} ${CPPS})
target_link_libraries(AudioEncode PRIVATE libacm)

target_include_directories(AudioEncode PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
