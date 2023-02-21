#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    int x, y, number;
};

/* Считаем расстояние относительно точки старта */
int distance(Point p) {
    return pow(p.x, 2) + pow(p.y, 2);
}

/* Считаем векторное произведение для направления пути обхода */
int direction(Point a, Point b) {
    return a.x * b.y - b.x * a.y;
}

/* Берём либо ту, которая в положительном направлении пути обхода, либо ближнюю*/
bool operator<(Point a, Point b) {
    return direction(a, b) > 0 || (direction(a, b) == 0 && distance(a) < distance(b));
}

void solution() {
    int n;
    Point start;
    vector<Point> greater, less;
    cin >> n;
    cin >> start.x >> start.y;

    for (int i = 2; i <= n; ++i) {
        Point curr_point;
        cin >> curr_point.x >> curr_point.y;
        curr_point.number = i;
        curr_point.x -= start.x; curr_point.y -= start.y; // смещаем систему координат в начальную точку

        /* Разделяем все точки на два типа */
        if (curr_point.y > 0 || (curr_point.y == 0 && curr_point.x > 0)) greater.push_back(curr_point);
        else less.push_back(curr_point);
    }

    sort(greater.begin(), greater.end()); 
    sort(less.begin(), less.end());

    cout << n << endl << 1 << endl;

    if (!greater.size() || !less.size() || direction(greater[greater.size() - 1], less[0]) > 0) {
        greater.insert(greater.end(), less.begin(), less.end());
        for (size_t i = 0; i < greater.size(); ++i) cout << greater[i].number << endl;
    }
    else {
        less.insert(less.end(), greater.begin(), greater.end());
        for (size_t i = 0; i < less.size(); ++i) cout << less[i].number << endl;
    }
}

int main() {
    solution();
    return 0;
}