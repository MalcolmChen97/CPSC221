#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
 #include <iostream> 



int ran;
std::string type;
int guess;

int main(){
	srand(0);
	ran=1+rand()%100;
	guess=0;	
while(guess!= ran){
	std::cin >> type;
	if(type=="end"){
	guess=ran;
}else{
guess=atoi(type.c_str());
if(guess>ran){
std::cout << "too big" << std::endl;}
else if(guess < ran){
std::cout << "too small" << std::endl;}
else{
std::cout << "correct" << std::endl;}

}
 
}
std::cout << "end of game" << std::endl;
return 0;
}


