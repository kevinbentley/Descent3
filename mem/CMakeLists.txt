set(CPPS
  mem.cpp
)

add_library(mem STATIC ${CPPS})
target_compile_definitions(mem PUBLIC
  $<$<BOOL:${ENABLE_MEM_RTL}>:MEM_USE_RTL>
)
target_include_directories(mem PUBLIC
  $<BUILD_INTERFACE:
    ${PROJECT_SOURCE_DIR}/mem
  >
)
