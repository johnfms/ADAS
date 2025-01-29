#ifndef IR_H_
#define IR_H_
#define ir_right PD3
#define ir_left PD2
#include <avr/io.h>
#include <avr/interrupt.h>
typedef enum {
	IR_CLEAR,
	IR_LEFT_DETECTED,
	IR_RIGHT_DETECTED
} IRState;
volatile IRState current_ir_state = IR_CLEAR;

void ir_init(){
		DDRD &=~(1<<ir_right);
		DDRD &=~(1<<ir_left);
		PORTD |= (1 << ir_right) | (1 << ir_left);
		MCUCR |= (1 << ISC01) | (1 << ISC00);  // INT0 triggers on rising edge
	    MCUCR |= (1 << ISC11) | (1 << ISC10);  // INT1 triggers on rising edge
		GICR |= (1 << INT0) | (1 << INT1);// Enable INT0 and INT1 interrupts
		sei();// Enable global interrupts
}
ISR(INT0_vect) {
	current_ir_state = IR_RIGHT_DETECTED;
}

// INT1 ISR (Right sensor)
ISR(INT1_vect) {
	current_ir_state = IR_LEFT_DETECTED;
}

IRState get_ir_state() {
	 if ((PIND & (1 << ir_left))) {
		 		 return IR_RIGHT_DETECTED;

		 } else if ((PIND & (1 << ir_right))) {
			 		 return IR_LEFT_DETECTED;

		 } else {
		 return IR_CLEAR;
	 }
}


#endif /* IR_H_ */