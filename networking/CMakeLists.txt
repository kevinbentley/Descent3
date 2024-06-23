set(HEADERS)
set(CPPS
  networking.cpp
  $<$<PLATFORM_ID:Windows>:
    directplay.cpp
  >
)

if(WIN32)
  set(PLATFORMCPPS "directplay.cpp")
  set(PLATFORM_LIBS ${DXGUID_LIBRARY})
endif()

add_library(networking STATIC ${HEADERS} ${CPPS} ${PLATFORMCPPS})
target_link_libraries(networking PRIVATE
  ddio mem ${PLATFORM_LIBS}
)
