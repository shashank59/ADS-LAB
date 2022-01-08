#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class Node{
    public:
        int value;
        Node *left,*right;
        int height;
        Node(int value,Node *left,Node *right,int height){
            this->value=value;
            this->left=left;
            this->right=right;
            this->height=height;
        }
};

int height(Node *n){
    if(n==NULL)
        return 0;
    return n->height;
}

Node *newNode(int value){
    Node *node=new Node(value,NULL,NULL,1);
    return node;
}

Node *rightRotate(Node *element){
    Node *left=element->left;
    Node *right=left->right;
    left->right=element;
    element->left=right;

    element->height=1+max(height(element->left),height(element->right));
    left->height=max(height(left->left),height(left->right))+1;
    return left;
}

Node *leftRotate(Node *element){
    Node *right=element->right;
    Node *left=right->left;
    right->left=element;
    element->right=left;

    element->height=1+max(height(element->left),height(element->right));
    right->height=max(height(right->left),height(right->right))+1;
    return right;
}

int balance(Node *n){
    return height(n->left)-height(n->right);
}


Node *insert(Node *n,int key){
    if(n==NULL){
        return newNode(key);
    }

    if(n->value>key){
        n->left=insert(n->left,key);
    }else if(n->value<key){
        n->right=insert(n->right,key);
    }else{
        return n;
    }

    n->height=1+max(height(n->left),height(n->right));

    int bal=balance(n);

    if(bal>1 && n->left->value>key){
        return rightRotate(n);
    }
    if(bal>1 && n->left->value<key){
        n->left=leftRotate(n->left);
        return rightRotate(n);
    }

    if(bal<-1 && n->right->value<key){
        return leftRotate(n);
    }

    if(bal<-1 && n->right->value>key){
        n->right=rightRotate(n->right);
        return leftRotate(n);
    }
    return n;
}

void inOrder(Node *n){
    if(n==NULL){
        return;
    }
    inOrder(n->left);
    std::cout << "Value: " << n->value << " Height: " << n->height << endl;
    inOrder(n->right);
}

Node *deleteNode(Node *root,int key){
    if(root==NULL)
        return root;
    if(key<root->value){
        root->left=deleteNode(root->left,key);
    }else if(key>root->value){
        root->right=deleteNode(root->right,key);
    }else{
        if(root->left==NULL&&root->right==NULL){
            free(root);
            return NULL;
        }else if(root->left==NULL&&root->right!=NULL){
            Node *temp=root->right;
            free(root);
            return temp;
        }else if(root->left!=NULL&&root->right==NULL){
            Node *temp=root->left;
            free(root);
            return temp;
        }else{
            Node *curr=root->right;
            while(curr->left!=NULL){
                curr=curr->left;
            }
            root->value=curr->value;
            root->right=deleteNode(root->right,curr->value);
        }

        if(root==NULL){
            return root;
        }
        root->height=1+max(height(root->left),height(root->right));
        int bal=balance(root);
        if(bal>1&&balance(root->left)>0){
            return rightRotate(root);
        }else if(bal>1&&balance(root->left)<0){
            root->left=leftRotate(root->left);
            return rightRotate(root->right);
        }else if(bal<-1&&balance(root->right)<0){
            return leftRotate(root);
        }else if(bal<-1&&balance(root)){
            root->right=rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }
}




int main(){
    Node *root=NULL;
    root = insert(root,13);
    root = insert(root,10);
    cout << "first print"<<endl;
    inOrder(root);
    root = insert(root,9);
    cout << "second print"<<endl;
    inOrder(root);
    root = insert(root,11);
    cout << "third print"<<endl;
    root = insert(root,40);
    root = insert(root,-23);
    inOrder(root);
    root = deleteNode(root,-23);
    inOrder(root);
    return 0;
}
