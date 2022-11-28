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

#include "kvp_message.h"

KvpClient::KvpClient(string storage_name) {
    m_storage_name = storage_name;
}

KvpClient::~KvpClient() {
    
}

string KvpClient::set(string key, string value){
    return this->send_msg(KPV_MSG_OP_SET, key, value);
}

string KvpClient::get(string key){
    return this->send_msg(KPV_MSG_OP_GET, key, "");
}

string KvpClient::del(string key) {
    return this->send_msg(KPV_MSG_OP_DELETE, key, "");
}

string KvpClient::send_msg(KvpMessageOperationEn_t op, string key, string value) {

    int msgid;

    pid_t pid = getpid();
    uint32_t key_size = key.size();
    uint32_t value_size = value.size();
    uint32_t msg_index = 0;
    uint32_t op_value = (uint32_t)op;

    KvpMessageSt_t message;

    string result("");

    if ((key_size + 1 <= KVP_MSG_MAX_KEY_SIZE) &&
        (key_size > 0) && 
        (value_size + 1 <= KVP_MSG_MAX_VALUE_SIZE)) {
  
        // Create unique key for message
        key_t unique_key = ftok(m_storage_name.c_str(), 99);
    
        // Create queue
        msgid = msgget(unique_key, 0666 | IPC_CREAT);
        message.msg_key = 1;

        //Put message together
        memcpy((void*)(&message.msg_buf[msg_index]), (void*)(&pid), sizeof(pid_t));
        msg_index += sizeof(pid_t);

        memcpy((void*)(&message.msg_buf[msg_index]), (void*)(&op_value), sizeof(uint32_t));
        msg_index += sizeof(uint32_t);

        memcpy((void*)(&message.msg_buf[msg_index]), (void*)(&key_size), sizeof(uint32_t));
        msg_index += sizeof(uint32_t);

        memcpy((void*)(&message.msg_buf[msg_index]), (void*)(&value_size), sizeof(uint32_t));
        msg_index += sizeof(uint32_t);

        // Copy key and value with null terminated character
        memcpy((void*)(&message.msg_buf[msg_index]), (void*)(key.c_str()), key_size);
        msg_index += key_size;
        message.msg_buf[msg_index] = '\0';
        msg_index ++;

        memcpy((void*)(&message.msg_buf[msg_index]), (void*)(value.c_str()), value_size);
        msg_index += value_size;
        message.msg_buf[msg_index] = '\0';
        msg_index ++;

        cout << message.msg_buf << "\n";
    
        // msgsnd to send message
        msgsnd(msgid, &message, sizeof(message), 0);
    }
    
    return result;
}