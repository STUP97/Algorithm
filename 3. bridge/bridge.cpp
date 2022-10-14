#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

ifstream input_fp("bridge.inp");   
ofstream output_fp("bridge.out");

typedef struct card_data{
	char pat;
	char num;
	int p_num;
	int n_num;
}card;

char diller;
vector<card> E;
vector<card> W;
vector<card> S;
vector<card> N;

void clear_data(){
	E.clear();
	W.clear();
	S.clear();
	N.clear();
}

void print_data(){
	output_fp << "S:";
	for(int i=0; i<S.size(); i++){
		output_fp << " " << S[i].pat << S[i].num;
	}
	output_fp << endl;
	output_fp << "W:";
	for(int i=0; i<W.size(); i++){
		output_fp << " " << W[i].pat << W[i].num;
	}
	output_fp << endl;
	output_fp << "N:";
	for(int i=0; i<N.size(); i++){
		output_fp << " " << N[i].pat << N[i].num;
	}
	output_fp << endl;
	output_fp << "E:";
	for(int i=0; i<E.size(); i++){
		output_fp << " " << E[i].pat << E[i].num;
	}
	output_fp << endl;
	
}

bool compare(card A, card B){
	if(A.p_num == B.p_num){
		return A.n_num < B.n_num;
	}
	else{
		return A.p_num < B.p_num;
	}
}

void sort_data(){
	sort(E.begin(),E.end(),compare);
	sort(W.begin(),W.end(),compare);
	sort(S.begin(),S.end(),compare);
	sort(N.begin(),N.end(),compare);
}

void input_data(){
	card c_data;
	for(int i=0; i<52; i++){
		input_fp >> c_data.pat >> c_data.num;
		switch(c_data.pat){
			case 'C':
				c_data.p_num = 1;
				break;
			case 'D':
				c_data.p_num = 2;
				break;
			case 'S':
				c_data.p_num = 3;
				break;
			case 'H':
				c_data.p_num = 4;
		}
		switch(c_data.num){
			case '2':
				c_data.n_num = 2;
				break;
			case '3':
				c_data.n_num = 3;
				break;
			case '4':
				c_data.n_num = 4;
				break;
			case '5':
				c_data.n_num = 5;
				break;
			case '6':
				c_data.n_num = 6;
				break;
			case '7':
				c_data.n_num = 7;
				break;
			case '8':
				c_data.n_num = 8;
				break;
			case '9':
				c_data.n_num = 9;
				break;
			case 'T':
				c_data.n_num = 10;
				break;
			case 'J':
				c_data.n_num = 11;
				break;
			case 'Q':
				c_data.n_num = 12;
				break;
			case 'K':
				c_data.n_num = 13;
				break;
			case 'A':
				c_data.n_num = 14;
		}
		switch(diller){
			case 'E':
				S.push_back(c_data);
				diller = 'S';
				break;
			case 'W':
				N.push_back(c_data);
				diller = 'N';
				break;
			case 'S':
				W.push_back(c_data);
				diller = 'W';
				break;
			case 'N':
				E.push_back(c_data);
				diller = 'E';
				break;
		}
	}
}

int main(){
	char temp;
	for(;;){
		input_fp >> temp;
		if(temp == '#'){
			break;
		}
		else{
			diller = temp;
		}
		input_data();
		sort_data();
		print_data();
		clear_data();
	}	
}
