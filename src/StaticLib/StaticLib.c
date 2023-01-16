#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義
#include <stdlib.h> 
#include "../include/lib_func.h"


// 基数ソート(引数が不適切であればfalseを返す)
// 基数は256で実装せよ
bool radix_sort(item* begin, const item* end)
{
	// ToDo: 基数ソートを実装する
    int size = (int)(end - begin);
    if (!begin || !end || size < 0)return false;
    if (size < 2)return true;
    int radix = 256;
    unsigned int digit = 1;
    item* copy = (item*)malloc(sizeof(item) * size);
    int* sort = (int*)malloc(sizeof(int) * size);
    if (!sort || !copy)return false;
    unsigned int max = begin[0].key;
    for (int i = 1; i < size; i++)
    {
        if (max >= begin[i].key)continue;
        max = begin[i].key;
    }
    if (max < 0)return false;
    for (digit; digit <= max; digit *= radix)
    {
        for (int i = 0; i < size; i++)
        {
            sort[i] = (begin[i].key / digit) % radix;
        }
        int index = 0;
        for (int i = 0; i < radix; i++) 
        {
            for (int j = 0; j < size; j++) 
            {
                if (sort[j] != i)continue;
                copy[index++] = begin[j];
            }
        }
        for (int i = 0; i < size; i++)
        {
            begin[i] = copy[i];
        }
    }
    free(sort);
    free(copy);
    return true;
}