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
    ~STACK(){delete [] S;}
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
    Node* MakeNode(int, char);
    void OutNodes(Node*, int, int);
    void RDFS(Node*, int*);
public:
    Tree(char, char, int);
    ~Tree();
    void MakeTree() {root = MakeNode(0, 0);}
    void InpTree() {root = MakeNode(0, 1);}
    bool exist() {return root != nullptr;}
    void OutTree();
    int DFS();
    void RDFS(int*);
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


Node *Tree::MakeNode(int depth, char flag)
{
    Node *v = nullptr;
    int Y;

    if (flag)
    {
        if (depth < maxrow)
        {
            cout << "Вершина (Глубина: " << depth << ", Тег: " << num << ") 1/0: ";
            cin >> Y;
        }
        else
        {
            cout << "Вы достигли максимальной глубины дерева! Невозможно создать потомка\n";
            Y = 0;
        }
    }
    else
        Y = (depth < rand() % 4 + 1) && (num <= maxnum);

    if (Y)
    {
        v = new Node;
        v->depth = depth;
        v->left = MakeNode(depth+1, flag);
        v->tag = num++;
        v->middle = MakeNode(depth+1, flag);
        v->right = MakeNode(depth+1, flag);
    }

    if(depth-1 > max_depth)
        max_depth = depth-1;

    return v;
}

void Tree::OutTree()
{
    clrscr();
    OutNodes(root, 1, offset);
    for (int i=0; i < maxrow; i++)
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
{
    const int MaxS = 20;
    int count = 0;
    STACK <Node *> stack(MaxS);
    stack.push(root);
    while (!stack.empty())
    {
        Node *v = stack.pop();
        if (v->depth != max_depth && v->is_leaf())
        {
            count++;
            cout << '[' << v->tag << "]_";
        }
        else
            cout << v->tag << '_';
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
{
    if (v)
    {
        if (v->depth != max_depth && v->is_leaf())
        {
            (*count)++;
            cout << '[' << v->tag << "]_";
        }
        else
            cout << v->tag << '_';
        RDFS(v->left, count);
        RDFS(v->middle, count);
        RDFS(v->right, count);
    }
}


int main()
{
    srand(time(NULL));
    Tree root('A', 'Z', 5);
    int menu_item,
        num_leaves;

    do
    {
        cin.sync();
        cout << "1 - Ввести дерево\n";
        cout << "2 - Сгенерировать дерево\n";
        cout << "> ";
        cin >> menu_item;
        switch(menu_item)
        {
            case 1:
                root.InpTree();
                cout << "\n\nВведенное дерево:\n";
                break;
            case 2:
                root.MakeTree();
                cout << "\n\nСгенерированное дерево:\n";
                break;
            default:
                cout << "Такого пункта не существует, повторите ввод!\n";
        }
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(32767,'\n');
        }
    }
    while(menu_item > 2 || menu_item < 1 || cin.fail());

    if (root.exist())
    {
        root.OutTree();
        cout<< '\n' << "Обход в глубину: ";
        num_leaves = root.DFS();
        cout << "\nКоличество листьев не на самом нижнем уровне: " << num_leaves << '\n';
        num_leaves = 0;
        cout<< '\n' << "Обход в глубину (рекурсивный): ";
        root.RDFS(&num_leaves);
        cout << "\nКоличество листьев не на самом нижнем уровне: " << num_leaves << '\n';
    }
    else cout << "Дерево пусто!\n";

    return 0;
}
