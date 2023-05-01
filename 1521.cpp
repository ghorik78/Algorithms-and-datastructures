#include <iostream>

int find_mth_max(int tree[], int m, int n_max) {
	int x = 1;

    /* Ищём m-ое число в дереве */
	while (2 * x < n_max) {
        /* Если в левом поддереве есть как минимум m пар, то переходим в него и идём дальше */
		if (tree[x * 2] >= m) {
			x *= 2;
		}
        /* Иначе ищем m - tree[x*2] число в другом узле 2x+1 */
		else {
			m -= tree[x * 2];
			x = x * 2 + 1;
		}
	}

    /* Нашли узел, в котором нужное нам число */
    /* Если он есть в правой части дерева, то возвращаем, если нет, то углубляемся */
	if (tree[x] == 2)
		return tree[2 * x + m - 1];
	else
		if (tree[2 * x + 1] != 0)
			return tree[2 * x + 1];
		else
			return tree[2 * x];
}

int main() {
	int n, k;
	std::cin >> n;
	std::cin >> k;

	if (n == 1) {
		std::cout << 1;
		return 0;
	}

	int n_max = 1;
	while (n_max < n)
		n_max <<= 1;
    
    /* Резервируем память под дерево отрезков, хранящее информацию о количестве непустых пар */
	int* tree_data = new int[2 * n_max];

    /* Вторую половину дерева заполяем просто по порядку */
	for (int i = 0; i < n; i++)
		tree_data[n_max + i] = i + 1;

    /* Первую половину дерева заполняем иначе */
	for (int i = n_max - 1; i > 0; i--) {
        /* Если пара лежит во второй половине, то единичка */
		if (2 * i >= n_max) {
			tree_data[i] = 0;
			if (tree_data[2 * i] != 0)
				tree_data[i]++;
			if (tree_data[2 * i + 1] != 0)
				tree_data[i]++;
		}
        /* Если пара в первой половине, то сумма */
		else tree_data[i] = tree_data[2 * i] + tree_data[2 * i + 1];
	}

	int prev = 0;
	/* Пока не исключим всех солдат */
	while (n > 0) {
		prev = (prev + k - 1) % n;
		n--;
		int index = find_mth_max(tree_data, prev + 1, n_max);
		std::cout << index << " ";
		tree_data[n_max + index - 1] = 0;

		int j = n_max + index - 1;
		while (j > 1) {
			j /= 2;
			tree_data[j]--;
		}
	}

	return 0;
}