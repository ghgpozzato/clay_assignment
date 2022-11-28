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
 * \brief Exit handler used to close the server when terminated by user.
*/
void exit_handler(int s){
    
    if (kvp_server != NULL) {
        delete kvp_server;
        kvp_server = NULL;
    }

    exit(s);
}

/**
 * \brief Server main application. Wait for IPC messages from clients and then handle them.
*/
int main() {

    KvpMessageSt_t kvp_msg = {0};
    KvpMessageDataSt_t kvp_data = {0};

    string kvp_path(KVP_DEFAULT_STORAGE_STR);

    kvp_server = new KvpServer(kvp_path);

    signal(SIGINT, exit_handler);

    try {
        while (true) {
            // Loop in the message queue
            kvp_server->receive(&kvp_msg);

            // Convert received IPC to data.
            buf_to_kvp_data(&kvp_msg, &kvp_data);

            // Process data.
            kvp_server->execute(&kvp_data);

            // Converted response data to IPC
            kvp_data_to_buf(&kvp_data, &kvp_msg);

            // Send IPC
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