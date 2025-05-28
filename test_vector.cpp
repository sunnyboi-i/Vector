#include <gtest/gtest.h>
#include "vector.hpp"

TEST(VectorTest, DefaultConstructor) {
  Vector<int> vec;
  EXPECT_TRUE(vec.empty());
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 0);
}

TEST(VectorTest, InitializerListConstructor) {
  Vector<int> vec = {1, 2, 3};
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[2], 3);
}

TEST(VectorTest, CopyConstructor) {
  Vector<int> original = {4, 5, 6};
  Vector<int> copy = original;
  EXPECT_EQ(copy.size(), original.size());
  EXPECT_EQ(copy[1], 5);
}

TEST(VectorTest, MoveConstructor) {
  Vector<int> source = {7, 8, 9};
  Vector<int> moved = std::move(source);
  EXPECT_EQ(moved.size(), 3);
  EXPECT_EQ(moved[2], 9);
  EXPECT_EQ(source.size(), 0);
}

TEST(VectorTest, PushBackAndPopBack) {
  Vector<int> vec;
  vec.push_back(10);
  vec.push_back(20);
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec.back(), 20);
  vec.pop_back();
  EXPECT_EQ(vec.size(), 1);
  EXPECT_EQ(vec.back(), 10);
}

TEST(VectorTest, ResizeAndReserve) {
  Vector<int> vec(2, 1);
  vec.reserve(10);
  EXPECT_GE(vec.capacity(), 10);
  vec.resize(5, 2);
  EXPECT_EQ(vec.size(), 5);
  EXPECT_EQ(vec[4], 2);
  vec.resize(0);
  EXPECT_EQ(vec.size(), 0);
}

TEST(VectorTest, Looping) {
  Vector<int> vec{1,2,3};
  for (size_t i = 0; i < 100000; i++) {
    vec.push_back(i);
  }
  EXPECT_EQ(vec.size(), 100003);
  vec.clear();
  EXPECT_EQ(vec.size(), 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}