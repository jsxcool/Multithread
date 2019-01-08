/*
The problem is to synchronize n number of threads using pthread library. The idea is take thread count and print 1 in first thread, print 2 in second thread, print 3 in third thread, ….. print n in nth thread and again repeat from thread 1 infinitely.
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>         // std::chrono::seconds
#include <condition_variable>

using namespace std;

mutex mtx;
condition_variable cond;
int num = 1;

void print(int i){
	mtx.lock();
	cout << i << ' ';
	mtx.unlock();
}

void print2(int i){
	if(num == i){
		mtx.lock();
		cout << i << ' ';
		num++;
		mtx.unlock();
	}
	else{
		cond.notify_all();
	}
}


int main(){
	vector<thread> vec;
	int n = 1;
	cout << "enter the number of threads: ";
	cin >> n;
	
	// create n default threads
	for(int i=0; i<n; i++)
		vec.push_back(thread());
		
	// assign function to thread
	for(int i=0; i<n; i++){
		vec[i] = thread(print, i+1);
		// waiting print to finish
		this_thread::sleep_for(chrono::milliseconds(10)); 
	}

	
	/*    can't work
	for(int i=0; i<n; i++){
		vec[i] = thread(print2, i+1);
	}
	*/
	
			
	// wait all threads done
	for(int i=0; i<n; i++)
		vec[i].join();


	cout << '\n';
	
}
