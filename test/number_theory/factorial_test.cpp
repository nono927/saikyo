#include "number_theory/factorial.hpp"

#include <gtest/gtest.h>

TEST(FactorialTest, Fact) {
    Factorial fact(4);
    EXPECT_EQ(fact.fact(0).val(), 1);
    EXPECT_EQ(fact.fact(1).val(), 1);
    EXPECT_EQ(fact.fact(2).val(), 2);
    EXPECT_EQ(fact.fact(3).val(), 6);
}

TEST(FactorialTest, InverseFact) {
    Factorial fact(4);
    EXPECT_EQ(fact.ifact(0).val(), 1);
    EXPECT_EQ(fact.ifact(1).val(), 1);
    EXPECT_EQ(fact.ifact(2).val(), 499122177);
    EXPECT_EQ(fact.ifact(3).val(), 166374059);
}

TEST(FactorialTest, Extend) {
    Factorial fact(4);
    EXPECT_EQ(fact.fact(10).val(), 3628800);
}

TEST(FactorialTest, Binom) {
    Factorial fact(6);
    EXPECT_EQ(fact.binom(5, 2).val(), 10);
}