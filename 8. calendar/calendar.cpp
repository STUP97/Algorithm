#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

ifstream input_fp("calendar.inp");   
ofstream output_fp("calendar.out");

string DotW1, DotW2;
int state;
int begin_Y, begin_M, begin_D, end_Y, end_M, end_D;
int Week1, Week2;
string week_of_the_day[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

void input_data(){
	char temp;
	switch(state){
		case 0:	
			input_fp >> begin_Y >> temp >> begin_M >> temp >> begin_D >> end_Y >> temp >> end_M >> temp >> end_D;
//			cout << begin_Y << temp << begin_M << temp << begin_D << temp  << temp  << end_Y << temp << end_M << temp << end_D << endl;
			break;
		case 1:
			input_fp >> begin_Y >> temp >> begin_M >> temp >> begin_D >> end_Y >> temp >> end_M >> temp >> end_D >> temp >> DotW2;
			for(int i=0; i<7; i++){
				if(week_of_the_day[i].compare(DotW2) == 0){
					Week2 = i;
					break;
				}
			}			
			break;
		case 2:
			input_fp >> begin_Y >> temp >> begin_M >> temp >> begin_D >> temp >> DotW1 >> end_Y >> temp >> end_M >> temp >> end_D;
			for(int i=0; i<7; i++){
				if(week_of_the_day[i].compare(DotW1) == 0){
					Week1 = i;
					break;
				}
			}
			break;
		case 3:
			input_fp >> begin_Y >> temp >> begin_M >> temp >> begin_D >> temp >> DotW1 >> end_Y >> temp >> end_M >> temp >> end_D >> temp >> DotW2;
			for(int i=0; i<7; i++){
				if(week_of_the_day[i].compare(DotW1) == 0){
					Week1 = i;
					break;
				}
			}
			for(int i=0; i<7; i++){
				if(week_of_the_day[i].compare(DotW2) == 0){
					Week2 = i;
					break;
				}
			}
			break;
	}
}

void Zeller(int Y, int M, int D, int DotW, int mod){
	int W,a,b,c,d;
	if(M == 1 || M == 2){
		Y -= 1;
		M += 12;
	}
	// @@YY MM DD
	a = Y/100;
	// YY@@ MM DD
	b = Y%100;
	// YYYY @@ DD
	c = M;
	// YYYY MM @@
	d = -6+D*7;
	
	int tmp1 = 21*a/4;
	int tmp2 = 5*b/4;
	int tmp3 = 26*(c+1)/10;
	W = tmp1 + tmp2 + tmp3 + d-1;
	W = W%7;
	
	if(W <= DotW){
		d += DotW-W;
	}
	else if(W > DotW){
		d += 7+DotW-W;
	}
	if(mod == 2)
		end_D = d;
	else
		begin_D = d;
}

void find_YMD(){
	switch(state){
		case 3:
		case 1:
			Zeller(end_Y, end_M, end_D, Week2,2);
			if(state == 1)
				break;
		case 2:
			Zeller(begin_Y, begin_M, begin_D, Week1,1);
	}
//	cout << begin_Y << "-" << begin_M << "-" << begin_D << "    "  << end_Y << "-" << end_M << "-" << end_D << endl;
} 

bool date_validation(int y, int m, int d){
	// 홀수 달 
	if(m%2 == 1){
		if(m < 9){
			if(d > 31){
				return false;
			}
		}
		else{
			if(d > 30){
				return false;
			}
		}
	}
	// 짝수 달
	else{
		// 2,4,6 월 
		if(m < 8){
			if(m == 2){
				// 윤년 
				if((y%4 == 0 && y%100 != 0) || y%400 == 0) {
					if(d > 29)
						return false;
				}
				else if(d > 28) 
					return false;
			}
			else if(d > 30)
				return false;
		}
		// 8, 10, 12 월 
		else
			if(d > 31)
				return false;
	} 
	return true;
}

bool check_date(){
	if(!date_validation(begin_Y, begin_M, begin_D)){
		return false;
	}
	if(!date_validation(end_Y, end_M, end_D)){
		return false;
	}
	return true;
}
/* 
제라의 공식을 이용하여 요일로 주어진 데이터를 연월일 형식으로 바꾼다.  OK 
입력받은 연월일이 실제로 존재하는지 확인한다.  
검증된 연월일 데이터 간의 차이를 구한다. 
*/

int calc_date(int y, int m, int d){
	// 년 
	int days = (y-1)*365 + (y-1)/4 - (y-1)/100 + (y-1)/400;
	// 월
	int month[] = {31,28,31,30,31,30,31,31,30,31,30,31};
	if(m > 2){
		if((y%4 == 0 && y%100 != 0) || y%400 == 0){
			days += 1;
		}
	}
	for(int i=0; i<m-1; i++){
		days += month[i];
	}
//	cout << days << endl;
	// 일
	days += d;
	return days;
}

int calc_date_gab(){
	int begin_days = calc_date(begin_Y, begin_M, begin_D);
	int end_days = calc_date(end_Y, end_M, end_D);
//	cout << begin_days << " " << end_days << endl;
	int ret;
	if(begin_days > end_days){
		ret = begin_days - end_days;
	}
	else{
		ret = end_days - begin_days;
	}
	return ret;
} 

void print_data(bool availability){
	if(availability){
		int result = calc_date_gab();
		output_fp << result << endl;
	}
	else{
		output_fp << "-1" << endl;
	}
}

int main(){
	bool availability;
	for(;;){
		input_fp >> state;
		if(state == -1){
			break;
		} 
		input_data();	
		// 요일 입력타입 연월일로 변환 
		find_YMD();
		// 날짜 유효성 검사 
		availability = check_date();
		// 출력 
		print_data(availability);
	}
}	
	
