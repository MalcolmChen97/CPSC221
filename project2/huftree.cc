//
//  main.cpp
//  project2
//
//  Created by ChenZengzhan on 2016-11-12.
//  Copyright © 2016 ChenZengzhan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <functional>
#include <iomanip>
#include "priority_queue.h"

#include "codetree.h"

// Print the Huffman code tree and list of codes for a given text file.
using namespace PQ;
using namespace std;





void usage() {
    std::cerr << "Usage: huftree text.txt" << std::endl;
    throw std::exception();
}

int main( int argc, char *argv[] ) {
    if( argc != 2 ) {
        usage();
    }
    
    int freq[256] = { 0 };	// array initialized to 0
    
    std::ifstream fin( argv[1] );
    if( fin.is_open() ) {
        char ch;
        while (fin >> std::noskipws >> ch) {	// don't skip whitespace
            freq[(int)ch]++;
        }
        
        fin.close();
    }
    
    Codetree ct = Codetree( freq );
    //
        ct.printTree();
        ct.printCode();
    //
    return 0;
}
