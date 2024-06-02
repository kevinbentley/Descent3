set(HEADERS HyperAnarchy.h hyperstr.h)
set(CPPS hyperanarchy.cpp)

set(NETGAME_MODULE hyperanarchy)

add_library(${NETGAME_MODULE} MODULE ${CPPS} ${HEADERS})
set_target_properties(${NETGAME_MODULE} PROPERTIES CXX_VISIBILITY_PRESET "hidden")
set_target_properties(${NETGAME_MODULE} PROPERTIES PREFIX "")
set_target_properties(${NETGAME_MODULE} PROPERTIES SUFFIX ".d3m")

target_link_libraries(${NETGAME_MODULE}
  dmfc
  grtext
  dd_video
  2dlib
  module
  renderer
  physics
  model
  manage
  bitmap
  networking
  ddio
)
install(TARGETS "${NETGAME_MODULE}" DESTINATION ${CMAKE_INSTALL_LIBDIR}/netgames)
