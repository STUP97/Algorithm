#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

ifstream input_fp("jump.inp");
ofstream output_fp("jump.out");

int size;
long long memoization[100001];
vector<int> arr;

void input_data(){
	int temp;
	input_fp >> size;
	for(int i=0; i<size; i++){
		input_fp >> temp;
		arr.push_back(temp);
	}
}

long long calc(int n){
	if(n >= arr.size()){
		return 0;
	}
	else if(memoization[n] != 0){
		return memoization[n];
	}
	int num = arr[n];
	return memoization[n] = num + calc(n+num);
}

void get_maximum(){
	int max = 0;
	int temp;
	for(int i=0; i<size; i++){
		temp = calc(i);
		if(max < temp){
			max = temp;
		}
	}
	output_fp << max << endl;
}

void clear(){
	arr.clear();
	for(int i=0; i<size; i++){
		memoization[i] = 0;
	}
}

int main(){
	int T;
	input_fp >> T;
	for(int i=0; i<T; i++){
		input_data();
		get_maximum();
		clear();
	}
}
