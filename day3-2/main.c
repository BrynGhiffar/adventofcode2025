#include <stdio.h>
#include <string.h>
#include <sys/param.h>

#define K 12

long long max_voltage(const char* nums, int n) {
	long long max = 0, val;
	int start = 0;
	for (int i = 0; i < K; i++) {
		char mx = nums[start];
		start += 1;
		for (int j = start; j < n - K + i + 1; j++) {
			if (nums[j] > mx) {
				mx = nums[j];
				start = j + 1;
			}
		}
		max *= 10LL;
		max += (long long) (mx - '0');
	}
	return max;
}

int main() {
	const int BANK_LENGTH = 1024;
	char bank[BANK_LENGTH];
	int n = 0;
	long long res = 0;
	int is_eof = 0;
	while (1) {
		if (scanf("%c", &bank[n]) == EOF) {
			break;
		}

		if (bank[n] == '\n') {
			bank[n] = '\0';
			res += max_voltage(bank, n);
			memset(bank, 0, BANK_LENGTH);
			n = 0;
		} else {
			n += 1;
		}
	}

	printf("res: %lld", res);
}
