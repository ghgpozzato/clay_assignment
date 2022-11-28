#include <gtest/gtest.h>

#include "kvp_storage.hpp"

#include <stdexcept>

// Basic test to assert a element is added. 
TEST(KvpStorageTest, testAddDataResultOk) {

    KvpStorage<string, string> kvp_storage("test/storage.dat");

    kvp_storage.set("K1", "V1");

    string value = kvp_storage.get("K1");

    EXPECT_EQ("V1", value);
    EXPECT_EQ(1, kvp_storage.size());

    // Empty map after operations
    kvp_storage.clear();
}

// Basic Test to assert element is deleted
TEST(KvpStorageTest, testEraseDataResultOk) {

    KvpStorage<string, string> kvp_storage("test/storage.dat");

    kvp_storage.set("K1", "V1");

    kvp_storage.del("K1");

    EXPECT_EQ(0, kvp_storage.size());

    // Empty map after operations
    kvp_storage.clear();
}

// Basic Test to assert map is cleared
TEST(KvpStorageTest, testClearDataResultOk) {

    KvpStorage<string, string> kvp_storage("test/storage.dat");

    kvp_storage.set("K1", "V1");
    kvp_storage.set("K2", "V2");

    EXPECT_EQ(2, kvp_storage.size());

    // Empty map after operations
    kvp_storage.clear();

    EXPECT_EQ(0, kvp_storage.size());
}

// Test Raise exception when key does not exist
TEST(KvpStorageTest, testKeyInvalidRaiseException) {

    KvpStorage<string, string> kvp_storage("test/storage.dat");

    EXPECT_THROW(kvp_storage.get("K1"), std::out_of_range);
}

// Test Persistance of the KVP Storage
TEST(KvpStorageTest, testPersistence) {

    KvpStorage<string, string> *kvp_storage = new KvpStorage<string, string>("test/storage.dat");

    kvp_storage->set("K1", "V1");

    delete kvp_storage;

    KvpStorage<string, string> *kvp_storage2 = new KvpStorage<string, string>("test/storage.dat");

    EXPECT_EQ(1, kvp_storage2->size());

    // Empty map after operations
    kvp_storage2->clear();

    delete kvp_storage2;
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}