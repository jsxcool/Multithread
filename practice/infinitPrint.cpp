#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>         // std::chrono::seconds

using namespace std;

mutex mtx;
condition_variable cond1, cond2, cond3;
int num = 1;

void print(int n){
	while(1){
		unique_lock<mutex> locker(mtx);
		if(num == 1)
			cond1.notify_one();
		else if (num == 2)
			cond2.notify_one();
		else
			cond3.notify_one();
		
		// print the number that a certain thread holds 
		cout << n << ' ';
		
		// print next num
		if(num == 1) {
			cond1.wait(locker);
			num == 2;
		}
		else if(num == 2){
			cond2.wait(locker);
			num == 3;
		}
		else{
			cond3.wait(locker);
			num == 1;
		}
		
		locker.unlock();
	
	}
}

int main(){
	thread t1(print, 1);
	thread t2(print, 2);
	thread t3(print, 3);
	
	t1.join();
	t2.join();
	t3.join();
}

