# KvpStorage Library 
add_library(KvpStorage SHARED kvp_storage.cpp)
target_include_directories(KvpStorage PUBLIC ../inc)

# KvpServer Library
add_library(KvpServer SHARED kvp_server.cpp kvp_storage.cpp)
target_include_directories(KvpServer PUBLIC ../inc)
target_include_directories(KvpServer PUBLIC ../../common/inc)
target_link_libraries(KvpServer PRIVATE KvpMessage)

# Kvp Server Main
add_executable(ServerMain server_main.cpp)
target_include_directories(ServerMain PUBLIC ../inc)
target_include_directories(ServerMain PUBLIC ../../common/inc)
target_link_libraries(ServerMain PRIVATE KvpServer KvpMessage)
