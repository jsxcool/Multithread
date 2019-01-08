#include <iostream>
#include <thread>		 
using namespace std;

void fun(string a){
	for(int i=0; i<10; i++)
		cout << a << '\n';
}

int main(){
	string a = "jsx is cool!";
	
	thread t1(fun, a);    // t1 starts running
	
	t1.detach();   // seperate the connection between t1 and other threads (i.e main() here). t1 will run freely on its own --daemon process
	// main() won't wait t1. But t1 still runs for a while after main() terminated until the system shuts down.
	
	// t1.join();   can't do this. Once detached, it's not joinable() 
	
	cout << "main() terminated\n";
}
