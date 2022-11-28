/**
 * Interface header for the KVP server. 
*/

#ifndef SERVER_INC_KVP_SERVER_HPP
#define SERVER_INC_KVP_SERVER_HPP

#include "kvp_storage.hpp"

#include "kvp_message.h"

#include "sys/ipc.h"

using namespace std;

class KvpServer {

    private:
    KvpStorage<string, string> *m_kvp_storage;
    key_t m_server_key;
    int m_queue_id;

    public:
    KvpServer(string storage_name);
    ~KvpServer();

    size_t receive(KvpMessageSt_t *kvp_msg);
    void execute(size_t msg_size, KvpMessageSt_t *kvp_msg);
};



#endif //SERVER_INC_KVP_SERVER_HPP