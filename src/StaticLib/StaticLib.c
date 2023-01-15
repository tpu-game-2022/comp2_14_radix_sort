#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義

#include "../include/lib_func.h"

#include <stdlib.h>

int getRadixLimit(item*begin,int size) {

    int n = begin[0].key;
    for (size_t i = 1; i < size; i++) {
        if (n < begin[i].key) {
            n = begin[i].key;
        }
    }
}

// 基数は256で実装せよ
bool radix_sort(item * begin, const item * end)
{
    if (begin == NULL || end == NULL) return false;

    int size = end - begin;
    if (size < 0) return false;
    if (size <= 1) return true;

    int n = getRadixLimit(begin, size);

    item* rad = (item*)malloc(sizeof(item) * (size));
    if (rad == NULL)  return false; 

    item* y = (item*)malloc(sizeof(item) * size);
    if (y == NULL) return false; 

    const int max = 256;
    int m = 1;

    while (m <= n) {

        memcpy_s(rad, sizeof(item) * size, begin, sizeof(item) * size);

        for (size_t i = 0; i < size; i++) {
            rad[i].key = (rad[i].key / m) % max;
        }

        int k = 0;
        for (size_t radix_i = 0; radix_i < max; radix_i++) {
            for (size_t ary_i = 0; ary_i < size; ary_i++) {
                if (rad[ary_i].key == radix_i) {
                    y[k++] = begin[ary_i];
                }
            }

        }

        memcpy_s(begin, sizeof(item) * size, y, sizeof(item) * size);

        m *= max;
    }

    free(rad);
    free(y);

    return true;
}