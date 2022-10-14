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


//vector<block> blocks;
block blocks[10001]; 
int result_x, result_y, size;
bool move_down, move_left;


void input_data(){
	register int i;
	block temp;
	input_fp >> size;
	result_x = 0;
	result_y = 0;
	move_down = false;
	move_left = false;
	for(i=0; i<size; i++){
//		input_fp >> temp.dx >> temp.dy >> temp.ux >> temp.uy;
//		blocks.push_back(temp);
		input_fp >> blocks[i].dx >> blocks[i].dy >> blocks[i].ux >> blocks[i].uy;
	}
}

bool compare_Y(block a, block b){
	return a.dy < b.dy;
}
bool compare_uY(block a, block b){
	return a.uy < b.uy;
}
bool compare_X(block a, block b){
	return a.dx < b.dx;
}
bool compare_uX(block a, block b){
	return a.ux < b.ux;
}
bool downward(){
	// Y기준으로 정렬 
	// down 동작을 진행할 때 좌측에 깔려있는 도형들에 대해
	// 모서리 둘 중 하나가 변 안에 들어오거나
	// 깔려있는 도형이 down 동작을 하려는 도형보다 좌 우로 더 크면
	// 해당 도형의 uy값을 min에 저장
	// 만약 현재 도형을 down 하려할 때 dy값과 바뀔 위치인 min 값이 같으면 
	// 현재 움직일 수 없는 상태.
	// 만약 움직였다면 total_move를 참으로 변경
//	sort(blocks.begin(), blocks.end(), compare_Y);
	sort(blocks, blocks+size, compare_Y);
//	for(int i=0; i<size; i++){
//		cout << blocks[i].dy << " ";
//	}
//	cout << endl;
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
			sort(blocks, blocks+i, compare_uX);
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
				move = true;
				temp.uy = temp.uy - temp.dy + min;
				temp.dy = min;
				blocks[i] = temp;
			}
		}
	}
	return move;
}

bool leftward(){
	// X 기준으로 정렬
	// left 동작을 진행할 때 좌측에 깔려있는 도형들에 대해
	// 모서리 둘 중 하나가 변 안에 들어오거나
	// 깔려있는 도형이 left 동작을 하려는 도형보다 위 아래로 더 크면
	// 해당 도형의 ux값을 min에 저장
	// 만약 현재 도형을 left 하려할 때 dx값과 바뀔 위치인 min 값이 같으면 
	// 현재 움직일 수 없는 상태.
	// 만약 움직였다면 total_move를 참으로 변경 
//	sort(blocks.begin(), blocks.end(), compare_X);
	sort(blocks, blocks+size, compare_X);
//	for(int i=0; i<size; i++){
//		cout << blocks[i].dx << " ";
//	}
//	cout << endl;
	int min;
	bool move = false;
	block temp;
	register int i, j;
	for(i=0; i<size; i++){
		min = 0;
		if(blocks[i].dx == 0){
			continue;
		}
		temp = blocks[i];
		
		sort(blocks, blocks+i, compare_uY);
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
			move = true;
			temp.ux = temp.ux - temp.dx + min;
			temp.dx = min;
			blocks[i] = temp;
		}
//		if(ret < blocks[i].ux){
//			ret = blocks[i].ux;
//		}
 	}
	return move;
}
void calc(){
	// 만약 둘 다 move_down과 move_left가 한 번도 일어나지 않으면 결과값을 저장하고 반복문 중단 
	// 둘 중 한번이라도 실행되었다면 초기화 후 반복 
	register int i;
	while(true){
		if(!downward() || !leftward()){
			break;
		}
	}
	for(i=0; i<size; i++){
		if(result_y < blocks[i].uy)
			result_y = blocks[i].uy;
		if(result_x < blocks[i].ux)
			result_x = blocks[i].ux;
	}
}




int main(){
	int T;
	input_fp >> T;
	for(T; T>0; T--){
		input_data();
		calc();
		output_fp << result_x << " " << result_y << "\n";
//		blocks.clear();
	}
}
