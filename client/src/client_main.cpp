/**
 * Main client application for the KVP Storage
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <filesystem>

#include "kvp_client.hpp"

using namespace std;

/**
 * \brief Main application of the client. Responsible for querying data from the
 * user and interacting with the KVP Server.
*/
int main(int argc, char** argv) {

    ifstream *file_input = NULL;

    filesystem::path curr_path = filesystem::current_path();

    // If a file is passed it will read input from it first before getting the user input.
    if (argc > 1) {
        curr_path /= string(argv[1]);
        cout << string(curr_path) << endl;
        file_input = new ifstream(argv[1]);
    }

    while (true) {

        string user_input;

        string cmd, key, value;

        if (file_input != NULL) {
            if(!getline(*file_input, user_input)) {
                getline(cin, user_input);
            }
        } else {
            getline(cin, user_input);
        }

        cout << user_input << endl;

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
