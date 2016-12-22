#ifndef CODETREE_H_
#define CODETREE_H_
#include <vector>
#include <string>
#include <functional>
#include "priority_queue.h"
using namespace PQ;
using namespace std;
class Codetree{
public:
    int frequency;
    char zimu;
    Codetree* left;
    Codetree* right;
    Codetree( );
    ~Codetree();
    Codetree( int* freq);
    Codetree( int f,char z);
    void printTree();
    void printCode();
    
};
class Compare {
public:
    bool operator()(Codetree* a, Codetree* b) {
        return a->frequency > b->frequency;
    }
};

Codetree* buildtree(int* freq){
    mypriority_queue<Codetree*,vector<Codetree*>,Compare> queque;
    for (int i=0; i<256; i++) {
        if(freq[i]>0){
            Codetree* newtree=new Codetree(freq[i],(char) i);
            queque.push(newtree);
            
        }
    }
    while(queque.size()>1){
        Codetree* a;
        a=queque.top();
        queque.pop();
        Codetree* b;
        b=queque.top();
        queque.pop();
        Codetree* mix=new Codetree(a->frequency+b->frequency,0);
        if(a->frequency>b->frequency){
            mix->left=b;
            mix->right=a;
        }else{
            mix->left=a;
            mix->right=b;
        }
        
        queque.push(mix);
    }
    return queque.top();
}

Codetree::Codetree( int* freq){
    
    
    Codetree* result=buildtree(freq);
    frequency=result->frequency;
    left=result->left;
    right=result->right;
}







void printChar( int ch ) {
    if( ch < 16 ) {
        std::cout << "x0" << std::hex << ch;
    } else if( ch < 32 || ch > 126 ) {
        std::cout << "x" << std::hex << ch;
    } else {
        std::cout << "\"" << (char)ch << "\"";
    }
}

void printTreeHelper(Codetree* r,string pre){
    if( r == NULL ) return;
    if( r->right == NULL ) { // implies r->left == NULL
        printChar(r->zimu);
        std::cout << std::endl;
    } else {
        std::cout << "." << std::endl;
        std::cout << pre << "|`1-";
        printTreeHelper(r->right, pre + "|   ");
        std::cout << pre + "|   " << std::endl;
        std::cout << pre << "`-0-";
        printTreeHelper(r->left, pre + "    ");
    }
    
    
}



void printpreorder(Codetree* root,string ct){
    
    if (root->zimu != 0) {
        if (root->zimu == ' ') {
            cout << "\""<<" "<< "\""<<": "<< ct << '\n';
        } else {
            
            printChar(root->zimu);
            cout<< ": " << ct << '\n';
        }
    } else {
        printpreorder(root->left,ct + "0" );
        printpreorder(root->right,ct + "1");
    }
    
    
}
void Codetree::printCode(){
    Codetree* pointer=this;
    string codetable="";
    printpreorder(pointer,codetable);
}

Codetree::Codetree(int f,char z){
    frequency=f;
    zimu=z;
    left=NULL;
    right=NULL;
}

Codetree::Codetree(){
    
}

void Codetree::printTree(){
    Codetree* pointer=this;
    string h="";
    bool left=false;
    printTreeHelper(pointer,h);
    cout<<'\n';
}

Codetree::~Codetree(){
   }
#endif
