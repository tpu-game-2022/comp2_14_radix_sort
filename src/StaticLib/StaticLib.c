#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義
#include <stdlib.h> 
#include "../include/lib_func.h"


// 基数ソート(引数が不適切であればfalseを返す)
// 基数は256で実装せよ
bool radix_sort(item* begin, const item* end)
{
	// ToDo: 基数ソートを実装する
	const int size = end - begin;

	if (begin == NULL || end == NULL || size < 1) return false;
	if (size == 1) return true;

	int* digits = (int*)malloc(sizeof(int) * size);
	item* sorted_items = (item*)malloc(sizeof(item) * size);

	if (digits == NULL || sorted_items == NULL) return false;

	for (int rad = 0; rad < 32; rad += 8)
	{
		for (int i = 0; i < size; ++i)
		{
			digits[i] = (begin[i].key >> rad) & 255;
		}

		for (int i = 0, k = 0; i < 256; ++i)
		{
			for (int j = 0; j < size; j++)
			{
				if (digits[j] != i) continue;
				sorted_items[k++] = begin[j];
			}
		}

		memcpy_s(begin, sizeof(item) * size, sorted_items, sizeof(item) * size);
	}

	free(digits);
	free(sorted_items);

	return true;
}
