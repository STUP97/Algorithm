#include<iostream>
#include<fstream>
using namespace std;

ifstream input_fp("stickers.inp");
ofstream output_fp("stickers.out");

int size;
int stickers[2][100001];
int memoization[2][100001];
int result;

void input_data(){
	int temp;
	input_fp >> size;
	for(int i=0; i<2; i++){
		for(int j=0; j<size; j++){
			input_fp >> stickers[i][j];
			memoization[i][j] = -1;
		}
	}
}

int calc(int y, int x){
	if(x == size-1){
		return stickers[y][x];
	}
	else if(x != -1){
		if(memoization[y][x] != -1){
			return memoization[y][x];
		}
	}
	int sum = -1;
	int temp;
	if(x == -1){
		temp = calc(0,x+1);
		if(sum < temp){
			sum = temp;
		}
		temp = calc(1,x+1);
		if(sum < temp){
			sum = temp;
		}
		return sum;
	}
	else{
		if(y == 0){
			temp = calc(1,x+1);
			if(sum < temp){
				sum = temp;
			}
		}
		else{
			temp = calc(0,x+1);
			if(sum < temp){
				sum = temp;
			}
		}
		if(x != size-2){
			temp = calc(0,x+2);
			if(sum < temp){
				sum = temp;
			}
			temp = calc(1,x+2);
			if(sum < temp){
				sum = temp;
			}
		}
	}	
	return memoization[y][x] = sum + stickers[y][x];
}

int main(){
	int T;
	input_fp >> T;
	for(int i=0; i<T; i++){
		input_data();
		if(size > 10000){
			for(int i=0; i<size/10000; i++){
				result = calc(0, size-i*10000);
			}
		}
		result = calc(0,-1);
		output_fp << result << endl;
	}
}
