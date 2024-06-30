if (HogMaker_DIR)
	find_package(HogMaker REQUIRED)
else()
	add_executable(
		HogMaker
		HogMaker/HogFormat.cpp
		HogMaker/HogMaker.cpp
	)
	export(TARGETS HogMaker FILE "${CMAKE_BINARY_DIR}/HogMakerConfig.cmake")
	add_dependencies(HogMaker get_git_hash)
	target_include_directories(HogMaker PRIVATE ${PROJECT_BINARY_DIR}/lib)
endif()
