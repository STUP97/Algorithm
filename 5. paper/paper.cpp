#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

ifstream input_fp("paper.inp");   
ofstream output_fp("paper.out");

typedef struct paper_size_position_data{
	int lx;
	int ly;
	int rx;
	int ry;
}paper;

vector<paper> temp_data;
vector<paper> data;
vector<paper> stack; 
int T, result_A, result_B, result_C;


void input_data(){
	int x,y,w,h;
	paper temp;
	input_fp >> T;
	for(int i=0; i<T; i++){
		input_fp >> x >> y >> w >> h;
		temp.lx = x;
		temp.ly = y;
		temp.rx = w+x;
		temp.ry = h+y;
		temp_data.push_back(temp);
	}
	for(int i=0; i<T; i++){
		data.push_back(temp_data[temp_data.size()-1]);
		temp_data.pop_back();
	//	들어간 데이터 체크. 
	//    cout << paper_data[i].lx << " "<< paper_data[i].ly << " " << paper_data[i].rx - paper_data[i].lx << " " << paper_data[i].ry - paper_data[i].ly << endl;
	}
	result_A = 0;
	result_B = 0;
	result_C = 0;
}

bool hide_all(paper p){
	paper temp1;
	paper temp2;
	paper temp3;
	paper temp4;
	for(int i=0; i<stack.size(); i++){
		// 모두 가리는 경우 
		if(stack[i].lx <= p.lx && p.rx <= stack[i].rx && stack[i].ly <= p.ly && p.ry <= stack[i].ry){
			return true;
		}
		// 네개의 사각형이 나오는 경우 
		else if(p.lx < stack[i].lx && stack[i].rx < p.rx && p.ly < stack[i].ly && stack[i].ry < p.ry){
			temp1.lx = p.lx;
			temp1.ly = p.ly;
			temp1.rx = p.rx;
			temp1.ry = stack[i].ly;
			
			temp2.lx = p.lx;
			temp2.ly = stack[i].ry;
			temp2.rx = p.rx;
			temp2.ry = p.ry;
			
			temp3.lx = p.lx;
			temp3.ly = stack[i].ly;
			temp3.rx = stack[i].lx;
			temp3.ry = stack[i].ry;
			
			temp4.lx = stack[i].rx;
			temp4.ly = stack[i].ly;
			temp4.rx = p.rx;
			temp4.ry = stack[i].ry;
			if(!hide_all(temp1)){
				return false;
			}
			else if(!hide_all(temp2)){
				return false;
			}
			else if(!hide_all(temp3)){
				return false;
			}
			else if(!hide_all(temp4)){
				return false;
			}
			else{
				return true;
			}
		}
		// 세개의 사각형이 나오는 경우
		// 우측 변 관통형
		else if(p.lx < stack[i].lx && stack[i].lx < p.rx && p.ly < stack[i].ly && stack[i].ry < p.ry && p.rx <= stack[i].rx) {
			temp1.lx = p.lx;
			temp1.ly = p.ly;
			temp1.rx = p.rx;
			temp1.ry = stack[i].ly;
			
			temp2.lx = p.lx;
			temp2.ly = stack[i].ly;
			temp2.rx = stack[i].lx;
			temp2.ry = stack[i].ry;
			
			temp3.lx = p.lx;
			temp3.ly = stack[i].ry;
			temp3.rx = p.rx;
			temp3.ry = p.ry;
			if(!hide_all(temp1)){
				return false;
			}
			else if(!hide_all(temp2)){
				return false;
			}
			else if(!hide_all(temp3)){
				return false;
			}
			else{
				return true;
			}
		}
		// 좌측 변 관통형
		else if(p.lx < stack[i].rx && stack[i].rx < p.rx && p.ly < stack[i].ly && stack[i].ry < p.ry && stack[i].lx <= p.lx){
			temp1.lx = p.lx;
			temp1.ly = p.ly;
			temp1.rx = p.rx;
			temp1.ry = stack[i].ly;
			
			temp2.lx = stack[i].rx;
			temp2.ly = stack[i].ly;
			temp2.rx = p.rx;
			temp2.ry = stack[i].ry;
			
			temp3.lx = p.lx;
			temp3.ly = stack[i].ry;
			temp3.rx = p.rx;
			temp3.ry = p.ry;
			if(!hide_all(temp1)){
				return false;
			}
			else if(!hide_all(temp2)){
				return false;
			}
			else if(!hide_all(temp3)){
				return false;
			}
			else{
				return true;
			}
		}
		// 상단 변 관통형
		else if(p.ly < stack[i].ly && stack[i].ly < p.ry && p.lx < stack[i].lx && stack[i].rx < p.rx && p.ry <= stack[i].ry){
			temp1.lx = p.lx;
			temp1.ly = p.ly;
			temp1.rx = p.rx;
			temp1.ry = stack[i].ly;
			
			temp2.lx = p.lx;
			temp2.ly = stack[i].ly;
			temp2.rx = stack[i].lx;
			temp2.ry = p.ry;
			
			temp3.lx = stack[i].rx;
			temp3.ly = stack[i].ly;
			temp3.rx = p.rx;
			temp3.ry = p.ry;
			if(!hide_all(temp1)){
				return false;
			}
			else if(!hide_all(temp2)){
				return false;
			}
			else if(!hide_all(temp3)){
				return false;
			}
			else{
				return true;
			}
		}
		// 하단 변 관통형 
		else if(p.ly < stack[i].ry && stack[i].ry < p.ry && p.lx < stack[i].lx && stack[i].rx < p.rx && stack[i].ly <= p.ly){
			temp1.lx = p.lx;
			temp1.ly = stack[i].ry;
			temp1.rx = p.rx;
			temp1.ry = p.ry;
			
			temp2.lx = p.lx;
			temp2.ly = p.ly;
			temp2.rx = stack[i].lx;
			temp2.ry = stack[i].ry;
			
			temp3.lx = stack[i].rx;
			temp3.ly = p.ly;
			temp3.rx = p.rx;
			temp3.ry = stack[i].ry;
			if(!hide_all(temp1)){
				return false;
			}
			else if(!hide_all(temp2)){
				return false;
			}
			else if(!hide_all(temp3)){
				return false;
			}
			else{
				return true;
			}
		}
		// 두개의 사각형이 나오는 경우
		// 우측 상단 가림형
		else if(p.lx < stack[i].lx && stack[i].lx < p.rx && p.ly < stack[i].ly && stack[i].ly < p.ry && p.rx <= stack[i].rx && p.ry <= stack[i].ry){
			temp1.lx = p.lx;
			temp1.ly = p.ly;
			temp1.rx = p.rx;
			temp1.ry = stack[i].ly;
			
			temp2.lx = p.lx;
			temp2.ly = stack[i].ly;
			temp2.rx = stack[i].lx;
			temp2.ry = p.ry;
			if(!hide_all(temp1)){
				return false;
			}
			else if(!hide_all(temp2)){
				return false;
			}
			else{
				return true;
			}
		} 
		// 좌측 상단 가림형
		else if(p.lx < stack[i].rx && stack[i].rx < p.rx && p.ly < stack[i].ly && stack[i].ly < p.ry && stack[i].lx <= p.lx && p.ry <= stack[i].ry){
			temp1.lx = p.lx;
			temp1.ly = p.ly;
			temp1.rx = p.rx;
			temp1.ry = stack[i].ly;
			
			temp2.lx = stack[i].rx;
			temp2.ly = stack[i].ly;
			temp2.rx = p.rx;
			temp2.ry = p.ry;
			if(!hide_all(temp1)){
				return false;
			}
			else if(!hide_all(temp2)){
				return false;
			}
			else{
				return true;
			}
		}
		// 우측 하단 가림형
		else if(p.lx < stack[i].lx && stack[i].lx < p.rx && p.ly < stack[i].ry && stack[i].ry < p.ry && p.rx <= stack[i].rx && stack[i].ly <= p.ly){
			temp1.lx = p.lx;
			temp1.ly = stack[i].ry;
			temp1.rx = p.rx;
			temp1.ry = p.ry;
			
			temp2.lx = p.lx;
			temp2.ly = p.ly;
			temp2.rx = stack[i].lx;
			temp2.ry = stack[i].ry;
			if(!hide_all(temp1)){
				return false;
			}
			else if(!hide_all(temp2)){
				return false;
			}
			else{
				return true;
			}
		}
		// 좌측 하단 가림형 
		else if(p.lx < stack[i].rx && stack[i].rx < p.rx && p.ly < stack[i].ry && stack[i].ry < p.ry && stack[i].lx <= p.lx && stack[i].ly <= p.ly){
			temp1.lx = p.lx;
			temp1.ly = stack[i].ry;
			temp1.rx = p.rx;
			temp1.ry = p.ry;
			
			temp2.lx = stack[i].rx;
			temp2.ly = p.ly;
			temp2.rx = p.rx;
			temp2.ry = stack[i].ry;
			if(!hide_all(temp1)){
				return false;
			}
			else if(!hide_all(temp2)){
				return false;
			}
			else{
				return true;
			}
		}
		// 세로 관통형
		else if(p.lx < stack[i].lx && stack[i].rx < p.rx && stack[i].ly <= p.ly && p.ry <= stack[i].ry){
			temp1.lx = p.lx;
			temp1.ly = p.ly;
			temp1.rx = stack[i].lx;
			temp1.ry = p.ry;
			
			temp2.lx = stack[i].rx;
			temp2.ly = p.ly;
			temp2.rx = p.rx;
			temp2.ry = p.ry;
			if(!hide_all(temp1)){
				return false;
			}
			else if(!hide_all(temp2)){
				return false;
			}
			else{
				return true;
			}
		}
		// 가로 관통형 
		else if(p.ly < stack[i].ly && stack[i].ry < p.ry && stack[i].lx <= p.lx && p.rx <= stack[i].rx){
			temp1.lx = p.lx;
			temp1.ly = p.ly;
			temp1.rx = p.rx;
			temp1.ry = stack[i].ly;
			
			temp2.lx = p.lx;
			temp2.ly = stack[i].ry;
			temp2.rx = p.rx;
			temp2.ry = p.ry;
			if(!hide_all(temp1)){
				return false;
			}
			else if(!hide_all(temp2)){
				return false;
			}
			else{
				return true;
			}
		}
		// 하나의 사각형이 나오는 경우 
		// 덮는 색종이가 위 아래를 빈틈없이 가리고 왼쪽을 덮지 않고 오른쪽으로 튀어나올때 
		else if(p.lx < stack[i].lx && stack[i].lx < p.rx && stack[i].ly <= p.ly && p.ry <= stack[i].ry){
			temp1.lx = p.lx;
			temp1.ly = p.ly;
			temp1.rx = stack[i].lx;
			temp1.ry = p.ry;
			if(!hide_all(temp1)){
				return false;
			}
			else{
				return true;
			}
		} 
		// 덮는 색종이가 위 아래를 빈틈없이 가리고 오른쪽을 덮지 않고 왼쪽으로 튀어나올때 
		else if(p.lx < stack[i].rx && stack[i].rx < p.rx && stack[i].ly <= p.ly && p.ry <= stack[i].ry){
			temp1.lx = stack[i].rx;
			temp1.ly = p.ly;
			temp1.rx = p.rx;
			temp1.ry = p.ry;
			if(!hide_all(temp1)){
				return false;
			}
			else{
				return true;
			}
		} 
		// 덮는 색종이가 좌 우를 빈틈없이 가리고 아래쪽을 덮지 않고 위쪽으로 튀어나올때 
		else if(p.ly < stack[i].ly && stack[i].ly < p.ry && stack[i].lx <= p.lx && p.rx <= stack[i].rx){
			temp1.lx = p.lx;
			temp1.ly = p.ly;
			temp1.rx = p.rx;
			temp1.ry = stack[i].ly;
			if(!hide_all(temp1)){
				return false;
			}
			else{
				return true;
			}
		}
		// 덮는 색종이가 좌 우를 빈틈없이 가리고 아래쪽을 덮지 않고 아래쪽으로 튀어나올때 
		else if(p.ly < stack[i].ry && stack[i].ry < p.ry && stack[i].lx <= p.lx && p.rx <= stack[i].rx){
			temp1.lx = p.lx;
			temp1.ly = stack[i].ry;
			temp1.rx = p.rx;
			temp1.ry = p.ry;
			if(!hide_all(temp1)){
				return false;
			}
			else{
				return true;
			}
		}
		
	}
	return false;
}
// 아래의 가려지는지 온전히 보이는지 함수를 변형하여 재귀함수로 만들어 전체가 가려지는 것이 최종적으로 다 나오는 경우가 아니면 보이는 것.  

void somewhere_hiding(){
	bool hide;
	for(int i=0; i<T; i++){
		hide = false;
		for(int j=0; j<stack.size(); j++){
			// 전체를 덮을 경우 
			if(stack[j].lx <= data[0].lx && stack[j].ly <= data[0].ly && data[0].rx <= stack[j].rx && data[0].ry <= stack[j].ry){
				hide = true;
				break;
			} 
			// 상단 변 또는 하단 변이 포함 될 경우    y값 범위 고정 x값 범위 조절. 
			else if((data[0].ly < stack[j].ry && stack[j].ry <= data[0].ry) || (data[0].ly <= stack[j].ly && stack[j].ly < data[0].ry)){
				if(data[0].lx <= stack[j].lx && stack[j].lx < data[0].rx){
					hide = true;
					break;
				}
				else if(data[0].lx < stack[j].rx && stack[j].rx <= data[0].rx){
					hide = true;
					break;
				}
				else if(stack[j].lx <= data[0].lx && data[0].rx <= stack[j].rx){
					hide = true;
					break;
				}
			} 
			// 우측 변 또는 좌측 변이 포함 될 경우 
			else if((data[0].lx < stack[j].rx && stack[j].rx <= data[0].rx) || (data[0].lx <= stack[j].lx && stack[j].lx < data[0].rx)){
				if(data[0].ly <= stack[j].ly && stack[j].ly < data[0].ry){
					hide = true;
					break;
				}
				else if(data[0].ly < stack[j].ry && stack[j].ry <= data[0].ry){
					hide = true;
					break;
				}
				else if(stack[j].ly <= data[0].ly && data[0].ry <= stack[j].ry){
					hide = true;
					break;
				}
			}
		}
		// 가려진 부분 없을 때. 
		if(!hide){
			result_C++;
			stack.push_back(data[0]);
			data.erase(data.begin());
		}
		// 가려진 부분 있을 때. 
		else{
			// 전부 다 가려지는지 확인. 
			bool check = hide_all(data[0]);
			if(check){
				result_A++;
				data.erase(data.begin());	
			}
			else{
				result_B++;
				stack.push_back(data[0]);
				data.erase(data.begin());	
			}
		}
		//cout << result_A << " " << result_B << " " << result_C << endl;
	}
}


void print_result(){
	output_fp << result_A << " " << result_B << " " << result_C;
}
int main(){
	input_data();
	somewhere_hiding();
	print_result();
}
