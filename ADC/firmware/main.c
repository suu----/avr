#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include <stdio.h>
#include"uart0.h"
#include"uart0.c"

void rs_puts(char *st) //文字列を一文字ずつに変換して送信
{
	
	unsigned char ust;
	
	while (*st != '\0') {
		ust = *st;
		uart0_putc(ust);
		st++;
		_delay_ms(10);
	}
}

int main()
{
	DDRD|=1<<6;	//PD6を出力に
	uart0_init();	//uart0初期化
	sei();	//uart0受信割り込み有効化のためグローバル割り込み有効
	int piyo = 100;
	char foo[64];
	
	//main loop
	for(;;)
	{
		
		sprintf(foo,"%d\n",piyo);//intを文字列にして代入
		rs_puts(foo);	//文字列送信
		_delay_ms(100);
		PORTD^=1<<6;//Toggle LED

	}
	return 1;
}
