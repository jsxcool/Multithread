/* mutex is a lockable object that is designed to prevent other threads accessing the 
 * shared resources, when I(the thread) is use them.
*/


#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex mtx;

int count = 0;

void print_block (int n, char c) {
 // between lock() and unlock(), the std::cout is protected
	mtx.lock();
	for (int i=0; i<n; ++i) { std::cout << c; }
	std::cout << '\n';
	mtx.unlock();
	count++;    // however, count is not protected
}
// if there is a exception in the critical section, we may not go to unlock()
// so lock_guard() may be useful.
// because it can only lock local variable or class member, not global variable eg, cout.

    
void add(){
	count++;
}



int main(void){
	std::thread th1 (print_block,100,'*');
	std::thread th2 (print_block,200,'$');
	std::thread th3 (add);
	
	th1.join();
	th2.join();
	th3.join();
	
	cout << count << '\n';
}

