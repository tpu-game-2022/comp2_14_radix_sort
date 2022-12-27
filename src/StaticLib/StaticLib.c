#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義
#include <stdio.h>
#include <stdlib.h>
#include "../include/lib_func.h"


// 基数ソート(引数が不適切であればfalseを返す)
// 基数は256で実装せよ
bool radix_sort(item* begin, const item* end)
{
	// ToDo: 基数ソートを実装する
	if (!begin || !end || end - begin < 0)return false;

	if (end - begin < 2)return true;

	//int size = end - begin;

	swap_radix(begin, end - begin, 256);

	return true;
}

static void swap_radix(item* order, const int num, const int rad)
{
	int i, j, count, n;
	int level = 1, skep = 0;
	
	item *copy = (item*)malloc(sizeof(item) * num);
	int *bottom = (int*)malloc(sizeof(int) * num + 1);

	while (skep != num)
	{
		skep = 0;

		for (i = 0; i < num; i++)
		{
			n = order[i].key / level;
			bottom[i] = n % rad;

			if (order[i].key < (unsigned)level)
				skep++;
		}

		count = 0;

		for (i = 0; i <= rad; i++)
		{
			for (j = 0; j < num; j++)
			{
				if (bottom[j] == i)
					copy[count] = order[j];

				count++;
			}
		}

		for (i = 0; i < num; i++)
			order[i] = copy[i];

		level *= rad;
	}

	free(copy);
	free(bottom);
}