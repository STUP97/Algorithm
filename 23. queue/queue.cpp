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
	// 오른쪽 자식노드가 있을 떄. 
	if(priority[n*2+1] != 0){
		// 자식노드 2개 다 부모노드보다 클 때 
		if(priority[n] < priority[n*2] && priority[n] < priority[n*2+1]){
			// 왼쪽 자식이 더 크면 부모는 왼쪽 자식과 바꾼다. 
			if(priority[n*2] > priority[n*2+1]){
				swap(n,n*2);
				n *= 2;
				if(n <= 500000 && n <= cnt){
					adjust(n);
				}
			}
			// 오른쪽 자식이 더 크면 부모는 오른쪽 자식과 바꾼다. 
			else{
				swap(n,n*2+1);
				n *= 2;
				n++;
				if(n <= 500000 && n <= cnt){
					adjust(n);
				}
			}
		}
		// 왼쪽 자식노드만 부모노드보다 클 때. 
		// 왼쪽 자식노드와 부모노드를 바꾸고 왼쪽 자식노드를 부모로 하여 재귀
		else if(priority[n] < priority[n*2] && priority[n] > priority[n*2+1]){
			swap(n,n*2);
			n *= 2;
			if(n <= 500000 && n <= cnt){
				adjust(n);
			}
		}
		// 오른쪽 자식노드만 부모노드보다 클 때. 
		// 오른쪽 자식노드와 부모노드를 바꾸고 왼쪽 자식노드를 부모로 하여 재귀
		else if(priority[n] > priority[n*2] && priority[n] < priority[n*2+1]){
			swap(n,n*2+1);
			n *= 2;
			n++;
			if(n <= 500000 && n <= cnt){
				adjust(n);
			}
		}
	}
	// 오른쪽 자식노드가 없을 때.
	// 왼쪽 자식노드만 부모노드보다 클 때.
	// 왼쪽 자식노드와 부모노드를 바꾸고 왼쪽 자식노드를 부모로 하여 재귀
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
