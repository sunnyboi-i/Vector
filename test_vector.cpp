#include <gtest/gtest.h>
#include <algorithm>
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
  Vector<int> vec{1, 2, 3};
  for (size_t i = 0; i < 100000; i++) {
    vec.push_back(i);
  }
  EXPECT_EQ(vec.size(), 100003);
  vec.clear();
  EXPECT_EQ(vec.size(), 0);
}

TEST(VectorTest, IteratorTraversal) {
  Vector<int> vec = {1, 2, 3, 4};
  int expected = 1;
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    EXPECT_EQ(*it, expected++);
  }
  EXPECT_EQ(expected, 5); // Ensure we visited all elements
}

TEST(VectorTest, ConstIteratorTraversal) {
  const Vector<int> vec = {1, 2, 3, 4};
  int expected = 1;
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    EXPECT_EQ(*it, expected++);
  }
  EXPECT_EQ(expected, 5);
}

TEST(VectorTest, IteratorRandomAccess) {
  Vector<int> vec = {10, 20, 30, 40, 50};
  auto it = vec.begin();
  it += 2;
  EXPECT_EQ(*it, 30);
  it -= 1;
  EXPECT_EQ(*it, 20);
  EXPECT_EQ(it[2], 40); // Random access with []
  auto it2 = it + 3;
  EXPECT_EQ(*it2, 50);
  EXPECT_EQ(it2 - it, 3); // Iterator difference
}

TEST(VectorTest, IteratorComparison) {
  Vector<int> vec = {1, 2, 3};
  auto it1 = vec.begin();
  auto it2 = vec.begin();
  EXPECT_TRUE(it1 == it2);
  EXPECT_FALSE(it1 != it2);
  ++it2;
  EXPECT_TRUE(it1 < it2);
  EXPECT_TRUE(it2 > it1);
  EXPECT_TRUE(it1 <= it2);
  EXPECT_TRUE(it2 >= it1);
}

TEST(VectorTest, EmptyVectorIterators) {
  Vector<int> vec;
  EXPECT_EQ(vec.begin(), vec.end());
}

TEST(VectorTest, IteratorWithSTLAlgorithmSort) {
  Vector<int> vec = {5, 2, 8, 1, 9};
  std::sort(vec.begin(), vec.end());
  Vector<int> expected = {1, 2, 5, 8, 9};
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec[i], expected[i]);
  }
}

TEST(VectorTest, IteratorWithSTLAlgorithmFind) {
  Vector<int> vec = {10, 20, 30, 40, 50};
  auto it = std::find(vec.begin(), vec.end(), 30);
  EXPECT_NE(it, vec.end());
  EXPECT_EQ(*it, 30);
  it = std::find(vec.begin(), vec.end(), 99);
  EXPECT_EQ(it, vec.end());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}