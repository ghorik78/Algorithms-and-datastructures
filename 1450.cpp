#include <iostream>
using namespace std;

struct pipe_line {
    int a, b;
    int c;
};

int main() {
    int n, m, s, f;

    /* Читаем количество станций и газопроводов */
    cin >> n >> m;
    pipe_line pipes[m];
    int res[n+1];
    fill_n(res, n+1, -1);
    
    /* Для каждого газопровода считываем номера соединяющих станций и его прибыльность */
    for (int i = 0; i < m; i++) 
        cin >> pipes[i].a >> pipes[i].b >> pipes[i].c;

    /* Читаем номера первой и последней станции */
    cin >> s >> f;

    /* Идём по каждому газопроводу. Если с его помощью получаем прибыль, то к суммарной выгоде прибавляем прибыль этого газопровода. */
    res[s] = 0;
    for (int i = 1; i < n; i++)
        for (int j = 0; j < m; j++)
            if (res[pipes[j].a] != -1 && res[pipes[j].b] < res[pipes[j].a] + pipes[j].c)
                res[pipes[j].b] = res[pipes[j].a] + pipes[j].c;
    
    /* Если по итогу получилась какая-то прибыль, то выводим её */
    if (res[f] != -1) cout << res[f];
    else cout << "No solution";
    return 0;
}