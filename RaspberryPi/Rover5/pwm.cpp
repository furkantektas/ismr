#include "pwm.h"

#include <iostream>
#include <time.h>
#include <wiringPi.h>
#include <softPwm.h>

using namespace std;

int encoderLookupTable[4][4] =	{
									0,-1, 1, 0,
						 			1, 0, 0,-1,
						 			-1,0, 0, 1,
						 			0, 1, -1,0
						 		};

	/* the data from taken from encoder1 pins */
	int lastIntrValue1=0;
	int totalDistance1=0;

	/* the data from taken from encoder2 pins */
	int lastIntrValue2=0;
	int totalDistance2=0;

int PWM::getTotalDistance1(){
	return totalDistance1;
}


int PWM::getTotalDistance2(){
	return totalDistance2;
}

PWM::PWM(){
	setup();
}

void PWM::resetEncoder(){
	/* the data from taken from encoder1 pins */
	lastIntrValue1 = 0;
	totalDistance1 = 0;

	/* the data from taken from encoder2 pins */
	lastIntrValue2 = 0;
	totalDistance2 = 0;
}

int setup(){
	wiringPiSetup () ;

	softPwmCreate(PWM_PORT,0,100);
	pinMode(PORT1, OUTPUT);
	pinMode(PORT2, OUTPUT);
	pinMode(ENCODER1_A, INPUT);
	pinMode(ENCODER1_B, INPUT);
	pinMode(ENCODER2_A, INPUT);
	pinMode(ENCODER2_B, INPUT);

	
	lastIntrValue1 = encoderValue(1);
	lastIntrValue2 = encoderValue(2);
	


	// set Pin 17/0 generate an interrupt on high-to-low transitions
  	// and attach encoder1Interrupt() to the interrupt
  	if ( wiringPiISR(INTERRUPTPIN, INT_EDGE_BOTH,&encoder1Interrupt )< 0 ){
        cout<<"error on interrupt 1"<<endl;
        return 1;
    }

    if(wiringPiISR(INTERRUPTPIN2, INT_EDGE_BOTH,&encoder2Interrupt) < 0 ){
    	cout<<"error on interrupt 2"<<endl;
    	return 1;
    }
}

int encoderValue(int encoder){
	switch(encoder)
	{
		case 1:
			return  digitalRead(ENCODER1_A)*2+digitalRead(ENCODER1_B);
		case 2:
			return  digitalRead(ENCODER2_A)*2+digitalRead(ENCODER2_B);
	}
	return 0;
}

void encoder1Interrupt(){
	int currentVal  = encoderValue(1) ;
 	totalDistance1 += encoderLookupTable[lastIntrValue1][currentVal];
 	//cout<<"1 => \n"<<digitalRead(ENCODER1_A)<<" "<<digitalRead(ENCODER1_B)<<" "<<totalDistance1<<endl;
 	
 	lastIntrValue1 = currentVal;
}
void encoder2Interrupt(){
	int currentVal  = encoderValue(2) ;

 	totalDistance2 += encoderLookupTable[lastIntrValue2][currentVal];
 	//cout<<"2 => \n"<<digitalRead(ENCODER2_A)<<" "<<digitalRead(ENCODER2_B)<<" "<<totalDistance2<<endl;
 	lastIntrValue2 = currentVal;
}
void PWM::forward() {
	digitalWrite(PORT1,HIGH);
	digitalWrite(PORT2,HIGH);
	volatile int i;
	for(i=0;i<100;i++)
		;
	softPwmWrite(PWM_PORT,DUTYCYCLE);
}

void PWM::backward() {
	softPwmWrite(PWM_PORT,DUTYCYCLE);
	digitalWrite(PORT1,LOW);
	digitalWrite(PORT2,LOW);
}

void PWM::left() {
	digitalWrite(PORT1,LOW);
	digitalWrite(PORT2,HIGH);
	softPwmWrite(PWM_PORT,DUTYCYCLE);
}

void PWM::right() {
	digitalWrite(PORT1,HIGH);
	digitalWrite(PORT2,LOW);
	softPwmWrite(PWM_PORT,DUTYCYCLE);
}

void PWM::stop() {
	softPwmWrite(PWM_PORT,0);
	digitalWrite(PORT1,LOW);
	digitalWrite(PORT2,LOW);
}