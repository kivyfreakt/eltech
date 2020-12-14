#include <vector>
#include <list>
#include <queue>

class Graph
{
    int num, n, m;
    vector <list<int>> LIST;

    void spaning_tree(int);
    public:
        Graph(int); // ввод графа
        // Graph(int, char); // генерирование случайного графа
        void spaning_forest();
        void print();
};

class Forest
{
    int n; // количество вершин
    int m; // количество ребер
    vector <pair<int, int>> edges; // список ребер
    public:
        Forest();
        void print();
    friend class Graph;
};

char ch(char c) {return c+'a';}
