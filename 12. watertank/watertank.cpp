#include<iostream>
#include<algorithm>
#include<fstream>
#include<vector>
using namespace std;

   /* input_fp 파일을 받아서 변수에 넣기. */
ifstream input_fp("watertank.inp");   
   /* output_fp 파일에 변수를 넣기 */
ofstream output_fp("watertank.out");

typedef struct XY_pointer{
	int y;
	int x;
}data;

// n = 세로길이 m = 가로길이 h = 높이 
int n,m,h,under_hole;
// 가로 구멍 정보 
int width[1001][1001];
// 세로 구멍 정보 
int length[1001][1001];
int result[1001][1001];

void input_data(){
	int temp;
	// 세로 가로 높이 순서로 입력. 
	input_fp >> n >> m >> h;
	// 가로벽의 개수는 세로길이+1 따라서 n+1 
	for(int i=0; i<n+1; i++){
		for(int j=0; j<m; j++){
			input_fp >> temp;
			width[i][j] = temp;
		}
	}
	// 세로벽의 개수는 가로길이+1 따라서 m+1
	for(int i=0; i<n; i++){
		for(int j=0; j<m+1; j++){
			input_fp >> temp;
			length[i][j] = temp;
		}
	}
	// 물탱크의 모든공간에 물 집어넣기.
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			result[i][j] = h;
		}
	} 
}
// 모든 공간을 방문하는게 아닌 바깥과 연결된 구멍들을 탐색.
// 간단하게 DFS 방식으로 연결구조 확인. 
// 바깥과 연결된 구멍의 개수와 위치 파악.
// 바깥과 연결된 구멍을 기본 루트로 DFS 진행.(다른 바깥구멍 상정x) 
// 모든 구멍 완료 시 모든 연결구조 방문으로 처리 후 종료.
// 외부와 연결된 구멍 찾기. 


void solve(int y, int x, int hole, vector<data> visit){
	if(result[y][x] > hole){
		result[y][x] = hole;
	}
	data temp;
	temp.y = y;
	temp.x = x;
	visit.push_back(temp);
	bool check = false;
	check = false;
	if(y > 0){
		if(width[y][x] >= 0){
			for(int i=0; i<visit.size(); i++){
				if(visit[i].y == y-1 && visit[i].x == x){
					check = true;
					break;
				}
			}
			if(!check){
				if(hole < width[y][x]){
					solve(y-1,x,width[y][x],visit);
				}
				else{
					solve(y-1,x,hole,visit);
				}
			}
		}
	}
	check = false;
	if(x > 0){
		if(length[y][x] >= 0){
			for(int i=0; i<visit.size(); i++){
				if(visit[i].y == y && visit[i].x == x-1){
					check = true;
					break;
				}
			}
			if(!check){
				if(hole < length[y][x]){
					solve(y,x-1,length[y][x],visit);
				}
				else{
					solve(y,x-1,hole,visit);
				}
			}
		}
	}
	check = false;
	if(y < n-1){
		if(width[y+1][x] >= 0){
			for(int i=0; i<visit.size(); i++){
				if(visit[i].y == y+1 && visit[i].x == x){
					check = true;
					break;
				}
			}
			if(!check){
				if(hole < width[y+1][x]){
					solve(y+1,x,width[y+1][x],visit);
				}
				else{
					solve(y+1,x,hole,visit);
				}
			}
		}
	}
	check = false;
	if(x < m-1){
		if(length[y][x+1] >= 0){
			for(int i=0; i<visit.size(); i++){
				if(visit[i].y == y && visit[i].x == x+1){
					check = true;
					break;
				}
			}
			if(!check){
				if(hole < length[y][x+1]){
					solve(y,x+1,length[y][x+1],visit);
				}
				else{
					solve(y,x+1,hole,visit);
				}
			}
		}
	}
}

void cout_watertank(){
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			cout << result[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int calc_data(){
	int low_hole, ret = 0;
	vector<data> visit;
	// 가로 
	for(int i=0; i<2; i++){
		for(int j=0; j<m; j++){
			if(width[i*n][j] >= 0){
				low_hole = width[i*n][j];
				if(i == 0)
					solve(0,j,low_hole,visit);
				else
					solve(n-1,j,low_hole,visit);
			}
		}
	}
	
	// 세로 
	for(int i=0; i<n; i++){
		for(int j=0; j<2; j++){
			if(length[i][j*m] >= 0){
				low_hole = length[i][j*m];
				if(j == 0)
					solve(i,0,low_hole,visit);
				else
					solve(i,m-1,low_hole,visit);
			}
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			ret += result[i][j];
		}
	}
	return ret;
}


int main(){
	// 계산할 물탱크의 개수 받아오기. 
	int size, result;
	input_fp >> size;
	for(int i=0; i<size; i++){
		input_data();
		result = calc_data();
		output_fp << result << endl;
	}
	
	
	input_fp.close();   
	output_fp.close();
	return 0;
}

