/**
 * Interface header for the KVP Client
*/

#ifndef CLIENT_INC_KVP_CLIENT_HPP
#define CLIENT_INC_KVP_CLIENT_HPP

#include <string>

#include "kvp_message.hpp"

using namespace std;

/**
 * \brief Responsible for providing the methods to interact with the KVP Server
*/
class KvpClient {

    private:
    string m_storage_name;
    string send_msg(KvpMessageOperationEn_t op, string key, string value);

    public:
    KvpClient(string storage_name);
    ~KvpClient();

    string set(string key, string value);
    string get(string key);
    string del(string key);
};



#endif //CLIENT_INC_KVP_CLIENT_HPP