#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <string>

#ifndef GRAPH_H
#define GRAPH_H

class Forest
{
    int n; // количество вершин
    int m; // количество ребер
    std::vector <std::pair<int, int>> edges; // список ребер
    public:
        Forest(int maxV): n(maxV) {};
        void print();
    friend class Graph;
};

class Graph
{
    int n; // количество вершин
    int m; // количество ребер
    std::vector <std::list<int>> LIST; // список смежности

    void spanning_tree(int, bool*, std::vector<std::pair<int, int>>*); // построение сгивающего дерева
    public:
        Graph(); // пример графа
        Graph(int); // ввод графа
        Graph(int, char); // генерирование случайного графа
        Forest spanning_forest(); // постоение ширинного стягивающего леса
};

#endif
