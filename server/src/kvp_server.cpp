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

#include "kvp_message.h"
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

void KvpServer::execute(size_t msg_size, KvpMessageSt_t *kvp_msg) {

    static KvpMessageSt_t a_message;
    pid_t pid = 0;
    uint32_t operation = 0;
    uint32_t key_size = 0;
    uint32_t value_size = 0;
    uint32_t msg_index = 0;
    

    // Check if message received contains the correct header information.
    if (msg_size == sizeof(KvpMessageSt_t)) {

        memcpy((void*)&pid, (void*)(&kvp_msg->msg_buf[msg_index]), sizeof(pid_t));
        msg_index += sizeof(pid_t);

        memcpy((void*)&operation, (void*)(&kvp_msg->msg_buf[msg_index]), sizeof(uint32_t));
        msg_index += sizeof(uint32_t);

        memcpy((void*)&key_size, (void*)(&kvp_msg->msg_buf[msg_index]), sizeof(uint32_t));
        msg_index += sizeof(uint32_t);

        memcpy((void*)&value_size, (void*)(&kvp_msg->msg_buf[msg_index]), sizeof(uint32_t));
        msg_index += sizeof(uint32_t);

        cout << pid << " " << operation << " " << key_size << " " << value_size << endl;

        string key(&kvp_msg->msg_buf[msg_index]);
        msg_index += key_size;
        msg_index ++;

        string value(&kvp_msg->msg_buf[msg_index]);

        switch (operation) {

            case KPV_MSG_OP_GET:
            {

            }
            break;

            case KPV_MSG_OP_SET:
            {
                cout << "SET" << " " << key << " " << value << endl;
                m_kvp_storage->set(key, value);
            }
            break;

            case KPV_MSG_OP_DELETE:
            {
                m_kvp_storage->del(key);
            }
            break;
        }
    }
}