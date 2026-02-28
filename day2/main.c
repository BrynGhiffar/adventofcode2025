#include <stdbool.h>
#include <stdio.h>
#include <string.h>

long long is_invalid(long long v) {
	char sdig[100];
	sprintf(sdig, "%lld", v);
	int n = strlen(sdig);
	if (n % 2 != 0) return 0;
	if (strncmp(sdig, sdig + n / 2, n / 2) == 0) {
		return v;
	}
	return 0;
}

long long count_range(long start, long end) {
	long long count = 0;
	while (start <= end) {
		count += is_invalid(start);
		start++;
	}
	return count;
}

int main() {
	long long start, end;
	long long res = 0;

	while (1) {
		if (scanf("%lld-%lld", &start, &end) == EOF) break;
		long long k = count_range(start, end);
		printf("%lld\n", k);
		res += k;
	}

	printf("res: %lld\n", res);
}
