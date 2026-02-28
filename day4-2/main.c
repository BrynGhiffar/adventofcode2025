#include <stdio.h>
#include <stdbool.h>

int count(char* grid, int width, int height) {
	int res = 0;
	int surr[] = { 0, -1, 1, -1, 1, 0, 1, 1, 0, 1, -1, 1, -1, 0, -1, -1 };
	const int SURRN = 16;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int surround = 0;
			if (grid[i + j * width] != '@') {
				continue;
			}

			for (int k = 0; k < SURRN; k += 2) {
				int x = i + surr[k];
				int y = j + surr[k + 1];
				if (x < 0) continue;
				if (y < 0) continue;
				if (x >= width) continue;
				if (y >= height) continue;
				if (grid[x + y * width] != '@') continue;
				surround += 1;
			}

			if (surround < 4) {
				grid[i + j * width] = '.';
				res += 1;
			}
		}
	}
	return res;
}

int main() {
	char ch;
	int width = 0;
	int height = 0;
	bool first_row = 1;
	char grid[102400];
	int i = 0;
	while (scanf("%c", &ch) != EOF) {
		if (ch != '\n' && first_row) {
			width += 1;
		} else if (ch == '\n'){
			first_row = false;
			continue;
		}

		grid[i] = ch;
		i += 1;
	}
	int res = 0, curr;
	height = i / width;
	while ((curr = count(grid, width, height)) > 0) {
		printf("%d\n", curr);
		res += curr;
	}
	printf("res: %d\n", res);

}
