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
int memoization_A[8][1000000]; 
int memoization_B[8][1000000]; 
bool coin_move_A(int pre_mov, int num);
bool coin_move_B(int pre_mov, int num);


void input_data(){
	input_fp >> P >> K >> S;
}

// p*n 자리에는 동전을 놓을 수 없음.
// 동전은 1~k 이동할 수 있음.
// 시작점은 s
// 상대방이 앞전에 부른 숫자를 부를 순 없음. 

// 영희가 각각의 위치로 움직였을 때, 철수를 이기는 단 하나의 위치가 있어야 하고 
// 철수가 각각의 위치로 움직였을 때, 모든 위치에 대해 영희가 이기거나 움직일 위치가 없다면
// 영희의 승리
// 그 외에 철수의 승리. 
	// 영희의 차례에서 
	// 남은 수가 K보다 작거나 같을 때, 
	// 남은 수의 크기와 저번 움직임의 크기가 같지 않을때 영희의 승리
	// 남은 수의 크기와 저번 움직임의 크기가 같을 때 영희의 패배. 
	// 남은 수가 K보다 클 떄
	// 영희가 동전을 놓을 수 있는 모든 경우의 수를 보인다. 
	// 		저번의 움직임과 다르고 
	//		p의 배수값으로 가지 않을 때.
	// 영희는 해당 위치에 동전을 옮긴다.
	// 이때 영희가 이기면 그 이동한 거리와 함께 반환한다. 
	// 만약 단 한번도 이기지 못한다면 영희는 패배한다. 
	// 철수의 차례에서 
	// 남은 수가 K보다 작거나 같을 때, 
	// 남은 수의 크기와 저번 움직임의 크기가 같지 않을때 영희의 패배 
	// 남은 수의 크기와 저번 움직임의 크기가 같을 때 영희의 승리. 
	// 남은 수가 K보다 클 떄
	// 철수가 동전을 놓을 수 있는 모든 경우의 수를 보인다. 
	// 		저번의 움직임과 다르고 
	//		p의 배수값으로 가지 않을 때.
	// 철수는 해당 위치에 동전을 옮긴다.
	// 이때 철수가 모두 지면 영희의 승리. 
	// 단 한번이라도 철수가 이기면 영희의 패배.
	

	// 영희의 차례에서 
	// 남은 수가 K보다 작거나 같을 때, 
	// 남은 수의 크기와 저번 움직임의 크기가 같지 않을때 영희의 승리
	// 남은 수의 크기와 저번 움직임의 크기가 같을 때 영희의 패배. 
	// 남은 수가 K보다 클 떄
	// 영희가 동전을 놓을 수 있는 모든 경우의 수를 보인다. 
	// 		저번의 움직임과 다르고 
	//		p의 배수값으로 가지 않을 때.
	// 영희는 해당 위치에 동전을 옮긴다.
	// 이때 영희가 이기면 그 이동한 거리와 함께 반환한다. 
	// 만약 단 한번도 이기지 못한다면 영희는 패배한다. 
		
bool coin_move_A(int pre_mov, int num){
//	cout << "Now_A : " << num << " pre_mov : " << pre_mov << endl;
	if(memoization_A[pre_mov][num] != 0){
		if(memoization_A[pre_mov][num] == 1){
			return true;
		}
		else{
			return false;
		}
	}
	if(num-K <= 0 && num != pre_mov){
		win_move = num;
		memoization_A[pre_mov][num] = 1;
		return true;
	}
	for(int i=1; i<=K; i++){
		if(i != pre_mov && (num-i)%P != 0 && num-i >= 0){
			if(coin_move_B(i,num-i)){
				win_move = i;
				memoization_A[pre_mov][num] = 1;
				return true;
			}
		}
	}
	memoization_A[pre_mov][num] = 2;
	return false;
}

	// 철수의 차례에서 
	// 남은 수가 K보다 작거나 같을 때, 
	// 남은 수의 크기와 저번 움직임의 크기가 같지 않을때 영희의 패배 
	// 남은 수의 크기와 저번 움직임의 크기가 같을 때 영희의 승리. 
	// 남은 수가 K보다 클 떄
	// 철수가 동전을 놓을 수 있는 모든 경우의 수를 보인다. 
	// 		저번의 움직임과 다르고 
	//		p의 배수값으로 가지 않을 때.
	// 철수는 해당 위치에 동전을 옮긴다.
	// 이때 철수가 모두 지면 영희의 승리. 
	// 단 한번이라도 철수가 이기면 영희의 패배.
bool coin_move_B(int pre_mov, int num){
//	cout << "Now_B : " << num << " pre_mov : " << pre_mov << endl;
	if(memoization_B[pre_mov][num] != 0){
		if(memoization_B[pre_mov][num] == 1){
			return true;
		}
		else{
			return false;
		}
	}
	if(num-K <= 0 && num != pre_mov){
		memoization_B[pre_mov][num] = 2;
		return false;
	}
	for(int i=1; i<=K; i++){
		if(i != pre_mov && (num-i)%P != 0 && num-i >= 0){
			if(!coin_move_A(i,num-i)){
				memoization_B[pre_mov][num] = 2;
				return false;
			}
		}
	}
	memoization_B[pre_mov][num] = 1;
	return true;
}

void reset(){
	for(int i=0; i<=7; i++){
		for(int j=0; j<=S; j++){
			memoization_A[i][j] = 0;
			memoization_B[i][j] = 0;
		}
	}
}

void print_mem(){
	for(int i=0; i<=7; i++){
		for(int j=0; j<=S; j++){
			cout << memoization_A[i][j] << " ";
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
		for(int i=1; i<=S/K; i++){
			result = coin_move_A(0,i*K);
		}
		result = coin_move_A(0,S);
//		result = coin_move_A(0,(S%(P*K)));
		if(result){
			output_fp << S-win_move << endl;
		}
		else{
			output_fp << "-1" << endl;
		}
//		print_mem();
		reset();
	}
}
