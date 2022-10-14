#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream input_fp("family.inp");   
ofstream output_fp("family.out");

typedef struct linked_node{
	int p;
	int c;
}node;

int T, size, result;
vector<int> family[500001];

bool check_root[500001];


void input_data(){
	int p;
	int c;
	input_fp >> size;
	for(int i=0; i<size-1; i++){
		input_fp >> p >> c;
		if(!check_root[c]){
			check_root[c] = true;
		}
		family[p].push_back(c);
	}
	for(int i=1; i<=size; i++){
		if(!check_root[i]){
			family[0].push_back(i);
			break;
		}
	}
}

int calc_data(int p, int cnt){
	int max = cnt;
	int get_num;
	for(int i=0; i<family[p].size(); i++){
		get_num = calc_data(family[p][i], cnt+1);
		if(get_num > max){
			max = get_num;
		}
	}
	return max;
}

void clear_data(){
	for(int i=0; i<size+1; i++){
		check_root[i] = false;
		family[i].clear();
	}
}





int main(){
	input_fp >> T;
	for(int i=0; i<T; i++){
		input_data();
		result = calc_data(0,0);
		output_fp << result << endl;
		clear_data();
	}
}	
		
