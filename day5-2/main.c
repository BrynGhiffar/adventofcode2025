#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>

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
	for (int i = 2; i < len; i += 2) {
		for (int j = i; j > 1; j -= 2) {
			if (arr[j] < arr[j - 2]) {
				swap(&arr[j], &arr[j - 2]);
				swap(&arr[j + 1], &arr[j - 1]);
			}
		}
	}
}

int merge_ranges(unsigned long long *arr, int len) {
	int current = len;
	int i = 0;
	int j = i + 2;
	while (j + 1 < len) {
		while (j + 1 < len && (arr[i + 1] >= arr[j])) {
			arr[i + 1] = MAX(arr[j + 1], arr[i + 1]);
			current -= 2;
			j += 2;
		}
		if (j + 1 < len) {
			arr[i + 2] = arr[j];
			arr[i + 3] = arr[j + 1];
		}
		i += 2;
		j += 2;
	}
	return current;
}

int safe_add(unsigned long long a, unsigned long long b, unsigned long long *result) {
    // Check if b is greater than the maximum possible value minus a
    if (b > ULLONG_MAX - a) {
        // Overflow will occur
        return 0; // Indicate failure/overflow
    } else {
        // Safe to add
        *result = a + b;
        return 1; // Indicate success
    }
}

int safe_sub(unsigned long long a, unsigned long long b, unsigned long long *result) {
	if (a >= b) {
		*result = a - b;
		return 1;
	} else {
		return 0;
	}
}

int main() {
	char c;

	unsigned long long ans = 0;
	char line[1024];
	int col = 0;
	unsigned long long ranges[1024];
	int range_size = 0;

	memset(line, 0, col);
	memset(ranges, 0, col);
	while (1) {
		if (scanf("%c", &line[col]) == EOF) {
			if (col > 0) {
				parse_range(line, &ranges[range_size]);
				range_size += 2;
				col = 0;
				memset(line, 0, sizeof line);
			}
			break;
		}

		if (line[col] == '\n') {
			parse_range(line, &ranges[range_size]);
			range_size += 2;
			col = 0;
			memset(line, 0, sizeof line);
		} else {
			col += 1;
		}
	}

	printf("range size: %d\n", range_size);
	sort_ranges(ranges, range_size);
	print_array(ranges, range_size);
	range_size = merge_ranges(ranges, range_size);
	print_array(ranges, range_size);
	for (int i = 0; i < range_size; i += 2) {
		unsigned long long diff;
		int succ = safe_sub(ranges[i + 1], ranges[i], &diff);
		if (!succ) {
			fprintf(stderr, "Failed to do safe subtraction");
			exit(1);
		}
		succ = safe_add(ans, diff, &ans);
		if (!succ) {
			fprintf(stderr, "Failed to do safe addition");
			exit(1);
		}
		succ = safe_add(ans, 1ULL, &ans);
		if (!succ) {
			fprintf(stderr, "Failed to do safe addition");
			exit(1);
		}
	}

	printf("%llu\n", ans);
}
