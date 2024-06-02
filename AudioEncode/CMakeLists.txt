set(HEADERS
  audio_encode.h)
set(CPPS
  audio_encode.cpp)

add_library(AudioEncode STATIC ${HEADERS} ${CPPS})
target_link_libraries(AudioEncode libacm)

target_include_directories(AudioEncode PUBLIC
  $<BUILD_INTERFACE:
    ${PROJECT_SOURCE_DIR}/AudioEncode
  >
)
