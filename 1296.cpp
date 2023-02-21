#include <iostream>
#include <vector>
#include <algorithm>

void solution() {
    int n, ans = 0;
    int val, prev_s = 0;

    /* Читаем входные данные */
    std::cin >> n;

    for (size_t i = 0; i < n; ++i) {
        std::cin >> val;

        /* По алгоритму Кадане берём максимум из суммы всех предыдущих и текущего, либо 0, если первая сумма отрицательная  */
        prev_s = std::max(prev_s + val, 0);

        /* Сразу ищем максимум в массиве */
        ans = prev_s >= ans ? prev_s : ans; 
    }

    std::cout << ans << std::endl;
}

int main() {
    solution();
    return 0;
}