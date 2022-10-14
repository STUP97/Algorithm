#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

ifstream input_fp("paper.inp");   
ofstream output_fp("paper.out");

typedef struct data_set{
	int x;
	int y;
}pir;

typedef struct data{
	pir a;
	pir b;
	pir c;
	pir d;
}paper;

vector<paper> paper_data;
vector<paper> stack; 
int T, result_A, result_B, result_C;



void input_data(){
	int x,y,w,h;
	pir pair_temp;
	paper temp;
	input_fp >> T;
	for(int i=0; i<T; i++){
		input_fp >> x >> y >> w >> h;
		// ���ϴ��� 
		pair_temp.x = x;
		pair_temp.y = y;
		temp.a = pair_temp;
		// ���ϴ��� 
		pair_temp.x = x+w;
		pair_temp.y = y;
		temp.b = pair_temp;
		// �»���� 
		pair_temp.x = x;
		pair_temp.y = y+h;
		temp.c = pair_temp;
		// ������ 
		pair_temp.x = x+w;
		pair_temp.y = y+h;
		temp.d = pair_temp;
		
		paper_data.push_back(temp);
	}
	result_A = 0;
	result_B = 0;
	result_C = 0;
}


// �������� �κ��� ���� �� ��ü�� ���������� Ȯ��. 
bool hide_all(paper p, int spot){
	paper temp1;
	paper temp2;
	paper temp3;
	paper temp4;
	for(int i=0; i<stack.size(); i++){
		if(stack[i].a.x <= p.a.x && p.d.x <= stack[i].d.x && stack[i].a.y <= p.a.y && p.d.y <= stack[i].d.y){
			return true;
		}
		// ������ �����̿��� ���� ����� �������� ��� 
		else if(p.a.x < stack[i].a.x && stack[i].a.x < p.d.x && p.a.y < stack[i].a.y && stack[i].a.y < p.d.y && p.d.x <= stack[i].d.x && p.d.y <= stack[i].d.y){	
			temp1.a = p.a;
			temp1.b = p.b;
			temp1.c.x = p.a.x;
			temp1.c.y = stack[i].a.y;
			temp1.d.x = p.d.x;
			temp1.d.y = stack[i].a.y;
			
			temp2.a = temp1.c;
			temp2.b = stack[i].a;
			temp2.c = p.c;
			temp2.d.x = stack[i].a.x;
			temp2.d.y = p.d.y;
			
			if(!hide_all(temp1,i+1)){
				return false;
			}
			else if(!hide_all(temp2,i+1)){
				return false; 
			}
			else{
				return true;
			} 
		}
		// ������ �����̿� ���� ����� �������� ��� 
		else if(p.a.x < stack[i].b.x && stack[i].b.x < p.d.x && p.a.y < stack[i].b.y && stack[i].b.y < p.d.y && p.c.x >= stack[i].c.x && p.c.y <= stack[i].c.y){
			temp1.a = p.a;
			temp1.b = p.b;
			temp1.c.x = p.a.x;
			temp1.c.y = stack[i].a.y;
			temp1.d.x = p.d.x;
			temp1.d.y = stack[i].a.y;
			
			temp2.a = stack[i].b;
			temp2.b = temp1.d;
			temp2.c = p.c;
			temp2.d.x = stack[i].d.x;
			temp2.d.y = p.d.y;
			
			if(!hide_all(temp1,i+1)){
				return false;
			}
			else if(!hide_all(temp2,i+1)){
				return false; 
			}
			else{
				return true;
			} 
		}
		// ������ �����̿� ���� �ϴ��� �������� ���	
		else if(p.a.x < stack[i].c.x && stack[i].c.x < p.d.x && p.a.y < stack[i].c.y && stack[i].c.y < p.d.y && p.b.x <= stack[i].b.x && p.b.y >= stack[i].b.y){
			temp1.a.x = p.a.x;
			temp1.a.y = stack[i].d.y;
			temp1.b.x = p.d.x;
			temp1.b.y = stack[i].d.y;
			temp1.c = p.c;
			temp1.d = p.d;
			
			temp2.a = p.a;
			temp2.b.x = stack[i].a.x;
			temp2.b.y = p.a.y;
			temp2.c = temp1.a;
			temp2.d = stack[i].c;
			
			if(!hide_all(temp1,i+1)){
				return false;
			}
			else if(!hide_all(temp2,i+1)){
				return false; 
			}
			else{
				return true;
			} 
		}
		// ������ �����̿� ���� �ϴ��� �������� ��� 
		else if(p.a.x < stack[i].d.x && stack[i].d.x < p.d.x && p.a.y < stack[i].d.y && stack[i].d.y < p.d.y && p.a.x >= stack[i].a.x && p.a.y >= stack[i].a.y){
			temp1.a.x = p.a.x;
			temp1.a.y = stack[i].d.y;
			temp1.b.x = p.d.x;
			temp1.b.y = stack[i].d.y;
			temp1.c = p.c;
			temp1.d = p.d;
			
			temp2.a.x = stack[i].d.x;
			temp2.a.y = p.a.y;
			temp2.b = p.b;
			temp2.c = stack[i].d;
			temp2.d = temp1.b;
			
			if(!hide_all(temp1,i+1)){
				return false;
			}
			else if(!hide_all(temp2,i+1)){
				return false; 
			}
			else{
				return true;
			} 
		}
		// ������ �����̿� �߾��� �������� ��� 
		else if(p.a.x < stack[i].a.x && stack[i].a.x < p.d.x && p.a.y < stack[i].a.y && stack[i].a.y < p.d.y && p.a.x < stack[i].d.x && stack[i].d.x < p.d.x && p.a.y < stack[i].d.y && stack[i].d.y < p.d.y){
			temp1.a = p.a;
			temp1.b = p.b;
			temp1.c.x = p.a.x;
			temp1.c.y = stack[i].a.y;
			temp1.d.x = p.d.x;
			temp1.c.y = stack[i].a.y;
			
			temp2.a.x = p.a.x;
			temp2.a.y = stack[i].d.y;
			temp2.b.x = p.d.x;
			temp2.b.y = stack[i].d.y;
			temp2.c = p.c;
			temp2.d = p.d;
			
			temp3.a = temp1.c;
			temp3.b = stack[i].a;
			temp3.c = temp2.a;
			temp3.d = stack[i].c;
			
			temp4.a = stack[i].b;
			temp4.b = temp1.d;
			temp4.c = stack[i].d;
			temp4.d = temp2.b;
			
			
			if(!hide_all(temp1,i+1)){
				return false;
			}
			else if(!hide_all(temp2,i+1)){
				return false; 
			}
			else if(!hide_all(temp3,i+1)){
				return false;
			}
			else if(!hide_all(temp4,i+1)){
				return false; 
			}
			else{
				return true;
			} 
		}
		// ������ �����̿� ��� ���� �Ϻκ��� �������� ���
		else if(p.a.x < stack[i].a.x && stack[i].a.x < p.d.x && p.a.y < stack[i].a.y && stack[i].a.y < p.d.y && p.a.x < stack[i].b.x && stack[i].b.x < p.d.x && stack[i].d.y >= p.d.y){
			temp1.a = p.a;
			temp1.b = p.b;
			temp1.c.x = p.a.x;
			temp1.c.y = stack[i].a.y;
			temp1.d.x = p.d.x;
			temp1.d.y = stack[i].a.y;
			
			temp2.a = temp1.c;
			temp2.b = stack[i].a;
			temp2.c = p.c;
			temp2.d.x = stack[i].a.x;
			temp2.d.y = p.d.y;
			
			temp3.a = stack[i].b;
			temp3.b = temp1.d;
			temp3.c.x = stack[i].a.x;
			temp3.c.y = p.d.y;
			temp3.d = p.d;
			
			if(!hide_all(temp1,i+1)){
				return false;
			}
			else if(!hide_all(temp2,i+1)){
				return false; 
			}
			else if(!hide_all(temp3,i+1)){
				return false;
			}
			else{
				return true;
			} 
		}
		// ������ �����̿� ���� ���� �Ϻκ��� �������� ���
		else if(p.a.x < stack[i].a.x && stack[i].a.x < p.d.x && p.a.y < stack[i].a.y && stack[i].a.y < p.d.y && p.a.y < stack[i].c.y && stack[i].c.y < p.d.y && stack[i].d.x >= p.d.x){
			temp1.a = p.a;
			temp1.b = p.b;
			temp1.c.x = p.a.x;
			temp1.c.y = stack[i].a.y;
			temp1.d.x = p.d.x;
			temp1.d.y = stack[i].a.y;
			
			temp2.a.x = p.a.x;
			temp2.a.y = stack[i].d.y;
			temp2.b.x = p.d.x;
			temp2.b.y = stack[i].d.y;
			temp2.c = p.c;
			temp2.d = p.d;
			
			temp3.a = temp1.c;
			temp3.b = stack[i].a;
			temp3.c = temp2.a;
			temp3.d = stack[i].c;
	
			if(!hide_all(temp1,i+1)){
				return false;
			}
			else if(!hide_all(temp2,i+1)){
				return false; 
			}
			else if(!hide_all(temp3,i+1)){
				return false;
			}
			else{
				return true;
			} 
		}
	// ������ �����̿� ���� ���� �Ϻκ��� �������� ���
		else if(p.a.x < stack[i].b.x && stack[i].b.x < p.d.x && p.a.y < stack[i].b.y && stack[i].b.y < p.d.y && p.a.y < stack[i].d.y && stack[i].d.y < p.d.y && stack[i].a.x <= p.d.x){	
			temp1.a = p.a;
			temp1.b = p.b;
			temp1.c.x = p.a.x;
			temp1.c.y = stack[i].a.y;
			temp1.d.x = p.d.x;
			temp1.d.y = stack[i].a.y;
			
			temp2.a.x = p.a.x;
			temp2.a.y = stack[i].d.y;
			temp2.b.x = p.d.x;
			temp2.b.y = stack[i].d.y;
			temp2.c = p.c;
			temp2.d = p.d;
				
			temp3.a = stack[i].b;
			temp3.b = temp1.d;
			temp3.c = stack[i].d;
			temp3.d = temp2.b;
			
			if(!hide_all(temp1,i+1)){
				return false;
			}
			else if(!hide_all(temp2,i+1)){
				return false; 
			}
			else if(!hide_all(temp3,i+1)){
				return false;
			}
			else{
				return true;
			} 
		}
		// ������ �����̿� �ϴ� ���� �Ϻκ��� �������� ��� 
		else if(p.a.x < stack[i].c.x && stack[i].c.x < p.d.x && p.a.y < stack[i].c.y && stack[i].c.y < p.d.y && p.a.x < stack[i].d.x && stack[i].d.x < p.d.x && stack[i].a.y <= p.a.y){
			temp1.a.x = p.a.x;
			temp1.a.y = stack[i].d.y;
			temp1.b.x = p.d.x;
			temp1.b.y = stack[i].d.y;
			temp1.c = p.c;
			temp1.d = p.d;
			
			temp2.a = p.a;
			temp2.b.x = stack[i].a.x;
			temp2.b.y = p.a.y;
			temp2.c = temp1.a;
			temp2.d = stack[i].c;
			
			temp3.a.x = stack[i].d.x;
			temp3.a.y = p.a.y;
			temp3.b = p.b;
			temp3.c = stack[i].d;
			temp3.d = temp1.b;
			
			if(!hide_all(temp1,i+1)){
				return false;
			}
			else if(!hide_all(temp2,i+1)){
				return false; 
			}
			else if(!hide_all(temp3,i+1)){
				return false;
			}
			else{
				return true;
			} 
		}
		// ������ �����̿� ���� ���� �������� ���
		else if(stack[i].a.x <= p.a.x && p.d.x <= stack[i].d.x && p.a.y < stack[i].a.y && stack[i].a.y < p.d.y && p.d.y <= stack[i].d.y){
			temp1.a = p.a;
			temp1.b = p.b;
			temp1.c.x = p.a.x;
			temp1.c.y = stack[i].a.y;
			temp1.d.x = p.d.x;
			temp1.d.y = stack[i].a.y;
			
			if(!hide_all(temp1,i+1)){
				return false;
			}
			else{
				return true;
			} 
		}
		// ������ �����̿� ������ ���� �������� ���
		else if(stack[i].a.x <= p.a.x && p.d.x <= stack[i].d.x && p.a.y < stack[i].d.y && stack[i].d.y < p.d.y && p.a.y >= stack[i].a.y){
			temp1.a.x = p.a.x;
			temp1.a.y = stack[i].d.y;
			temp1.b.x = p.d.x;
			temp1.b.y = stack[i].d.y;
			temp1.c = p.c;
			temp1.d = p.d;
			
			if(!hide_all(temp1,i+1)){
				return false;
			}
			else{
				return true;
			} 
		}
		// ������ �����̿� ������ ���� �������� ���
		else if(stack[i].a.y <= p.a.y && p.d.y <= stack[i].d.y && p.a.x < stack[i].a.x && stack[i].a.x < p.d.x && p.d.x <= stack[i].d.x){
			temp1.a = p.a;
			temp1.b.x = stack[i].a.x;
			temp1.b.y = p.a.y;
			temp1.c = p.c;
			temp1.d.x = stack[i].a.x;
			temp1.d.y = p.d.y;
			
			if(!hide_all(temp1,i+1)){
				return false;
			}
			else{
				return true;
			} 
		}
		// ������ �����̿� ���� ���� �������� ���
		else if(stack[i].a.y <= p.a.y && p.d.y <= stack[i].d.y && p.a.x < stack[i].d.x && stack[i].d.x < p.d.x && p.a.x >= stack[i].a.x){
			temp1.a.x = stack[i].d.x;
			temp1.a.y = p.a.y;	
			temp1.b = p.b;
			temp1.c.x = stack[i].d.x;
			temp1.c.y = p.d.y;
			temp1.d = p.d;
			
			if(!hide_all(temp1,i+1)){
				return false;
			}
			else{
				return true;
			} 
		}
		// ������ �����̿� ���� ���η� ������ϴ� ��� 
		else if(p.a.x < stack[i].a.x && stack[i].d.x < p.d.x && stack[i].a.y <= p.a.y && p.d.y <= stack[i].d.y){
			temp1.a = p.a;
			temp1.b.x = stack[i].a.x;
			temp1.b.y = p.a.y;
			temp1.c = p.c;
			temp1.d.x = stack[i].a.x;
			temp1.d.y = p.d.y;
			
			temp2.a.x = stack[i].d.x;
			temp2.a.y = p.a.y;
			temp2.b = p.b;
			temp2.c.x = stack[i].d.x;
			temp2.c.y = p.d.y;
			temp2.d = p.d;
			
			if(!hide_all(temp1,i+1)){
				return false;
			}
			else if(!hide_all(temp2,i+1)){
				return false; 
			}
			else{
				return true;
			} 
		}
		// ������ �����̿� ���� ���η� ������ϴ� ���
		else if(p.a.y < stack[i].a.y && stack[i].d.y < p.d.y && stack[i].a.x <= p.a.x && p.d.x <= stack[i].d.x){
			temp1.a = p.a;
			temp1.b = p.b;
			temp1.c.x = p.a.x;
			temp1.c.y = stack[i].a.y;
			temp1.d.x = p.d.x;
			temp1.d.y = stack[i].a.y;
			
			temp2.a.x = p.a.x;
			temp2.a.y = stack[i].d.y;
			temp2.b.x = p.d.x;
			temp2.b.y = stack[i].d.y;
			temp2.c = p.c;
			temp2.d = p.d;
			
			if(!hide_all(temp1,i+1)){
				return false;
			}
			else if(!hide_all(temp2,i+1)){
				return false; 
			}
			else{
				return true;
			} 
		} 
	}
	return false;
}

// �������� �κ��� �ִ��� Ȯ��. 
void hide_somewhere(){
	paper temp = paper_data[paper_data.size()-1];
	bool hide = false; 
	int spot;
	for(int i=0; i<stack.size(); i++){
		// ���ο� ������ ������ �𼭸��� �ִ��� 
		if(temp.a.x <= stack[i].a.x && stack[i].a.x < temp.d.x && temp.a.y <= stack[i].a.y && stack[i].a.y < temp.d.y){
			hide = true;
			spot = i;
			break;
		}
		else if(temp.a.x < stack[i].b.x && stack[i].b.x <= temp.d.x && temp.a.y <= stack[i].b.y && stack[i].b.y < temp.d.y){
			hide = true;
			spot = i;
			break;
		}
		else if(temp.a.x <= stack[i].c.x && stack[i].c.x < temp.d.x && temp.a.y < stack[i].c.y && stack[i].c.y <= temp.d.y){
			hide = true;
			spot = i;
			break;
		}
		else if(temp.a.x < stack[i].d.x && stack[i].d.x <= temp.d.x && temp.a.y < stack[i].d.y && stack[i].d.y <= temp.d.y){
			hide = true;
			spot = i;
			break;
		}
		// �ܺο� ���� ������ ���̸� ��������. 
		// ���� �������� ���� ���� ���� 
		else if(temp.a.x <= stack[i].a.x && stack[i].a.x < temp.d.x && stack[i].a.y <= temp.a.y && temp.d.y <= stack[i].d.y) {
			hide = true;
			spot = i;
			break;
		}
		// ���� �������� ���� ���� ���� 
		else if(temp.a.x < stack[i].d.x && stack[i].d.x <= temp.d.x && stack[i].a.y <= temp.a.y && temp.d.y <= stack[i].d.y) {
			hide = true;
			spot = i;
			break;
		}
		// �ϴ� �������� ���� ���� ���� 
		else if(temp.a.y <= stack[i].a.y && stack[i].a.y < temp.d.y && stack[i].a.x <= temp.a.x && temp.d.x <= stack[i].d.x) {
			hide = true;
			spot = i;
			break;
		}
		// �Ʒ� 
		else if(temp.a.y < stack[i].d.y && stack[i].d.y <= temp.d.y && stack[i].a.x <= temp.a.x && temp.d.x <= stack[i].d.x) {
			hide = true;
			spot = i;
			break;
		}
		// ��ü 
		else if(stack[i].a.x <= temp.a.x && stack[i].a.y <= temp.a.y && temp.d.x <= stack[i].d.x && temp.d.y <= stack[i].d.y){
			hide = true;
			spot = i;
			break;
		}
		
	}
	// �������� �κ��� ���� ��. 
	if(!hide){
		stack.push_back(paper_data[paper_data.size()-1]);
		paper_data.pop_back();
		result_C++;
	}
	// �������� �κ��� ���� ��. 
	else{
		bool check = false; 
		check = hide_all(temp, spot);
		// ���� ������ ��.	
		if(check){
			paper_data.pop_back();
			result_A++; 
		}
		// �Ϻκи� ������ ��. 
		else{
			stack.push_back(paper_data[paper_data.size()-1]);
			paper_data.pop_back();
			result_B++;
		}
	}
	return;
}

void solve(){
	for(int i=0; i<T; i++){
		hide_somewhere();	
	}
}

void print_result(){
	output_fp << result_A << " " << result_B << " " << result_C;
}


int main(){
	input_data();
	solve();
	print_result();
}

/*
�Է¹��� �����̸� �������� ��ġ. 
������ ��� ���̴� ������ Ȯ��.
�������� ������ Ȯ��.
�Ⱥ��̴� ������ Ȯ��. 

������ 0 ~ 100,000,000 

������ ����ִ� ���� ���� �ִ��� Ȯ��. 


���ϴ� ���� ������ ����ִ� ������ ���ϴ������� ������
	���ٸ� ���� ���� ������ ����ִ� ������ ���ϴ������� ������.
 
 
 

*/
