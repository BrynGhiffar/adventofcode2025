#include <stdio.h>
#include <string.h>
#include <sys/param.h>
#include <stdint.h>

#define MAX_COL 102400 // Maximum number of columns
#define MAX_LINES 100 // Maximum number of lines
#define MAX_ARR_LENGTH 102400


struct Grid {
	int32_t len_col;
	int32_t len_line;
	char buffer[MAX_LINES * MAX_COL];
};

struct Grid grid;

void put(int32_t line, int32_t col, char c) {
	grid.buffer[col + line * MAX_COL] = c;
}

char* get(int32_t line, int32_t col) {
	return &grid.buffer[col + line * MAX_COL];
}

void load_grid() {
	memset(&grid, 0, sizeof grid);
	char c;
	int32_t col = 0;
	int32_t line = 0;
	int32_t idx;
	while (scanf("%c", &c) != EOF) {
		if (c == '\n') {
			col = 0;
			line++;
			continue;
		}
		put(line, col, c);
		col++;
		grid.len_col = MAX(grid.len_col, col + 1);
	}
	grid.len_line = line;
	if (col > 0) {
		grid.len_line += 1;
	}
}

void print_grid() {
	for (int32_t i = 0; i < grid.len_line; i++) {
		for (int32_t j = 0; j < grid.len_col; j++) {
			printf("%c", *get(i, j));
		}
		printf("\n");
	}
}


struct Array {
	int32_t length;
	int32_t buffer[MAX_ARR_LENGTH];
};

struct Array init_arr() { // Initialize a stack allocated array
	struct Array arr;
	memset(&arr, 0, sizeof arr);
	return arr;
}

int32_t append(struct Array *arr, int32_t number) {
	if (arr->length == MAX_ARR_LENGTH) return 32;
	arr->buffer[arr->length] = number;
	return ++arr->length;
}

void print_array(struct Array *arr) {
	printf("[");
	for (int i = 0; i < arr->length; i++) {
		printf("%d, ", arr->buffer[i]);
	}
	printf("]\n");
}

struct Array get_columns() {
	struct Array arr = init_arr();
	for (int32_t i = 0; i < grid.len_col; i++) {
		char *c = get(grid.len_line - 1, i);
		if (*c == '*' || *c == '+') {
			if (i > 0) {
				append(&arr, i - 1);
			}
			append(&arr, i);
		}
	}
	printf("length: %d", arr.length);
	append(&arr, grid.len_col - 1);
	return arr;
}

uint64_t parse_number(char* string, int32_t n) {
	uint64_t value = 0;
	for (int i = 0; i < n; i++) {
		if (string[i] >= '0' && string[i] <= '9') {
			value *= 10ULL;
			value += (uint64_t) (string[i] - '0');
		}
	}
	return value;
}

uint64_t calc_column(int32_t col_start, int32_t col_end) {
	char op = *get(grid.len_line - 1, col_start);
	uint64_t sum = 0;
	if (op == '*') {
		sum = 1;
	}

	for (int i = col_start; i < col_end; i++) {
		uint64_t value = 0;
		for (int j = 0; j < grid.len_line - 1; j++) {
			char c = *get(j, i);
			if (c >= '0' && c <= '9') {
				value *= 10;
				value += (uint64_t) (c - '0');
			}
		}
		printf("value: %ld\n", value);
		if (op == '*') {
			sum *= value;
		} else {
			sum += value;
		}
	}
	printf("%ld\n", sum);
	return sum;
}

uint64_t solve(struct Array *cols) {
	uint64_t sum = 0;
	for (int i = 0; i < cols->length; i+=2) {
		sum += calc_column(cols->buffer[i], cols->buffer[i + 1]);
	}
	return sum;
}

int main() {
	load_grid();
	// print_grid();
	struct Array cols = get_columns();
	print_array(&cols);
	uint64_t res = solve(&cols);
	printf("res: %ld", res);
}
