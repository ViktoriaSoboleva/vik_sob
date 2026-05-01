#include <gtest/gtest.h>
#include "doubly_linked_list.hpp"

using biv::DoublyLinkedList;

TEST(DLLTest, InitialSizeIsZero) {
	DoublyLinkedList<int> l;
	EXPECT_EQ(l.get_size(), 0u);
}

TEST(DLLTest, PushBackIncreasesSize) {
	DoublyLinkedList<int> l;
	l.push_back(1);
	l.push_back(2);
	EXPECT_EQ(l.get_size(), 2u);
}

TEST(DLLTest, HasItem) {
	DoublyLinkedList<int> l;
	l.push_back(10);
	l.push_back(20);
	EXPECT_TRUE(l.has_item(10));
	EXPECT_TRUE(l.has_item(20));
	EXPECT_FALSE(l.has_item(99));
}

TEST(DLLTest, RemoveFirst) {
	DoublyLinkedList<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(1);
	bool ok = l.remove_first(1);
	EXPECT_TRUE(ok);
	EXPECT_EQ(l.get_size(), 2u);
	EXPECT_TRUE(l.has_item(1)); // второй экземпляр ещё есть
	EXPECT_TRUE(l.has_item(2));
}

TEST(DLLTest, RemoveAbsent) {
	DoublyLinkedList<int> l;
	l.push_back(1);
	bool ok = l.remove_first(99);
	EXPECT_FALSE(ok);
	EXPECT_EQ(l.get_size(), 1u);
}

TEST(DLLTest, RemoveOnlyElement) {
	DoublyLinkedList<int> l;
	l.push_back(42);
	bool ok = l.remove_first(42);
	EXPECT_TRUE(ok);
	EXPECT_EQ(l.get_size(), 0u);
	EXPECT_FALSE(l.has_item(42));
}

TEST(DLLTest, RemoveFromEnd) {
	DoublyLinkedList<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	bool ok = l.remove_first(3);
	EXPECT_TRUE(ok);
	EXPECT_EQ(l.get_size(), 2u);
}

TEST(DLLTest, ManyElements) {
	DoublyLinkedList<int> l;
	for (int i = 0; i < 100; ++i) {
		l.push_back(i);
	}
	EXPECT_EQ(l.get_size(), 100u);
	EXPECT_TRUE(l.has_item(99));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
