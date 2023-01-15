#pragma once // インクルードガード

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// C++ でCのライブラリを使うときのおまじない
#ifdef __cplusplus
extern "C" {
#endif

	typedef struct item_
	{
		unsigned int key;
		char value[256];
	}item;

	// 基数ソート(引数が不適切であればfalseを返す)
	// 基数は256で実装せよ
	bool radix_sort(item *begin, const item* end);

	bool swap_radix(item *order, int num, int rad);//bool外すと通らない

	// C++ でCのライブラリを使うときのおまじない
#ifdef __cplusplus
} // extern "C"
#endif
