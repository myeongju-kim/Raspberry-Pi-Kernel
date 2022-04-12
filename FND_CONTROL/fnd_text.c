
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>

const int FndSelectPin[6]={4,17,18,27,22,23};
const FndPin[8]={6,12,13,16,19,20,26,21};
const int FndFont[5]={0x3F,0x38,0x38,0x79,0x76};

void Init(int num){

	int i;
	if(wiringPiSetupGpio()==-1){
		printf("wiringPiSetupGpio() error\n");
		exit(-1);
	}
	for (i=0; i<6; i++){
		if(i==num)
			continue;
		pinMode(FndSelectPin[i], OUTPUT);
		digitalWrite(FndSelectPin[i], HIGH);
	}
	for (i=0; i<8; i++){
		pinMode(FndPin[i], OUTPUT);
		digitalWrite(FndPin[i], LOW);
	}
}
void FndSelect(int position){
	int i;
	for(i=0; i<6; i++){
		if(i==position)
			digitalWrite(FndSelectPin[i], LOW);
		else
			digitalWrite(FndSelectPin[i], HIGH);
	}

}
void FndDisplay(int position, int num){
	int i,j;
	int flag=0;
	int shift=0x01;
	for(i=0; i<8; i++){
		flag=(FndFont[num] & shift);
		digitalWrite(FndPin[i], flag);
		shift<<=1;
	}
	FndSelect(position);
}

int main(){
	int data[5]={0,1,2,3,4};
	int open[6]={0,1,2,3,4,5};
	while(1){
		int pos;
		Init(open[5]);
		clock_t t1, t2;
		t1=clock();
		while(1){
			t2=clock();
			for(pos=0; pos<5; pos++){
				FndDisplay(open[pos], data[pos]);
				delay(1);
			}
			if((double)(t2-t1)/1000>0.5)
				break;
		}
		int temp=open[0];
		for(pos=0; pos<5; pos++)
			open[pos]=open[pos+1];
		open[5]=temp;
	}
	return 0;

}
