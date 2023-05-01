#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

vector<vector<int>> field;
int n, h_x, h_y, iter = 1;

void put_angle(int x1, int y1, int x2, int y2, int iter) {
	/* Вместо треугольников рисуем прямоугольники, наслаивая их друг на друга. Рисовать начинаем из вершины предыдущего.*/
	for (int i = x1; i <= x2; ++i) {
		for (int j = y1; j <= y2; ++j) {
			if (field[i][j] == 0) field[i][j] = iter;
		}
	}
}

void fill(int x1, int y1, int x2, int y2) {
	/* Если перешли к рассмотрению области, вмещающей лишь один прямоугольничек, то завершаем алгоритм */
	if (x2 - x1 == 1) { put_angle(x1, y1, x2, y2, iter++); return; }

	int c_x = x1 + (x2 - x1 + 1) / 2;
	int c_y = y1 + (y2 - y1 + 1) / 2;
	int type;

	if (h_x >= c_x) {
		type = h_y >= c_y ? 1 : 2;
		h_y >= c_y ? fill(c_x, c_y, x2, y2) : fill(c_x, y1, x2, c_y - 1);
	}
	else {
		type = h_y >= c_y ? 3 : 4;
		h_y >= c_y ? fill(x1, c_y, c_x - 1, y2) : fill(x1, y1, c_x - 1, c_y - 1); 
	}

	put_angle(c_x - 1, c_y - 1, c_x, c_y, iter++);

	if (type != 1) {
		h_x = c_x;
		h_y = c_y;
		fill(c_x, c_y, x2, y2);
	}

	if (type != 2) {
		h_x = c_x;
		h_y = c_y - 1;
		fill(c_x, y1, x2, c_y - 1);
	}

	if (type != 3) {
		h_x = c_x - 1;
		h_y = c_y;
		fill(x1, c_y, c_x - 1, y2);
	}
	
	if (type != 4) {
		h_x = c_x - 1;
		h_y = c_y - 1;
		fill(x1, y1, c_x - 1, c_y - 1);
	}

}

int main() {
	cin >> n;
	cin >> h_x >> h_y;

	int width = pow(2, n); int height = pow(2, n);
	int h_mx = h_x; int h_my = h_y;
	field = vector<vector<int>>(width + 1, vector<int>(height + 1));

	fill(1, 1, width, height);
	field[h_mx][h_my] = 0;

	for (int i = 1; i <= width; ++i) {
		for (int j = 1; j <= height; ++j) {
			cout << field[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}