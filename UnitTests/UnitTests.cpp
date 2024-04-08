#include "pch.h"
#include "CppUnitTest.h"
#include "../ChunkList/ChunkList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace fefu_laboratory_two;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:
		TEST_METHOD(DefaultConstuctorTest)
		{
			ChunkList<int, 3> list;
			Assert::AreEqual(list.get_size(), 0);
			Assert::IsTrue(list.empty() == true);
		}

		TEST_METHOD(ValueConstructorTest) {
			Allocator<int> allocator;
			ChunkList<int, 3> list(5, 4, allocator);
			Assert::AreEqual(5, list.get_size());
			for (int i = 0; i < 5; i++) {
				Assert::AreEqual(4, list[i]);
			}
		}

		TEST_METHOD(DefaultValueConstructorTest) {
			Allocator<int> allocator;
			ChunkList<int, 3> list(5, int(), allocator);
			Assert::AreEqual(5, list.get_size());
			for (int i = 0; i < 5; i++) {
				Assert::AreEqual(int(), list[i]);
			}
		}

		TEST_METHOD(CopyConstructorTest) {
			ChunkList<int, 3> first_list;
			for (int i = 0; i < 5; i++) {
				first_list.push_back(i);
			}
			auto second_list = first_list;
			for (int i = 0; i < 5; i++) {
				Assert::AreEqual(first_list[i], second_list[i]);
			}
			Assert::AreEqual(first_list.get_size(), second_list.get_size());
		}

		TEST_METHOD(CopyConstructorWithAllocatorTest) {
			Allocator<int> allocator;
			ChunkList<int, 3> first_list;
			for (int i = 0; i < 5; i++) {
				first_list.push_back(i);
			}
			ChunkList<int, 3> second_list(first_list, allocator);
			for (int i = 0; i < 5; i++) {
				Assert::AreEqual(first_list[i], second_list[i]);
			}
			Assert::AreEqual(first_list.get_size(), second_list.get_size());
		}

		TEST_METHOD(AssignTest) {
			Allocator<int> allocator;
			ChunkList<int, 3> list(5, 4, allocator);
			list.assign(3, 3);
			Assert::AreEqual(3, list.get_size());
			for (int i = 0; i < list.get_size(); i++) {
				Assert::AreEqual(3, list[i]);
			}
		}

		TEST_METHOD(AtTest) {
			ChunkList<int, 3> list;
			for (int i = 0; i < 5; i++) {
				list.push_back(i);
			}
			Assert::AreEqual(2, list.At(2));
			Assert::AreEqual(4, list.At(4));
		}

		TEST_METHOD(BracketsTest) {
			ChunkList<int, 3> list;
			for (int i = 0; i < 30; i++) {
				list.push_back(i);
			}
			for (int i = 0; i < 30; i++) {
				Assert::AreEqual(i, list[i]);
			}
		}

		TEST_METHOD(ClearTest) {
			ChunkList<int, 5> list;
			for (int i = 4; i < 42; i++) {
				list.push_back(i);
			}
			list.clear();
			Assert::IsTrue(list.empty() == true);
		}

		TEST_METHOD(FrontTest) {
			ChunkList<int, 5> list;
			for (int i = 4; i < 42; i++) {
				list.push_back(i);
			}
			Assert::AreEqual(4, list.front());
		}

		TEST_METHOD(BackTest) {
			ChunkList<int, 5> list;
			for (int i = 4; i < 42; i++) {
				list.push_back(i);
			}
			Assert::AreEqual(41, list.back());
		}

		TEST_METHOD(IteratorsTest) {
			ChunkList<int, 8> list;
			int* test_arr = new int[10];
			for (int i = 0; i < 10; i++) {
				list.push_back(i);
				test_arr[i] = i;
			}
			int j = 0;
			for (auto iter : list)
				Assert::IsTrue(test_arr[j++] == iter);
			auto it1 = list.begin();
			auto it2 = list.begin();
			Assert::IsTrue(it1 == it2);
			Assert::IsTrue(it1 >= it2);
			it2++;
			Assert::IsTrue(it2 > it1);
			it1 += 2;
			it2 -= 1;
			Assert::IsTrue(it1 > it2);
			auto it3 = list.back();
			Assert::AreEqual(9, it3);
		}

		TEST_METHOD(InsertTest) {
			ChunkList<int, 8> list;
			for (int i = 0; i < 10; i++)
				list.push_back(i);
			auto it = list.cbegin();
			it += 2;
			list.insert(it, 2);
			Assert::AreEqual(2, list[2]);
		}

		TEST_METHOD(PopBackTest) {
			ChunkList<int, 3> list;
			for (int i = 0; i < 10; i++)
				list.push_back(i);
			list.pop_back();
			Assert::AreEqual(8, list[list.get_size() - 1]);
		}
	};
}
