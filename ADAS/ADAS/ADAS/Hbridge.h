#ifndef HBRIDGE_H_
#define HBRIDGE_H_
#define IN1 PB0
#define IN2 PD4
#define IN3 PD5
#define IN4 PD6
#define ENA PB3 // PWM pin for left motor (OC0)
#define ENB PD7 // PWM pin for right motor (OC2)

void hbridge_init(){
	DDRB|=(1<<ENA)|(1<<IN1);
	DDRD|=(1<<ENB)|(1<<IN4)|(1<<IN3)|(1<<IN2);
	TCCR0|=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS01);//fast pwm - not inverting - prescaler 8 (timer 0)
	TCCR2|=(1<<WGM20)|(1<<WGM21)|(1<<COM21)|(1<<CS21);//fast pwm - not inverting - prescaler 8 (timer 2)
	PORTB |= (1 << ENA);// Enable PWM outputs
	PORTD |= (1 << ENB);
}
void set_motor_speed(uint8_t left_speed,uint8_t right_speed) {
	OCR0 = left_speed;  //left motor speed
	OCR2 = right_speed;  //right motor speed
}
void move_forward() {
	PORTB |= (1 << IN1);
	PORTD |= (1 << IN3);
	PORTD &=~(1 << IN2);
	PORTD &=~(1 << IN4);
}
void move_right() {
	PORTB |= (1 << IN1);
	PORTD &=~(1 << IN2);
	PORTD &=~(1 << IN3);
	PORTD &=~(1 << IN4);
	
}
void move_left() {
	PORTD |= (1 << IN3);
	PORTB &=~(1 << IN1);
	PORTD &=~(1 << IN2);
	PORTD &=~(1 << IN4);
}
void stop_motors() {
		PORTB &= ~(1 << IN1);  // Disable left motor
		PORTD &= ~(1 << IN3);  // Disable right motor
		PORTD &= ~(1 << IN2);  // Clear all direction pins
		PORTD &= ~(1 << IN4);
		set_motor_speed(0,0);    // Set speed to 0 (not necessary when motors are disabled, but good practice)
}

#endif /* HBRIDGE_H_ */