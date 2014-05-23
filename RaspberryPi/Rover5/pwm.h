#ifndef PWM_H
#define PWM_H

#define PWM_PORT  1 //// GPIO18
#define PORT1     2
#define PORT2     3
#define DUTYCYCLE 15
// encoder 1
#define INTERRUPTPIN 0 	// GPIO17
#define ENCODER1_A 14 	
#define ENCODER1_B 4 	// GPIO23 

// encoder 2
#define INTERRUPTPIN2 7 // GPIO4
#define ENCODER2_A 6 	//GPIO25
#define ENCODER2_B 5 	//GPIO24


class PWM{
public:
	PWM();
	
	int getTotalDistance1();
	int getTotalDistance2();
	void forward();
	void backward();
	void left();
	void right();
	void stop();
	void resetEncoder();
	
};

int setup();
void encoder1Interrupt();
void encoder2Interrupt();
int encoderValue(int encoder);

#endif