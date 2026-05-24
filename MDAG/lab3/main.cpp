#include <iostream>
#include <windows.h>

#include <algorithm> // Нужен для функции сортировки std::sort

using namespace std;

const int MAX = 100;

// Структура для удобного хранения ребра
struct Edge {
    int u, v, w;
};

// Компаратор для сортировки ребер по весу (от меньшего к большему)
bool compareEdges(Edge a, Edge b) {
    return a.w < b.w;
}

Edge edges[MAX * MAX]; // Массив для всех ребер графа
int parent_set[MAX];   // Массив родителей для СНМ (Системы Непересекающихся Множеств)

// Функция СНМ: находит «главную» вершину (представителя множества)
int find_set(int v) {
    if (v == parent_set[v])
        return v;
    return parent_set[v] = find_set(parent_set[v]); 
}

// Функция СНМ: объединяет два множества в одно
bool union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        parent_set[b] = a;
        return true; // Объединение успешно (вершины были в разных компонентах)
    }
    return false; // Вершины уже в одном множестве (добавление ребра создаст цикл!)
}

int main() {
    // Включаем русский язык в консоли
    SetConsoleOutputCP(CP_UTF8);


    // 1. Инициализация СНМ: изначально каждая вершина сама себе родитель
    for (int i = 0; i < MAX; i++) {
        parent_set[i] = i;
    }

    // 2. Спрашиваем количество ребер
    int m;
    cout << "Сколько будет ребер? ";
    cin >> m;

    // 3. Ввод ребер
    cout << "Вводи тройки чисел (u v w), где u и v - вершины, а w - вес ребра:" << endl;
    int max_vertex = 0;
    
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        
        // Запоминаем максимальный индекс вершины
        if (edges[i].u > max_vertex) max_vertex = edges[i].u;
        if (edges[i].v > max_vertex) max_vertex = edges[i].v;
    }

    int n = max_vertex + 1; // Общее количество вершин

    // 4. Главный шаг алгоритма Крускала — сортировка ВСЕХ ребер по весу
    sort(edges, edges + m, compareEdges);

    int total_weight = 0;
    int edges_count = 0; // Счётчик ребер, взятых в остов

    cout << "\nРебра в минимальном остовном дереве:" << endl;

    // 5. Перебираем отсортированные ребра и строим остов
    for (int i = 0; i < m; i++) {
        // Пытаемся объединить вершины ребра. Если они в разных компонентах — берем ребро!
        if (union_sets(edges[i].u, edges[i].v)) {
            cout << edges[i].u << " <-> " << edges[i].v << " (вес: " << edges[i].w << ")" << endl;
            total_weight += edges[i].w;
            edges_count++;
            
            // В остове всегда должно быть ровно n - 1 ребер. Если набрали — выходим раньше
            if (edges_count == n - 1) break;
        }
    }

    // Проверка на связность графа
    

    cout << "\nОбщий вес дерева: " << total_weight << endl;

    return 0;
}