#include <wiringPi.h>
#include <softPwm.h>
#define LED_ON 1
#define LED_OFF 0

const int Led=4;

int main(void){
	int i;
	if(wiringPiSetupGpio()==-1) 
		return 1;
	pinMode(Led,OUTPUT);
	digitalWrite(Led,LED_OFF);
	softPwmCreate(Led,0,128);
	while(1){
		digitalWrite(Led,LED_ON);
		for(i=0; i<=100; i++){
			softPwmWrite(Led,i);
			delay(30);
		}
		for(i=100; i>=0; i--){
			softPwmWrite(Led,i);
			delay(30);
		}
	}
	return 0;
}

