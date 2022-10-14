#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

ifstream input_fp("hanoi.inp");
ofstream output_fp("hanoi.out");

typedef struct Disk{
	char color;
	int size;
	int stack;
}disk;

int memoization[101];
int color_size;
int mov_cnt;
vector<disk> hanoi_data;
bool order = true; 		// true일 때 Blue 2회.false 일때 Red 2회  


void input_data(){
	disk temp;
	mov_cnt = 0;
	input_fp >> color_size;
	for(int i=1; i<=color_size; i++){
		input_fp >> temp.color >> temp.stack;
		temp.size = i;
		hanoi_data.push_back(temp); 
	}
}

int set_memoization(int n){
	if(memoization[n] != 0){
		return memoization[n];
	}
	if(n == 0){
		return memoization[0] = hanoi_data[0].stack;
	}
	else{
		int temp = 2 * set_memoization(n-1);
		temp += hanoi_data[n].stack;
		return memoization[n] = temp;
	}
}

void hanoi(){
	mov_cnt += memoization[hanoi_data.size()-1];
//	cout << "move_count : " << mov_cnt << endl;
	char color;
	for(int i=color_size-1; i>=0; i--){
		color = hanoi_data[i].color;
		if(color == 'R' && hanoi_data[i].stack != 1 && !order){
			mov_cnt += memoization[i];
//			cout << "move_count : " << mov_cnt << endl;
			if(i != 0){
				mov_cnt -= memoization[i-1];
//				cout << "move_count : " << mov_cnt << endl;
			}
			else{
				mov_cnt--;
//				cout << "move_count : " << mov_cnt << endl;
			}
			order = true;
		}
		else if(color == 'B' && hanoi_data[i].stack != 1 && order){
			mov_cnt += memoization[i];
//			cout << "move_count : " << mov_cnt << endl;
			if(i != 0){
				mov_cnt -= memoization[i-1];
//				cout << "move_count : " << mov_cnt << endl;
			}
			else{
				mov_cnt--;
//				cout << "move_count : " << mov_cnt << endl;
			}
		}
		else{
			if(order)	
				order = false;
		}
	}
}

void reset(){
	hanoi_data.clear();
	for(int i=0; i<color_size; i++){
		memoization[i] = 0;
	}
	order = true; 
}

void print_mem(){
	for(int i=0; i<color_size; i++){
		cout << memoization[i] << endl;
	}
	cout << endl;
}

int main(){
	int T;
	input_fp >> T;
	for(int i=0; i<T; i++){
		input_data();
		set_memoization(color_size-1);
//		print_mem();
		hanoi();
		output_fp << mov_cnt << endl;
		reset();
	}
}
