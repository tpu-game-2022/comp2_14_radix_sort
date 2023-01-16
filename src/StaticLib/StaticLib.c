#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義

#include "../include/lib_func.h"

// 基数ソート(引数が不適切であればfalseを返す)
// 基数は256で実装せよ


bool radix_sort(item* begin, const item* end)
{
	const int ElementCount = (int)(end-begin);
    int Digit_Max = 256;//最大桁数
	unsigned int Digit_Min = 1;//最低桁数

	if (!begin || !end||ElementCount<0)return false;
	if (ElementCount<2)return true;//要素数１時にそのまま

	item* radix = (item*)malloc(sizeof(item) * ElementCount);
	if (radix==NULL)return false;
	item* clone = (item*)malloc(sizeof(item) * ElementCount);//一時保存用
	if (clone==NULL)return false;

	unsigned int Digit = begin[0].key;//どの桁まで探索するのか
	for (size_t i = 1; i < ElementCount; i++)
	{
		if (Digit < begin[i].key) {
			Digit = begin[i].key;
		}
	}

	if (Digit < 0)return false;//桁数0はfalse

	while (Digit_Min<=Digit)
	{
		memcpy_s(radix, sizeof(item) * ElementCount, begin, sizeof(item) * ElementCount);

		for (size_t i = 0; i < ElementCount; i++) {
			radix[i].key = (radix[i].key/Digit_Min) % Digit_Max;
		}

		int k = 0;
		for (size_t Radix_i = 0; Radix_i < Digit_Max; Radix_i++)
		{
			for (size_t Ary_j = 0; Ary_j < ElementCount; Ary_j++)
			{
				if (radix[Ary_j].key == Radix_i)
				{
					clone[k++] = begin[Ary_j];
				}
			}
		}
			memcpy_s(begin, sizeof(item) * ElementCount, clone, sizeof(item) * ElementCount);

			Digit_Min *= Digit_Max;
	}

	free(radix);
	free(clone);
	return true;
}
