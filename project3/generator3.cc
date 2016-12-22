
#include <iostream>
#include <cstdlib> // for atoi
#include <time.h> 

using namespace std;
int main(int argc, char* argv[])
{
    if (argc != 2) // remember, argv[0] is the program name
    {
        cerr << "Wrong number of arguments!" << endl;
        return 1; }

	srand(time(NULL));
	


    int n = atoi(argv[1]);



    for(int i = 1; i <= n/2; i++) {
        cout << "I " << i << endl;
        
    }

    for(int i = 1; i <=n/2; i++) {
        cout << "F " <<i << endl;
        
    }
    return 0; }
