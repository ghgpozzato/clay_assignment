/**
 * KVP Storage class implementation.
*/

#include "kvp_storage.hpp"

#include <map>

#include <errno.h>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <stdio.h>
#include <stdexcept>
#include <string>
#include <sys/file.h>
#include <unistd.h>

using namespace std;

/**
 * Class Constructor. 
 * 
 * \brief Create the instance of the KVP Storage. 
 * 
 * \param storage_name Path for the persistent storage in disk for the KVP Map
 * 
 * \note Only one instance of a unique Kvp Storage file can be instantiated at a time.
*/
template <class T_key, class T_value>
KvpStorage<T_key, T_value>::KvpStorage(string storage_name) {

    filesystem::path curr_path = filesystem::current_path();
    curr_path /= storage_name;

    m_storage_path = string(curr_path);

    cout << m_storage_path << endl;

    // Allow only one connection to the kvp storage file
    m_lock_path = m_storage_path + ".lock";

    int m_lock = open(m_lock_path.c_str(), O_CREAT | O_RDWR, 0666);
    int rc = flock(m_lock, LOCK_EX | LOCK_NB);
    if(rc) {
        if(EWOULDBLOCK == errno) {
            throw invalid_argument("KVP Storage already in use by another process.");
        }
    } else {
        // Read file data and populate map.
        ifstream kvp_storage_in(storage_name.c_str());

        // Do not allow keys / values that are empty
        if (kvp_storage_in.peek() != std::ifstream::traits_type::eof()) {
            while (true) {

                if (kvp_storage_in.eof()) {
                    break;
                } else {
                    T_key key;
                    T_value value;

                    kvp_storage_in >> key;
                    kvp_storage_in >> value;

                    if (key.size() != 0 && value.size() != 0) {
                        this->set(key, value);
                    }
                }
            }
        }
    }
};

/**
 * Class destructor.
 * 
 * \brief Release the KVP Storage and save it to file.
*/
template <class T_key, class T_value>
KvpStorage<T_key, T_value>::~KvpStorage(){

    ofstream ofs(m_storage_path.c_str(), ofstream::trunc);

    for (auto const& pair : m_storage) {
        ofs << pair.first << endl << pair.second << endl;
    }

    // Release file lock
    flock(m_lock, LOCK_UN);
    close(m_lock);
    remove(m_lock_path.c_str());
};

/**
 * \brief Get the value associated with a key
 * 
 * \param key Unique identifier in the KVP Map
 * 
 * \return Value associated with the key.
 * 
 * \throw Throw std::out_of_range exception in case the key does not exist.
*/
template <class T_key, class T_value>
T_value KvpStorage<T_key, T_value>::get(T_key key){
    
    if (m_storage.find(key) == m_storage.end()) {
        throw out_of_range("Invalid KVP key");
    }

    return m_storage[key];
}

/**
 * \brief Set a KVP key value pair
 * 
 * \param key Selected key
 * \param value Selected value
 * 
 * \note In case key exist value will be overwrite.
*/
template <class T_key, class T_value>
void KvpStorage<T_key, T_value>::set(T_key key, T_value value){
    m_storage[key] = value;
};

/**
 * \brief Delete a selected key 
 * 
 * \param key Selected key to be deleted. 
 * 
 * \throw Throw std::out_of_range exception in case the key does not exist.
*/
template <class T_key, class T_value>
void KvpStorage<T_key, T_value>::del(T_key key){

    if (m_storage.find(key) == m_storage.end()) {
        throw out_of_range("Invalid KVP key");
    }

    m_storage.erase(key);
}

/**
 * \brief Returns the size of the KVP storage.
*/
template <class T_key, class T_value>
size_t KvpStorage<T_key, T_value>::size(){
    return m_storage.size();
}

/** 
 * \brief Remove all the data from the KVP Storage.
*/
template <class T_key, class T_value>
void KvpStorage<T_key, T_value>::clear(){
    return m_storage.clear();
}

template class KvpStorage<string, string>;