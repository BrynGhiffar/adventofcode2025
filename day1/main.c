#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main() {
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
