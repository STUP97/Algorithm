#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

ifstream input_fp("sequence.inp");   
ofstream output_fp("sequence.out");


int main(){
	int i,T,num;	
	vector<int> arr;
	input_fp >> T;
	int sequence[T];
	int result[T];
	for(i=0;i<T;i++){
		input_fp >> num;
		arr.push_back(num);
	}
	for(i=0;i<T;i++){
		input_fp >> sequence[i];
	}
	sort(arr.begin(), arr.end());
	for(i=T-1;i>=0;i--){
		result[i] = arr[sequence[i]];
		vector<int> ::iterator iter = arr.begin();
		iter += sequence[i];
		arr.erase(iter);
	}
	for(i=0;i<T;i++){
		output_fp << result[i] << endl;
	}
	input_fp.close();   
	output_fp.close();
	return 0;
}
