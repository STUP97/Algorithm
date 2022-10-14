#include<iostream>
#include<string>
#include<fstream>
using namespace std;

ifstream input_fp("color.inp");
ofstream output_fp("color.out");

int DP[5002][5002], color_cnt1[5002][26], color_cnt2[5002][26];
string line_1, line_2;

int min(int a, int b) { 
	return a < b ? a : b; 
}


void input_data(){
	string temp;
	line_1.push_back('*');
	line_2.push_back('*');
	getline(input_fp, temp);
	for(int i=0; i<temp.size(); i++){
		line_1.push_back(temp[i]);
	}
	getline(input_fp, temp);
	for(int i=0; i<temp.size(); i++){
		line_2.push_back(temp[i]);
	}
	for(int i=0; i<5002; i++){
		for(int j=0; j<5002; j++){
			DP[i][j] = 2000000000;
		}
		for(int j=0; j<26; j++){
			color_cnt1[i][j] = 0;
			color_cnt2[i][j] = 0;
		}
	}
}


//모든 차량에 대해 실행. 
int get_len(int x, int y, int color) {
	// 임시 숫자 1과 2를 0으로 초기화 시키고. 
	int temp1 = 0, temp2 = 0;
	// 만약 해당 x또는 y로 늘렸을 때 최종 색깔의 크기와 같다면
	// 해당 갯수를 반환 
	if (color_cnt1[x][color] == color_cnt1[line_1.size()-1][color] && color_cnt2[y][color] == color_cnt2[line_2.size()-1][color] ) 
		temp1 = x + y;
	// 만약 최종 갯수가 1개라면
	// 0을 반환시킨다 
	if (color_cnt1[x][color] + color_cnt2[y][color] == 1) 
		temp2 = x + y;
	return temp1 - temp2;
}

void solve() {
	//1번 차로 전체에 대해 반복한다. 
	for (int i = 1; i < line_1.size(); i++) {
		// 모든 동일한 색깔에 대해서 
		for (int j = 0; j < 26; j++) {
			// 이전 색상 카운트와 동일하게 변경한다. 
			color_cnt1[i][j] = color_cnt1[i - 1][j];
		}
		//그 후 현재 색깔에 대해 카운팅 한다. 
		color_cnt1[i][line_1[i] - 'A']++;
	}
	//2번 차로 전체에 대해 반복한다. 
	for (int i = 1; i < line_2.size(); i++) {
		// 모든 동일한 색깔에 대해서 
		for (int j = 0; j < 26; j++) {
			// 이전의 색상 카운트와 동일하게 변경한다. 
			color_cnt2[i][j] = color_cnt2[i - 1][j];
		}
		//그 후 현재 색깔에 대해 카운팅 한다. 
		color_cnt2[i][line_2[i] - 'A']++;
	}
	
	for(int i=0; i<26; i++){
		cout << color_cnt1[line_1.size()-1][i];
	}
	cout << endl;
	for(int i=0; i<26; i++){
		cout << color_cnt2[line_2.size()-1][i];
	}
	cout << endl;
	// 아무것도 들어오지 않은 차로는 0이고 
	DP[0][0] = 0;
	// 모든 1번라인 차량에 대해 반복 
	for (int i = 0; i < line_1.size(); i++) {
		//모든 2번라인 차량에 대해 반복 
		for (int j=0; j<line_2.size(); j++) {
			//temp1은 아래의 get_len을 통해 무언가를 가져온다. 
			//만약 첫번째 차가 들어왔을 때 나오는 길이.
			//만약 두번째 차가 들어왔을 때 나오는 길이. 
			int temp1 = get_len(i+1, j, line_1[i+1]-'A');
			int temp2 = get_len(i, j+1, line_2[j+1]-'A');
//			cout << "i : " << i << " j : " << j << endl;
//			cout << "temp1 : " << temp1 << " temp2 : " << temp2 << endl; 
			DP[i + 1][j] = min(DP[i + 1][j], DP[i][j] + temp1);
			DP[i][j + 1] = min(DP[i][j + 1], DP[i][j] + temp2);
		}
	}
}

int main() {
	string g;
	int T;
	input_fp >> T;
	getline(input_fp, g);
	while (T--) {
		input_data();
		solve();
		output_fp << DP[line_1.size()-1][line_2.size()-1] << endl;
		line_1.clear();
		line_2.clear();
	}

	return 0;
}
