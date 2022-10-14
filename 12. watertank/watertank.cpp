#include<iostream>
#include<algorithm>
#include<fstream>
#include<vector>
using namespace std;

   /* input_fp ������ �޾Ƽ� ������ �ֱ�. */
ifstream input_fp("watertank.inp");   
   /* output_fp ���Ͽ� ������ �ֱ� */
ofstream output_fp("watertank.out");

typedef struct XY_pointer{
	int y;
	int x;
}data;

// n = ���α��� m = ���α��� h = ���� 
int n,m,h,under_hole;
// ���� ���� ���� 
int width[1001][1001];
// ���� ���� ���� 
int length[1001][1001];
int result[1001][1001];

void input_data(){
	int temp;
	// ���� ���� ���� ������ �Է�. 
	input_fp >> n >> m >> h;
	// ���κ��� ������ ���α���+1 ���� n+1 
	for(int i=0; i<n+1; i++){
		for(int j=0; j<m; j++){
			input_fp >> temp;
			width[i][j] = temp;
		}
	}
	// ���κ��� ������ ���α���+1 ���� m+1
	for(int i=0; i<n; i++){
		for(int j=0; j<m+1; j++){
			input_fp >> temp;
			length[i][j] = temp;
		}
	}
	// ����ũ�� �������� �� ����ֱ�.
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			result[i][j] = h;
		}
	} 
}
// ��� ������ �湮�ϴ°� �ƴ� �ٱ��� ����� ���۵��� Ž��.
// �����ϰ� DFS ������� ���ᱸ�� Ȯ��. 
// �ٱ��� ����� ������ ������ ��ġ �ľ�.
// �ٱ��� ����� ������ �⺻ ��Ʈ�� DFS ����.(�ٸ� �ٱ����� ����x) 
// ��� ���� �Ϸ� �� ��� ���ᱸ�� �湮���� ó�� �� ����.
// �ܺο� ����� ���� ã��. 


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
	// ���� 
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
	
	// ���� 
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
	// ����� ����ũ�� ���� �޾ƿ���. 
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

