/*
Given a 2-D matrix, find the element having maximum value using multi-threading.
*/

#include <iostream>
#include <thread>
#include <future>  // used to get function return value

using namespace std;

const int V = 4; 
int mat[][V] = {{1, 5, 3, 6}, {22, 80, 4, 34}, 
            	{4, 45, 67, 3}, {99, 3, 23, 3}}; 

int findMax(int row){
	int* arr = mat[row];
	int max = -9999999;
	for(int i=0; i<V; i++)
		if(arr[i] > max)
			max = arr[i];
	return max;
}

int main() {
	/*for(int i=0; i<4; i++){
		int* temp = mat[i];
		for(int j=0; j<4; j++)
			cout << temp[j] << ' ';
		cout << '\n';
	}*/
	
	int max[4];
	for(int i=0; i<4; i++){
		future<int> ret = async(findMax, i);
		max[i] = ret.get();
	}
	
	int ret = max[0];
	for(int i=1; i<4; i++)
		if(max[i] > ret)
			ret = max[i];
			
	cout << ret << '\n';
	
	


}
