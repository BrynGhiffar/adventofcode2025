#include <stdbool.h>
#include <stdio.h>
#include <string.h>

long long is_invalid(long long v) {
	char sdig[100];
	sprintf(sdig, "%lld", v);
	int n = strlen(sdig);
	for (int i = 1; i <= (n / 2); i++) {
		bool all_match = true;
		if (n % i != 0) continue;
		for (int s1 = 0; s1 < (n - i); s1 += i) {
			int s2 = s1 + i;
			if (strncmp(sdig + s1, sdig + s2, i) != 0) {
				all_match = false;
				break;
			}
		}
		if (all_match) return v;
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
