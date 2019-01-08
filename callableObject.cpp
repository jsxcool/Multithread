#include <iostream>
#include <thread>
#include <chrono>         // std::chrono::seconds

using namespace std;

class A{
private:
	int self;
public:
	A():self(0) {}
	
	void operator()(int n) {
		self = n;
	}
	
	void f(int add) {self += add;}
	
	friend ostream& operator << (ostream& s, A a){
		s << a.self << '\n';
		return s; 
	}
};

void square(int x) {cout << x*x << '\n';}

int main(){
	A a;
	cout << a ;   // 0
	
	thread t1(a, 6); // copy of a() runs in t1
	this_thread::sleep_for (std::chrono::milliseconds(100));
	t1.join();
	cout << a;  // 0
	
	thread t2(ref(a), 6); // a() in runs in t2
	this_thread::sleep_for (std::chrono::milliseconds(100));
	t2.join();
	cout << a;  // 6
	
	thread t3(A(), 8); // temperary A() runs in t3; A() is not relational with a
	this_thread::sleep_for (std::chrono::milliseconds(100));
	t3.join();
	cout << a;  // 6
	
	thread t4(&A::f, a, 1);  // copy of a.f(1) in t4;
	this_thread::sleep_for (std::chrono::milliseconds(100));
	t4.join();
	cout << a;  // 6
	
	thread t5(&A::f, &a, 2);  // a.f(2) in t5
	this_thread::sleep_for (std::chrono::milliseconds(100));
	t5.join();
	cout << a;  // 8
	
	thread t6([](int x){cout << x*x << '\n';}, 3);  // lamda function runs in t4
	thread t7(square, 3);   // call regular functio
	
	t6.join();
	t7.join();
	
	
	
	// the same way to use in:   bind(), async(), call_once()
	
	
}
