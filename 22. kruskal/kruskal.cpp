#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

ifstream input_fp("kruskal.inp");
ofstream output_fp("kruskal.out");

typedef struct uvw_index{
	int u;
	int v;
	int w;
	int index;
}uvwi;

int n, m;
int union_check[10001];
uvwi kruskal[1000001];
vector<uvwi> result_k;

bool compare(uvwi x, uvwi y){
	if(x.w != y.w) 
	    return x.w < y.w;
	else
		return x.index < y.index;
}

bool equal(int x, int y){
	return union_check[x] == union_check[y];
}

void input_data(){
	int tmp;
	uvwi temp;
	input_fp >> n >> m;
	for(int i=0; i<m; i++){
		input_fp >> temp.u >> temp.v >> temp.w;
		if(temp.u > temp.v){
			tmp = temp.u;
			temp.u = temp.v;
			temp.v = tmp;
		}
		temp.index = i;
		kruskal[i] = temp;
	}
	for(int i=0; i<10000; i++){
		union_check[i] = i;
	}
	sort(kruskal, kruskal+m, compare);
}

void merge(int p, int q){
	for(int i=0; i<n; i++){
		if(q == union_check[i]){
			union_check[i] = p;
		}
	}
}

void kruskal_algo(){
	int temp;
	int x = 0;
	int edge_cnt = 0;
	//노드개수-1 개의 엣지를 찾으면 종료 
	while(edge_cnt < n-1){
		if(!equal(kruskal[x].u,kruskal[x].v)){
			// 다른 연결구조와 동기화 작업 
			// temp와 같은 모든 union을 merge
			// 연결한 edge 결과 vector에 추가. 
			// edge 카운팅  
			merge(union_check[kruskal[x].u], union_check[kruskal[x].v]);
			result_k.push_back(kruskal[x]);
			edge_cnt++;
		}
		x++;
	}
}
void print_data(){
    int result = 0;
	for(int i=0; i<result_k.size(); i++){
		result += result_k[i].w;
	}
	output_fp << result << endl;
	for(int i=0; i<result_k.size(); i++){
		output_fp << result_k[i].index << endl;
	}
}


int main(){
	input_data();
	kruskal_algo();
	print_data();
}


// n <= 10000   
// m <= 1000000 
// w <= 10000
// index <= 10000
// result_max == n-1 * m == 100,000,000

/*

void print_union(int edge_cnt){
	cout << edge_cnt << endl;
	for(int i=0; i<n; i++){
		if(i%5 == 0){
			cout << endl;
		}
		cout << union_check[i] << " ";
	}
	cout << endl;
	cout << endl;
}


*/
