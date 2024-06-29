set(HEADERS roboAnarchy.h roboanarchystr.h)
set(CPPS roboanarchy.cpp)

set(NETGAME_MODULE roboanarchy)

add_library(${NETGAME_MODULE} MODULE ${CPPS} ${HEADERS})
set_target_properties(${NETGAME_MODULE} PROPERTIES CXX_VISIBILITY_PRESET "hidden")
set_target_properties(${NETGAME_MODULE} PROPERTIES PREFIX "")
set_target_properties(${NETGAME_MODULE} PROPERTIES SUFFIX ".d3m")

target_link_libraries(${NETGAME_MODULE} PRIVATE
  dmfc
  misc
)
install(TARGETS "${NETGAME_MODULE}" DESTINATION ${CMAKE_INSTALL_LIBDIR}/netgames)
