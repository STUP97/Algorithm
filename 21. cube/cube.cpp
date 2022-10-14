#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

ifstream input_fp("cube.inp");
ofstream output_fp("cube.out");

int memoization[201][201][201];
int Width,Length,Height;

void input_data(){
	input_fp >> Width >> Length >> Height;
}

void memoization_data(int W, int L, int H, int data){
	memoization[W][L][H] = data;
	memoization[W][H][L] = data;
	memoization[L][W][H] = data;
	memoization[H][W][L] = data;
	memoization[H][L][W] = data;
	memoization[L][H][W] = data;
}

int calc(int W, int L, int H){
//	cout << "W : " << W << " L : " << L << " H : " << H << endl;
	if(memoization[W][L][H] != 0){
		return memoization[W][L][H];
	}
	if(W == L && W == H && L == H){
		return 1;
	}
	if(W == 1 || L == 1 || H == 1){
		return W*L*H;
	}
	int min = 8000001;			// W,L,H <= 200 ÀÌ¹Ç·Î 200^3 == 8000000 
	int temp;
	for(int i=1; i<=W/2; i++){
		temp = calc(i,L,H) + calc(W-i,L,H);
		if(temp < min){
			min = temp;
		}
	}
	for(int i=1; i<=L/2; i++){
		temp = calc(W,i,H) + calc(W,L-i,H);
		if(temp < min){
			min = temp;
		}
	}
	for(int i=1; i<=H/2; i++){
		temp = calc(W,L,i) + calc(W,L,H-i);
		if(temp < min){
			min = temp;
		}
	}
	memoization_data(W,L,H,min);
	return min;
}

int main(){
	int T, result;
	input_fp >> T;
	for(int i=0; i<T; i++){
		input_data();
		result = calc(Width,Length,Height);
		output_fp << result << endl;
	}
}
