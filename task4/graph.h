#include <vector>
#include <list>
#include <queue>

#ifndef GRAPH_H
#define GRAPH_H


class Graph
{
    int n; // количество вершин
    int m; // количество ребер
    std::vector <std::list<int>> LIST;

    void spanning_tree(int, bool*);
    public:
        Graph(int); // ввод графа
        Graph(int, char); // генерирование случайного графа
        void spanning_forest();
};

// class Forest
// {
//     int n; // количество вершин
//     int m; // количество ребер
//     std::vector <std::pair<int, int>> edges; // список ребер
//     public:
//         Forest();
//     friend class Graph;
// };

#endif
