/**
 * Interface header for the KVP storage. 
*/

#ifndef SERVER_INC_KVP_STORAGE_HPP
#define SERVER_INC_KVP_STORAGE_HPP

#include <string>
#include <stdexcept>
#include <map>

using namespace std;

/**
 * \brief KVP Storage class that implements the key value using the standard map 
 * data structure.
 * 
*/
template <class T_key, class T_value>
class KvpStorage {

    private:
    int m_lock;
    map<T_key, T_value> m_storage;
    string m_storage_name;

    public:
    KvpStorage(string storage_name);
    ~KvpStorage();

    T_value get(T_key key);
    void set(T_key key, T_value value);
    void del(T_key key);

    size_t size();
    void clear();
};



#endif //SERVER_INC_KVP_STORAGE_HPP