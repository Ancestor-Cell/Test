#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<ctime>
using namespace std;

double random(){
	return 2.0*(double)rand()/RAND_MAX-1;
}
#define random random()

struct Node{
	double ans;
	double deri;
	double *wght;
};

struct Floor{
	Node *floor;
	Node dfrt;
};

struct Brain{
	double *qst;
	Floor *hide_floor;
	Floor output_floor;
	int floornum,innum,outnum,hidenum;
	Brain(int floorsize,int insize,int outsize,int hidesize){
		floornum=floorsize;
		innum=insize;
		outnum=outsize;
		hidenum=hidesize;
		hide_floor=new Floor[floorsize];		//创建隐藏层 
		qst=new double[insize];					//创建输入层 
		output_floor->floor=new Node[outsize];	//创建输出层 
		for(int i=1;i<floorsize;++i){
			hide_floor[i]->floor=new Node[hidesize];	//具象化隐藏层 
			for(int j=1;j<hidesize;++j){
				hide_floor[i]->floor[j]->wght=new double[hidesize];
		}
int main(){
	srand(time(NULL));
}
