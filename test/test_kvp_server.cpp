
#include <gtest/gtest.h>

#include "kvp_server.hpp"

TEST(KvpServerTest, testConstructor) {

    KvpServer a_kvp_server = KvpServer("test_kvp_server.dat");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}