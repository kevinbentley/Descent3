add_library(stb STATIC
		stb.cpp
		stb_image_write.h
)
target_include_directories(stb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
