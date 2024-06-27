add_executable(cfile_tests
  cfile_tests.cpp
)
target_link_libraries(cfile_tests PRIVATE
  GTest::gtest_main
  cfile
)
target_include_directories(cfile_tests PRIVATE ${PROJECT_SOURCE_DIR}/lib)

gtest_discover_tests(cfile_tests
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/cfile/tests
)
