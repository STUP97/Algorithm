#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

ifstream input_fp("coinmove.inp");
ofstream output_fp("coinmove.out");

int P;
int K;
int S;
int win_move;
int memoization[7][1000000]; 
bool coin_move_A(int pre_mov, int num);
bool coin_move_B(int pre_mov, int num);


void input_data(){
	input_fp >> P >> K >> S;
}

// p*n �ڸ����� ������ ���� �� ����.
// ������ 1~k �̵��� �� ����.
// �������� s
// ������ ������ �θ� ���ڸ� �θ� �� ����. 

// ���� ������ ��ġ�� �������� ��, ö���� �̱�� �� �ϳ��� ��ġ�� �־�� �ϰ� 
// ö���� ������ ��ġ�� �������� ��, ��� ��ġ�� ���� ���� �̱�ų� ������ ��ġ�� ���ٸ�
// ������ �¸�
// �� �ܿ� ö���� �¸�. 
	// ������ ���ʿ��� 
	// ���� ���� K���� �۰ų� ���� ��, 
	// ���� ���� ũ��� ���� �������� ũ�Ⱑ ���� ������ ������ �¸�
	// ���� ���� ũ��� ���� �������� ũ�Ⱑ ���� �� ������ �й�. 
	// ���� ���� K���� Ŭ ��
	// ���� ������ ���� �� �ִ� ��� ����� ���� ���δ�. 
	// 		������ �����Ӱ� �ٸ��� 
	//		p�� ��������� ���� ���� ��.
	// ����� �ش� ��ġ�� ������ �ű��.
	// �̶� ���� �̱�� �� �̵��� �Ÿ��� �Բ� ��ȯ�Ѵ�. 
	// ���� �� �ѹ��� �̱��� ���Ѵٸ� ����� �й��Ѵ�. 
	// ö���� ���ʿ��� 
	// ���� ���� K���� �۰ų� ���� ��, 
	// ���� ���� ũ��� ���� �������� ũ�Ⱑ ���� ������ ������ �й� 
	// ���� ���� ũ��� ���� �������� ũ�Ⱑ ���� �� ������ �¸�. 
	// ���� ���� K���� Ŭ ��
	// ö���� ������ ���� �� �ִ� ��� ����� ���� ���δ�. 
	// 		������ �����Ӱ� �ٸ��� 
	//		p�� ��������� ���� ���� ��.
	// ö���� �ش� ��ġ�� ������ �ű��.
	// �̶� ö���� ��� ���� ������ �¸�. 
	// �� �ѹ��̶� ö���� �̱�� ������ �й�.
	

	// ������ ���ʿ��� 
	// ���� ���� K���� �۰ų� ���� ��, 
	// ���� ���� ũ��� ���� �������� ũ�Ⱑ ���� ������ ������ �¸�
	// ���� ���� ũ��� ���� �������� ũ�Ⱑ ���� �� ������ �й�. 
	// ���� ���� K���� Ŭ ��
	// ���� ������ ���� �� �ִ� ��� ����� ���� ���δ�. 
	// 		������ �����Ӱ� �ٸ��� 
	//		p�� ��������� ���� ���� ��.
	// ����� �ش� ��ġ�� ������ �ű��.
	// �̶� ���� �̱�� �� �̵��� �Ÿ��� �Բ� ��ȯ�Ѵ�. 
	// ���� �� �ѹ��� �̱��� ���Ѵٸ� ����� �й��Ѵ�. 
		
bool coin_move_A(int pre_mov, int num){
//	cout << "Now_A : " << num << " pre_mov : " << pre_mov << endl;
	if(memoization[pre_mov][num] != 0){
		if(memoization[pre_mov][num] == 1){
			return true;
		}
		else{
			return false;
		}
	}
	if(num-K <= 0 && num != pre_mov){
		win_move = num;
		memoization[pre_mov][num] = 1;
		return true;
	}
	for(int i=1; i<=K; i++){
		if(i != pre_mov && (num-i)%P != 0 && num-i >= 0){
			if(!coin_move_B(i,num-i)){
				win_move = i;
				memoization[pre_mov][num] = 1;
				return true;
			}
		}
	}
	memoization[pre_mov][num] = 2;
	return false;
}

	// ö���� ���ʿ��� 
	// ���� ���� K���� �۰ų� ���� ��, 
	// ���� ���� ũ��� ���� �������� ũ�Ⱑ ���� ������ ������ �й� 
	// ���� ���� ũ��� ���� �������� ũ�Ⱑ ���� �� ������ �¸�. 
	// ���� ���� K���� Ŭ ��
	// ö���� ������ ���� �� �ִ� ��� ����� ���� ���δ�. 
	// 		������ �����Ӱ� �ٸ��� 
	//		p�� ��������� ���� ���� ��.
	// ö���� �ش� ��ġ�� ������ �ű��.
	// �̶� ö���� ��� ���� ������ �¸�. 
	// �� �ѹ��̶� ö���� �̱�� ������ �й�.
bool coin_move_B(int pre_mov, int num){
//	cout << "Now_B : " << num << " pre_mov : " << pre_mov << endl;
	if(memoization[pre_mov][num] != 0){
		if(memoization[pre_mov][num] == 1){
			return true;
		}
		else{
			return false;
		}
	}
	if(num-K <= 0 && num != pre_mov){
		memoization[pre_mov][num] = 1;
		return true;
	}
	for(int i=1; i<=K; i++){
		if(i != pre_mov && (num-i)%P != 0 && num-i >= 0){
			if(!coin_move_A(i,num-i)){
				memoization[pre_mov][num] = 1;
				return true;
			}
		}
	}
	memoization[pre_mov][num] = 2;
	return false;
}

void reset(){
	for(int i=0; i<8; i++){
		for(int j=0; j<S+1; j++){
			memoization[i][j] = 0;
		}
	}
}

void print_mem(){
	for(int i=0; i<7; i++){
		for(int j=0; j<S+1; j++){
			cout << memoization[i][j] << " ";
			if(j%10 == 0){
				cout << "# ";
			}
		}
		cout << endl;
	}
}

int main(){
	int T;
	bool result;
	input_fp >> T;
	for(int i=0; i<T; i++){
		input_data();
		result = coin_move_A(0,S);
//		result = coin_move_A(0,(P*K)+(S%(P*K)));
		if(result){
//			cout << "true" << endl;
			output_fp << S-win_move << endl;
		}
		else{
//			cout << "false" << endl;
			output_fp << "-1" << endl;
		}
		print_mem();
		reset();
	}
}
