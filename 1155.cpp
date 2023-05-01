#include <iostream>
#include <vector>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <math.h>

using namespace std;

int get_max_vertex_idx(const vector<int>& v) {
    return static_cast<int>(distance(v.begin(), max_element(v.begin(), v.end())));
}

int get_vertex_idx(const vector<char>& v, char vertex) {
    return abs(static_cast<int>(v.begin() - find(v.begin(), v.end(), vertex)));
}

int get_max_possible_vertex_idx(const vector<char>& p_v, const vector<char>& v_names, const vector<int>& v_values) {
    int vertex_idx_1 = get_vertex_idx(v_names, p_v[0]);
    int vertex_value_1 = v_values[vertex_idx_1];

    int vertex_idx_2 = get_vertex_idx(v_names, p_v[1]);
    int vertex_value_2 = v_values[vertex_idx_2];

    int vertex_idx_3 = get_vertex_idx(v_names, p_v[2]);
    int vertex_value_3 = v_values[vertex_idx_3];

    int max_val = max(vertex_value_1, max(vertex_value_2, vertex_value_3));
    if (max_val == vertex_value_1) return vertex_idx_1;
    if (max_val == vertex_value_2) return vertex_idx_2;
    if (max_val == vertex_value_3) return vertex_idx_3;
}

bool is_inside(const vector<char>& v, char value) {
    return count(v.begin(), v.end(), value);
}



void solution() {
    vector<char> v_names = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    vector<int> v_values(8);
    map<char, vector<char>> possible_vertexes = { {'A', {'B', 'D', 'E'}},
                                                  {'B', {'A', 'C', 'F'}},
                                                  {'C', {'B', 'D', 'G'}},
                                                  {'D', {'A', 'C', 'H'}},
                                                  {'E', {'A', 'F', 'H'}},
                                                  {'F', {'B', 'E', 'G'}},
                                                  {'G', {'C', 'F', 'H'}},
                                                  {'H', {'D', 'E', 'G'}} };

    for (int i = 0; i < 8; ++i)
        cin >> v_values[i];

    if (v_values[0] + v_values[2] + v_values[5] + v_values[7] != v_values[1] + v_values[3] + v_values[4] +v_values[6]) { cout << "IMPOSSIBLE"; return; }
    
    while (true)
    {
        int  max_vertex_idx = get_max_vertex_idx(v_values);
        int  max_vertex_value = v_values[max_vertex_idx];
        char max_vertex_name = v_names[max_vertex_idx];

        int max_possible_vertex_idx = get_max_possible_vertex_idx(possible_vertexes[max_vertex_name], v_names, v_values);
        int max_possible_vertex_value = v_values[max_possible_vertex_idx];

        if (max_possible_vertex_value && max_vertex_value) {
            v_values[max_vertex_idx]--;
            v_values[max_possible_vertex_idx]--;
            cout << max_vertex_name << v_names[max_possible_vertex_idx] << "-" << endl;
        }
        
        long long _sum = accumulate(v_values.begin(), v_values.end(), 0);

        if (!_sum) break;

        /* Выбираем ту вершину, которая связана с изолированной вершиной*/
        if (_sum % 2 == 0) {

            for (int i = 0; i < 8; ++i) {
                char current_vertex = v_names[i]; // Выбрали вершину
                int  current_vertex_value = v_values[i];

                if (!current_vertex_value) continue;

                bool is_isolated = true;

                // Ищем изолированную 
                for (char vertex: possible_vertexes[current_vertex]) {
                    int possible_vertex_idx = get_vertex_idx(v_names, vertex);
                    int possible_vertex_value = v_values[possible_vertex_idx];

                    if (possible_vertex_value) { is_isolated = false; break; }
                }

                if (is_isolated) {
                    
                    for (int j = 0; j < 7; ++j) {
                        bool is_possible = false;

                        for (int k = j; k < 8; ++k) {
                            char pivot_vertex = v_names[j];
                            char pivot_possible_vertex = v_names[k];
                            int  pivot_vertex_idx = j;
                            int  pivot_possible_vertex_dx = k;

                            is_possible = is_inside(possible_vertexes[pivot_vertex], pivot_possible_vertex) && (is_inside(possible_vertexes[pivot_vertex], current_vertex) || (is_inside(possible_vertexes[pivot_possible_vertex], current_vertex)));

                            if (is_possible) {
                                int pivot_vertex_value = v_values[j];
                                int pivot_possible_vertex_value = v_values[k];

                                if (!(pivot_vertex_value || pivot_possible_vertex_value)) {
                                    v_values[j]++;
                                    v_values[k]++;
                                    cout << pivot_vertex << pivot_possible_vertex << '+' << endl;

                                    char vertex_to_destroy = is_inside(possible_vertexes[pivot_vertex], current_vertex) ? pivot_vertex : pivot_possible_vertex;
                                    int vertex_to_destroy_idx = get_vertex_idx(v_names, vertex_to_destroy);
                                    int current_vertex_idx = get_vertex_idx(v_names, current_vertex);

                                    v_values[vertex_to_destroy_idx]--;
                                    v_values[current_vertex_idx]--;
                                    cout << vertex_to_destroy << current_vertex << '-' <<endl;

                                    break;
                                }
                            }
                        }

                        if (is_possible) break;
                    }
                }
            }
        }
    }
}

/*Найти ту, у которой значение 0, и она связана с той, которая изолирована.*/

int main() {
    solution();
    return 0;
}