/**
 * Definitions and data structures that are used in the communication
 * between server and client of KVP Storage.
*/

#ifndef COMMON_INCLUDE_KVP_MESSAGE_H
#define COMMON_INCLUDE_KVP_MESSAGE_H

#include <stdint.h>
#include <sys/msg.h>

/**
 * \brief Default queue channel used between Client and Server
*/

/**
 * \brief Maximum size of the KVP Key. Maximum size will be one less as it is a null terminated string.
*/
#define KVP_MSG_MAX_KEY_SIZE 256

/**
 * \brief Maximum size of the KVP Pair. Maximum size will be one less as it is a null terminated string.
*/
#define KVP_MSG_MAX_PAIR_SIZE 1024

/**
 * \brief Maximum size of the KVP Message
 * 
 * \note 
 * The message buffer will be created following the message protocol as:
 * 
 * | process PID | Operation | Num bytes Key | Num bytes Value | Key String  | Value String  | 
 * |     pid_t   | uint32_t  |    uint32     |      uint32     |     N chars |      M chars  |  
*/
#define KVP_MSG_HEADER (sizeof(pid_t) + 3 * sizeof(uint32_t))
#define KVP_MSG_MAX_SIZE (KVP_MSG_HEADER + KVP_MSG_MAX_KEY_SIZE + KVP_MSG_MAX_PAIR_SIZE)

/**
 * \brief Enumeration with the allowed operations
*/
typedef enum {
    KPV_MSG_OP_NONE = 0,
    KPV_MSG_OP_GET = 1,
    KPV_MSG_OP_SET = 2,
    KPV_MSG_OP_DELETE = 3,
} KvpMessageOperationEn_t;

/**
 * \brief Message format used when exchaging message from client to server
 * 
*/
typedef struct {
    __syscall_slong_t msg_key;
    char              msg_buf[KVP_MSG_MAX_SIZE];
} KvpMessageSt_t;

#endif //COMMON_INCLUDE_KVP_MESSAGE_H