#include <wiringPi.h>
#include <softPwm.h>

#define MOTOR_MT_N_PIN 17
#define MOTOR_MT_P_PIN 4

#define LEFT_ROTATE 1
#define RIGHT_ROTATE 2

void MotorStop(){
	softPwmWrite(MOTOR_MT_N_PIN, 0);
	softPwmWrite(MOTOR_MT_P_PIN, 0);
}

void MotorControl(int speed, int rotate){
	if(rotate==LEFT_ROTATE){
		digitalWrite(MOTOR_MT_P_PIN, LOW);
		softPwmWrite(MOTOR_MT_N_PIN, speed);
	}
	else if (rotate==RIGHT_ROTATE){
		digitalWrite(MOTOR_MT_N_PIN,LOW);
		softPwmWrite(MOTOR_MT_P_PIN,speed);
	}
}

int main(void){
	if(wiringPiSetupGpio()==-1)
		return -1;
	pinMode(MOTOR_MT_N_PIN, OUTPUT);
	pinMode(MOTOR_MT_P_PIN, OUTPUT);

	softPwmCreate(MOTOR_MT_N_PIN, 0, 128);
	softPwmCreate(MOTOR_MT_P_PIN, 0 ,128);
	int direct[8]={1,1,1,1,2,2,2,2};
	int speed[8]={25,50,75,100,100,75,50,25};
	int i=0;
	while(1){
		MotorControl(speed[i],direct[i]);
		delay(2000);
		MotorStop();
		delay(2000);
		i++;
		if(i>=8)
			i=0;
	}
	return 0;
}
