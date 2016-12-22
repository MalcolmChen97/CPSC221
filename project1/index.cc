#include <iostream>
#include <fstream>
#include <sstream>
#include <string>       // provides string class
#include <cctype>       // provides isalpha() and tolower()
#include <vector>       // provides ordered array
#include <set>


using namespace std;

// The following function should be moved into your skiplist.cc file when you
// write that.  It implements the random bit generation.
#include <ctime>                // for time()
#include <cstdlib>              // for rand(), srand(), and RAND_MAX

int randBit(void) {             // return a "random" bit
    static int bitsUpperBd=0;
    static int bits;              // store bits returned by rand()
    if( bitsUpperBd == 0 ) {      // refresh store when empty
        bitsUpperBd = RAND_MAX;
        bits = rand();
    }
    int b = bits & 1;
    bits >>= 1;
    bitsUpperBd >>= 1;
    return b;
}

const int MAX_HEIGHT=16;
int pagenumber;
struct haha{ //a node-like struct
    set<int> num;       //record all the pages a haha instance have
    string content;     //the word that the node represent
    int occur;          //the number of occurence of the word
    int height;         //the height of the node
    
    haha * next[MAX_HEIGHT];    //an array of pointers to haha
};



// Remove all characters except letters (A-Z,a-z) from line,
// except keep '-' or '\'' if they are between letters.
void lowercaseWords(string & line) {
    for( string::iterator it = line.begin(); it != line.end(); ++it ) {
        if( !isalpha(*it) ) {
            if( (*it != '-' && *it != '\'') ||
               it == line.begin() || it+1 == line.end() ||
               !isalpha(*(it-1)) || !isalpha(*(it+1)) ) {
                *it = ' ';
            }
        } else {
            *it = tolower(*it);
        }
    }
}


bool helper1(int con,set<int> rest){    //a helper function to help determine whether the "-" can be applied
    return (rest.find(con)!=rest.end());
}
int helper2(int con,set<int> rest){     //a helper function to decide how many numbers are omitted
    int anum=0;
    int acopy=con;
    while (rest.find(acopy+1)!=rest.end()){
        anum++;
        acopy++;
    }
    return anum;
}


haha* update[MAX_HEIGHT];       //A global array that is used to insert new haha

void print(ostream & output, haha* head) {      // a fuction to help write things to the file
    haha* hihi=head->next[0];
   
    while(hihi!=NULL){
        
        output <<hihi->content<<" "<<"("<<hihi->occur<<") ";
        
        int c=1;
        int d=0;
        int occ=0;
        stringstream s;
        
        int maxPage=pagenumber/40+1;
        
        
            while(c<=maxPage){                  //this loop print all things related to page numbers
                if( hihi->num.find(c)!=hihi->num.end()){
                    if(occ==0){
                        s<<c;
                    }
                    if(helper1(c+1,hihi->num)){
                        s<<"-"<<c+helper2(c,hihi->num);
                        c=c+helper2(c,hihi->num);
                    }else if(occ!=0){
                        s<<","<<c;
                    }
                    occ++;
                }
               
                c++;
                           }

        
        
        output<<s.str();
        hihi=hihi->next[0];
        output<<endl;
    }
}





haha *find(haha* head,string w){        // a function to find a haha that contain string w
    haha *head1=head;
    
    for (int h = head1->height - 1; h >= 0; h--) {
        
        while (head1->next[h]!=nullptr  && w.compare(head1->next[h]->content) > 0) {
            
            
                head1 =  head1->next[h];
            
        }
        update[h]=head1;
        if ( head1->next[h]!=nullptr && !head1->next[h]->content.compare(w)) {
            
            
            return head1->next[h];
        }
        
    }
    
    return nullptr;     //if it doesnt find anything, just return a null pointer.
}

int randomHeight() {    //to generate a random number between 1 and MAX_HEIGHT
    srand(time(0));
    int i=0;
    for (i = 1; i<MAX_HEIGHT; ++i) {
        if (randBit() == 1) break;
    }
    return i;
}

void insert(haha* head,haha* tem) {     //use the global array update to insert haha
   
    for (int h = 0; h < tem->height; ++h) {
        if(update[h]!=NULL) {
        tem->next[h] = update[h]->next[h];    // initialize x's next pointers
        
        }
        update[h]->next[h]=tem;
    }
}

int main(int argc, char *argv[]) {
    if( argc != 3 ) {
        cerr << "Usage: " << argv[0] << " book.txt index.txt" << endl;
        exit(1);
    }
    
    ifstream fin;
    fin.open(argv[1]);
    if( !fin.is_open() ) {
        cerr << "Unable to open " << argv[1] << endl;
        exit(2);
    }
    
    ofstream fout;
    fout.open(argv[2]);
    if( !fout.is_open() ) {
        cerr << "Unable to open " << argv[2] << endl;
        exit(3);
    }
    
    string line, word;
    pagenumber=0;
    haha * head=new haha;
    head->content.clear();
    head->occur = 0;
    head->height = MAX_HEIGHT;
    
    
    
    while( !fin.eof() ) {
        pagenumber++;
        getline(fin,line);
        lowercaseWords(line);
        istringstream iss(line, istringstream::in);
        while( iss >> word ) {
            
            
            
            haha* node=find(head,word);
            if(node!=nullptr){          //if the word is found
                node->occur++;
                node->num.insert(pagenumber/40+1);
                
            }else{                  //if the word is found
                
                haha *tem=new haha;
                tem->content=word;
                tem->occur=1;
                tem->height=randomHeight();
                tem->num.insert(pagenumber/40+1);
                insert(head,tem);
            }
            
        }
    }
    
    print(fout, head);
    
}

