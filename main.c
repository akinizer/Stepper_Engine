#include<P32xxxx.h>
void initialvel(unsigned int khz){
	TRISB = 0; // PORT B as output port
	PORTB = 1; // Set RB0 to high
	PWM1_Init(khz);
}
void velocity(unsigned int khz){
	PWM1_Set_Duty(khz);
}
void latency(int seconds){
	Delay_ms(seconds*1000);	
}

bool enabled(int EN){
	return EN=1;
}
void turnleft(){
	latency(2);
	velocity(1.5);
	latency(2);
	PORTB.F0 = 1;
	velocity(4.5);
}

void turnright(){
	latency(2);
	velocity(1.5);
	latency(2);
	PORTB.F1 = 1;	
	velocity(4.5);	
}
void breaktime(){
	PORTB = 0; // or PORTB = 3 		
}

void run(){
	 
	initialvel(4500); //initial speed 4.5 khz
	 
	PORTA = 0x00010001;
	int EN = 1;
	int DIR;
	
	if(EN==1){
		do	 {
			int shft = PORTA;
			shft << 7;
			shft >> 7;
			
			if(shft == 0x1)
				turnright();
			}
			
			else if(shft == 0x0)
				turnleft();
			}
			
			latency(2);
			
			PORTA = PORTA >> 1;

		}while(PORTA!=0x0);
	
	}
	else {
		EN==0;
		breaktime();
	}
}

void main()
{
	run();
}