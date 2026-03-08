#include <stdio.h>
#include <string.h>

int parse_int(const char* line, unsigned long long* out);

void parse_range(const char* line, unsigned long long* out) {
	out[0] = 0;
	out[1] = 0;
	int len = parse_int(line, &out[0]);
	parse_int(&line[len + 1], &out[1]);
}

int parse_int(const char* line, unsigned long long* out) {
	*out = 0ULL;
	int i = 0;
	for (; ('0' <= line[i]) && (line[i] <= '9'); i++) {
		*out = *out * 10ULL + (unsigned long long) (line[i] - '0');
	}
	printf("int: %llu\n", *out);
	return i;
}

void print_array(unsigned long long* arr, int len) {
	for (int i = 0; i < len; i++) {
		printf("%llu ", arr[i]);
	}
	printf("\n");
}

void swap(unsigned long long *i1, unsigned long long *i2) {
	unsigned long long temp = *i1;
	*i1 = *i2;
	*i2 = temp;
}

void sort_ranges(unsigned long long* arr, int len) {
	// Using bubble sort
	for (int i = 0; i < len; i += 2) {
		for (int j = i; j + 3 < len; j+= 2) {
			if (arr[j] > arr[j + 2]) {
				swap(&arr[j], &arr[j + 2]);
				swap(&arr[j + 1], &arr[j + 3]);
			}
		}
	}
}

int main() {
	char c;

	int ans = 0;
	unsigned long long ingredients[1024];
	int ingredients_size = 0;
	char line[1024];
	int col = 0;
	unsigned long long ranges[1024];
	int range_size = 0;
	int is_ingredients = 0;

	memset(line, 0, col);
	memset(ranges, 0, col);
	while (1) {
		if (scanf("%c", &line[col]) == EOF) {
			if (col > 0) {
				parse_int(line, &ingredients[ingredients_size]);
				ingredients_size += 1;
				col = 0;
				memset(line, 0, col);
			}
			break;
		}

		if (line[col] == '\n' && col == 0 && !is_ingredients) {
			is_ingredients = 1;
			col = 0;
			memset(line, 0, col);
		} else if (line[col] == '\n' && !is_ingredients) {
			parse_range(line, &ranges[range_size]);
			range_size += 2;
			col = 0;
			memset(line, 0, sizeof line);
		} else if (line[col] == '\n' && is_ingredients) {
			parse_int(line, &ingredients[ingredients_size]);
			ingredients_size += 1;
			col = 0;
			memset(line, 0, col);
		} else {
			col += 1;
		}
	}

	sort_ranges(ranges, range_size);
	print_array(ranges, range_size);
	printf("\n\n");
	print_array(ingredients, ingredients_size);

	for (int i = 0; i < ingredients_size; i++) {
		for (int j = 0; j < range_size; j += 2) {
			if ((ranges[j] <= ingredients[i]) && (ingredients[i] <= ranges[j + 1])) {
				printf("%llu %llu %llu \n", ranges[j], ranges[j + 1], ingredients[i]);
				ans += 1;	
				break;
			}
		}
	}

	printf("%d\n", ans);
}
