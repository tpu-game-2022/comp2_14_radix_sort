#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義

#include "../include/lib_func.h"

#include<stdio.h>
// 基数ソート(引数が不適切であればfalseを返す)
// 基数は256で実装せよ
bool radix_sort(item* begin, const item* end)
{
	// ToDo: 基数ソートを実装する
	int size = end - begin;
	if (!begin || !end || size < 0)
		return false;
	if (size < 2)
		return true;
	int radix = 256;
    int  C_radix= 1;

	item* sort = (item*)malloc(sizeof(item) * (size));
	if (sort == NULL)
		return false;
	item* swap = (item*)malloc(sizeof(item) * size);
	if (swap == NULL)
		return false;

	unsigned int maxdigit = begin[0].key;
	for (size_t i = 1; i < size; i++) {
		if (maxdigit < begin[i].key)maxdigit = begin[i].key;
	}
	if (maxdigit < 0)return false;

	while (C_radix <= maxdigit) {
		memcpy_s(sort, sizeof(item) * size, begin, sizeof(item) * size);
		for (size_t i = 0; i < size; i++) {
			sort[i].key = (sort[i].key / C_radix) % radix;
		}
		int index = 0;
		for (size_t radex_i = 0; radex_i < radix; radex_i++) {
			for (size_t ary_i = 0; ary_i < size; ary_i++) {
				if (sort[ary_i].key == radex_i)swap[index++] = begin[ary_i];
			}
		}
		memcpy_s(begin, sizeof(item) * size, swap, sizeof(item) * size);
		C_radix *= radix;
	}
	free(sort);
	free(swap);
	return true;
}