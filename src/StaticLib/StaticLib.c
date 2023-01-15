#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義
#include <stdlib.h>
#include "../include/lib_func.h"


// 基数ソート(引数が不適切であればfalseを返す)
// 基数は256で実装せよ
bool radix_sort(item* begin, const item* end)
{
	// ToDo: 基数ソートを実装する
	if (!begin || !end || end - begin < 0)return false;

	if (end - begin < 2)return true;

	int size = end - begin;

	return swap_radix(begin, size, 256);
}

bool swap_radix(item* order, const int num, const int rad)
{
	int count, skep = 0;
	unsigned int level = 1;
	
	item *copy = (item*)malloc(sizeof(item) * num);
	if (copy == NULL) return false;

	int *bottom = (int*)malloc(sizeof(int) * num);
	if (bottom == NULL) { 
		free(copy);    //最初に取得した領域の解放
		return false; 
	}

	while (skep != num)
	{
		skep = 0;
		
		for (int i = 0; i < num; i++)
		{
			bottom[i] = (order[i].key / level) % rad;

			if (order[i].key < level)//全て上回るなら終了条件
				skep++;
		}

		count = 0;

		for (int i = 0; i < rad; i++)
		{
			for (int j = 0; j < num; j++)
			{
				if (bottom[j] == i)
					copy[count++] = order[j];
			}
		}

		for (int i = 0; i < num; i++)
			order[i] = copy[i];

		level *= rad;
	}

	free(copy);
	free(bottom);
	return true;
}