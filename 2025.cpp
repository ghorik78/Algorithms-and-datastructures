#include <iostream>
#include <vector>

int T, n, k;

int solution(int n, int k) {
	int players = n;
	int fights = 0;
	std::vector<int> teams(k);

	/* Распределяем игроков по командам с наименьшей разницей в их количестве */
	while (players) {
		teams[players % k] += 1;
		players--;
	}

	/* Перемножаем количества, исключая повторы */
	for (int i = 0; i < k - 1; ++i) {
		for (int j = i+1; j < k; ++j) {
			fights += teams[i] * teams[j];
		}
	}

	return fights;
}

int main() {
	/* Читаем входные данные */
	std::cin >> T;

	for (int i = 0; i < T; ++i) {
		std::cin >> n >> k;
		std::cout << solution(n, k) << endl;
	}

	return 0;
}