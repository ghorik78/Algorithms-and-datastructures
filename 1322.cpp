#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

int get_index(char c){
    if(c >= 'A' && c <= 'Z') return c-'A';
    if(c == '_') return 26;
    return c-'a'+27;
}

int count(char s[], char sym, int end) {
    int c = 0;
    for (int i = 0; i < end; ++i) {
        if (s[i] == sym) c++;
    }
    return c;
}

int get_symbol_idx(char s[], char sym) {
    for (int i = 0; i < strlen(s); ++i) {
        if (s[i] == sym) return i;
    }
}

int cmp(const void *p1, const void* p2) {
    char p_f = *((char*) p1);
    char p_s = *((char*) p2);
    if (get_index(p_f) > get_index(p_s)) return 1;
    if (get_index(p_s) > get_index(p_f)) return -1;
    return 0;
}

void solution(int n, char s[]) {
    /* Преобразование Барроуза-Уилера */
    map<char, int> unique_less;
    int len = strlen(s);
    vector<int> entries(len);

    if (n >= len) cout << s << endl;
    
    /* Считаем количество вхождений каждого символа в подстроку на соответствующем шаге */
    for (int i = 0; i < len; ++i) {
        char substring[100000];
        for (int j = 0; j < i; ++j) { substring[j] = s[j]; }
        entries[i] = count(substring, s[i], i);
    }

    /* Считаем количество символов, лексикографически меньших, чем текущий */
    int less[54];
    memset(less, 0, sizeof(less));
    for (int i = 0; i < len; ++i) { less[get_index(s[i])]++; }
    for (int i = 1; i < 54; ++i) { less[i] += less[i-1]; }

    /* Количество символов, меньших s_{n-1} + количество строк, начинающихся с s_{n-1} */
    char output[100001]; 
    char last_symbol = s[n]; 
    int  last_symbol_idx = get_symbol_idx(s, last_symbol);
    int  next_symbol_idx = entries[last_symbol_idx] + less[get_index(last_symbol) - 1];
    int  iter = 1;
    output[len - 1] = last_symbol;
    
    while (iter != len) {
        output[len - iter - 1] = s[next_symbol_idx];
        next_symbol_idx = entries[next_symbol_idx] + less[get_index(s[next_symbol_idx]) - 1];
        iter++;
    }

    cout << output << endl;

}

int main(){
    int n; char s[100001];
    cin >> n; cin >> s;

    if ((n <= 0) || (n > 100001)) { n = 100001; }
    solution(n-1, s);
    
    return 0;
}