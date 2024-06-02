set(HEADERS
  adecode.h
  aencode.h)

set(CPPS
  aencode.cpp
  adecode.cpp)

# these are the relevant source files from upstream libacm (https://github.com/markokr/libacm/)
set(LIB_SRC
  decode.c
  libacm.h)

add_library(libacm STATIC ${HEADERS} ${CPPS} ${LIB_SRC})

target_include_directories(libacm PUBLIC
  $<BUILD_INTERFACE:
    ${PROJECT_SOURCE_DIR}/libacm
  >
)
