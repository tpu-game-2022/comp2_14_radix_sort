#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義
#include <stdlib.h>
#include "../include/lib_func.h"


// 基数ソート(引数が不適切であればfalseを返す)
// 基数は256で実装せよ
bool radix_sort(item* begin, const item* end)
{
	// ToDo: 基数ソートを実装する

	int array_size = end - begin;

	if (begin == NULL || end == NULL || array_size < 0)return false;
	if (array_size < 2)return true;

	int radix = 256;
	int C_radix = 1;
    int* radix_array = (int*)malloc(sizeof(int) * array_size);
//	unsigned int radix_array2[1000];
	item* cp_item_array = (item*)malloc(sizeof(item) * array_size);

	if (radix_array == NULL||cp_item_array==NULL)return false;

	int max = begin[0].key;
	for (int i = 1;i < array_size;i++)
	{
		if (begin[i].key > max)
			max = 
		begin[i].key;
	}
	
	while (C_radix <= max)
	{
		for (int i = 0;i < array_size;i++)
		{
			//radix_array2[i] = (begin[i].key/C_radix) % radix;
			radix_array[i] = (begin[i].key/C_radix)% radix;
		}

		int x=0;

		for (int i = 0;i < radix;i++)
		{
			for (int j = 0;j < array_size;j++)
			{
				if (radix_array[j] == i)
				{
					cp_item_array[x++] = begin[j];
				}

			}
		}

		for (int i = 0;i < array_size;i++)
		{
			begin[i] = cp_item_array[i];
		}

		C_radix *= 256;
	
	} 

	free(radix_array);
	free(cp_item_array);

	return true;
}
