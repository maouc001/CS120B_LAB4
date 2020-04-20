/*      Author: maouc001
 *      Partner(s) Name:
 *      Lab Section: 022
 *      Assignment: Lab # 4  Exercise # 2
 *      Exercise Description: [optional - include for your own benefit]
 *      I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Init, Decrement, DecrementWait, Increment, IncrementWait, S9, S0} state;
unsigned char cnt;	// holds the count 

void Tick() {
   switch (state) {

        case Start:             // initial transition
                state = Init ;
                break;

	case Init: 
		if ( !(PINA & 0x02) && (PINA & 0x01) ) {
			cnt ++;
			state = Increment ;
		} else if ( (PINA & 0x02) && !(PINA & 0x01) ) {
			cnt -- ;
			state = Decrement ;
		} else if ( (PINA & 0x02) && (PINA & 0x01) ) {
			state = S0 ;
		} else {
			state = Init ;
		}
		break;

        case Decrement:
                if ( (PINA & 0x02) && (PINA & 0x01) )  {
                        state = S0 ;
                } else if ( !(PINA & 0x02) ) {
			state = DecrementWait ;
		} else {
			state = Decrement ;
		}
                break;

        case DecrementWait:
                if ( (PINA & 0x02) && (cnt == 1) ) {
                        state = S0 ;
                } else if ( PINA & 0x01) {
			cnt ++ ;
			state = Increment ;
		} else if ( (PINA & 0x02) && (cnt > 1)) {
			cnt -- ;
			state = Decrement ;
		} else {
			state = DecrementWait ;
		} 
                break;

        case Increment:
                if ( (PINA & 0x02) && (PINA & 0x01) ) {
                        state = S0 ;
                } else if ( !(PINA & 0x01) ) {
			state = IncrementWait ; 
		} else {
			state = Increment ; 
		}
                break;

        case IncrementWait:
                if ( (PINA & 0x01) && (cnt < 8) ) {
			cnt ++ ; 
                        state = Increment ;
                } else if ( (PINA & 0x01) && (cnt == 8) ) {
			state = S9 ;
		} else if ( (PINA & 0x02) ) {
			cnt -- ;
			state = Decrement ; 
		} else {
			state = IncrementWait ;
		}
                break;
	
	case S9:
		if ( (PINA & 0x02) && (PINA & 0x01) ) {
			state = S0 ; 
		} else if ( (PINA & 0x02) && !(PINA & 0x01) ) {
			cnt-- ;
			state = Decrement ;
		} else {
			state = S9 ;
		}		
		break;
	
	case S0 :
		if ( (PINA & 0x01) &&  !(PINA & 0x02) ) {
			cnt ++ ;
			state = Increment ;
		} else {
			state = S0;
		}

        default:
                state = Start ;
                break;
    }

    // State actions
    switch (state) {

        case Init:
                cnt = 7 ;
                break;
	
	case S9:
		cnt = 9 ;
		break;
	
	case S0:
		cnt = 0 ;
		break;
	
	default: 
		cnt = cnt;
		break;
    }
}

int main(void) {

    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;  // configure port A's 8 pins as inputs
    DDRC = 0xFF; PORTC = 0x00;  // configure port C's 8 pins as outputs

    /* initialise the start state */
    PORTC = 0x00;
    cnt = 0;

    while (1) {

        Tick() ;
	PORTC = cnt;
    }
    return 1;
} 
