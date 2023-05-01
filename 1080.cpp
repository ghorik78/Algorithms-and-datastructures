#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct node_t {
	bool isChecked;
	bool color;
	vector<int> neighbors;
};

node_t nodes[99];
queue<int> q;
int n;


int getNextX() {
	int x = 0;
	cin >> x;
	return x;
}


bool isColoringPosible() {

	while (!q.empty()) {
		int curr = q.front();
		q.pop();

		for (int i = 0; i < nodes[curr].neighbors.size();  ++i) {
			int next = nodes[curr].neighbors[i];
			if (!nodes[next].isChecked) {
				nodes[next].isChecked = true;
				nodes[next].color = nodes[curr].color == 0 ? 1 : 0;
				q.push(next);
			}
			else if (nodes[next].color == nodes[curr].color) {
				return false;
			}
		}
	}
	return true;
}


int main() {
    /* Читаем количество стран, а также граничащие между собой страны */
	cin >> n;

	for (int i = 1; i <= n; ++i) {
		int x = 0;
		while ((x = getNextX()) != 0) {
			nodes[i].neighbors.push_back(x);
			nodes[x].neighbors.push_back(i);
		}
	}

    /* Первую страну красим в синий цвет */
	q.push(1);
	nodes[1].isChecked = true;
	nodes[1].color = 0;

    /* Итерируем список всех стран. Каждую из стран пытаемся покрасить в противоположный от предыдущей цвет.
     * Если новая страна уже покрашена, то проверяем, что цвет другой. */
	if (n != 0 && isColoringPosible()) {
		for (int i = 1; i <= n; ++i)
            cout << nodes[i].color;
	}
    /* Если покрасить невозможно, то -1 */
    else {
		cout << - 1;
	}

	getchar();
	getchar();
}
	


