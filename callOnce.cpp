/* void call_once( std::once_flag& flag, Callable&& f, Args&&... args );
 * used to substitute if statement, more efficiency
*/


#include <iostream>
#include <mutex>

using namespace std;

once_flag _flag;

void start(){
	cout << "start: ";
}

void print(int count){
	call_once( _flag, start);
	// call_once can also use lamda function, eg,
	// []() { cout<<"start: "; }     to substitute void start()
	cout << count << ' ';
}



int main(){
	int i = 0;
	while(i < 20){
		print(i);
		i++;
	}
	
}
