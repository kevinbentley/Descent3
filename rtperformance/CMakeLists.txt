set(HEADERS
  rtperformance.h)
set(CPPS
  rtperformance.cpp)

add_library(rtperformance STATIC ${HEADERS} ${CPPS})
target_link_libraries(rtperformance PRIVATE
  ddio
  bitmap
  manage
)


target_include_directories(rtperformance PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

