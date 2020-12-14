#include <iostream>
#include <string>
#include <vector>
#include "graph.h"

using namespace std;

char ch(char c) {return c+'a';}

Graph::Graph(int maxV): n(0), m(0)
{
    int G[maxV][maxV];
    string s;

    for (int i = 0; i < maxV; ++i)
        for (int j = 0; j < maxV; ++j)
            G[i][j] = 0;

    cout << "\nВведите множества смежности (строки букв a до z)\n";

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


Graph::Graph(int maxV, char c): n(0), m(0)
{
    int G[maxV][maxV];
    string s;

    for (int i = 0; i < maxV; ++i)
        for (int j = 0; j < i; ++j)
            G[i][j] = G[j][i] = rand()%2;

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



void Graph :: spanning_tree(int start_node, bool* visited)
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
        {
            if (!visited[adj_node])
            {
                visited[adj_node] = true;
                q.push(adj_node);
                cout << current_node << ' ' << adj_node << '\n';
                // добавить ребро (current_node, adj_node) в дерево
            }
        }
    }
    cout << "\n\n";
}

void Graph :: spanning_forest()
/*
    Поиск стягивающего леса серией поисков в ширину.
*/
{
    // создать лес
    bool *visited = new bool[n];

    for (int node = 0; node < n; ++node)
    {
        if (!visited[node]) // если вершина не была посещена, то
        {
            // запускаем обход из этой вершины
            spanning_tree(node, visited);
        }
    }
}
