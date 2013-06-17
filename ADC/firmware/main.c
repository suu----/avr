#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include <stdio.h>
#include"uart0.h"
#include"uart0.c"

void usart_init(void){
	UBRR0 = 6;


	UCSR0B = _BV(TXEN0) | _BV(RXEN0);

	//frame format
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
}
void usart_tx(char data){
	/* Wait for empty transmit buffer */
	while ((UCSR0A & _BV(UDRE0)) == 0 );
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

void rs_puts(char *st) //文字列を一文字ずつに変換して送信
{
	
	
	while (*st != '\0') {
		usart_tx(*st);
		st++;
		_delay_ms(10);
	}
}

int main()
{
	DDRD|=1<<6;	//PD6を出力に
	 usart_init();	//uart初期化
	int piyo = 100;
	char foo[64];
	
	//main loop
	for(;;)
	{
<<<<<<< HEAD
<<<<<<< HEAD
                
        //sprintf(foo,"%d \r\n",piyo);//intを文字列にして代入
        //rs_puts(foo);	//文字列送信
        uart0_putc('a');
        _delay_ms(1000);
=======
=======
>>>>>>> 3f296686149c535c3cd6ff1207599052306d168f
		
		sprintf(foo,"%d\n\r",piyo);//intを文字列にして代入
	 	rs_puts(foo);	//文字列送信
		_delay_ms(100);
<<<<<<< HEAD
>>>>>>> 3f296686149c535c3cd6ff1207599052306d168f
=======
>>>>>>> 3f296686149c535c3cd6ff1207599052306d168f
		PORTD^=1<<6;//Toggle LED

	}
	return 1;
}
