# KvpClient Library 
add_library(KvpClient SHARED kvp_client.cpp)
target_include_directories(KvpClient PUBLIC ../inc)
target_include_directories(KvpClient PUBLIC ../../common/inc)

# # KvpServer Library
# add_library(KvpServer SHARED kvp_server.cpp kvp_storage.cpp)
# target_include_directories(KvpServer PUBLIC ../inc)
# target_include_directories(KvpServer PUBLIC ../../common/inc)

# Kvp Server Main
add_executable(ClientMain client_main.cpp)
target_include_directories(ClientMain PUBLIC ../inc)
target_include_directories(ClientMain PUBLIC ../../common/inc)
target_link_libraries(ClientMain PRIVATE KvpClient)
