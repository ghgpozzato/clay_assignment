/**
 * Main process of the KVP Storage server. 
 * 
 * Will instantiate a default server and wait for command through
 * the IPC message queue.
*/
#include <iostream>
#include <stdio.h>
#include <string>

#include "kvp_server.hpp"

#include "kvp_message.h"

using namespace std;

int main() {

    KvpMessageSt_t kvp_msg = {0};

    string kvp_path("data/kvp_default.dat");

    KvpServer kvp_server(kvp_path);

    while (true) {

        size_t num_bytes = kvp_server.receive(&kvp_msg);

        cout << num_bytes << endl;

        kvp_server.execute(num_bytes, &kvp_msg);
    }

    return 0;
}