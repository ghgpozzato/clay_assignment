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

        if (cmd == "GET") {
            user_input_ss >> quoted(key);

            string result;
            try {
                result = KvpClient(KVP_DEFAULT_STORAGE_STR).get(key);
            } catch (...) {
                cout << "ERROR" << endl;
            }

            cout << cmd << " " << key << " " << result << endl;
        } else if (cmd == "SET") {
            user_input_ss >> quoted(key);
            user_input_ss >> quoted(value);

            try {
                KvpClient(KVP_DEFAULT_STORAGE_STR).set(key, value);
                cout << "OK" << endl;
            } catch (...) {
                cout << "ERROR" << endl;
            }

            cout << cmd << " " << key << " " << value << endl;
        } else if (cmd == "DELETE") {
            user_input_ss >> quoted(key);

            try {
                KvpClient(KVP_DEFAULT_STORAGE_STR).del(key);
                cout << "OK" << endl;
            } catch (...) {
                cout << "ERROR" << endl;
            }

            cout << cmd << " " << key << endl;
        }

    }
}
