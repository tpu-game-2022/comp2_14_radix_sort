#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義
#include <stdlib.h> //memcpy_sのエラー回避

#include "../include/lib_func.h"


// 基数ソート(引数が不適切であればfalseを返す)
// 基数は256で実装せよ
bool radix_sort(item* begin, const item* end)
{
    int size = (int)(end - begin);
    if (!begin || !end || size < 0) {
        return false;
    }
    //要素数１ならそのまま
    if (size < 2) {
        return true;
    }
    int radix = 256;
    unsigned int digit = 1;

    item* sort = (item*)malloc(sizeof(item) * (size));
    if (sort == NULL) { return false; }

    //ソート後の一時的な配列
    item* swap = (item*)malloc(sizeof(item) * size);
    if (swap == NULL) { return false; }

    //最大桁数探索
    unsigned int maxdigit = begin[0].key;
    for (size_t i = 1; i < size; i++) {
        if (maxdigit < begin[i].key) {
            maxdigit = begin[i].key;
        }
    }
    if (maxdigit < 0) {
        return false;
    }

    while (digit <= maxdigit) {
        //radにソート用配列をコピー
        memcpy_s(sort, sizeof(item) * size, begin, sizeof(item) * size);

        //ソートする桁をdigitに変更
        for (size_t i = 0; i < size; i++) {
            sort[i].key = (sort[i].key / digit) % radix;
        }

        //0~radix-1(基数)でソート
        int index = 0;
        for (size_t radix_i = 0; radix_i < radix; radix_i++) {
            for (size_t ary_i = 0; ary_i < size; ary_i++) {
                if (sort[ary_i].key == radix_i) {
                    swap[index++] = begin[ary_i];
                }
            }

        }

        memcpy_s(begin, sizeof(item) * size, swap, sizeof(item) * size);
        //次の基数へ
        digit *= radix;
    }
    free(sort);
    free(swap);
    return true;
}
