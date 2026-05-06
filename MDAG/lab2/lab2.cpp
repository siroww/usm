#include <iostream>

using namespace std;

const int MAX = 100;
int match[MAX];
bool g[MAX][MAX];
bool used[MAX];
int n = MAX, k = MAX; // Просто берем с запасом

bool dfs(int v) {
    if (used[v]) return false;
    used[v] = true;
    for (int to = 0; to < k; to++) {
        if (g[v][to]) {
            if (match[to] == -1 || dfs(match[to])) {
                match[to] = v;
                return true;
            }
        }
    }
    return false;
}

int main() {
    // 1. Спрашиваем только количество ребер
    int m;
    cout << "Skolko budet reber? ";
    cin >> m;

    for (int i = 0; i < MAX; i++) match[i] = -1;

    // 2. Ввод самих ребер
    cout << "Vvodi pary (u v):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (u >= 0 && u < MAX && v >= 0 && v < MAX) {
            g[u][v] = true;
        }
    }

    // 3. Автоматический расчет
    int result = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) used[j] = false;
        if (dfs(i)) result++;
    }

    // 4. Вывод
    cout << "\nNaideno par: " << result << endl;
    for (int i = 0; i < k; i++) {
        if (match[i] != -1) {
            cout << match[i] << " <-> " << i << endl;
        }
    }

    return 0;
}