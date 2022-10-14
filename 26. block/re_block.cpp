#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

ifstream input_fp("block.inp");
ofstream output_fp("block.out");

typedef struct Block{
	unsigned int dx;
	unsigned int dy;
	unsigned int ux;
	unsigned int uy;
}block;

typedef struct Segment{
	int s;
	int e;
	vector<block*> stack;
}segment;

vector<block> blocks;
segment segment_y[20001];
segment segment_x[20001];
int result_x, result_y, size;

bool Compare_Y(block a, block b){
	return a.dy < b.dy;
}

bool Compare_X(block a, block b){
	return a.dx < b.dx;
}



bool down_blocks(){
	sort(blocks.begin(), blocks.end(), Compare_Y);
	int min;
	bool move = false;
	block temp;
	register int i, j;
	for(i=0; i<size; i++){
		min = 0;
		if(blocks[i].dy == 0){
			continue;
		}
		else{
			temp = blocks[i];
			for(j=i-1; j>=0; j--){
				if((temp.dx <= blocks[j].dx && blocks[j].dx < temp.ux) || (temp.dx < blocks[j].ux && blocks[j].ux <= temp.ux) || (blocks[j].dx <= temp.dx && temp.ux <= blocks[j].ux)){
					if(min < blocks[j].uy){
						min = blocks[j].uy;
						if(temp.dy == min){
							break;
						}
					}
				}
			}
			if(temp.dy != min){
				temp.uy = temp.uy - temp.dy + min;
				temp.dy = min;
				blocks[i] = temp;
			}
		}
	}
}

void left_blocks(){
	sort(blocks.begin(), blocks.end(), Compare_X);
	int min;
	block temp;
	register int i, j;
	for(i=0; i<size; i++){
		min = 0;
		if(blocks[i].dx == 0){
			continue;
		}
		temp = blocks[i];
		for(j=i-1; j>=0; j--){
			if((temp.dy < blocks[j].dy && blocks[j].dy < temp.uy) || (temp.dy < blocks[j].uy && blocks[j].uy < temp.uy) || (blocks[j].dy <= temp.dy && temp.uy <= blocks[j].uy)){
				if(min < blocks[j].ux){
					min = blocks[j].ux;
					if(temp.dx == min){
						break;
					}
				}
			}
		}
		if(temp.dx != min){
			temp.ux = temp.ux - temp.dx + min;
			temp.dx = min;
			blocks[i] = temp;
		}
 	}
}


void input_data(){
	int tmp;
	int min;
	block temp;
	
	input_fp >> size;
	result_x = 0;
	result_y = 0;
	for(int i=0; i<size; i++){
		input_fp >> temp.dx >> temp.dy >> temp.ux >> temp.uy;
		blocks.push_back(temp);
	}
	down_blocks();
	left_blocks();
	segment_x[0] = &segment_x[1];
	for(int i=0; i<size; i++){
		if(block[i].dx == 0){
			segment_x[i].stack.push_back(block);
			for(int j=i+1; j<size; j++){
			}
		}
	}
}


// x에 대해서 dx == 0 일 때 root에 추가. 
// 그 이후 사각형에 대해서 dx != 0일 때, 
// dx가 0인 사각형의 dy ~ uy 범위 안에 해당 사각형이 포함되면
// 해당 dx가 0인 사각형의 인덱스에 push_back한다.
 

// y에 대해서 dy == 0 일 때 root에 추가. 
// 그 이후 사각형에 대해서 dy != 0일 때, 
// dx가 0인 사각형의 dx ~ ux 범위 안에 해당 사각형이 포함되면
// 해당 dy가 0인 사각형의 인덱스에 push_back한다.

void calc(){
	
}

int main(){
	int T;
	input_fp >> T;
	for(T; T>0; T--){
		input_data();
		calc();
		output_fp << result_x << " " << result_y << "\n";
		blocks.clear();
	}
}
