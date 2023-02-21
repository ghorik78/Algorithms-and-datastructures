#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Sign
{
    int value, number;
};


void solution() {
    int n;
    cin >> n;

    vector<Sign> signs(n); 
    Sign maxPoint, minPoint;
    minPoint.value = INT32_MAX;

    /* Читаем все точки и запоминаем их внутри вектора */
    for (int i = 0; i < n; ++i) {
        cin >> signs[i].value; signs[i].number = i + 1;

        /* Ищем минимум и максимум */
        maxPoint = signs[i].value >= maxPoint.value ? signs[i] : maxPoint;
        minPoint = signs[i].value < minPoint.value ? signs[i] : minPoint;
    }

    --minPoint.number; --maxPoint.number;

    /* Внутри вектора каждой точке находим пару и выводим её */
    while (minPoint.number != maxPoint.number) {
        cout << signs[maxPoint.number].number << " " << signs[minPoint.number].number << " ";

        --signs[minPoint.number].value; --signs[maxPoint.number].value;
        minPoint.value = INT32_MAX; maxPoint.value = 0;

        for (size_t i = 0; i < n; ++i) {
            if (signs[i].value && signs[i].value >= maxPoint.value) {
                maxPoint.value = signs[i].value;
                maxPoint.number = i;
            }
            if (signs[i].value && signs[i].value < minPoint.value) {
                minPoint.value = signs[i].value;
                minPoint.number = i;
            }
        }
        
        /* Если пару найти уже не удаётся, то переходим в циклу вывода точек без пары */
        if (minPoint.value == INT32_MAX) break;
    }

    /* Цикл вывода оставшихся без пары точек */
    for (int i = 0; i < maxPoint.value; ++i) {
        cout << signs[maxPoint.number].number << " ";
    }
}

int main() {
    solution();
    return 0;
}