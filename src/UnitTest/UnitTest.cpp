#include "pch.h"
#include <chrono>
#include <random>
#include "CppUnitTest.h"
#include "../include/lib_func.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(基本確認)
	{
	public:
		_CrtMemState sStartMemState;
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#ifdef _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif
		}
		TEST_METHOD_CLEANUP(Cleanup)
		{
#ifdef _DEBUG
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}

	public:

		TEST_METHOD(一要素はそのまま)
		{
			item items[1] = { {1, "Hello world!"} };
			Assert::IsTrue(radix_sort(items, items + sizeof(items) / sizeof(item)));
			Assert::AreEqual("Hello world!", items[0].value);

		}

		TEST_METHOD(２要素でそのまま)
		{
			item items[2] ={
				{2, "Hello"},
				{4, "world!"},
			};
			Assert::IsTrue(radix_sort(items, items + sizeof(items) / sizeof(item)));
			Assert::AreEqual("Hello", items[0].value);
			Assert::AreEqual("world!", items[1].value);
		}

		TEST_METHOD(２要素で入れ替え)
		{
			item items[2] = {
				{9, "world!"},
				{7, "Hello"},
			};
			Assert::IsTrue(radix_sort(items, items + sizeof(items) / sizeof(item)));
			Assert::AreEqual("Hello", items[0].value);
			Assert::AreEqual("world!", items[1].value);
		}
	};

	TEST_CLASS(品質確認)
	{
	public:
		_CrtMemState sStartMemState;
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#ifdef _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif
		}
		TEST_METHOD_CLEANUP(Cleanup)
		{
#ifdef _DEBUG
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}

		bool bubble_sort(item* begin, const item* end)
		{
			if (begin == NULL || end == NULL || end < begin) return false;

			for (item* it = begin; it != end; it++) {
				for (item* it2 = it + 1; it2 != end; it2++) {
					if (it2->key < it->key)
					{
						item tmp = *it;
						*it = *it2;
						*it2 = tmp;
					}
				}
			}
			return true;
		}

	public:

		TEST_METHOD(NULLは帰り値がfalse)
		{
			item items[1];
			Assert::IsFalse(radix_sort(NULL, items));
			Assert::IsFalse(radix_sort(items, NULL));
		}

		TEST_METHOD(endのアドレスが小さいのはダメ)
		{
			item items[1];
			Assert::IsFalse(radix_sort(items + sizeof(items) / sizeof(item), items));
		}

		TEST_METHOD(たくさんの要素を入れ替え)
		{
			const int NUM = 10000;
			item* items = (item*)malloc(sizeof(item) * NUM);
			if (NULL == items) { Assert::Fail(); return; }

			for (int i = 0; i < NUM; i++) {
				items[i].key = NUM - i;
				sprintf_s(items[i].value, 256, "%d", i);
			}

			Assert::IsTrue(radix_sort(items, items + NUM));

			for (int i = 0; i < NUM; i++) {
				char buf[256];
				sprintf_s(buf, 256, "%d", NUM - i - 1);
				Assert::AreEqual(buf, items[i].value);
			}

			free(items);
		}

		TEST_METHOD(バブルソートとの比較)
		{
			const int NUM = 100000;
			std::random_device rnd;
			item* items = (item*)malloc(sizeof(item) * NUM);
			Assert::IsNotNull(items);
			for (int i = 0; i < NUM; i++) {
				items[i].key = i;
				sprintf_s(items[i].value, 256, "%d", i);
			}
			for (int i = 0; i < NUM; i++) {
				int r = rnd() % NUM;
				unsigned int k = items[i].key;
				items[i].key = items[r].key;
				items[r].key = k;
			}

			item* item_b = (item*)malloc(sizeof(item) * NUM);
			Assert::IsNotNull(item_b);
			memcpy_s(item_b, sizeof(item) * NUM, items, sizeof(item) * NUM);

			std::chrono::system_clock::time_point timeStt, timeEnd;
			timeStt = std::chrono::system_clock::now();
			bubble_sort(item_b, item_b + NUM);
			timeEnd = std::chrono::system_clock::now();
			uint64_t  sortTime_bubble = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStt).count();

			timeStt = std::chrono::system_clock::now();
			radix_sort(items, items + NUM);
			timeEnd = std::chrono::system_clock::now();
			uint64_t  sortTime_radix = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStt).count();

			for (int i = 0; i < NUM; i++) {
				Assert::AreEqual(item_b[i].value, items[i].value);
			}

			Assert::IsTrue(sortTime_radix * 100 < sortTime_bubble);// 数が大きければ100倍ぐらい早い

			free(item_b);
			free(items);
		}
	};
}
