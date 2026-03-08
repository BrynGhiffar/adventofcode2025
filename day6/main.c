#include <string.h>
#include <stdio.h>

int parse_int(const char* line, unsigned long long* out) {
	*out = 0ULL;
	int i = 0;
	for (; ('0' <= line[i]) && (line[i] <= '9'); i++) {
		*out = *out * 10ULL + (unsigned long long) (line[i] - '0');
	}
	printf("int: %llu\n", *out);
	return i;
}


int parse_line(const char* line, unsigned long long* arr) {
	int col = 0;
	int ncol = 0;
	while (1) {
		while (line[col] == ' ' || line[col] == '\t') col++;
		if ('0' > line[col] || line[col] > '9') break;
		col += parse_int(&line[col], &arr[ncol]);
		ncol += 1;
	}
	return ncol;
}

void print_array(unsigned long long* arr, int len) {
	for (int i = 0; i < len; i++) {
		printf("%llu ", arr[i]);
	}
	printf("\n");
}

int parse_line_symbols(const char* line, char* symbols) {
	int ncol = 0;
	int col = 0;
	while (line[col] != '\n') {
		while (line[col] == ' ' || line[col] == '\t') col++;
		symbols[ncol] = line[col];
		col += 1;
		ncol += 1;
	}
	return ncol;
}

int is_numbers(const char *line) {
	int col = 0;
	while (line[col] == ' ') col++;
	return ('0' <= line[col]) && (line[col] <= '9');
}

int is_add(char ch) {
	return ch == '+';
}

unsigned long long solve(unsigned long long *numbers, int width, int line_no, const char* symbols) {
	char ch;
	unsigned long long curr = 0, ans = 0;
	for (int i = 0; i < width; i++) {
		ch = symbols[i];
		if (is_add(ch)) {
			curr = 0;
		} else {
			curr = 1;
		}
		for (int j = 0; j < line_no; j++) {
			if (is_add(ch)) {
				curr += numbers[width * j + i];
			} else {
				curr *= numbers[width * j + i];
			}
		}

		ans += curr;

	}
	return ans;
}

#define MAX_LINE 10240

int main() {
	int col = 0;
	char line[MAX_LINE];
	char symbols[MAX_LINE];
	int width = 0;
	int line_no = 0;
	unsigned long long numbers[MAX_LINE];
	memset(numbers, 0, MAX_LINE);
	memset(symbols, 0, MAX_LINE);
	while (1) {
		if (scanf("%c", &line[col]) == EOF) {
			break;
		}

		if (line[col] == '\n') {
			if (is_numbers(line)) {
				if (width == 0) {
					width = parse_line(line, &numbers[line_no * width]);
				} else {
					parse_line(line, &numbers[line_no * width]);
				}
				line_no += 1;
			} else {
				parse_line_symbols(line, symbols);
			}
			col = 0;
			memset(line, 0, MAX_LINE);
		} else {
			col += 1;
		}
	}
	printf("%d %d\n %s\n", width, line_no, symbols);
	print_array(numbers, width * line_no);
	unsigned long long ans = solve(numbers, width, line_no, symbols);
	printf("ans: %llu\n", ans);
}
