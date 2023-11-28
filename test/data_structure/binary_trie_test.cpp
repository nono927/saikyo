#include "data_structure/binary_trie.hpp"

#include <gtest/gtest.h>

TEST(BinaryTrieTest, Empty) {
    BinaryTrie target;
    EXPECT_EQ(target.size(), 0);
    EXPECT_FALSE(target.contains(0));
    EXPECT_FALSE(target.contains(100));
}

TEST(BinaryTrieTest, InsertOne) {
    BinaryTrie target;
    target.insert(100);
    EXPECT_EQ(target.size(), 1);
    EXPECT_FALSE(target.contains(0));
    EXPECT_TRUE(target.contains(100));
}

TEST(BinaryTrieTest, InsertSameValues) {
    BinaryTrie target;
    target.insert(100);
    target.insert(100);
    target.insert(100);
    EXPECT_EQ(target.size(), 3);
    EXPECT_EQ(target.count(100), 3);
}

TEST(BinaryTrieTest, InsertNegative) {
    BinaryTrie target;
    EXPECT_DEATH(target.insert(-1), "");
}

TEST(BinaryTrieTest, Erase) {
    BinaryTrie target;

    target.insert(100);
    target.insert(200);
    EXPECT_EQ(target.size(), 2);
    EXPECT_TRUE(target.contains(100));
    EXPECT_TRUE(target.contains(200));
    EXPECT_DEATH(target.erase(0), "");

    target.erase(100);
    EXPECT_EQ(target.size(), 1);
    EXPECT_FALSE(target.contains(100));
    EXPECT_TRUE(target.contains(200));
    EXPECT_DEATH(target.erase(100), "");
}

TEST(BinaryTrieTest, LowerUpperBound) {
    BinaryTrie target;
    target.insert(333);
    target.insert(111);
    target.insert(444);
    target.insert(111);
    target.insert(555);

    EXPECT_EQ(target.lower_bound(100), 111);
    EXPECT_EQ(target.upper_bound(100), 111);
    EXPECT_EQ(target.lower_bound(333), 333);
    EXPECT_EQ(target.upper_bound(333), 444);
    EXPECT_EQ(target.lower_bound(600), -1);
    EXPECT_EQ(target.upper_bound(600), -1);
}

TEST(BinaryTrieTest, MinMax) {
    BinaryTrie target;
    target.insert(333);
    target.insert(111);
    target.insert(444);
    target.insert(111);
    target.insert(555);

    EXPECT_EQ(target.min_element(), 111);
    EXPECT_EQ(target.max_element(), 555);
}

TEST(BinaryTrieTest, KthElement) {
    BinaryTrie target;
    target.insert(3'333'333'333'333'333'333LL);
    target.insert(1'111'111'111'111'111'111LL);
    target.insert(4'444'444'444'444'444'444LL);
    target.insert(1'111'111'111'111'111'111LL);
    target.insert(5'555'555'555'555'555'555LL);

    EXPECT_EQ(target.kth_element(0), 1'111'111'111'111'111'111LL);
    EXPECT_EQ(target.kth_element(1), 1'111'111'111'111'111'111LL);
    EXPECT_EQ(target.kth_element(2), 3'333'333'333'333'333'333LL);
    EXPECT_EQ(target.kth_element(3), 4'444'444'444'444'444'444LL);
    EXPECT_EQ(target.kth_element(4), 5'555'555'555'555'555'555LL);
    EXPECT_DEATH(target.kth_element(-1), "");
    EXPECT_DEATH(target.kth_element(5), "");
}

TEST(BinaryTrieTest, XorCount) {
    BinaryTrie target;
    target.insert(1);
    target.insert(1);
    target.insert(5);
    target.xor_all(3);

    EXPECT_EQ(target.count(1), 0);
    EXPECT_EQ(target.count(2), 2);
    EXPECT_EQ(target.count(5), 0);
    EXPECT_EQ(target.count(6), 1);
}

TEST(BinaryTrieTest, XorInsert) {
    BinaryTrie target;
    target.insert(1);
    target.xor_all(3);
    target.insert(1);
    target.insert(5);

    EXPECT_EQ(target.count(1), 1);
    EXPECT_EQ(target.count(2), 1);
    EXPECT_EQ(target.count(5), 1);
    EXPECT_EQ(target.count(6), 0);
}

TEST(BinaryTrieTest, XorErase) {
    BinaryTrie target;
    target.insert(1);
    target.xor_all(3);
    target.insert(1);
    target.insert(5);
    target.erase(1);

    EXPECT_EQ(target.count(1), 0);
    EXPECT_EQ(target.count(2), 1);
    EXPECT_EQ(target.count(5), 1);
    EXPECT_EQ(target.count(6), 0);
}

TEST(BinaryTrieTest, XorLowerUpperBound) {
    BinaryTrie target;
    target.insert(333);  // 333 xor 321 = 12
    target.insert(111);  // 111 xor 321 = 302
    target.insert(444);  // 444 xor 321 = 253
    target.insert(111);
    target.insert(555);  // 555 xor 321 = 874
    target.xor_all(321);

    EXPECT_EQ(target.lower_bound(100), 253);
    EXPECT_EQ(target.upper_bound(100), 253);
    EXPECT_EQ(target.lower_bound(302), 302);
    EXPECT_EQ(target.upper_bound(302), 874);
    EXPECT_EQ(target.lower_bound(875), -1);
    EXPECT_EQ(target.upper_bound(875), -1);
}

TEST(BinaryTrieTest, XorMinMax) {
    BinaryTrie target;
    target.insert(333);  // 333 xor 321 = 12
    target.insert(111);  // 111 xor 321 = 302
    target.insert(444);  // 444 xor 321 = 253
    target.insert(111);
    target.insert(555);  // 555 xor 321 = 874
    target.xor_all(321);

    EXPECT_EQ(target.min_element(), 12);
    EXPECT_EQ(target.max_element(), 874);
}

TEST(BinaryTrieTest, XorKthElement) {
    BinaryTrie target;
    target.insert(333);  // 333 xor 321 = 12
    target.insert(111);  // 111 xor 321 = 302
    target.insert(444);  // 444 xor 321 = 253
    target.insert(111);
    target.insert(555);  // 555 xor 321 = 874
    target.xor_all(321);

    EXPECT_EQ(target.kth_element(0), 12);
    EXPECT_EQ(target.kth_element(1), 253);
    EXPECT_EQ(target.kth_element(2), 302);
    EXPECT_EQ(target.kth_element(3), 302);
    EXPECT_EQ(target.kth_element(4), 874);
    EXPECT_DEATH(target.kth_element(-1), "");
    EXPECT_DEATH(target.kth_element(5), "");
}