#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

ifstream input_fp("queue.inp");
ofstream output_fp("queue.out");


typedef struct ListNode {
	int num;
	struct ListNode *llink;
	struct ListNode *rlink;
}listNode;

listNode *Tree;				// Æ®¸® 

void insert_Tree(int num){
	listNode *newNode, *p;
	newNode = (listNode *)malloc(sizeof(listNode));
	newNode->num = num;
	newNode->llink = NULL;
	newNode->rlink = NULL;
	if(Tree == NULL){
		Tree = (listNode *)malloc(sizeof(listNode));
		Tree->rlink = newNode;
	}
	else{
		p = Tree->rlink;
		for(;;){
			if((p->num > num) && (p->rlink == NULL)){
				p->rlink = newNode;
				break;
			}
			else if((p->num < num) && (p->llink == NULL)){
				p->llink = newNode;
				break;
			}
			else if((p->num > num) && (p->rlink != NULL)){
				p = p->rlink;
			}
			else if((p->num < num) && (p->llink != NULL)){
				p = p->llink;
			}
			else if(p->num == num)
				break;
		}
	}
}
void delete_root(int num){
	listNode *p;
	p = Tree->rlink;		// root
	if(p->llink == NULL && p->rlink == NULL){
		Tree->rlink = NULL;
	}
	else if(p->llink == NULL && p->rlink != NULL){
		
	}
	else if(p->llink != NULL && p->rlink == NULL){
		
	}
	else if(p->llink != NULL && p->rlink != NULL){
		
	}
	for(;;){
			if((p->num > num) && (p->rlink == NULL)){
				p->rlink = newNode;
				break;
			}
			else if((p->num < num) && (p->llink == NULL)){
				p->llink = newNode;
				break;
			}
			else if((p->num > num) && (p->rlink != NULL)){
				p = p->rlink;
			}
			else if((p->num < num) && (p->llink != NULL)){
				p = p->llink;
			}
			else if(p->num == num)
				break;
		}
	}
}
bool input_data(){
	int temp;
	input_fp >> temp;
	if(temp == 'q'){
		return true;
	}
	else if(temp == 'd'){
		
	}
	else if(temp == 'r'){
		
	}
	else{
		if(Tree == NULL){
			Tree = (listNode *)malloc(sizeof(listNode));
			Tree->rlink = newNode;
		}
		listNode *newNode;
		newNode = (listNode *)malloc(sizeof(listNode));
		newNode->num = temp;
		newNode->llink = NULL;
		newNode->rlink = NULL;
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
