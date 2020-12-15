#include "graph.h"

using namespace std;

char ch(char c) {return c+'a';}

Graph :: Graph(int maxV): n(0), m(0)
/*
    Ввод графа на maxV вершинах
*/
{
    int G[maxV][maxV];
    string s;

    // обнуление матрицы
    for (int i = 0; i < maxV; ++i)
        for (int j = 0; j < maxV; ++j)
            G[i][j] = 0;

    cout << "\nВведите множества смежности (строки букв a до z)\n";

    // заполнение матрицы смежности
    do
    {
        cout << "v[" << ch(n) << "] = ";
        cin >> s;
        for (auto i : s)
            if (isalpha(i))
            {
                int j = tolower(i) - 'a';
                G[n][j] = G[j][n] = 1;
            }
        ++n;
    }
    while(isalpha(s[0]) && n < maxV);

    // заполнение списка смежности
    n = m = 0;
    LIST.resize(maxV);
    for (int i = 0; i < maxV; ++i)
    {
        int f = 0;
        cout << '\n' << ch(i) << ": ";
        for (int j = 0; j < maxV; ++j)
            if (G[i][j])
            {
                ++f;
                LIST[i].push_back(j);
                cout << ch(j);
            }
            else cout << '-';
        m += f;
        if (f)
            ++n;
        else
            break;
    }

    cout << "\n|V| = " << n << ", |E| = " << m/2 << '\n';
}


Graph :: Graph(int maxV, char c): n(0), m(0)
/*
    Генерация случайного графа на maxV вершинах.
*/
{
    int G[maxV][maxV];

    // генерация случайной матрицы смежности
    for (int i = 0; i < maxV; ++i)
        for (int j = i; j < maxV; ++j)
            if (i == j)
                G[i][j] = G[j][i] = 0;
            else
                G[i][j] = G[j][i] = rand()%2;

    // заполнение списка смежности
    n = m = 0;
    LIST.resize(maxV);
    for (int i = 0; i < maxV; ++i)
    {
        int f = 0;
        cout << '\n' << ch(i) << ": ";
        for (int j = 0; j < maxV; ++j)
            if (G[i][j])
            {
                ++f;
                LIST[i].push_back(j);
                cout << ch(j);
            }
            else cout << '-';
        m += f;
        if (f)
            ++n;
        else
            break;
    }

    cout << "\n|V| = " << n << ", |E| = " << m/2 << '\n';
}



void Graph :: spanning_tree(int start_node, bool* visited, vector <pair<int, int>> *tree)
/*
    Поиск стягивающего дерева поиском в ширину.
*/
{
    queue<int> q;
    visited[start_node] = true;
    q.push(start_node);

    while (!q.empty())
    {
        int current_node = q.front();
        q.pop();

        for (auto adj_node : LIST[current_node])
            if (!visited[adj_node])
            {
                visited[adj_node] = true;
                q.push(adj_node);
                // cout << "Добавлено ребро: " << current_node << ' ' << adj_node << '\n';
                tree->push_back(make_pair(current_node, adj_node));
            }
    }
    cout << "\n\n";
}

Forest Graph :: spanning_forest()
/*
    Поиск стягивающего леса серией поисков в ширину.
*/
{

    Forest f(n); // т.к стягивающий лес, то количество вершин графа = количество вершин леса
    bool *visited = new bool[n]; // список посещенных вершин для обхода всех компонент

    for (int node = 0; node < n; ++node)
        if (!visited[node]) // если вершина не была посещена, то
        {
            // запускаем обход из этой вершины
            spanning_tree(node, visited, &f.edges);
        }
    delete [] visited;
    return f;
}

void Forest :: print()
{
    cout << "Количество вершин: " << n << '\n';
    cout << "Список ребер: \n";
    for (auto e:edges)
        cout << ch(e.first) << " " << ch(e.second) << '\n';
}
