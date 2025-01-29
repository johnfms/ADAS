/*
 * ADAS.c
 * Authors : johnfms
 */

#define F_CPU 8000000UL

//==--libraries--==
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.h"
#include "ultrasonic.h"
#include "Hbridge.h"
#include "ir.h"
//==--defines--==
#define MIN_DISTANCE 10
#define MAX_DISTANCE 50
typedef enum {
	forward,
	turn_left,
	turn_right,
	stopped
} CarMode;
volatile CarMode mode = forward;
#include "leds.h"

//==--functions--==
uint8_t calc_speed(uint16_t distance) {
	if (distance <= MIN_DISTANCE) {
			return 0;  // Stop if too close
		} else if (distance >= MAX_DISTANCE) {
			return 255;  // Full speed if far away
		} else {
		// Linear equation: speed = m * distance + b
			return (uint8_t)((distance - MIN_DISTANCE) * 255 / (MAX_DISTANCE - MIN_DISTANCE));
		}
}
void update_display(uint16_t distance, uint8_t speed, const char* mode_str) {
	char buffer[17];
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	snprintf(buffer, sizeof(buffer), "D:%3u S:%3u", distance, speed);
	lcd_str(buffer);
	lcd_cmd(0xC0);
	lcd_str(mode_str);
}

//==--Start Main--==
int main(void) {
	lcd_init();
	ultrasonic_init();
	hbridge_init();
	ir_init();
	init_leds();
	char buffer[16];
	uint16_t distance;
	uint8_t speed;
	IRState irstate;
	lcd_cmd(0x80);
	lcd_str("    ADAS Car    ");
	lcd_cmd(0xC0);
	lcd_str("==--john fms--==");
	_delay_ms(50);
	
	while (1) {
		distance = measure_distance();
		speed = calc_speed(distance);
		irstate=get_ir_state();
		if (speed==0){
			mode=stopped;
		}else{
			switch (irstate) {
				case IR_LEFT_DETECTED:
				mode = turn_right;
				break;
				case IR_RIGHT_DETECTED:
				mode = turn_left;
				break;
				case IR_CLEAR:
				mode = forward;
				break;
			}
		}
		switch (mode) {
			case forward:
				set_motor_speed(speed, speed);
				move_forward();
				update_display(distance, speed, "Moving Forward");
				break;
			case turn_left:
				set_motor_speed(speed/2, speed);
				move_left();
				update_display(distance, speed, "Turning Left");
				 break;
			case turn_right:
				set_motor_speed(speed, speed/2);
				move_right();
				update_display(distance, speed, "Turning Right");
				break;
			case stopped:
				stop_motors();
			    update_display(distance, speed, "Emergency Stop");
				break;
		}
		update_leds(mode);
		_delay_ms(5);
	}
}