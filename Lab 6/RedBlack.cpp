#include <bits/stdc++.h>

using namespace std;

class Node{
    public:
    Node *left,*right,*parent;
    char color;
    int key;

    Node(int key){
        this->key=key;
        this->color='R';
        this->left=NULL;
        this->right=NULL;
        this->parent=NULL;
    }
};

class RedblackTree{
    public:
    Node *root;
    bool ll=false,rr=false,rl=false,lr=false;
    RedblackTree(){
        root=NULL;
    }

    Node *rotateLeft(Node* node){
        Node *x=node->right;
        Node *t=x->left;
        x->left=node;
        node->right=t;
        node->parent=x;
        if(t!=NULL){
            t->parent=node;
        }
        return x;
    }

    Node *rotateRight(Node* node){
        Node *x=node->left;
        Node *t=x->right;
        x->right=node;
        node->left=t;
        node->parent=x;
        if(t!=NULL){
            t->parent=node;
        }
        return x;
    }


    Node *insertHelp(Node *root,int data){
        bool f=false;
        if(root==NULL){
            return new Node(data);
        }else if(root->key>data){
            root->left=insertHelp(root->left,data);
            root->left->parent=root;
            if(root!=this->root){
                if(root->color=='R'&&root->left->color=='R'){
                    f=true;
                }
            }
        }else{
            root->right=insertHelp(root->right,data);
            root->right->parent=root;
            if(root!=this->root){
                if(root->color=='R'&&root->right->color=='R'){
                    f=true;
                }
            }
        }

        if(this->ll){
            root=rotateLeft(root);
            root->color='B';
            root->left->color='R';
            this->ll=false;
        }else if(this->rr){
            root=rotateRight(root);
            root->color='B';
            root->right->color='R';
            this->rr=false;
        }else if(this->rl){
            root->right=rotateRight(root->right);
            root->right->parent=root;
            root=rotateLeft(root);
            root->color='B';
            root->left->color='R';
            this->rl=false;
        }else if(this->lr){
            root->left=rotateLeft(root->left);
            root->left->parent=root;
            root=rotateRight(root);
            root->color='B';
            root->right->color='R';
            this->lr=false;
        }

        if(f){
            if(root->parent->right==root){
                if(root->parent->left==NULL||root->parent->left->color=='B'){
                    if(root->left!=NULL&&root->left->color=='R'){
                        this->rl=true;
                    }else if(root->right!=NULL&&root->right->color=='R'){
                        this->ll=true;
                    }
                }else{
                    root->parent->left->color='B';
                    root->color='B';
                    if(root->parent!=this->root){
                        root->parent->color='R';
                    }
                }
            }else{
                if(root->parent->right==NULL||root->parent->right->color=='B'){
                    if(root->right!=NULL&&root->right->color=='R'){
                        this->lr=true;
                    }else{
                        this->rr=true;
                    }
                }else{
                    root->parent->right->color='B';
                    root->color='B';
                    if(root->parent!=this->root){
                        root->parent->color='R';
                    }
                }
            }
            f=false;
        }

        return root;
    }

    void insert(int data){
        if(this->root==NULL){
            this->root=new Node(data); 
            this->root->color='B';
            return;
        }
        this->root=insertHelp(this->root,data);
    }

    void preOrder(Node *root){
        if(root==NULL)
            return;
        cout<<"data:"<<root->key<<" Color:"<<root->color<<endl;
        preOrder(root->left);
        preOrder(root->right);
    }
};

int main(){
    RedblackTree* root=new RedblackTree();
    root->insert(12);
    root->insert(16);
    root->preOrder(root->root);
    root->insert(14);
    root->preOrder(root->root);
    
}
