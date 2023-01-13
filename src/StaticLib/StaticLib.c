#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義
#include <stdlib.h>

#include "../include/lib_func.h"

typedef struct SORT_ITEM_ {
	unsigned int key;
	int index;
	struct SORT_ITEM_* next;
}SORT_ITEM;


// 基数ソート(引数が不適切であればfalseを返す)
// 基数は256で実装せよ
bool radix_sort(item* begin, const item* end)
{
	if (begin == NULL || end == NULL || end < begin) return false;
	if (end - begin <= 1) return true;// 絶対ソートされない

	int num = (int)(end - begin);
	SORT_ITEM* a_item = (SORT_ITEM*)malloc(sizeof(SORT_ITEM) * num);
	if (a_item == NULL) return false;

	enum { RADIX = 256 };
	SORT_ITEM* head[2][RADIX];
	SORT_ITEM* tail[2][RADIX];
	SORT_ITEM** read_head, ** write_head;
	SORT_ITEM** read_tail, ** write_tail;
	write_head = head[0];
	read_head = head[1];
	write_tail = tail[0];
	read_tail = tail[1];

	for (int i = 0; i < RADIX; i++) {
		read_head[i] = NULL;
		read_tail[i] = NULL;
	}

	unsigned int max_key = 0;
	for (int i = 0; i < num; i++) {
		const item* s = begin + i;
		SORT_ITEM* p = a_item + i;
		p->index = i;

		int r = s->key % RADIX;
		// r のリストの最後に追加
		if (read_tail[r] == NULL) {
			read_head[r] = p;
		}
		else {
			read_tail[r]->next = p;
		}
		read_tail[r] = p;
		p->next = NULL;

		p->key = s->key / RADIX;
		if (max_key < s->key) max_key = s->key;
	}

	while (max_key) {

		for (int i = 0; i < RADIX; i++) {
			write_head[i] = NULL;
			write_tail[i] = NULL;
		}

		for (int i = 0; i < RADIX; i++) {
			SORT_ITEM* p = read_head[i];
			while (p) {
				int r = p->key % RADIX;
				SORT_ITEM* next = p->next;
				if (write_tail[r] == NULL) {
					write_head[r] = p;
				}
				else {
					write_tail[r]->next = p;
				}
				write_tail[r] = p;
				p->next = NULL;

				p->key /= RADIX;
				p = next;
			}
		}

		SORT_ITEM** tmp = read_head;
		read_head = write_head;
		write_head = tmp;

		tmp = read_tail;
		read_tail = write_tail;
		write_tail = tmp;

		max_key /= RADIX;
	}

	item* a_copy = (item*)malloc(sizeof(item) * num);
	if (a_copy == NULL) return false;
	memcpy_s(a_copy, sizeof(item) * num, begin, sizeof(item) * num);

	int idx = 0;
	for (int i = 0; i < RADIX; i++) {
		SORT_ITEM* p = read_head[i];
		while (p) {
			begin[idx++] = a_copy[p->index];
			p = p->next;
		}
	}

	free(a_copy);
	free(a_item);

	return true;
}
