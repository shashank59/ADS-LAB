#include <bits/stdc++.h>

using namespace std;

class Node{
    public:
        int key;
        Node **forward;

        Node(int key,int level){
            this->key=key;
            this->forward = new Node*[level+1];
            memset(forward,0,sizeof(Node*)*(level+1));
        }
};

class skipList
{
private:
    int MaxLevel;
    float P;
    int level;
    Node *head;
public:
    skipList(float P,int MaxLevel){
        this->MaxLevel=MaxLevel;
        this->P=P;
        level=0;
        head = new Node(-1,MaxLevel);
    };
    
    int randomLevel(){
        float r=(float)(rand())/RAND_MAX;
        cout<<r<<" ";
        int lvl=0;
        while(r<P&&lvl<MaxLevel){
            lvl++;
            r=(float)(rand())/RAND_MAX;
        }
        return lvl;
    }

    Node *createNode(int key,int level){
        Node *newNode=new Node(key,level);
        return newNode;
    }

    void insertNode(int key){
        Node *curr=head;
        Node *update[MaxLevel+1];
        memset(update,0,sizeof(Node*)*(MaxLevel+1));

        for(int i=level;i>=0;i--){

            while(curr->forward[i]!=NULL && curr->forward[i]->key<key){
                curr=curr->forward[i];
            }
            update[i]=curr;
        }
        curr=curr->forward[0];
        if(curr==NULL || curr->key != key){
            int rlevel=randomLevel();

            if(rlevel>level){
                for(int i=level+1;i<=rlevel;i++){
                    update[i]=head;
                }
                level=rlevel;
            }

            Node *newNode=new Node(key,rlevel);

            for(int i=0;i<=rlevel;i++){
                newNode->forward[i]=update[i]->forward[i];
                update[i]->forward[i]=newNode;
            }
            cout<<"New Node inserted"<<rlevel<<endl;
        }
    }

    void displayList(){
        cout<<"* Linked List *"<<endl;

        for(int i=0;i<=level;i++){
            Node *curr=head->forward[i];
            cout<<"Level "<<i<<":";
            while(curr!=NULL){
                cout<<curr->key<<" ";
                curr=curr->forward[i];
            }
            cout<<endl;
        }
    }

    void deleteNode(int key){
        Node *curr=head;
        Node *update[MaxLevel+1];
        memset(update,0,sizeof(Node*)*(MaxLevel+1));

        for(int i=level;i>=0;i--){

            while(curr->forward[i]!=NULL && curr->forward[i]->key<key){
                curr=curr->forward[i];
            }
            update[i]=curr;
        }
        curr=curr->forward[0];
        if(curr!=NULL && curr->key == key){
            for(int i=0;i<=level;i++){
                if(update[i]->forward[i]!=curr)
                    break;
                update[i]->forward[i]=curr->forward[i];
            }
            while(level>0&&head->forward[level]==0){
                level--;
            }
            free(curr);            
            return;
        }else{
            cout<<"No such element to delete"<<endl;
        }

    }
};

int main()
{
	// Seed random number generator
	srand((unsigned)time(0));

	// create SkipList object with MAXLVL and P
	skipList lst(0.5,3);

	lst.insertNode(3);
	lst.insertNode(6);
	lst.insertNode(7);
	lst.insertNode(9);
	lst.insertNode(12);
	lst.insertNode(19);
	lst.insertNode(17);
	lst.insertNode(26);
	lst.insertNode(21);
	lst.insertNode(25);
	lst.displayList();
    lst.deleteNode(19);
    lst.deleteNode(9);
    lst.displayList();
}







