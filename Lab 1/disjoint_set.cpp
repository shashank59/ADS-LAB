#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int parent[25]={};
int find(int val)
{
    while(parent[val]!=-1)
    {
        val=parent[val];
    }
    return val;
}
void isneighbour(int arr[5][5],int i,int j)
{
    int i1,j1;
    if(i==0)
        i1=0;
    else
        i1=i-1;
    for(;i1<5&&i1<=i+1;i1++)
        {
        if(j==0)
            j1=0;
        else
            j1=j-1;
        for(;j1<5&&j1<=j+1;j1++)
        {
            if(arr[i1][j1]==1)
            {
                    int index1=find((i1*5)+j1);
                    int index2=find((i*5)+j);
                    if(index1!=index2)
                    {
                            parent[index1]=index2;
                    }
            }
        }
        }
}
int main()
{
    int arr[5][5],k=0,island=0;
    cout<<"Enter Values to find Island\n";
    for(int i=0;i<25;i++)
    {
        parent[i]=-2;
    }
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
        {
            cin>>arr[i][j];
            if(arr[i][j]==1)
            {
                parent[k]=-1;
            }
            k++;
        }
   for(int i=0;i<5;i++)
        {
        for(int j=0;j<5;j++)
        {
            if(arr[i][j]==1)
            {
                isneighbour(arr,i,j);
            }
        }
        }
        for(int i=0;i<k;i++)
        {
                if(parent[i]==-1)
                island++;
        }
        cout<<"Number of Islands: "<<island<<endl;

}
