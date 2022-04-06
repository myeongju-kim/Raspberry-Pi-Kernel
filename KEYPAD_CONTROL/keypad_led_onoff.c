#include <wiringPi.h>
#include <unistd.h>

const int LedRed[8]={4,17,18,27,22,23,24,25};
const int Keypad[8]={16,13,12,6,21,26,20,19};
int Sign[8]={1,1,1,1,1,1,1,1};
int KeypadRead(){
	int i, keypadnum=-1;
	for(i=0; i<8; i++){
		if(!digitalRead(Keypad[i])){
			keypadnum=i;
			break;
		}
	}
	return keypadnum;
}

void LedControl(int keypadnum){
	int i;
	unsigned long last=0;
	unsigned long cur=millis();
	if(cur-last>200){
		digitalWrite(LedRed[keypadnum], Sign[keypadnum]);
		Sign[keypadnum]=!Sign[keypadnum];
	}
	last=cur;
}

int main(void){
	int i, keypadnum=-1;
	if(wiringPiSetupGpio()==-1)
		return 1;
	for(i=0; i<8; i++){
		pinMode(LedRed[i], OUTPUT);
		digitalWrite(LedRed[i], LOW);
	}
	for(i=0; i<8; i++)
		pinMode(Keypad[i], INPUT);
	while(1){
		keypadnum=KeypadRead();
		LedControl(keypadnum);
	}
	return 0;

}
