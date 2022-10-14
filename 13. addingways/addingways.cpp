#include<iostream>
#include<fstream>
#include<vector>
#define mod 1000000007
using namespace std;

ifstream input_fp("addingways.inp");
ofstream output_fp("addingways.out");

int N,K;
int memoization_P[301][301];

void input_data(){
	input_fp >> N >> K;
}

long long calc(int n, int k){
	if(memoization_P[n][k] != -1){
		return memoization_P[n][k];
	}
	long long ret = 0;
	if(n == k || k == 1){
		return 1;
	}
	else if(n < k || k == 0){
		return 0;
	}
	else{
		for(int i=0; i<k; i++){
			ret += calc(n-k,k-i)%mod;
			ret = ret%mod;
		}
		memoization_P[n][k] = ret;
		return ret;
	}
}

int main(){
	for(int i=0; i<301; i++){
		for(int j=0; j<301; j++){
			if(i < j || j == 0){
				memoization_P[i][j] = 0;
			}
			else if(i == j){
				memoization_P[i][j] = 1;
			}
			else{
				memoization_P[i][j] = -1;
			}
		}
	}
	for(;;){
		input_data();
		if(N == 0 && K == 0){
			break;
		}
		else{
			int data = calc(N,K);
			output_fp << data << endl;
		}
	}
	return 0;
}
