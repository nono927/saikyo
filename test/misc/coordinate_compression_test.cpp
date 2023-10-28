#include "misc/coordinate_compression.hpp"

#include <gtest/gtest.h>

TEST(CoordinateCompressionTest, Init) {
    CoordinateCompression({3, 1, 4, 1, 5});
    ASSERT_DEATH(CoordinateCompression({}), "");
}

TEST(CoordinateCompressionTest, Decode) {
    CoordinateCompression cc({3, -1, 4, -1, 5});
    ASSERT_EQ(cc.size(), 4);
    EXPECT_EQ(cc.decode(0), -1);
    EXPECT_EQ(cc.decode(1), 3);
    EXPECT_EQ(cc.decode(2), 4);
    EXPECT_EQ(cc.decode(3), 5);
    EXPECT_DEATH(cc.decode(-1), "");
    EXPECT_DEATH(cc.decode(4), "");
}

TEST(CoordinateCompressionTest, DecodeVector) {
    CoordinateCompression cc({3, -1, 4, -1, 5});
    std::vector<long long> input = {1, 0, 3, 2, 1};
    std::vector<long long> actual = cc.decode(input);
    std::vector<long long> expect = {3, -1, 5, 4, 3};
    EXPECT_EQ(actual, expect);
}

TEST(CoordinateCompressionTest, Encode) {
    CoordinateCompression cc({-2, 7, 1, 8, -2, 8});
    EXPECT_EQ(cc.encode(-2), 0);
    EXPECT_EQ(cc.encode(1), 1);
    EXPECT_EQ(cc.encode(7), 2);
    EXPECT_EQ(cc.encode(8), 3);
    EXPECT_DEATH(cc.encode(0), "");
    EXPECT_DEATH(cc.encode(2), "");
}

TEST(CoordinateCompressionTest, EncodeVector) {
    CoordinateCompression cc({-2, 7, 1, 8, -2, 8});
    std::vector<long long> input = {7, 7, -2, 1, 8, 1};
    std::vector<long long> actual = cc.encode(input);
    std::vector<long long> expect = {2, 2, 0, 1, 3, 1};
    EXPECT_EQ(actual, expect);
}

TEST(CoordinateCompressionTest, Bound) {
    CoordinateCompression cc({-2, 7, 1, 8, -2, 8});
    EXPECT_EQ(cc.bound(-3), -1);
    EXPECT_EQ(cc.bound(-2), 0);
    EXPECT_EQ(cc.bound(0), 0);
    EXPECT_EQ(cc.bound(7), 2);
    EXPECT_EQ(cc.bound(8), 3);
    EXPECT_EQ(cc.bound(9), 3);
}
