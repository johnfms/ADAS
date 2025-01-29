/*
 * leds.h
 *
 * Created: 2/9/2024 3:42:36 AM
 *  Author: john
 */ 


#ifndef LEDS_H_
#define LEDS_H_

#define LED_PORT PORTB
#define LED_DDR  DDRB
#define LED_RED PB4
#define LED_YELLOW_LEFT PB5
#define LED_YELLOW_RIGHT PB6
#define LED_GREEN PB7
#define buzzer PB2
void init_leds() {
	LED_DDR |= (1 << LED_RED) | (1 << LED_YELLOW_LEFT) | (1 << LED_YELLOW_RIGHT) | (1 << LED_GREEN) | (1 << buzzer);
	LED_PORT &= ~((1 << LED_RED) | (1 << LED_YELLOW_LEFT) | (1 << LED_YELLOW_RIGHT) | (1 << LED_GREEN) | (1 << buzzer));
}

void update_leds(CarMode current_mode) {
	LED_PORT &= ~((1 << LED_RED) | (1 << LED_YELLOW_LEFT) | (1 << LED_YELLOW_RIGHT) | (1 << LED_GREEN) | (1 << buzzer));
	switch(current_mode) {
		case forward:
		LED_PORT |= (1 << LED_GREEN);
		break;
		case turn_left:
		LED_PORT |= (1 << LED_YELLOW_LEFT);
		break;
		case turn_right:
		LED_PORT |= (1 << LED_YELLOW_RIGHT);
		break;
		case stopped:
		LED_PORT |= (1 << LED_RED);
		LED_PORT |= (1 << buzzer);

		break;
	}
}

#endif /* LEDS_H_ */