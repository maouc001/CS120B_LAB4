/*	Author: maouc001
 *      Partner(s) Name: 
 *	Lab Section: 022
 *	Assignment: Lab # 4  Exercise # 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, S01_release, S01_press, S10_release, S10_press} state;

void Tick() {

    // Transitions  
    switch (state) {
	
	case Start:       	// initial transition
		state = S01_release;
    		break;

	case S01_release:
		if ( PINA & 0x01 ) {
			state = S10_press; 
		} 		
		break;

	case S10_press:
		if ( !( PINA & 0x01 ) ) {
			state = S10_release;
		}
		break;

	case S10_release:
		if ( PINA & 0x01 ) {
			state = S01_press;
		}
		break;

	case S01_press:
		if ( !( PINA & 0x01 ) ) {
			state = S01_release;
		}
		break;
	
	default:
		state = S01_release ;	
		break;
    }

    // State actions  
    switch (state) {
	
	case S01_release:
		PORTB = 0x01;	// LED-1 = 0 , LED-0 = 1
		break;

	case S10_press:
		PORTB = 0x02;	// LED-1 = 1 , LED-0 = 0 
		break;

	case S10_release:
		PORTB = 0x02;	// LED-1 = 1 , LED-0 = 0
		break;

	case S01_press:
		PORTB = 0x01;	// LED-1 = 0 , LED-0 = 1
		break;
	
	default:
		printf("Not Valid Case");
		break;
    }   
}

int main(void) {

    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;  // configure port A's 8 pins as inputs 
    DDRB = 0xFF; PORTB = 0x00;  // configure port B's 8 pins as inputs

    /* initialise the start state */
    PORTB = 0x00; 
     
    while (1) {
	
	Tick() ; 
    }
    return 1;
}
