# clay_assignment

## Environment used: 
ubuntu 22.10
git 2.37.2
gcc 12.2.0
libgtest-dev 1.11.0
cmake 3.24.2

## Building Project 
The project was build using cmake. The following commands will build the whole project and test cases. Go to the root of the project.
% ./build_kvp

## Implementation remarks
The assignment was implemented using a server/client communication using IPC calls from standard C libraries. A common message is exchanged between server and client using the client PID as a unique identifier. The server is locked when deployed to prevent race conditions when writing it to disk. 

Because of limited time the KVPStorage was implemented using standard map. Boost library or a database could be used to allow better load management.

## Executing Unit tests
Basic unit tests were were and can be executed from the build folder. 
% ./run_ut

## Executing Integration/Manual tests
To ensure integration was working properly, integration test cases using input files were created. This is done with the following command
% ./KVPStorageServer_fin F_IN

F_IN has a list of commands.
A few test cases can be found in test/data. To confirm the success of the execution the storage was left readable. It can be found in the root folder "kvp_default.dat"

To ensure multiple clients the client can be executed without the server. This way multiple clients will wait for the server to be avaialble. When the server is available it will handle all the requests.

## Executing KVPStorage
To execute the KVPStorage:

Initiate the server
% ./KVPStorageServer

Intiate the client
% ./KVPStorage

## TBD 
Unit tests could be improved. I was able to set the framework and it can be extended with more time. It is also integrated with cmake.
KVPStorage to use a database
Use of boost library for serialization.

