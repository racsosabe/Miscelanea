#include<stdio.h>
#include<stdlib.h>

// START OF VECTOR TEMPLATE

struct Vector {
	int len;
	int capacity;
	int* a;
};

void init(struct Vector *vector) {
    vector -> len = 0;
    vector -> capacity = 1;
    vector -> a = (int*)malloc(sizeof(int));
}

int empty(struct Vector *vector) {
	return vector -> len == 0;
}

void push_back(struct Vector *vector, int x) {
	if(vector -> len == vector -> capacity) {
		int* b = (int*)malloc(vector -> capacity * sizeof(int));
		int ptr = 0;
		while(ptr < vector -> len) {
			b[ptr] = vector -> a[ptr];
			ptr++;
		}
		vector -> capacity *= 2;
		vector -> a = (int*)malloc(vector -> capacity * sizeof(int));
		ptr = 0;
		while(ptr < vector -> len) {
			vector -> a[ptr] = b[ptr];
			ptr++;
		}
		free(b);
	}
	vector -> a[vector -> len++] = x;
}

int back(struct Vector *vector) {
	if(empty(vector)) {
		printf("Error. Vector is empty\n");
		return -1;
	}
	return vector -> a[vector -> len - 1];
}

void pop_back(struct Vector *vector) {
	if(empty(vector)) {
		printf("Error. Vector is empty\n");
		return;
	}
	vector -> len--;
	if(vector -> len >= 1 && vector -> len <= vector -> capacity / 4) {
		int* b = (int*)malloc(vector -> capacity * sizeof(int));
		int ptr = 0;
		while(ptr < vector -> len) {
			b[ptr] = vector -> a[ptr];
			ptr++;
		}
		vector -> capacity /= 2;
		vector -> a = (int*)malloc(vector -> capacity * sizeof(int));
		ptr = 0;
		while(ptr < vector -> len) {
			vector -> a[ptr] = b[ptr];
			ptr++;
		}
		free(b);
	}
}

void swap(int *x, int *y) {
	int c = *x;
	*x = *y;
	*y = c;
}

void heapify(int* a, int n, int i) {
	int to = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if(l < n && a[l] > a[to]) to = l;
	if(r < n && a[r] > a[to]) to = r;
	if(i != to) {
		swap(&a[i], &a[to]);
		heapify(a, n, to);
	}
}

void heap_sort(int* a, int n) {
	int i;
	for(i = n / 2 - 1; i >= 0; i--) {
		heapify(a, n, i);
	}
	for(i = n - 1; i > 0; i--) {
		swap(&a[i], &a[0]);
		heapify(a, i, 0);
	}
}

void sort(struct Vector *vector) {
	heap_sort(vector -> a, vector -> len);
}

void print(struct Vector *vector) {
	int i;
	for(i = 0; i < vector -> len; i++) {
		printf("%d%c", vector -> a[i], " \n"[i + 1 == vector -> len]);
	}
}

// END OF VECTOR TEMPLATE