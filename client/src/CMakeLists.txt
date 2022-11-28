# KvpClient Library 
add_library(KvpClient SHARED kvp_client.cpp)
target_include_directories(KvpClient PUBLIC ../inc)
target_include_directories(KvpClient PUBLIC ../../common/inc)
target_link_libraries(KvpClient PRIVATE KvpMessage)

# Kvp Client Main
add_executable(ClientMain client_main.cpp)
target_include_directories(ClientMain PUBLIC ../inc)
target_include_directories(ClientMain PUBLIC ../../common/inc)
target_link_libraries(ClientMain PRIVATE KvpClient)
target_link_libraries(ClientMain PRIVATE KvpMessage)
