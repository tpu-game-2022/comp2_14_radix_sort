#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義

#include "../include/lib_func.h"
#include <stdlib.h>


// 基数ソート(引数が不適切であればfalseを返す)
// 基数は256で実装せよ
bool radix_sort(item* begin, const item* end)
{
	// ToDo: 基数ソートを実装する
	if(begin == NULL || end < begin)
	return false;

	int digit = 1, rad = 256, n = end - begin, max = begin[0].key;
	for (int i = 0; i < n; i++)
	{
		if (begin[i].key > max)
			max = begin[i].key;
	}

	item* temp = (item*)malloc(sizeof(item) * n);
	if (temp == NULL)
		return false;

	item* sort = (item*)malloc(sizeof(item) * n);
	if (sort == NULL)
		return false;

	while (digit <= max)
	{
		for (int i = 0; i < n; i++)
		{
			temp[i] = begin[i];
			temp[i].key = (temp[i].key / digit) % rad;
		}

		int element = 0;
		for (int i = 0; i < rad; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (temp[j].key == i)
				{
					sort[element++] = begin[j];
				}
			}
		}

		for (int i = 0; i < n; i++)
		{
			begin[i] = sort[i];
		}

		digit *= rad;
	}

	free(temp);
	free(sort);
	return true;
}