#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

   /* input_fp 파일을 받아서 변수에 넣기. */
ifstream input_fp("bitmap.inp");
   /* output_fp 파일에 변수를 넣기 */
ofstream output_fp ("bitmap.out");
vector<char> Bitmap[200];
vector<char> Result_Bitmap[200];
/*
B의 경우 bitmap에 데이터를 모두 받아온 후 재귀적 반복을 통해 D형으로 변환하여 bitmap에 push_back
D의 경우 실시간으로 하나하나 받으며 재귀를 통해 2차원 vector에 push_back
*/
//      
void BD_Changer(int Ry, int Rx, int y, int x, int Ey, int Ex){
  	int cnt_0 = 0;
  	int cnt_1 = 0;
  	if(y == Ey-1 && x == Ex-1){
    	Result_Bitmap[0].push_back(Bitmap[y][x]);
    	return;
  	}
  	for(int i=y;i<Ey;i++){
    	for(int j=x;j<Ex;j++){
      		if(Bitmap[i][j] == '0')
        		cnt_0++;
      		else if(Bitmap[i][j] == '1')
        		cnt_1++;
      		if(cnt_0 != 0 && cnt_1 != 0){
        		Result_Bitmap[0].push_back('D');
        //좌상단
        		BD_Changer(Ry,Rx,y,x,Ey-(Ey-y)/2,Ex-(Ex-x)/2);
        //우상단
        		if(Ex != Ex-(Ex-x)/2)
          			BD_Changer(Ry,Rx,y,Ex-(Ex-x)/2,Ey-(Ey-y)/2,Ex); 
        //좌하단
        		if(Ey != Ey-(Ey-y)/2)
          			BD_Changer(Ry,Rx,Ey-(Ey-y)/2,x,Ey,Ex-(Ex-x)/2);
        //우하단
        		if(Ex != Ex-(Ex-x)/2 && Ey != Ey-(Ey-y)/2)
          			BD_Changer(Ry,Rx,Ey-(Ey-y)/2,Ex-(Ex-x)/2,Ey,Ex);
        		break;
      		}
    	}
    	if(cnt_0 != 0 && cnt_1 != 0)
      		break;
  	}
  	if(cnt_0 == 0)
    	Result_Bitmap[0].push_back('1');
  	else if(cnt_1 == 0)
    	Result_Bitmap[0].push_back('0');
}

void DB_Changer(int Ry,int Rx,int y,int x,int Ey,int Ex){
  	char temp;
  	input_fp >> temp;
  	if(temp == 'D'){
    	DB_Changer(Ry,Rx,y,x,Ey-(Ey-y)/2,Ex-(Ex-x)/2);
    	if(Ex != Ex-(Ex-x)/2)
    		DB_Changer(Ry,Rx,y,Ex-(Ex-x)/2,Ey-(Ey-y)/2,Ex);
    	if(Ey != Ey-(Ey-y)/2)
      		DB_Changer(Ry,Rx,Ey-(Ey-y)/2,x,Ey,Ex-(Ex-x)/2);
    	if(Ex != Ex-(Ex-x)/2 && Ey != Ey-(Ey-y)/2)
      		DB_Changer(Ry,Rx,Ey-(Ey-y)/2,Ex-(Ex-x)/2,Ey,Ex);
  	}
	else if(temp == '0' || temp == '1'){
    	for(int i=y;i<Ey;i++){
      		for(int j=x;j<Ex;j++){
        		Result_Bitmap[i].push_back(temp);
      		}
    	}
  	}
}

void Change_Bitmap(char stat, int y, int x){
  	if(stat == 'B'){
    	char temp;
    	for(int i=0 ; i<y ; i++){
      		for(int j=0; j<x ; j++){
        		input_fp >> temp;
        		Bitmap[i].push_back(temp);
      		}
    	}
    	BD_Changer(y,x,0,0,y,x);
  	}
  	else if(stat == 'D'){
    	DB_Changer(y,x,0,0,y,x);
  	}
}

void Print_Bitmap(char stat,int y,int x){
	if(stat == 'D'){
    	int cnt=0;
      	output_fp << "B " << y << " " << x << endl;
      	for(int i=0;i<y;i++){
        	for(int j=0;j<Result_Bitmap[i].size();j++){
        		if(cnt != 0 && cnt%50 == 0)
          			output_fp << endl;
        		output_fp << Result_Bitmap[i][j];
        		cnt++;
        	}
      	}
    }
    //B -> D 출력
    else if(stat == 'B'){
      	output_fp << "D " << y << " " << x << endl;
      	int i = 0;
      	for(;;){
        	if(i == Result_Bitmap[0].size())
          		break;
        	if(i != 0 && i%50 == 0 && Result_Bitmap[0].size() != i/50*50)
          		output_fp << endl;
        		output_fp << Result_Bitmap[0][i++];
      	}
    }
    output_fp << endl;
}

int main() {
  	for(;;){
    	char stat;
    	int y, x;
    	input_fp >> stat;
    	if(stat == '#')
    		break;
    	input_fp >> y >> x;
    	Change_Bitmap(stat,y,x);
    	Print_Bitmap(stat,y,x);
    //D -> B 출력
    	
    	for(int i=0;i<y;i++){
      		Bitmap[i].clear();
      		Result_Bitmap[i].clear();
    	}	
  	}
  	return 0;
}
