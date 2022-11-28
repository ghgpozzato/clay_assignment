# clay_assignment

## Environment used: 
ubuntu 22.10
git 2.37.2
gcc 12.2.0
libgtest-dev 1.12.1-0.2
cmake 3.24.2

## To execute the gtest test cases symlink libgtest.a and libgtest_main.a to your /usr/lib folder

# The project was build using cmake. The following commands will build the whole project and test cases. Go to the root of the project.
% cmake CMakeLists.txt
% make

# The assignment was implemented using a server/client communication using IPC calls from standard C libraries. A common message is exchanged between server and client using the client PID as a unique identifier. The server is locked when deployed to prevent race conditions when writing it to disk. 

# Because of limited time the KVPStorage was implemented using standard map. Boost library or a database could be used to allow better load management.

# Basic unit tests were were created. The executables are stored in the test folder.

# To execute the KVPStorage:

# Initiate the server
% ./KVPStorageServer

# Intiate the client
% ./KVPStorage


