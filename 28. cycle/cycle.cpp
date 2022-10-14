#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

ifstream input_fp("cycle.inp");
ofstream output_fp("cycle.out");

int size;
vector<int> tree[50001];
int result1, result2;
bool visit[50001];

void input_data(){
	int temp1, temp2;
	input_fp >> size;
	for(int i=0; i<size-1; i++){
		input_fp >> temp1 >> temp2;
		tree[temp1].push_back(temp2);
		tree[temp2].push_back(temp1);
	}
}

int calc(int node, int pre_node){
	// 현재 노드가 트리의 단말노드일 때. 
	if(tree[node].size() == 1 && node == pre_node){
		visit[node] = true;
		return 1;
	}
	visit[node] = true;
	cout << node << " "  << pre_node << endl;
	int temp;
	int max = 0;
	int pre_max = 0;
	for(int i=0; i<tree[node].size(); i++){
		if(tree[node][i] != pre_node && !visit[tree[node][i]])
			temp = calc(tree[node][i], node); 
		if(temp > max){
			pre_max = max;
			max = temp;
		}
	}
	if(pre_node == 0){
		result2 = pre_max;
	}
	return max+1;
}

void reset(){
	result1 = 0;
	result2 = 0;
	for(int i=0; i<size; i++){
		visit[i] = false;
		tree[i].clear();
	}
}

int main(){
	int T;
	input_fp >> T;
	for(int i=0; i<T; i++){
		input_data();
		result1 = calc(1,0);
		output_fp << result1 + result2 + 1 << endl;
		reset();
	}
}
