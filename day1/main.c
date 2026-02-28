#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void part2() {
	int numbers[10240];
	char word[5];
	int sz;
	memset(word, 0, sizeof word);
	memset(numbers, 0, sizeof numbers);
	int x = 0;
	while (1) {
		if (scanf("%s", word) == EOF) break;;
		const char *numb = (word + 1);
		int val = atoi(numb);
		if (*word == 'R') {
			numbers[x] = val;
		} else {
			numbers[x] = -val;
		}
		x += 1;
	}

	int res = 50;
	int count = 0;
	for (int i = 0; i < x; i++) {
		int r = (numbers[i] % 100);
		count += abs(numbers[i] / 100);
		int nxt = ((res + r) % 100 + 100) % 100;
		if (res != 0 && ((res + r) >= 100 || (res + r) <= 0)) {
			count += 1;
		}
		res = nxt;
		printf("curr: %d\n", res);
	}
	printf("res: %d", count);
}

void part1() {
	int numbers[10240];
	char word[5];
	int sz;
	memset(word, 0, sizeof word);
	memset(numbers, 0, sizeof numbers);
	int x = 0;
	while (1) {
		if (scanf("%s", word) == EOF) break;;
		const char *numb = (word + 1);
		int val = atoi(numb);
		if (*word == 'R') {
			numbers[x] = val;
		} else {
			numbers[x] = -val;
		}
		x += 1;
	}

	int res = 50;
	int count = 0;
	for (int i = 0; i < x; i++) {
		res += numbers[i];
		if (res < 0) {
			res += 100;
		}
		res %= 100;
		if (res == 0) count++;
	}
	printf("res: %d", count);
}


int main() {
	// part1();
	part2();
}
