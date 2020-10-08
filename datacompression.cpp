//check if file exist or not
//capacity badhani hai
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<cstdio>
#include<bits/stdc++.h>
using namespace std;
//huffman node structure
struct huffmantree
{
    int f;
    char d;
    huffmantree *l,*r;
};
huffmantree* newnode(char ,int);
//minheap class
class minheap
{
    int heap_size;
    int capacity;
    huffmantree **a;
public:
    minheap(int j)
    {
        heap_size=0;
        capacity=j;
        a=new huffmantree*[j];
    }
    int parent(int i)
    {
        return((i-1)/2);
    }
    int left(int i)
    {
        return(2*i+1);
    }
    int right(int i)
    {
        return(2*i+2);
    }
    huffmantree *buildtree();
    void insert_node(huffmantree*);
    huffmantree* extract();
    void heapify(int);
    void show()
    {
        huffmantree* pr;
        pr=buildtree();
        pr=pr->r->r->r;
            cout<< char(pr->d) <<"->"<<pr->f<<endl;
    }
};
//to insert a new node in minheap
void minheap::insert_node(huffmantree *el)
{
    heap_size++;
    int y=heap_size-1;
    a[y]=el;
    while(a[parent(y)]->f > a[y]->f && y>=0)
    {
        swap(a[y],a[parent(y)]);
        y=parent(y);
    }
}
//to extract min node
huffmantree* minheap::extract()
{
    if(heap_size==0)
    {
        cout<<"No element to extract";
    }
    else
    {
        if(heap_size==1)
        {
            heap_size--;
            return(a[0]);
        }
        huffmantree* r=a[0];
        a[0]=a[heap_size-1];
        heap_size--;
        heapify(0);
        return(r);
    }
}
//to heapify
void minheap:: heapify(int q)
{
    int sm=q;
    int l=left(q);
    int r=right(q);
    if(l<heap_size && a[l]->f<a[sm]->f)
    {
        sm=l;
    }
    if(r<heap_size && a[r]->f<a[sm]->f)
    {
        sm=r;
    }
    if(sm!=q)
    {
        swap(a[q],a[sm]);
        heapify(sm);
    }
}

//to make huffmann tree
huffmantree* minheap::buildtree()
{
    huffmantree *lef,*rig,*par;
    while(heap_size!=1)
    {
    lef=extract();
    rig=extract();
    par=newnode('$',lef->f+rig->f);
    par->l=lef;
    par->r=rig;
    insert_node(par);
    }
    return(extract());
}







///
string st;
map<char,string> savecodes(char arr[],int i,huffmantree* root,map<char,string> mp)
{
    if(root->l)
    {
        arr[i]='0';
        mp=savecodes(arr,i+1,root->l,mp);
    }
    if(root->r)
    {
        arr[i]='1';
        mp=savecodes(arr,i+1,root->r,mp);
    }
    if(root->r==NULL && root->l==NULL)
    {
        for(int l=0;l<i;l++)
        {
            st[l]=arr[l];
            cout<<st;
        }
        mp[root->d]=st;
        cout<<endl;
        cout<<root->d<<" "<<st<<endl;
    }
    return mp;
}






//to make a NEw Node
huffmantree* newnode(char da,int fr)
{
    huffmantree *temp=new huffmantree;
    temp->f=fr;
    temp->d=da;
    temp->l=NULL;
    temp->r=NULL;
    return temp;
}






////find the frequency of each character in the given file
map<char,int> findfrequency(string nm)
{
    nm+=".txt";
    map<char,int> freq;
    for(int it=0;it<=255;it++)
    {
        char k=char(it);
        freq[k]=0;
    }
    char c;
    ifstream ifile;
    ifile.open(nm.c_str(),ios::in);
    while(ifile>>c)
    {
     freq[c]++;
    }
    return(freq);
}
//////////v





////Main Program
int main()
{
    minheap b(255);
    huffmantree *temp;

    string filename;
    cout<<"Enter Name Of File You Want To Compress";
    cin>>filename;
    map<char,int> frequency;
    frequency=findfrequency(filename);

    map<char,int>::iterator ut;
    for(ut=frequency.begin();ut!=frequency.end();++ut)
    {
        if(ut->second!=0)
            {
                //cout<<ut->first<<"->"<<ut->second<<endl;
                temp=newnode(ut->first,ut->second);
                b.insert_node(temp);
            }
    }

    huffmantree *pre=b.buildtree();

    map<char,string> codes;
    char aray[300];
    codes=savecodes(aray,0,pre,codes);
    map<char,string>::iterator t;
    cout<<codes['m']<<endl;
    for(t=codes.begin();t!=codes.end();++t)
    {
        cout<<t->first<<" Has code ="<<t->second<<endl;
    }
    //b.show();
}
