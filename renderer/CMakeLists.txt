set(HEADERS
  HardwareInternal.h
  RendererConfig.h
  dyna_gl.h
  gl_local.h
  gl_mesh.h
  gl_shader.h
)
set(CPPS
  clipper.cpp
  draw.cpp
  gl.c
  gl_draw.cpp
  gl_framebuffer.cpp
  gl_image.cpp
  gl_init.cpp
  gl_main.cpp
  gl_mesh.cpp
  gl_shader.cpp
  gl_shadersource.cpp
  globalvars.cpp
  instance.cpp
  points.cpp
  setup.cpp
  transforms.cpp
  $<$<PLATFORM_ID:Windows>:
    wgl.c
  >
)

add_library(renderer STATIC ${HEADERS} ${CPPS})
target_link_libraries(renderer PRIVATE
  bitmap
  ddio
  mem
  misc
)
