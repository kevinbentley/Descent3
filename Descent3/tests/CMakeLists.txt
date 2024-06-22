add_executable(
  porting-tests
  porting-tests.cpp
)

target_link_libraries(
  porting-tests
  GTest::gtest_main
  model
  manage
  physics
  bitmap
  module
  networking
  ddio
  2dlib
  $<$<PLATFORM_ID:Linux,Darwin>:
    linux
  >
  $<$<PLATFORM_ID:Windows>:
    win32
  >
)


gtest_discover_tests(porting-tests)
