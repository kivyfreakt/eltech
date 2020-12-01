#include <iostream>
#include <cstring>
#include <ctime>

using namespace std;

template<class Item> class STACK
{
    Item *S;
    int t;
public:
    STACK(int maxt):S(new Item[maxt]), t(0){}
    int empty() const{return t==0;}
    void push(Item item) {S[t++]=item;}
    Item pop(){return(t? S[--t]:0);}
};

class Node
{
    char tag;
    Node *left;
    Node *middle;
    Node *right;
    int depth;
public:
    Node():left(nullptr), middle(nullptr), right(nullptr) {}
    ~Node()
    {
        if (left) delete left;
        if (middle) delete middle;
        if (right) delete right;
    }
    bool is_leaf()
    {
        if (!left && !middle && !right)
            return true;
        return false;
    }
friend class Tree;
};

class Tree {
    Node *root;
    char num, maxnum;
    int maxrow, offset;
    int max_depth;
    char **SCREEN;
    void clrscr();
    Node* MakeNode(int depth);
    void OutNodes(Node* v, int r, int c);
public:
    Tree(char num, char maxnum, int maxrow);
    ~Tree();
    void MakeTree() {root = MakeNode(0);}
    bool exist() {return root != nullptr;}
    void OutTree();
    int DFS();
    void RDFS(int*);
    void RDFS(Node*, int*);
};

Tree::Tree(char nm, char mnm, int mxr):
num(nm), maxnum(mnm), maxrow(mxr), offset(40), root(nullptr), SCREEN(new char *[maxrow])
{
    for (int i=0;i<maxrow;i++)
        SCREEN[i] = new char[80];
}

Tree:: ~Tree()
{
    for (int i=0;i<maxrow;i++)
        delete[] SCREEN[i];
    delete[] SCREEN;
    delete root;
}


Node *Tree::MakeNode(int depth)
{
    Node *v = nullptr;
    int Y = (depth < rand() % 4 + 1) && (num <= maxnum);
    if (Y)
    {
        v = new Node;
        v->depth = depth;
        v->left = MakeNode(depth+1);
        v->tag = num++;
        v->middle = MakeNode(depth+1);
        v->right = MakeNode(depth+1);
    }
    if(depth-1 > max_depth)
        max_depth = depth-1;
    return v;
}

void Tree::OutTree()
{
    clrscr();
    OutNodes(root, 1, offset);
    for (int i=0; i<maxrow; i++)
    {
        SCREEN[i][79]=0;
        cout << '\n' << SCREEN[i];
    }
    cout << '\n';
}

void Tree::clrscr()
{
    for (int i=0; i<maxrow; i++)
        memset(SCREEN[i], '.', 80);
}

void Tree::OutNodes(Node *v, int r, int c)
{
    if (r && c && (c<80)) SCREEN[r-1][c-1] = v->tag;
    if (r < maxrow) {
        if (v->left) OutNodes(v->left, r+1, c-(offset >> r)+1);
        if (v->middle) OutNodes(v->middle, r+1, c);
        if (v->right) OutNodes(v->right, r+1, c+(offset >> r)-1);
    }
}


int Tree::DFS()
/*
     Нерекурсивный обход дерева в глубину
*/
{
    const int MaxS = 20; // максимальный размер стека
    int count = 0;
    STACK <Node *> stack(MaxS);
    stack.push(root);
    while (!stack.empty())
    {
        Node *v = stack.pop();
        cout << v->tag << '_';
        if (v->depth != max_depth && v->is_leaf())
            count++;
        if (v->right)
            stack.push(v->right);
        if (v->middle)
            stack.push(v->middle);
        if (v->left)
            stack.push(v->left);
    }
    return count;
}

void Tree::RDFS(int* c)
{
    RDFS(root, c);
}

void Tree::RDFS(Node* v, int* count)
/*
    Рекурсивный обход дерева в глубину
*/
{
    if (v)
    {
        cout << v->tag << '_';
        if (v->depth != max_depth && v->is_leaf())
            (*count)++;
        RDFS(v->left, count);
        RDFS(v->middle, count);
        RDFS(v->right, count);
    }
}


int main()
{
    Tree root('A', 'Z', 8);
    int num_leaves;
    srand(time(NULL));

    root.MakeTree();
    if (root.exist())
    {
        cout << "Дерево: \n";
        root.OutTree();
        cout<< '\n' << "Обход в глубину: ";
        num_leaves = root.DFS();
        cout << "\nКоличество листьев не на самом нижнем уровне: " << num_leaves << '\n';
        num_leaves = 0;
        cout<< '\n' << "Обход в глубину (рекурсивный): ";
        root.RDFS(&num_leaves);
        cout << "\nКоличество листьев не на самом нижнем уровне: " << num_leaves << '\n';
    }
    else cout << "Дерево пусто!";
    return 0;
}


//
// #include <iostream>
// #include <string.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// using namespace std;
//
// //Класс узел дерева
// class Node {char d;
//     Node *left; //левый сын
//     Node *middle; //средний сын
//     Node *right; //правый сын
// public:
//     Node(): left(NULL), middle(NULL), right(NULL){} //конструктор узла
//     ~Node(){if(left) delete left; //деструктор
//     if(middle) delete middle;
//     if(right) delete right;}
// friend class Tree; //дружественный класс дерево
// };
// //класс дерево
// class Tree
// {
//     Node *root; //указатель на корень дерева
//     char num, maxnum; //счетчик тегов и максимальный тег
//     int maxrow, offset; //максимальная глубина, смещение корня
//     char **SCREEN; //память для выдачи на экран
//     void clrscr(); //очистка рабочей памяти
//     Node *MakeNode(int depth);// создание поддерева
//     void OutNodes(Node *v, int r, int c); //выдача поддерева
//     Tree(const Tree&); //фиктивный конструктор копии
//     Tree operator=(const Tree&) const; //фиктивное присваивание
// public:
//     Tree(char num, char maxnum, int maxrow);
//     ~Tree();
//     void MakeTree() //ввод - генерация дерева
//     {
//         root=MakeNode(0);
//     }
//     bool exist(){return root!=NULL;} //проверка - дерево не пусто?
//     int DFS(); //обход дерева
//     void OutTree(); //выдача на экран
// };
// Tree::Tree(char nm, char mnm, int mxr):
//     num(nm), maxnum(mnm), maxrow(mxr), offset(40), root(NULL),
//     SCREEN(new char* [maxrow])
//     {
//         for(int i=0; i<maxrow; i++) SCREEN[i]=new char[80];
//     }
// Tree::~Tree()
// {
//     for(int i=0; i<maxrow; i++) delete []SCREEN[i];
//     delete []SCREEN;
//     delete root;
// }
// //функция-член для генерации случайного дерева
// Node* Tree::MakeNode(int depth)
// {
//     Node* v=NULL;
//     int Y=(depth<rand()%6+1)&&(num<='z');
//     //cout<<"Node("<<num<<','<<depth<<")1/0:"; cin>>Y;
//     if(Y){//создание узла, если Y=1
//         v=new Node;
//         v->left=MakeNode(depth+1);
//         v->d=num++;
//         v->middle=MakeNode(depth+1);
//         v->right=MakeNode(depth+1);
//         }
//     return v;
// }
// void Tree::OutTree()
// {
//     clrscr();
//     OutNodes(root, 1, offset);
//     for(int i=0; i<maxrow; i++){
//         SCREEN[i][79]=0;
//     cout<<'\n'<<SCREEN[i];
// }
// cout<<'\n';
// }
// void Tree::clrscr()
// {
//     for(int i=0; i<maxrow; i++)
//         memset(SCREEN[i],'.',80);
// }
// void Tree :: OutNodes(Node* v, int r, int c)
// {
//     if(r&&c&&(c<80)) SCREEN[r-1][c-1]=v->d; //вывод метки
//     if(r<maxrow){
//         if(v->left) OutNodes(v->left, r+1,  c-(offset>>r)); //левый сын
//         if(v->middle) OutNodes(v->middle, r+1, c); //средний сын
//         if(v->right) OutNodes(v->right, r+1, c+(offset>>r)); //правый сын
//         }
// }
// template<class Item> class STACK
// {
//     Item *S;
//     int t;
// public:
//     STACK(int maxt):S(new Item[maxt]), t(0){}
//     int empty() const{return t==0;}
//     void push(Item item) {S[t++]=item;}
//     Item pop(){return(t? S[--t]:0);}
// };
//
// //Нерекурсивный обход дерева в глубину
//
// int Tree::DFS()
// {
//     const int MaxS=20; //максимальный размер стека
//     int count=0;
//     STACK<Node*> S(MaxS); //создание стека указателей на узлы
//     S.push(root);
//     while(!S.empty()) //пока стек не пуст...
//     {
//         Node *v=S.pop(); //поднять узел из стека
//         cout<<v->d<<'_';//выдать тег, счет узлов
//         count++;
//         if(v->right) S.push(v->right); //STACK<-(правый сын)
//         if(v->middle) S.push(v->middle); //STACK<-(средний сын)
//         if(v->left) S.push(v->left); //STACK<-(левый сын)
//     }
//     return count;
// }
//
// int main()
// {
//     int n=0;
//     Tree Tr('a','z',8);
//     srand(time(NULL));
//     setlocale(LC_ALL,"Russian");
//     Tr.MakeTree();
//     if(Tr.exist()){
//         Tr.OutTree();
//         cout<<'\n'<<"Обход в глубину:";
//         n=Tr.DFS();
//         cout<<"Пройдено узлов="<<n;
//     }
//     else cout<<"Дерево пусто!";
//     cout<<'\n'<<"===Конец===";
// }
