#include <avr/delay.h>
#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#define TRIG_PIN PC3
#define ECHO_PIN PC4

void ultrasonic_init() {
	DDRC |= (1 << TRIG_PIN);  // TRIG output
	DDRC &= ~(1 << ECHO_PIN); // ECHO input
}

uint16_t measure_distance() {
	PORTC |= (1 << TRIG_PIN);	// start pulse
	_delay_us(10);				// 10 us to trig
	PORTC &= ~(1 << TRIG_PIN);// end pulse 

	// waiting echo to get high
	while (!(PINC & (1 << ECHO_PIN)));
	TCNT1 = 0; // reset timer
	TCCR1B |= (1 << CS11); //start timer by pre scaler 8 to make it 1Hz
	while (PINC & (1 << ECHO_PIN));// wait echo to finish pulse
	TCCR1B = 0; // stop timer
	// calculate the distance
	uint16_t count = TCNT1; //time
	uint16_t distance = (count * 0.0343) / 2; //time /2 to get the distance v=d/t d=v*t
	distance++;
	return distance;
}
#endif /* ULTRASONIC_H_ */