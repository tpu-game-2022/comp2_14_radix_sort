#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義
#include "stdlib.h"
#include "../include/lib_func.h"


// 基数ソート(引数が不適切であればfalseを返す)
// 基数は256で実装せよ
bool radix_sort(item* begin, const item* end)
{
	// ToDo: 基数ソートを実装する
	int size = end - begin;
	if(!begin||!end||size<0)return false;
	if (size < 2)return true;//要素数1は返却
	int radix = 256;//基数
	unsigned int digit = 1;

	item* sort = (item*)malloc(sizeof(item) * (size));
	if (sort == NULL)return false;
	item* swap = (item*)malloc(sizeof(item) * size);//ソート後の一時的な配列
	if (swap == NULL)return false;

	unsigned int maxdigit = begin[0].key;//最大桁数検索
	for (size_t i = 1; i < size; i++) {
		if (maxdigit < begin[i].key)maxdigit = begin[i].key;
	}
	if (maxdigit < 0)return false;

	while (digit <= maxdigit) {
		memcpy_s(sort, sizeof(item) * size, begin, sizeof(item) * size);//radにソート用配列コピー
		for (size_t i = 0; i < size; i++) {//ソート桁をdigitに変更
			sort[i].key = (sort[i].key / digit) % radix;
		}
		int index = 0;//ソート
		for (size_t radex_i = 0; radex_i < radix; radex_i++) {
			for (size_t ary_i = 0; ary_i < size; ary_i++) {
				if (sort[ary_i].key == radex_i)swap[index++] = begin[ary_i];
			}
		}
		memcpy_s(begin, sizeof(item) * size, swap, sizeof(item) * size);
		digit *= radix;//次の基数に変動
	}
	free(sort);
	free(swap);
	return true;
}
