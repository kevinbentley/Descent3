set(HEADERS
  ddgrWin32.h
  ddgrWin32DX.h
  ddgrWin32GDI.h)
set(CPPS
  ddgrWin32API.cpp
  ddgrWin32DX.cpp
  ddgrWin32GDI.cpp
  ddgrWin32Init.cpp)

add_library(dd_grwin32 STATIC ${HEADERS} ${CPPS})
target_link_libraries(dd_grwin32 PRIVATE
  misc
)
target_compile_definitions(dd_grwin32 PRIVATE DX_APP)
target_link_libraries(dd_grwin32 PRIVATE ${DDRAW_LIBRARY})
