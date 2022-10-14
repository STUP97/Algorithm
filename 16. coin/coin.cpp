#include<iostream>
#include<fstream>
#include<vector>
#define MAXIMUM 1000000001
using namespace std;


ifstream input_fp("coin.inp");
ofstream output_fp("coin.out");

int size;
vector<int> arr[2];
long long mem[2][100001];

void input_data(){
	int temp;
	input_fp >> size;
	for(int i=0; i<size; i++){
		input_fp >> temp;
		arr[0].push_back(temp);
	}
	for(int i=0; i<size; i++){
		input_fp >> temp;
		arr[1].push_back(temp);
	}
	arr[0][0] = 0;
	arr[1][size-1] = 0;
}

void mem_make(){
	long long a = 0;
	long long b = 0;
	for(int i=0; i<size; i++){
		if(size - i < size){
			a += arr[0][size-i];
		}
		if(i > 0){
			b += arr[1][i-1];
		}
		mem[0][size-1-i] = a;
		mem[1][i] = b; 
	}
}

long long Bob_score(int x){
	if(mem[0][x] > mem[1][x]){
		return mem[0][x];
	}
	else{
		return mem[1][x];
	}
}

long long get_result(){
	long long result = 10000000000;
	long long temp;
	mem_make();
	for(int i=0; i<size; i++){
		temp = Bob_score(i);
		if(result > temp){
			result = temp;
		}
	}
	return result;
}

void print_result(int result){
	output_fp << result << endl;
}

void reset(){
	arr[0].clear();
	arr[1].clear();
	for(int i=0; i<2; i++){
		for(int j=0; j<size; j++){
			mem[i][j] = 0;
		}	
	}
}

void print_mem(){
	for(int i=0; i<size; i++){
		cout << mem[0][i] << " ";
	}
	cout << endl;
	for(int i=0; i<size; i++){
		cout << mem[1][i] << " ";
	}
	cout << endl;
	cout << endl;
}


int main(){
	int T; 
	long long result;
	input_fp >> T;
	for(int i=0; i<T; i++){
		input_data();
		result = get_result();
		print_result(result);
		//print_mem();
		reset();
	}
}
