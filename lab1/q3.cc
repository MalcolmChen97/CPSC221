#include <iostream>
int global[10];
void fill_array(int a, int b);
int a1;
int a2;
int main(void) {
std::cin >> a1;
std::cin >> a2;	
	fill_array(a1,a2);       	
	for(int i=0;i<10;i++){
	std::cout << global[i]<< " " ; 
}

	std::cout<< std::endl;
	
}

void fill_array(int a, int b){
	global[0]=a;	
	for(int i=1;i<10;i++){
		global[i]=global[i-1]+b;
	}
			
}
