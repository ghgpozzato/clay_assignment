/**
 * Implementation of the KVP Cliente that will connect with the KVP Storage server
 * through ICP Message queues. 
*/

#include "kvp_client.hpp"

#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#include "kvp_message.hpp"

KvpClient::KvpClient(string storage_name) {
    m_storage_name = storage_name;
}

KvpClient::~KvpClient() {
    
}

/**
 * \brief SET command
*/
string KvpClient::set(string key, string value){
    return this->send_msg(KVP_MSG_OP_SET, key, value);
}

/**
 * \brief GET command
*/
string KvpClient::get(string key){
    return this->send_msg(KVP_MSG_OP_GET, key, "");
}

/**
 * \brief DELETE command
*/
string KvpClient::del(string key) {
    return this->send_msg(KVP_MSG_OP_DELETE, key, "");
}

/**
 * \brief Private function responsible to setting the operation and sending it 
 * to the KVP Server.
*/
string KvpClient::send_msg(KvpMessageOperationEn_t op, string key, string value) {

    int msgid = 0;

    KvpMessageDataSt_t kvp_data = {0};

    KvpMessageSt_t message = {0};

    kvp_data.pid = getpid();
    kvp_data.op = op;
    kvp_data.key = key;
    kvp_data.key_size = key.size();
    kvp_data.value = value;
    kvp_data.value_size = value.size();

    kvp_data_to_buf(&kvp_data, &message);

    string result("");

    if ((kvp_data.key_size < KVP_MSG_MAX_KEY_SIZE) &&
        (kvp_data.key_size > 0) && 
        (kvp_data.value_size < KVP_MSG_MAX_VALUE_SIZE)) {
  
        // Create unique key for message
        key_t unique_key = ftok(m_storage_name.c_str(), 99);
    
        // Create queue
        msgid = msgget(unique_key, 0666 | IPC_CREAT);
        message.msg_key = 1;

        // Send msg to server
        msgsnd(msgid, &message, sizeof(KvpMessageSt_t), 0);

        // Wait for answer
        msgrcv(msgid, &message, sizeof(KvpMessageSt_t), kvp_data.pid, 0);
        
        // Convert to kvp data
        buf_to_kvp_data(&message, &kvp_data);

        if (kvp_data.op == KVP_MSG_OP_OK) {
            if (op == KVP_MSG_OP_GET) {
                result = string(kvp_data.value);
            } else {
                result = string("OK");
            }
        } else {
            result = string("");
        }
    } else {
        result = string("");
    }
    
    return result;
}