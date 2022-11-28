/**
 * Main client application for the KVP Storage
*/
#include <iostream>
#include <sstream>
#include <iomanip>

#include "kvp_client.hpp"

using namespace std;

int main() {

    while (true) {

        string user_input;

        string cmd, key, value;

        getline(cin, user_input);

        stringstream user_input_ss(user_input);

        user_input_ss >> cmd;

        string result("");

        if (cmd == "GET") {
            user_input_ss >> quoted(key);

            result = KvpClient(KVP_DEFAULT_STORAGE_STR).get(key);

            //cout << cmd << " " << key << " " << result << endl;
        } else if (cmd == "SET") {
            user_input_ss >> quoted(key);
            user_input_ss >> quoted(value);

            result = KvpClient(KVP_DEFAULT_STORAGE_STR).set(key, value);

            //cout << cmd << " " << key << " " << value << endl;
        } else if (cmd == "DELETE") {
            user_input_ss >> quoted(key);

            result = KvpClient(KVP_DEFAULT_STORAGE_STR).del(key);

            //cout << cmd << " " << key << endl;
        }
        cout << result << endl;
    }
}
