#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

const double PI = 3.141592653;

struct point {
    int x;
    int y;
    size_t number;
    double angle_from_min;
};

/* Функция для сортировки чисел по углу */
int comparator (const void* p1, const void* p2) {
    point p_f = *((point*) p1);
    point p_s = *((point*) p2);
    if (p_f.angle_from_min - p_s.angle_from_min > 0) return 1;
    if (p_f.angle_from_min - p_s.angle_from_min < 0) return -1;
    return 0;
}

void solution() {
    int n, x, y = 0;
    struct point point_min = { 0, INT32_MAX, 0, 0};
    cin >> n;

    vector<point> points(n);
    pair<int, int> minPoint = make_pair(INT32_MAX, 0);

    /* Читаем все точки в цикле, параллельно выбирая опорную */
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
        points[i].number = i + 1;

        /* В качестве опорной точки выбираем либо самую нижнюю, либо самую левую, если она на одной высоте с нижней */
        if (points[i].y < minPoint.first || points[i].y == minPoint.first && points[i].x < points[minPoint.second].x) {
            minPoint.first = points[i].y;
            minPoint.second = i;
        }
    }

    /* Самую первую точку ставим в качестве опорной, чтобы потом отсортировать их по углу */
    swap(points[0], points[minPoint.second]);

    /* Считаем угол до каждой точки от опорной, рассматривая всевозможные случаи (сверху, слева, снизу и т.д.) */
     for (int i = 1; i < n; i++) {
        if (points[i].x == points[0].x) points[i].angle_from_min = PI / 2; 
        else if (points[i].y == points[0].y) points[i].angle_from_min = 0;
        else points[i].angle_from_min = atan((double)(points[i].y - points[0].y) / (double)(points[i].x - points[0].x));
        if (points[i].angle_from_min < 0) points[i].angle_from_min = points[i].angle_from_min + 2 * PI;
    }

    /* Сортируем по углу, а в качестве второй точки выбираем медиану массива углов */
    qsort(&points[0], n - 1, sizeof(struct point), comparator);

    cout << points[0].number << " " << points[n / 2].number << endl;
}

int main() {
    solution();
    return 0;
}