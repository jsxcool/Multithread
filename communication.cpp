#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex mtx;

void factorial(int n, int& x){
	mtx.lock();
	int res = 1;
	for(int i=2; i<=n; i++)
		res *= i;
	
	x = res;	
	mtx.unlock();
}

int x = 0;

int main(){
// pass the result from t1 to main thread
	thread t1(factorial, 8, ref(x));   //if use reference, must type as ref(x)
	
	cout << x << '\n';	  // t1 has not finished, x = 0
	t1.join();
	cout << x << '\n';
	

}
