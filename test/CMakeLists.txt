include(CTest)
enable_testing()

set(gtest_force_shared_crt ON)
find_package(GTest QUIET)
if(NOT GTest_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1)
  FetchContent_MakeAvailable(googletest)
endif()

add_executable(mpsc_test mpsc_test.cpp)

target_link_libraries(mpsc_test PRIVATE mpsc GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(mpsc_test)
