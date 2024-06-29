set(HEADERS)
set(CPPS
  networking.cpp
  $<$<PLATFORM_ID:Windows>:
    directplay.cpp
  >
)

add_library(networking STATIC ${HEADERS} ${CPPS})
target_link_libraries(networking PRIVATE
  ddio
  mem
  misc
)
