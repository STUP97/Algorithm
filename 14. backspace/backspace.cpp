#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

ifstream input_fp("backspace.inp");
ofstream output_fp("backspace.out");

string s;
string t;
vector<char> arr1;
vector<char> arr2;
bool check;

void input_data(){
	input_fp >> s >> t;
	// 역순배열 생성 
	for(int i=0; i<s.size(); i++){
		arr1.push_back(s[s.size()-1-i]);
	}
	for(int i=0; i<t.size(); i++){
		arr2.push_back(t[t.size()-1-i]);
	}
}

bool solve(){
	int a = 0;
	for(int i=0; i<arr2.size(); i++){
		if(arr1.size() < arr2.size()){
			return false;
		}
		/*
		// 8번 오버타임리미트 
		if(arr1[i] != arr2[i]){
			arr1.erase(arr1.begin()+i);
			if(arr1.size() > i+1){
				arr1.erase(arr1.begin()+i);
			}
			if(arr1[i] != arr2[i]){
				i--;
				continue;
			}
		}
		*/
		if(arr1[i+a] != arr2[i]){
			for(;;){
				if(arr1[i+a] == arr2[i]){
					break;
				}
				else{
					a++;
					if(arr1.size() > i+a+1){
						a++;
					}
					if(arr1.size() < i+a+1){
						return false;
					}
				}
			}
		}
	}
	return true;
}

void print_result(){
	if(check){
		output_fp << "YES" << endl;
	}
	else{
		output_fp << "NO" << endl;
	}
	arr1.clear();
	arr2.clear();
}


int main(){
	int T;
	input_fp >> T;
	for(int i=0; i<T; i++){
		input_data();
		check = solve();
		print_result();
	} 
	return 0;
}
