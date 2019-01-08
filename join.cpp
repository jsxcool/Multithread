#include <iostream>
#include <thread>		  // std::thread, std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
using namespace std;

// join: join one thread to the process
// After a call to this function, the thread object becomes non-joinable and can be destroyed safely.
 
void pause_thread(int n) 
{
  std::this_thread::sleep_for (std::chrono::seconds(n));
  std::cout << "pause of " << n << " seconds ended\n";
}
 
int main() 
{
  std::cout << "Spawning 3 threads...\n";
  std::thread t1 (pause_thread,1);
  std::thread t2 (pause_thread,2);
  std::thread t3 (pause_thread,3);
  
  std::cout << "Done spawning threads. Now waiting for them to join:\n";
  t1.join();   // wait t1 finish, it returns, go to next instruction
  t2.join();
  t3.join();
  std::cout << "All threads joined!\n";
  
  // A thread object is joinable if it represents a thread of execution.
  // After either its members join or detach has been called, it's unjoinable
  cout << "after joining, t1, t2 joinable ? "<< t1.joinable() << t2.joinable() << "\n";

	thread t4;
	cout << "only default created, t4 joinable ? "<< t4.joinable() << '\n';
	
	t4 = thread(pause_thread, 1);
	cout << "after equipped with function, t4 joinable ? "<< t4.joinable() << '\n';
	t4.join();

    return 0;
}
