#include <wiringPi.h>
const int LedRed[8]={4,17,18,27,22,23,24,25};
const int Keypad[3]={16,13,12};

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
	for(i=0; i<8; i++){
		if(i==keypadnum)
			digitalWrite(LedRed[i], HIGH);
		else
			digitalWrite(LedRed[i], LOW);
	}

}

int main(void){
	int i, keypadnum=-1;
	if(wiringPiSetupGpio()==-1)
		return 1;
	for(i=0; i<8; i++){
		pinMode(LedRed[i], OUTPUT);
		digitalWrite(LedRed[i], LOW);
	}
	for(i=0; i<3; i++)
		pinMode(Keypad[i], INPUT);

	while(1){
		keypadnum=KeypadRead();
		if(keypadnum==0){
			while(1){
				int flag=0;
				if(keypadnum==2)break;
				for(i=0; i<8; i++){
					keypadnum=KeypadRead();
					if(keypadnum==2){
						flag=1;
						break;
					}
					LedControl(i);
					delay(500);
				}
				digitalWrite(LedRed[i-1],LOW);
				if(flag)break;
			}
		}
		else if(keypadnum==1){
			while(1){
				int flag=0;
				for(i=7; i>=0; i--){
					keypadnum=KeypadRead();
					if(keypadnum==2){
						flag=1;
						break;
					}
					LedControl(i);
					delay(500);
				}
				digitalWrite(LedRed[i+1],LOW);
				if(flag)break;
			}
		}

	}
	return 0;

}
