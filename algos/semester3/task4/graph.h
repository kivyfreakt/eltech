#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <queue>
#include <string>
#include <iostream>

using namespace std;

class Forest
{
    int n; // количество вершин
    int m; // количество ребер
    vector <pair<int, int>> edges; // список ребер
    public:
        Forest(int maxV): n(maxV) {};
        void print();
    friend class Graph;
};


class Graph
{
    int n; // количество вершин
    int m; // количество ребер
    vector <list<int>> LIST; // список смежности

    void spanning_tree(int, bool*, vector<pair<int, int>>*, int*); // построение сгивающего дерева
    public:
        Graph(); // пример графа
        Graph(int); // ввод графа
        Graph(int, char); // генерирование случайного графа
        Forest spanning_forest(); // постоение ширинного стягивающего леса
};

#endif
