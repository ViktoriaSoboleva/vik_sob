#include <gtest/gtest.h>
#include "vector.hpp"

using biv::Vector;

TEST(VectorTest, InitialSizeIsZero) {
	Vector<int> v;
	EXPECT_EQ(v.get_size(), 0u);
}

TEST(VectorTest, PushBackIncreasesSize) {
	Vector<int> v;
	v.push_back(1);
	v.push_back(2);
	EXPECT_EQ(v.get_size(), 2u);
}

TEST(VectorTest, HasItem) {
	Vector<int> v;
	v.push_back(10);
	v.push_back(20);
	EXPECT_TRUE(v.has_item(10));
	EXPECT_TRUE(v.has_item(20));
	EXPECT_FALSE(v.has_item(99));
}

TEST(VectorTest, InsertAtBegin) {
	Vector<int> v;
	v.push_back(2);
	v.push_back(3);
	bool ok = v.insert(0, 1);
	EXPECT_TRUE(ok);
	EXPECT_EQ(v.get_size(), 3u);
	EXPECT_TRUE(v.has_item(1));
}

TEST(VectorTest, InsertInvalidPosition) {
	Vector<int> v;
	bool ok = v.insert(5, 42);
	EXPECT_FALSE(ok);
	EXPECT_EQ(v.get_size(), 0u);
}

TEST(VectorTest, RemoveFirst) {
	Vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(1);
	bool ok = v.remove_first(1);
	EXPECT_TRUE(ok);
	EXPECT_EQ(v.get_size(), 2u);
	EXPECT_TRUE(v.has_item(1)); // второй экземпляр ещё есть
	EXPECT_TRUE(v.has_item(2));
}

TEST(VectorTest, RemoveAbsent) {
	Vector<int> v;
	v.push_back(1);
	bool ok = v.remove_first(99);
	EXPECT_FALSE(ok);
	EXPECT_EQ(v.get_size(), 1u);
}

TEST(VectorTest, GrowBeyondInitialCapacity) {
	Vector<int> v;
	for (int i = 0; i < 100; ++i) {
		v.push_back(i);
	}
	EXPECT_EQ(v.get_size(), 100u);
	EXPECT_TRUE(v.has_item(99));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
