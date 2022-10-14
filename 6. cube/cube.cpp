#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream input_fp("cube.inp");   
ofstream output_fp("cube.out");
vector<char> cube;

bool IsSame(){
	bool ret = true;
	for(int i=0; i<6; i++){
		if(cube[i] != cube[i+6]){
    		ret = false;
    		break;
    	}
  	}
  	return ret;
}

void turn_cube(){           // ÁÂ·Î È¸Àü 90µµ
  	int temp;
  	temp = cube[1];
  	cube[1] = cube[2];
  	cube[2] = cube[4];
  	cube[4] = cube[3];
  	cube[3] = temp;
}

void spin_side_cube(){
  	int temp;
  	temp = cube[0];
  	cube[0] = cube[3];
  	cube[3] = cube[5];
  	cube[5] = cube[2];
  	cube[2] = temp;
}

void spin_front_cube(){
  	int temp;
  	temp = cube[0];
  	cube[0] = cube[4];
  	cube[4] = cube[5];
  	cube[5] = cube[1];
  	cube[1] = temp;
}

int main(){
	for(;;){
		char temp;
    	for(int i=0;i<12;i++){
    		input_fp >> temp;
    		cube.push_back(temp);
    	}
    	int Break_check = 0;
    	for(int i=0;i<11;i++){
    	  	if(cube[i] == cube[i+1])
    		    Break_check++;
    	}
    	if(Break_check == 11){
    		output_fp << "TRUE" << endl;
    		break;
    	}
		else{
			bool result = false;
    		for(int i=0;i<6;i++){
				if (i < 4)
    	    		spin_front_cube();
    	    	else if (i == 4)
    	    		spin_side_cube();
    	    	else{
    	    		spin_front_cube();
    	    		spin_front_cube();
    	    	}
    	    	if(cube[0] == cube[6] && cube[5] == cube[11]){
    	     		for(int j=0;j<4;j++){
    	    	   		turn_cube();
    	    	   		result = IsSame();
    	       			if(result)
    	       				break;
    	     		}
    	    	}
    	    	if(result)
    	    		break;
    	  	}
    	  	if(result)
    	    	output_fp << "TRUE" << endl;
    	  	else
    	    	output_fp << "FALSE" << endl;
    	  	cube.clear();
    	}
  	}
}	
		
