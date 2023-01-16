#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義
#include <stdlib.h>
#include "../include/lib_func.h"


// 基数ソート(引数が不適切であればfalseを返す)
// 基数は256で実装せよ
bool radix_sort(item* begin, const item* end)
{
	// ToDo: 基数ソートを実装する
	if (begin == NULL || end == NULL || begin > end)
		return false;
	if (begin+1 == end)
		return true;
	int digit = 1;
    int *rad = (int*)malloc(sizeof(int) * (end-begin));
    item *save = (item*)malloc(sizeof(item) * (end - begin));
    int max_key = 0;
    int max_digit = 1;
    for(int i = 0;i<end-begin;i++)
    {
        if (begin[i].key > max_key)
            max_key = begin[i].key;
    }
    while(!max_key)
    {
        max_key /= 256;
        max_digit *= 256;
    }
    while (digit <= max_digit)
    {
        for (int i = 0; i < end-begin; i++)
            rad[i] = (begin[i].key/digit) % 256;

      int  k = 0;                        
        for (int i = 0; i < 256 ; i++) 
        {
            for (int j = 0; j < end-begin; j++)
                if (rad[j] == i)
                {
                    save[k] = begin[j];
                    k++;
                }
        }
        for (int i = 0; i < end-begin; i++)
            begin[i] = save[i]; 
        digit *= 256;  
    }
    free(rad);
    free(save);
    return true;
}
