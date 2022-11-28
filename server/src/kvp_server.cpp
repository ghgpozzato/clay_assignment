/**
 * Server application for the KVP Storage. 
 * 
 * Is responsible for the allocation of the KVP Storage and to handle the IPCs of
 * the clients.
*/
#include "kvp_server.hpp"

#include <iostream>
#include <cstring>
#include <errno.h>
#include <stdio.h>
#include <string>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "kvp_message.hpp"
#include "kvp_storage.hpp"

using namespace std;

KvpServer::KvpServer(string storage_name) {

    m_kvp_storage = new KvpStorage<string, string>(storage_name);

    int msgid;
  
    // Create unique server key
    m_server_key = ftok(storage_name.c_str(), 99);
  
    // Create unique IPC queue
    m_queue_id = msgget(m_server_key, 0666 | IPC_CREAT);
}

KvpServer::~KvpServer() {

    // Destroy message queue
    msgctl(m_queue_id, IPC_RMID, NULL);

    delete m_kvp_storage;
}

size_t KvpServer::receive(KvpMessageSt_t *kvp_msg){

    return msgrcv(m_queue_id, kvp_msg, sizeof(KvpMessageSt_t), 1, 0);
}

void KvpServer::respond(KvpMessageSt_t *kvp_msg){

    msgsnd(m_queue_id, kvp_msg, sizeof(KvpMessageSt_t), IPC_NOWAIT);
}

void KvpServer::execute(KvpMessageDataSt_t* kvp_data) {
    
    try{
        if ((kvp_data->key_size < KVP_MSG_MAX_KEY_SIZE) && 
            (kvp_data->value_size < KVP_MSG_MAX_VALUE_SIZE)) {

            switch (kvp_data->op) {

                case KVP_MSG_OP_GET:
                {
                    //Update value and value size;
                    kvp_data->value = m_kvp_storage->get(kvp_data->key);
                    kvp_data->value_size = kvp_data->value.size();

                    cout << kvp_data->pid << " " << "GET" << " " << kvp_data->key << " " << kvp_data->value << endl;
                }
                break;

                case KVP_MSG_OP_SET:
                {
                    cout << kvp_data->pid << " " << "SET" << " " << kvp_data->key << " " << kvp_data->value << endl;
                    m_kvp_storage->set(kvp_data->key, kvp_data->value);
                }
                break;

                case KVP_MSG_OP_DELETE:
                {
                    cout << kvp_data->pid << " " << "DELETE" << " " << kvp_data->key << endl;
                    m_kvp_storage->del(kvp_data->key);
                }
                break;
            }
        } else {
            throw invalid_argument("KVP Message has invalid size");
        }

        kvp_data->op = KVP_MSG_OP_OK;
    } catch(...) {
        kvp_data->op = KVP_MSG_OP_ERROR;
    }
}