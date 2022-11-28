/**
 * Interface header for the KVP Client
*/

#ifndef CLIENT_INC_KVP_CLIENT_HPP
#define CLIENT_INC_KVP_CLIENT_HPP

#include <string>

using namespace std;

class KvpClient {

    private:
    string m_storage_name;
    void send_msg(KvpMessageOperationEn_t op, string key, string value)

    public:
    KvpClient();
    ~KvpClient();

    void set(string key, string value);
    void get(string key);
    void del(string key);
};



#endif //CLIENT_INC_KVP_CLIENT_HPP