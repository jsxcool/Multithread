#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <chrono>         // std::chrono::seconds
#include <condition_variable>   // used to wait and notice

using namespace std;

queue<int> data;     // shared data by two threads
mutex mtx;
condition_variable cond;

// produce data
void f1(){
	int count = 10;
	while(count > 0){
		unique_lock<mutex> locker(mtx);
		data.push(count);
		locker.unlock(); 
		cond.notify_one(); // notify one waiting thread: I'm done
		// cond.notify_all(); // wake up all the threads
		count--;
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

// use mutex lock to avoid data racing

// consume data
void f2(){
	int count = 0;
	while(count != 1){  // the last element in the queue
		if(!data.empty()){  // continue checking, waste CPU cycle
			unique_lock<mutex> locker(mtx);
			count = data.front();
			data.pop();
			locker.unlock();
			cout << count << ' ';
		}
	}
}

// Solution:
void f3(){
	int count = 0;
	while(count != 1){  // continue checking, waste CPU cycle
		unique_lock<mutex> locker(mtx);
		// use this lamda function to avoid spurious wake (wake itself)
		cond.wait(locker, [](){ return !data.empty();}); 
		//*** t2 sleeps, untill notified by t1 and the condition(i.e. data is not empty)
		// before going to sleep, t2 releases the locker
		count = data.front();
		data.pop();
		locker.unlock();
		cout << count << ' ';
	}
}



int main(){
// t1, t2 runs concurrently
	thread t1(f1);
	thread t2(f3);
	
	t1.join();
	t2.join();
}
