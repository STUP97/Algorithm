#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

ifstream input_fp("jump.inp");
ofstream output_fp("jump.out");

int result = 0;
vector<int> log_data;



void input_data(){
	result = 0;
	int size, temp;
	input_fp >> size;
	for(int i=0; i<size; i++){
		input_fp >> temp;
		log_data.push_back(temp);
	}
	sort(log_data.begin(),log_data.end());
}

void calc(){
	int temp;
	for(int i=0; i<log_data.size()-1; i++){
		if(i+2 == log_data.size()){
			temp = log_data[i+1] - log_data[i];
		}
		else{
			temp = log_data[i+2] - log_data[i];
		}
		if(temp > result){
			result = temp;
		}
	}
}

int main(){
	int T;
	input_fp >> T;
	for(int i=0; i<T; i++){
		input_data();
		calc();
		output_fp << result << endl;
		log_data.clear();
	}
}
