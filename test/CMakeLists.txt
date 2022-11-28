include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

# Test Executables
add_executable(run_ut_kvp_storage test_kvp_storage.cpp)
target_link_libraries(run_ut_kvp_storage PRIVATE GTest::GTest KvpStorage)
# add_test(run_ut_kvp_storage_gtest run_ut_kvp_storage)

add_executable(run_ut_kvp_server test_kvp_server.cpp)
target_include_directories(run_ut_kvp_server PUBLIC ../common/inc)
target_link_libraries(run_ut_kvp_server PRIVATE GTest::GTest KvpServer)
# add_test(run_ut_kvp_server_gtest run_ut_kvp_server)

include(GoogleTest)
gtest_discover_tests(run_ut_kvp_server)
gtest_discover_tests(run_ut_kvp_storage)