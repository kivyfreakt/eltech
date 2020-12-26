#ifndef TREE_H
#define TREE_H

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

class Tree
{
    int n; // количество вершин
    int root; // корень дерева
    vector <vector<int>> adj; // список смежности

    string dfs(int, vector<bool>&); // обход дерева в глубину
    string dfs_exec(); // оболочка обхода в глубину
    public:
        Tree(); // пример дерева
        Tree(char); // пример другого дерева (изоморфного 1)
        Tree(int); // ввод дерева
        Tree(int, char); // генерирование случайного дерева
        bool is_isomorph(Tree*); // проверка деревьев на изоморфность
};

#endif
