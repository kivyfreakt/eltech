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
        cout << "Node (" << num << ',' << depth << ") 1/0: ";
        cin >> Y;
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
/*
    Рекурсивный обход дерева в глубину
*/
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


int menu()
{
    int point;
    cout << "Выберите пункт меню" << endl;
    cout << "1 - Ввести дерево" << endl;
    cout << "2 - Сгенерировать дерево" << endl;
    cout << "0 - Выход" << endl;
    cout << "> ";
    cin >> point;
    return point;
}


int main()
{
    srand(time(NULL));
    Tree root('A', 'Z', 6);
    int menu_item,
        num_leaves;
    do
    {
        switch(menu_item = menu())
        {
            case 1:
                root.InpTree();
                break;
            case 2:
                root.MakeTree();
                break;
            case 0:
                cout << "До новых встреч!" << endl;
                break;
            default:
                cout << "Такого пункта не существует, повторите ввод!" << endl;
        }
    }
    while(!menu_item);
        if (menu_item)
        {
            if (root.exist())
            {
                cout << "\n\nДерево: \n";
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
        }

    return 0;
}
