set(HEADERS grtextlib.h)
set(CPPS
  grfont.cpp
  grtext.cpp
  textaux.cpp)

add_library(grtext STATIC ${HEADERS} ${CPPS})
target_link_libraries(grtext PRIVATE
  ddio
  mem
  misc
)
