#include <bits/stdc++.h>
using namespace std;
struct node{
    int value;
    struct node *ptr;
};
typedef struct node *NODE;
NODE XOR(NODE x,NODE y){
    return reinterpret_cast<NODE> (reinterpret_cast<uintptr_t> (x) ^ reinterpret_cast<uintptr_t> (y));
}
void push(NODE *head,int value){
    NODE newNode = (NODE)malloc(sizeof(struct node));
    newNode->value = value;
    newNode->ptr=XOR(NULL,*head);
    if(*head){
        (*head)->ptr=XOR(newNode,(*head)->ptr);
    }
    *head=newNode;
}
void traverse(NODE head){
    NODE curr=head;
    NODE prev=NULL;
    NODE next;
    while(curr!=NULL){
        cout<<curr->value<<"->";
        next=XOR(prev,curr->ptr);
        prev=curr;
        curr=next;
    }
    cout<<"NULL"<<endl;
}
NODE deleteNode(NODE head){
    if(head==NULL){
        return NULL;
    }
    NODE next=head->ptr;
    if(next){
        next->ptr=XOR(head,next->ptr);
    }
    free(head);
    return next;
}
int main(){
    int arr[] = {1,2,3,4,5,6,7,8};
    NODE head=NULL;
    for(int i=0;i<8;i++){
        push(&head,arr[i]);
    }
    traverse(head);
    while(head!=NULL)
        head = deleteNode(head);
    traverse(head);
    return 0;
}
