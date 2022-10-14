#include<iostream>
#include<fstream>
using namespace std;

ifstream input_fp("coin.inp");
ofstream output_fp("coin.out");

int bottle[3];

void input_data(){
	input_fp >> bottle[0] >> bottle[1] >> bottle[2];
	output_fp << "(" << bottle[0] << " " << bottle[1] << " " << bottle[2] << ") : ";
	bottle[0] = bottle[0]%4;
	bottle[1] = bottle[1]%4;
	bottle[2] = bottle[2]%4;
}

void print_result(){
	int cnt0 = 0;
	int cnt1 = 0; 
	int cnt2 = 0;
	int cnt3 = 0;
	for(int i=0; i<3; i++){
		if(bottle[i] == 0){
			cnt0++;
		} 
		else if(bottle[i] == 1){
			cnt1++;
		}
		else if(bottle[i] == 2){
			cnt2++;
		}
		else if(bottle[i] == 3){
			cnt3++;
		}
	}
	if((cnt0 == 2 && cnt1 == 1) || (cnt0 == 1 && cnt2 == 2) || (cnt0 == 1 && cnt3 == 2) || cnt1 == 3 || (cnt1 == 1 && cnt2 == 1 && cnt3 == 1)){
		output_fp << "-1" << endl;
	}
	else{
		output_fp << "1" << endl;
	}
}

void print_mod(){
	output_fp << "(" << bottle[0] << " " << bottle[1] << " " << bottle[2] << ")" << endl;;
} 

int main(){
	int T;
	input_fp >> T;
	for(int i=0; i<T; i++){
		input_data();
		print_result();
	}
}
