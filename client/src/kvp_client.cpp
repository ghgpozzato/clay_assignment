/**
 * Implementation of the KVP Cliente that will connect with the KVP Storage server
 * through ICP Message queues. 
*/

#include "kvp_client.hpp"

#include <cstring>
#include <stdio.h>
#include <stdint.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#include "kvp_message.h"

KvpClient::KvpClient(string storage_name) {
    m_storage_name = storage_name
}

KvpClient::~KvpClient() {
    
}

void KvpClient::set(string key, string value){
    this->send_msg(KPV_MSG_OP_SET, key, value);
}

void KvpClient::get(string key){
    this->send_msg(KPV_MSG_OP_GET, key, value);
}

void KvpClient::del(string key) {
    this->send_msg(KPV_MSG_OP_DELETE, key, value);
}

void KvpClient::send_msg(KvpMessageOperationEn_t op, string key, string value) {

    key_t key;
    int msgid;

    pid_t pid = getpid();
    uint32_t key_size = key.size();
    uint32_t value_size = value.size();
    uint32_t msg_index = 0;
    uint32_t op_value = (uint32_t)op;

    KvpMessageSt_t message;

    if ((key_size + 1 <= KVP_MSG_MAX_KEY_SIZE) &&
        (key_size > 0) && 
        (value_size + 1 <= KVP_MSG_MAX_VALUE_SIZE)) {
  
        // Create unique key for message
        key = ftok(m_storage_name.c_str(), 99);
    
        // Create queue
        msgid = msgget(key, 0666 | IPC_CREAT);
        message.msg_key = 1;

        //Put message together
        memcpy((void*)(&message.msg_buf[msg_index]), (void*)(pid_t), sizeof(pid_t));
        msg_index += sizeof(pid_t);

        memcpy((void*)(&message.msg_buf[msg_index]), (void*)(pid_t), sizeof(uint32_t));
        msg_index += sizeof(uint32_t);

        memcpy((void*)(&message.msg_buf[msg_index]), (void*)(pid_t), sizeof(uint32_t));
        msg_index += sizeof(uint32_t);

        // Copy key and value with null terminated character
        memcpy((void*)(&message.msg_buf[msg_index]), (void*)(key.c_str()), key_size + 1);
        msg_index += key_size + 1

        memcpy((void*)(&message.msg_buf[msg_index]), (void*)(value.c_str()), value_size + 1);
    
        // msgsnd to send message
        msgsnd(msgid, &message, sizeof(message), 0);
    
        // display the message
        printf("Data send is : %s \n", message.mesg_text);
}