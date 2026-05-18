#include <iostream>
#include <windows.h>

using namespace std;

// Берем фиксированный размер с запасом, как в твоем коде
const int MAX_V = 100;

int main() {
    // Установка русского языка в консоли
    SetConsoleOutputCP(CP_UTF8);
int adj[MAX_V][MAX_V] = {0};
    int degrees[MAX_V] = {0};

    int m;
    cout << "Сколько будет ребер? ";
    cin >> m;

    // ТЕПЕРЬ ВВОД ПРОСТО ЧЕРЕЗ ПРОБЕЛ
    cout << "Вводи пары чисел через пробел (например, 0 1):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v;
        
        // Считываем только чистые числа, без скобок
        cin >> u >> v;
        
        if (u >= 0 && u < MAX_V && v >= 0 && v < MAX_V) {
            adj[u][degrees[u]] = v;
            degrees[u] = degrees[u] + 1;
            
            adj[v][degrees[v]] = u;
            degrees[v] = degrees[v] + 1;
        }
    }

    // Алгоритм раскраски
    int result[MAX_V];
    for (int i = 0; i < MAX_V; i++) {
        result[i] = -1;
    }

    result[0] = 0;

    bool available[MAX_V];
    for (int i = 0; i < MAX_V; i++) {
        available[i] = false;
    }

    for (int u = 1; u < MAX_V; u++) {
        for (int i = 0; i < degrees[u]; i++) {
            int neighbor = adj[u][i];
            if (result[neighbor] != -1) {
                available[result[neighbor]] = true;
            }
        }

        int cr;
        for (cr = 0; cr < MAX_V; cr++) {
            if (!available[cr]) {
                break;
            }
        }

        result[u] = cr;

        for (int i = 0; i < degrees[u]; i++) {
            int neighbor = adj[u][i];
            if (result[neighbor] != -1) {
                available[result[neighbor]] = false;
            }
        }
    }

    // Вывод результата
    cout << "\nРезультат раскраски графа:" << endl;
    for (int u = 0; u < MAX_V; u++) {
        if (degrees[u] > 0) {
            cout << "Вершина " << u << " ---> Цвет " << result[u] << endl;
        }
    }

    return 0;
}