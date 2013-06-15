
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


unsigned char i=0;

ISR(TIMER0_COMPA_vect)  //タイマ割り込み
{
	PORTB ^= 1 << 2;//ポートBを反転
}



int main(void)
{
	//タイマ0,CTC,割り込み用、比較A一致で割り込み
	TCCR0A = 0b00000001;
	TCCR0B = 0b00000100; // N=128
	//OCR0A = 255;
	TIMSK0 = 0b0000010;	//比較A一致割り込み有効
    
	//方向レジスタの設定
	DDRB  = 1 << 2; //B2を出力
	DDRD  = 1 << 5; //D5を出力
	PORTB = 1 << 2;
    PORTD = 1 << 5;
	
	//割り込み許可
	sei();
	
	while(1){
		;
	}
}

