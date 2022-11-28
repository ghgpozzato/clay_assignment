/**
 * Main process of the KVP Storage server. 
 * 
 * Will instantiate a default server and wait for command through
 * the IPC message queue.
*/
#include <iostream>
#include <stdio.h>
#include <string>
#include <signal.h>

#include "kvp_server.hpp"

#include "kvp_message.hpp"

using namespace std;

KvpServer *kvp_server = NULL;

/**
 * \brief Exit handler used to save server when terminated by user.
*/
void exit_handler(int s){
    
    if (kvp_server != NULL) {
        delete kvp_server;
        kvp_server = NULL;
    }

    exit(s);
}

int main() {

    KvpMessageSt_t kvp_msg = {0};
    KvpMessageDataSt_t kvp_data = {0};

    string kvp_path(KVP_DEFAULT_STORAGE_STR);

    kvp_server = new KvpServer(kvp_path);

    signal(SIGINT, exit_handler);

    try {
        while (true) {

            kvp_server->receive(&kvp_msg);

            buf_to_kvp_data(&kvp_msg, &kvp_data);

            kvp_server->execute(&kvp_data);

            kvp_data_to_buf(&kvp_data, &kvp_msg);

            kvp_server->respond(&kvp_msg);
        }
    } catch (...) {
        if (kvp_server != NULL) {
            delete kvp_server;
            kvp_server = NULL;
        }
    }

    return 0;
}