#include <iostream>
#include <thread>		 
using namespace std;

void fun1(){
	for(int i=0; i<100; i++)
		cout << "from t1: "<< i << '\n';
}


int main(){
	thread t1(fun1);  // t1 starts running
	t1.join();    // join(), means until t1 is completed, it returns, and then go to the next line.	
		
	for(int i=0; i<100; i++)
		cout << "from main(): "<< i << '\n';
	
	// t1.join();     //if placing it here, very different 	

}
