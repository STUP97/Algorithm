#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

ifstream input_fp("exam.inp");   
ofstream output_fp("exam.out");


string good_str;
string str;
string s_left, s_right;
string question;
/*
"?" 는 good_str의 문자 중 하나로 바뀔 수 있다. 
"*" 은 good_str에 포함되지 않는 문자가 1개 이상 포함되는 문자열로 바뀌거나 빈 문자열로 바뀔 수 있다. 

"*"이 있을 경우
"*"을 기준으로 좌우로 나누어 양 끝에 배치한다. 

"*"이 없을 경우 
자체적으로 비교한다. 
*/

bool str_match(string s, string q){
	if(q.size() == 0){
		return true;
	}
	for(int i=0; i<s.size(); i++){
		if(s[i] != q[i]){
			if(s[i] == '?'){
				bool check = false;
				for(int j=0; j<good_str.size(); j++){
					if(good_str[j] == q[i]){
						check = true;
						break;
					}
				}
				if(!check){
					return false;
				}
			}
			else{
				return false;
			}
		}
	}
	return true;
}

bool star_match(string target){
	bool check;
	if(target.size() == 0){
		return true;
	}
	for(int i=0; i<target.size(); i++){
		check = false;
		for(int j=0; j<good_str.size(); j++){
			if(good_str[j] == target[i]){
				check = true;
				break;
			}
		}
		if(!check){
			return true;
		}
	}
	return false;
}

bool solve_problem(bool star){
//	cout << "str.size() : " << str.size() << " question.size() : " << question.size() << endl;
	if(star){
		string q_left, q_right, q_mid;
		q_left = question.substr(0, s_left.size());
		q_right = question.substr(question.size() - s_right.size());
		q_mid = question.substr(q_left.size(), question.size() - s_right.size() - s_left.size());
//		각각의 기준에 따라 문자열 쪼갠 결과 확인하기. 
//		cout << s_left.size() << " " << s_right.size() << endl;
//		cout << q_left.size() << " " << q_mid.size() << " " << q_right.size() << endl;
		if(!str_match(s_left,q_left)){
			return false;
		}
		else if(!str_match(s_right,q_right)){
			return false;
		}
		else if(!star_match(q_mid)){
			return false;
		}
		else{
			return true;
		}
	}
	else{
		if(!str_match(str,question)){
			return false;
		}
		else{
			return true;
		}
	}
	return true; 
}

void print_data(bool result){
	if(result){
		output_fp << "Yes" << endl;
	}
	else{
		output_fp << "No" << endl;
	}
}

void input_data_and_solve_problem(){
	int ques_size = 0;
	int star_point = 0;
	bool star = false;
	bool result = 0;
	input_fp >> good_str >> str >> ques_size;
	for(int i=0; i<str.size(); i++){
		if(str[i] == '*'){
			star = true;
			star_point = i;
			s_left = str.substr(0,star_point);
			s_right = str.substr(star_point+1);
			break;
		}
	}
	for(int i=0; i<ques_size; i++){
		input_fp >> question;
		result = solve_problem(star);
		// 결과 출력 
		print_data(result);
		question.clear();
	}
}

void clear_data(){
	good_str.clear();
	str.clear();
	question.clear();
}

int main(){
	int Test_Case;
	input_fp >> Test_Case;
	for(int i=1; i<=Test_Case; i++){
		output_fp << "Test Case: #" << i << endl;
		input_data_and_solve_problem();
		clear_data();
	}
}
