#include <bits/stdc++.h>

using namespace std;

class Node
{
public:
    int keys[3]; // An array that will hold max of 3 keys.
    Node **child;
    int n;
    bool leaf;

    Node(bool leaf)
    {
        this->leaf = leaf;
        child=new Node*[4];
        n=0;
    }

    void insertNonFull(int key)
    {
        int i = n - 1;
        if (leaf == true)
        {
            while (i >= 0 && keys[i] > key)
            {
                keys[i + 1] = keys[i];
                i--;
            }
            keys[i + 1] = key;
            n++;
        }
        else
        {
            while (i >= 0 && keys[i] > key)
            {
                i--;
            }

            if (child[i + 1]->n == 3)
            {
                splitChild(i + 1, child[i + 1]);

                if (keys[i + 1] < key)
                {
                    i++;
                }
            }
            child[i + 1]->insertNonFull(key);
        }
    }

    void splitChild(int i, Node *y)
    {
        Node *z = new Node(y->leaf);
        z->n = 1;

        z->keys[0] = y->keys[2];

        if (y->leaf == false)
        {
            z->child[0] = y->child[2];
            z->child[1] = y->child[3];
        }

        y->n = 1;

        for (int j = n; j >= i + 1; j--)
        {
            child[j + 1] = child[j];
        }
        child[i + 1] = z;

        for (int j = n - 1; j >= i; j--)
        {
            keys[j + 1] = keys[j];
        }
        keys[i] = y->keys[1];

        n++;
    }

    void traverse()
    {
        // if(leaf==true)
        //     cout<<"No. of elements in the node :"<<n<<" >> ";
        for (int i = 0; i <= n; i++)
        {
            // if(i==n){
            //     cout<<endl;
            // }
            if (leaf == false)
                child[i]->traverse();
            if(i!=n)
                cout << " " << keys[i];
        }
        // if(leaf==true){
        //     cout<<endl;
        // }
        // cout<<endl;
    }
};

class TwThTree
{
    Node *root;

public:
    TwThTree()
    {
        root = NULL;
    }

    void insert(int k)
    {

        // Allocate memory to root if it is NULL.

        if (root == NULL)
        {
            // Initialize root node
            root = new Node(true);
            root->keys[0] = k;
            root->n = 1;
        }
        else
        {
            if (root->n == 3)
            {
                Node *s = new Node(false);
                s->child[0] = root;
                s->splitChild(0, root);

                // int i = 0;
                // if (s->keys[0] < k)
                // {
                //     i++;
                // }
                s->insertNonFull(k);

                root = s;
            }
            else
            {
                root->insertNonFull(k);
            }
        }
    }
    void traverse()
    {
        if (root != NULL)
            root->traverse();
    }
};

int main()
{
    TwThTree t = TwThTree();
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);

    // cout << "Traversal of the constructed tree is ";
    t.traverse();
}
