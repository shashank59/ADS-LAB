#include <bits/stdc++.h>
using namespace std;
class Node{
    public:
        int* keys;
        Node** children;
        int n;
        bool leaf;
        int t;
        Node(int t,bool leaf){
            this->t=t;
            this->leaf=leaf;
            this->keys=new int[2*t-1];
            this->children=new Node*[2*t];
            n=0;
        }

        void insertNonFull(int key){
            int i=n-1;
            if(leaf){
                while(i>=0 && keys[i]>key){
                    keys[i+1]=keys[i];
                    i--;
                }
                keys[i+1]=key;
                n++;
            }else{
                while(i>=0 && keys[i]>key){
                    keys[i+1]=keys[i];
                    i--;
                }
                if(children[i+1]->n==2*t-1){
                    splitChild(i+1,children[i+1]);
                    if(keys[i+1]<key){
                        i++;
                    }
                }
                children[i+1]->insertNonFull(key);
            }
        }

        void splitChild(int index,Node *y){
            Node *z=new Node(y->t,y->leaf);
            // int j=0;
            z->n=t-1;
            for(int j=0;j<t-1;j++){
                z->keys[j]=y->keys[j+t];
            }
            if(!(y->leaf)){
                for(int j=0;j<t;j++){
                    z->children[j]=y->children[j+t];
                } 
            }
            y->n=t-1;

            for(int j=n;j>=index+1;j--){
                children[j+1]=children[j];
            }
            children[index+1]=z;
            for(int j=n-1;j>=index;j--){
                keys[j+1]=keys[j];
            }
            keys[index]=y->keys[t-1];
            n+=1;
        }

        void inOrder(){
            if(n==0){
                return;
            }
            int i=0;
            for(i=0;i<n;i++){
                if(!leaf){
                    children[i]->inOrder();
                }
                // cout<<endl;
                cout<<keys[i]<<" ";
            }
            if(!leaf){
                children[i]->inOrder();
            }
            cout<<endl;
        }
};

class BTree{
    public:
        int t;
        Node* root;

        BTree(int t){
            root=NULL;
            this->t=t;
        }

        void insert(int data){
            if(root==NULL){
                root=new Node(t,true);
                root->keys[0]=data;
                root->n=1;
            }else{
                if(root->n==2*t-1){
                    Node *s=new Node(t,false);
                    s->children[0]=root;
                    s->splitChild(0,root);
                    int i=0;
                    if(s->keys[0]<data){
                        i++;
                    }
                    s->children[i]->insertNonFull(data);
                    root=s;
                }else{
                    root->insertNonFull(data);
                }
            }
        }

        void inOrder(){
            root->inOrder();
        }
};

int main(){
    BTree t(3); // A B-Tree with minimum degree 3
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    cout<<"Hello World"<<endl;
    t.insert(30);
    t.insert(7);
    t.insert(17);
    t.inOrder();
    return 0;
}
