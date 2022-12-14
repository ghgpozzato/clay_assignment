/**
 * Basic functions used to exchange message between servef and client.
*/
#include "kvp_message.hpp"

#include <cstring>

/**
 * \brief Convert a KVP Message received to kvp data structure to be used in the
 * server/client
 * 
 * \param kvp_msg Pointer to the kvp_msg data structure to be read.
 * \param kvp_data Pointer to the kvp_data data structure to be written.
*/
void buf_to_kvp_data(KvpMessageSt_t *kvp_msg, KvpMessageDataSt_t *kvp_data){

    uint32_t msg_index = 0;

    memcpy((void*)&kvp_data->pid, (void*)(&kvp_msg->msg_buf[msg_index]), sizeof(pid_t));
    msg_index += sizeof(pid_t);

    memcpy((void*)&kvp_data->op, (void*)(&kvp_msg->msg_buf[msg_index]), sizeof(uint32_t));
    msg_index += sizeof(uint32_t);

    memcpy((void*)&kvp_data->key_size, (void*)(&kvp_msg->msg_buf[msg_index]), sizeof(uint32_t));
    msg_index += sizeof(uint32_t);

    memcpy((void*)&kvp_data->value_size, (void*)(&kvp_msg->msg_buf[msg_index]), sizeof(uint32_t));
    msg_index += sizeof(uint32_t);

    kvp_data->key = string(&kvp_msg->msg_buf[msg_index]);
    kvp_data->key_size = kvp_data->key.size();

    msg_index += kvp_data->key_size;
    msg_index ++;

    kvp_data->value = string(&kvp_msg->msg_buf[msg_index]);
    kvp_data->value_size = kvp_data->value.size();
}

/**
 * \brief Convert a KVP Data received to the kvp message to be send
 * 
 * \param kvp_data Pointer to the kvp_data data structure to be read.
 * \param kvp_msg Pointer to the kvp_msg data structure to be written.
*/
void kvp_data_to_buf(KvpMessageDataSt_t *kvp_data, KvpMessageSt_t *kvp_msg){

    uint32_t msg_index = 0;

    //Put message together
    memcpy((void*)(&kvp_msg->msg_buf[msg_index]), (void*)(&kvp_data->pid), sizeof(pid_t));
    msg_index += sizeof(pid_t);

    memcpy((void*)(&kvp_msg->msg_buf[msg_index]), (void*)(&kvp_data->op), sizeof(uint32_t));
    msg_index += sizeof(uint32_t);

    memcpy((void*)(&kvp_msg->msg_buf[msg_index]), (void*)(&kvp_data->key_size), sizeof(uint32_t));
    msg_index += sizeof(uint32_t);

    memcpy((void*)(&kvp_msg->msg_buf[msg_index]), (void*)(&kvp_data->value_size), sizeof(uint32_t));
    msg_index += sizeof(uint32_t);

    // Copy key and value with null terminated character
    memcpy((void*)(&kvp_msg->msg_buf[msg_index]), (void*)(kvp_data->key.c_str()), kvp_data->key_size);
    msg_index += kvp_data->key_size;
    kvp_msg->msg_buf[msg_index] = '\0';
    msg_index++;

    memcpy((void*)(&kvp_msg->msg_buf[msg_index]), (void*)(kvp_data->value.c_str()), kvp_data->value_size);
    msg_index += kvp_data->value_size;
    kvp_msg->msg_buf[msg_index] = '\0';
    msg_index++;

    kvp_msg->msg_key = kvp_data->pid;
}