#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

ifstream input_fp("fibonacci.inp");   
ofstream output_fp("fibonacci.out");

typedef struct Matrix{
	unsigned long long num[2][2];
}matrix;


matrix f;

matrix mux(matrix a, matrix b, int M){
	matrix ret;
	ret.num[0][0] = ((a.num[0][0]%M*b.num[0][0]%M)%M + (a.num[0][1]%M*b.num[1][0]%M)%M)%M;
	ret.num[0][1] = ((a.num[0][0]%M*b.num[0][1]%M)%M + (a.num[0][1]%M*b.num[1][1]%M)%M)%M;
	ret.num[1][0] = ((a.num[1][0]%M*b.num[0][0]%M)%M + (a.num[1][1]%M*b.num[1][0]%M)%M)%M;
	ret.num[1][1] = ((a.num[1][0]%M*b.num[0][1]%M)%M + (a.num[1][1]%M*b.num[1][1]%M)%M)%M;
	return ret;
}

matrix fibonacci(unsigned long long n, int M){
	matrix ret = f;
	if(n > 1){
		ret = fibonacci(n/2,M);
		ret = mux(ret,ret,M);
		if(n%2 == 1){
			ret = mux(ret,f,M);
		}
	}
	return ret;
}

void input_and_solve(){
	unsigned long long a,b,c,d,M;
	unsigned long long temp1, temp2;
	unsigned long long result;
	input_fp >> a >> b >> c >> d >> M;
	matrix ma = fibonacci(a,M);
	matrix mb = fibonacci(b,M);
	matrix mc = fibonacci(c,M);
	matrix md = fibonacci(d,M);
	a = ma.num[0][1];
	b = mb.num[0][1];
	c = mc.num[0][1];
	d = md.num[0][1];
	temp1 = (a*b)%M;
	temp2 = (c*d)%M;
	result = (temp1 + temp2)%M;
	output_fp << result << endl;
}

int main(){
	int Test_Case;
	input_fp >> Test_Case;
	f.num[0][0] = 1;
	f.num[0][1] = 1;
	f.num[1][0] = 1;
	f.num[1][1] = 0;
	for(int i=0; i<Test_Case; i++){
		input_and_solve();
	}
}
