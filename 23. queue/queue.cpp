#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;

ifstream input_fp("queue.inp");
ofstream output_fp("queue.out");

int priority[1000002];
int cnt = 0;

void swap(int a, int b){
	int temp;
	temp = priority[a];
	priority[a] = priority[b];
	priority[b] = temp;
}

void print_data(){
	for(int i=1; i<=cnt; i*=2){
		output_fp << priority[i] << " ";
	}
	output_fp << endl;
}

void adjust(int n){
	// ������ �ڽĳ�尡 ���� ��. 
	if(priority[n*2+1] != 0){
		// �ڽĳ�� 2�� �� �θ��庸�� Ŭ �� 
		if(priority[n] < priority[n*2] && priority[n] < priority[n*2+1]){
			// ���� �ڽ��� �� ũ�� �θ�� ���� �ڽİ� �ٲ۴�. 
			if(priority[n*2] > priority[n*2+1]){
				swap(n,n*2);
				n *= 2;
				if(n <= 500000 && n <= cnt){
					adjust(n);
				}
			}
			// ������ �ڽ��� �� ũ�� �θ�� ������ �ڽİ� �ٲ۴�. 
			else{
				swap(n,n*2+1);
				n *= 2;
				n++;
				if(n <= 500000 && n <= cnt){
					adjust(n);
				}
			}
		}
		// ���� �ڽĳ�常 �θ��庸�� Ŭ ��. 
		// ���� �ڽĳ��� �θ��带 �ٲٰ� ���� �ڽĳ�带 �θ�� �Ͽ� ���
		else if(priority[n] < priority[n*2] && priority[n] > priority[n*2+1]){
			swap(n,n*2);
			n *= 2;
			if(n <= 500000 && n <= cnt){
				adjust(n);
			}
		}
		// ������ �ڽĳ�常 �θ��庸�� Ŭ ��. 
		// ������ �ڽĳ��� �θ��带 �ٲٰ� ���� �ڽĳ�带 �θ�� �Ͽ� ���
		else if(priority[n] > priority[n*2] && priority[n] < priority[n*2+1]){
			swap(n,n*2+1);
			n *= 2;
			n++;
			if(n <= 500000 && n <= cnt){
				adjust(n);
			}
		}
	}
	// ������ �ڽĳ�尡 ���� ��.
	// ���� �ڽĳ�常 �θ��庸�� Ŭ ��.
	// ���� �ڽĳ��� �θ��带 �ٲٰ� ���� �ڽĳ�带 �θ�� �Ͽ� ���
	else if(priority[n*2] != 0){
		if(priority[n] < priority[n*2]){
			swap(n,n*2);
			n *= 2;
			if(n <= 500000 && n <= cnt){
				adjust(n);
			}
		}
	}
}

void insertion(int num){
	if(priority[num] > priority[num/2] && num/2 != 0){
		swap(num,num/2);
		num /= 2;
		insertion(num);
	}
}
bool input_data(){
	int temp;
	char order;
	string input;
	getline(input_fp, input);
	
	if(input[0] == 'q'){
		return true;
	}
	else if(input[0] == 'd'){
		priority[1] = priority[cnt];
		priority[cnt] = 0;
		cnt--;
		adjust(1);
	}
	else if(input[0] == 'r'){
		print_data();
	}
	else{
		cnt++;
		istringstream(input) >> temp;
		priority[cnt] = temp;
		temp = cnt;
		insertion(temp);
	}
	return false;
}

int main(){
	for(;;){
		if(input_data()){
			break;
		}
	}
}
