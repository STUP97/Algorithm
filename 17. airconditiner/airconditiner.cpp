#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

ifstream input_fp("airconditiner.inp");
ofstream output_fp("airconditiner.out");

typedef struct DATA{
	int spot;
	int temp;
}data;

vector<int> room;
vector<int> aircon_spot;
vector<data> spot_data;


void sort(){
	data temp;
	for(int i=0; i<spot_data.size(); i++){
		for(int j=i+1; j<spot_data.size(); j++){
			if(spot_data[i].temp > spot_data[j].temp){
				temp = spot_data[i];
				spot_data[i] = spot_data[j];
				spot_data[j] = temp;
			}
		}
	}
}

void check_need(){
	int gab;
	for(int i=0; i<spot_data.size(); i++){
		for(int j=i+1; j<spot_data.size(); j++){
			gab = spot_data[i].spot - spot_data[j].spot;
			if(gab < 0){
				gab *= -1;
			}
			if(spot_data[i].temp + gab <= spot_data[j].temp){
				spot_data.erase(spot_data.begin()+j);
				j--;
			}
		}
	}
}

void input_data(){
	int cnt, aircon, temp;
	data temp2;
	input_fp >> cnt >> aircon;
	for(int i=0; i<cnt; i++){
		room.push_back(1000000001);
	}
	for(int i=0; i<aircon; i++){
		input_fp >> temp;
		aircon_spot.push_back(temp-1);
	}
	for(int i=0; i<aircon; i++){
		input_fp >> temp;
		room[aircon_spot[i]] = temp;
		temp2.spot = aircon_spot[i];
		temp2.temp = temp;
		spot_data.push_back(temp2);
	}
	//sort();
	check_need();
}

void left_move(data x){
	x.spot--;
	x.temp++;
	if(x.spot < 0){
		return;
	}
	else if(room[x.spot] < x.temp){
		return;
	}
	else{
		room[x.spot] = x.temp;
		left_move(x);
	}
}
void right_move(data x){
	x.spot++;
	x.temp++;
	if(x.spot >= room.size()){
		return;
	}
	else if(room[x.spot] < x.temp){
		return;
	}
	else{
		room[x.spot] = x.temp;
		right_move(x);
	}
}

void calc(){
	for(int i=0; i<spot_data.size(); i++){
		left_move(spot_data[i]);
		right_move(spot_data[i]);
	}
}

void print_data(){
	for(int i=0; i<room.size(); i++){
		output_fp << room[i] << " ";
	}
	output_fp << endl;
}

void clear_data(){
	room.clear();
	aircon_spot.clear();
	spot_data.clear();
}

int main(){
	int T;
	input_fp >> T;
	for(int i=0; i<T; i++){
		input_data();
		calc();
		print_data();
		clear_data();
	}
}
