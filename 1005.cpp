#include <iostream>
#include <vector>

std::vector<int> s(20);
int n, _min = INT32_MAX;

void solution(int k1, int k2, int i) {
	if (i == n) { // Если разложили все камни, то проверяем разницу весов куч
		if (abs(k1 - k2) < _min) {
			_min = abs(k1 - k2);
		}
	}
	
	else {
		/* Рассматриваем следующий вариант, кладём камень в каждую из куч и проверяем результат на следующей итерации */
		solution(k1 + s[i], k2, i+1);
		solution(k1, k2 + s[i], i+1);
	}

	return;
}

int main() {
	/* Читаем входные данные */
	std::cin >> n;

	for (int i = 0; i < n; ++i)
		std::cin >> s[i];

	/* Начинаем перебор дерева всех возможных решений */
	solution(0, 0, 0);

	std::cout << _min;

	return 0;
}