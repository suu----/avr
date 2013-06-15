/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
	int a=0;
    
	DDRD |= 1 << 5;
    DDRD |= 1 << 6;

    //タイマ0,PWM,コンベアマッチでHigh
	TCCR0A = 0b11110011;
	TCCR0B = 0b00001001;
    
    OCR0A = 255;
    OCR0B = 128;

	//割り込み許可
	sei();
	
	while(1){
        
        if (a==25000) {
            a=0;
        }
        OCR0A = a/100 ;
        a++;
	}
}

