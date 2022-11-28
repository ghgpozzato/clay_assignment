# Locate GTest
find_package(GTest REQUIRED)
find_package(Threads)

# Test Executables
add_executable(run_ut_kvp_storage test_kvp_storage.cpp)
target_link_libraries(run_ut_kvp_storage PRIVATE GTest::GTest KvpStorage)
add_test(run_ut_kvp_storage kvp_storage_test)

add_executable(run_ut_kvp_server test_kvp_server.cpp)
target_include_directories(run_ut_kvp_server PUBLIC ../common/inc)
target_link_libraries(run_ut_kvp_server PRIVATE GTest::GTest KvpServer)
add_test(run_ut_kvp_server kvp_server_test)


