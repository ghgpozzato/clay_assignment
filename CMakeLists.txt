cmake_minimum_required(VERSION 3.16)

project(KvpStorage LANGUAGES CXX)

enable_testing()

add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(common)
add_subdirectory(test)



