#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

ifstream input_fp("bowling.inp");   
ofstream output_fp("bowling.out");


int frame = 0;
int total_score = 0;
vector<int> stack;

void calc_score(int score){
	total_score += score*stack.size();
	for(int i=0; i<stack.size(); i++){
		stack[i]--;
	}
	// 스택의 사이즈는 2를 넘을 수 없다. 
	if(stack.size() == 2){
		if(stack[0] == 0){
			stack.erase(stack.begin());
		}
		else if(stack[1] == 0){
			stack.pop_back();
		}
	}
	else if(stack.size() == 1){
		if(stack[0] == 0){
			stack.erase(stack.begin());
		}
	}
}

void solve(){
	if(frame > 10){
		return;
	}
	int temp, temp2;
	input_fp >> temp;
	if(temp == 10){
		total_score += 10;
		calc_score(10);
		stack.push_back(2);
		if(frame == 10){
			input_fp >> temp;
			calc_score(temp);
			input_fp >> temp;
			calc_score(temp);
		}
	}
	else{
		total_score += temp;
		calc_score(temp);
		input_fp >> temp2;
		total_score += temp2;
		calc_score(temp2);
		if(frame == 10 && temp + temp2 == 10){
			input_fp >> temp;
			total_score += temp;
		}
		else if(temp + temp2 == 10){
			if(frame == 10){
				input_fp >> temp;
				calc_score(temp);
			}
			else{
				stack.push_back(1);
			}
		}
	}
	//cout << frame << " total : " << total_score << endl;
	frame++;
	solve();
}

int main(){
	int T;
	input_fp >> T;
	for(int i=0;i<T; i++){
		frame = 1;
		total_score = 0;
		solve();
		stack.clear();
		output_fp << total_score << endl;
	}
}

