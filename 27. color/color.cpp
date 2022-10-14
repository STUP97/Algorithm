#include<iostream>
#include<fstream>
#include<string>
using namespace std;

ifstream input_fp("color.inp");
ofstream output_fp("color.out");

int DP[5002][5002];
int color_cnt1[5002][26];
int color_cnt2[5002][26];
string line_1, line_2;

// a, b�� ���ϰ� a Ȥ�� b�� ��ȯ 
int min(int a, int b) { 
	return a < b ? a : b; 
}
/*

���ϰ��� �ϴ� �� : Sum { LastIdx } - Sum { FirstIdx }

N���̺��� ä�� ��, 

�� A~Z���� 26���� �迭�� �� ������� ��� �ִ� �� ī��Ʈ ... color_cnt1, color_cnt2 


*/

void input_data(){
	string temp;
	line_1.push_back('@');		// �ε��� 0�� ������� ����. 
	line_2.push_back('@');		// �ε��� 0�� ������� ����. 
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
			DP[i][j] = 2147483647;
		}
		for(int j=0; j<26; j++){
			color_cnt1[i][j] = 0;
			color_cnt2[i][j] = 0;
		}
	}
}


int find_spot(int x, int y, int color) {
	// �ӽ� ���� 1�� 2�� 0���� �ʱ�ȭ ��Ű��. 
	int temp1 = 0, temp2 = 0;
	// ���� �ش� x�Ǵ� y�� �÷��� �� ���� ������ ũ��� ���ٸ�
	// �ش� ������ ��ȯ 
	if (color_cnt1[x][color] == color_cnt1[line_1.size()-1][color] && color_cnt2[y][color] == color_cnt2[line_2.size()-1][color]) 
		temp1 = x + y;
	// ���� ���� ������ 1�����
	// 0�� ��ȯ��Ų�� 
	if (color_cnt1[x][color] + color_cnt2[y][color] == 1) 
		temp2 = x + y;
	return temp1 - temp2;
}

void solve() {
	// �ƹ��͵� ������ ���� ���´� 0�̰� 
	int temp1, temp2;
	DP[0][0] = 0;
	//1�� ���� ��ü�� ���� �ݺ��Ѵ�. 
	for (int i=1; i<line_1.size(); i++) {
		// ��� ���� ���ؼ� 
		for (int j=0; j<26; j++) {
			// ���� ������ ���� ī��Ʈ�� ���� ī��Ʈ�� �����ϰ� �����Ѵ�. 
			color_cnt1[i][j] = color_cnt1[i-1][j];
		}
		//�� �� ���� ���� ���� ī���� �Ѵ�. 
		color_cnt1[i][line_1[i]-'A']++;
	}
	//2�� ���� ��ü�� ���� �ݺ��Ѵ�. 
	for (int i=1; i<line_2.size(); i++) {
		// ��� ������ ���� ���ؼ� 
		for (int j=0; j<26; j++) {
			// ������ ���� ī��Ʈ�� �����ϰ� �����Ѵ�. 
			color_cnt2[i][j] = color_cnt2[i-1][j];
		}
		//�� �� ���� ���� ���� ī���� �Ѵ�. 
		color_cnt2[i][line_2[i]-'A']++;
	}
	// ��� 1������ ������ ���� �ݺ� 
	for (int i=0; i<line_1.size(); i++) {
		//��� 2������ ������ ���� �ݺ� 
		for (int j=0; j<line_2.size(); j++) {
			//temp1�� �Ʒ��� get_len�� ���� ���𰡸� �����´�. 
			//���� ù��° ���� ������ �� ������ ����.
			//���� �ι�° ���� ������ �� ������ ����. 
			temp1 = find_spot(i+1, j, line_1[i+1]-'A');
			temp2 = find_spot(i, j+1, line_2[j+1]-'A');
			//�ִܰŸ��� ���� 
			DP[i + 1][j] = min(DP[i + 1][j], DP[i][j] + temp1);
			DP[i][j + 1] = min(DP[i][j + 1], DP[i][j] + temp2);
		}
	}
}

int main() {
	// �ݺ�Ƚ�� 
	int T;
	input_fp >> T;
	// getline�� ���� trash ó��. 
	string g;
	getline(input_fp, g);
	for(int i=0; i<T; i++){
		input_data();
		solve();
		output_fp << DP[line_1.size()-1][line_2.size()-1] << endl;
		line_1.clear();
		line_2.clear();
	}
}
