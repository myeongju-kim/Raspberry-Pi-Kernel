
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>

const int FndSelectPin[6]={4,17,18,27,22,23};
const FndPin[8]={6,12,13,16,19,20,26,21};
const int FndFont[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x27,0x7F,0X67};
const int FndFont2[10]={0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0xA7,0xFF,0xE7};
void Init(){

	int i;
	if(wiringPiSetupGpio()==-1){
		printf("wiringPiSetupGpio() error\n");
		exit(-1);
	}
	for (i=0; i<6; i++){
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
		if(position==2)
			flag=(FndFont2[num] & shift);
		else
			flag=(FndFont[num] & shift);
		digitalWrite(FndPin[i], flag);
		shift<<=1;
	}
	FndSelect(position);
}

int main(){
	int g[6]={0,0,0,0,0,0};
	Init();
	while(1){
		int pos;
		clock_t t1, t2;
		t1=clock();
		int a=0;
		while(1){
			t2=clock();
			for(pos=0; pos<6; pos++){
				FndDisplay(pos,g[pos]);
				delay(1);
			}
			if((double)(t2-t1)/1000>0.01)
				break;
		}
		g[0]++;
		if(g[0]>=10){
			g[0]=0;
			g[1]++;
		}
		if(g[1]>=10){
			g[1]=0;
			g[2]++;
		}
		if(g[2]>=10){
			g[2]=0;
			g[3]++;
		}
		if(g[3]>=10){
			g[3]=0;
			g[4]++;
		}
		if(g[4]>=10){
			g[4]=0;
			g[5]++;
		}
		if(g[5]>=10)
			break;
	}
	return 0;

}
