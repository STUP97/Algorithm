#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

ifstream input_fp("cross.inp");   
ofstream output_fp("cross.out");

int N;
vector<int> line;
vector<int> opt;

void input_data(){
	input_fp >> N;
	int temp;
	for(int i=0; i<N; i++){
		input_fp >> temp;
		line.push_back(temp);
	}
	for(int i=0; i<N; i++){
		input_fp >> temp;
		for(int j=0; j<N; j++){
			if(line[j] == temp){
				opt.push_back(j);
			}
		}
	}
}
int calc_data(){
	int cnt = 0;
	for(int i=0; i<N; i++){
		for(int x=0; x<i; x++){
			if(opt[x] > opt[i]){
				cnt++;
			}
		}
	}
	return cnt;
}

int main(){
	int T;
	input_fp >> T;
	for(int i=0; i<T; i++){
		input_data();
		output_fp << "Case " << i+1 << ": " << calc_data() << endl;
		line.clear();
		opt.clear();
	}
	return 0;
}
