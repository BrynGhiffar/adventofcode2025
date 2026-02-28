#include <stdio.h>
#include <string.h>
#include <sys/param.h>

int max_voltage(char* memo, const char* nums, int n) {
	int max = 0, val;
	memo[n - 1] = nums[n - 1];
	for (int i = n - 2; i >= 0; i--) {
		memo[i] = MAX(memo[i + 1], nums[i]);
		val = (int) (nums[i] - '0') * 10 + (int) (memo[i + 1] - '0');
		max = MAX(max, val);
	}
	return max;
}

int main() {
	const int BANK_LENGTH = 1024;
	char bank[BANK_LENGTH];
	char memo[BANK_LENGTH];
	int n = 0;
	int res = 0;
	int is_eof = 0;
	while (1) {
		if (scanf("%c", &bank[n]) == EOF) {
			break;
		}

		if (bank[n] == '\n') {
			bank[n] = '\0';
			res += max_voltage(memo, bank, n);
			memset(bank, 0, BANK_LENGTH);
			n = 0;
		} else {
			n += 1;
		}
	}

	printf("res: %d", res);
}
