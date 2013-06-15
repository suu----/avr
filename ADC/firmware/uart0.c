/*******************************************************************
 AVR用uart送受信処理
 *******************************************************************/
#include<avr/io.h>
#include<avr/interrupt.h>
#include<stdlib.h>
#include"uart0.h"
/*******************************************************************
 variables
 *******************************************************************/

volatile unsigned char TXbuf[UART0_TX_BUFFERSIZE];
volatile unsigned char TXbufptr;
volatile unsigned char TXbufendptr;

volatile unsigned char RXbuf[UART0_RX_BUFFERSIZE];
volatile unsigned char RXbufptr;
volatile unsigned char RXbufendptr;
/*******************************************************************
 functions
 *******************************************************************/
//initialize uart0
void uart0_init()
{
	UBRR0H = UBRR0_VALUE>>8;	UBRR0L = UBRR0_VALUE&0xFF;
	UCSR0A = ENABLE_U2X0<<U2X0;;
	UCSR0B =
#if (UART0_RX_BUFFERSIZE > 1)
	(1 << RXCIE0) | (1 << RXEN0) |
#endif
#if (UART0_TX_BUFFERSIZE > 1)
	(1 << TXEN0)|
#endif
	0;
	TXbufptr=0;	TXbufendptr=0;
	RXbufptr=0;	RXbufendptr=0;
}

/*******************************************************************
 //送信用関数群
 *******************************************************************/

#if (UART0_TX_BUFFERSIZE > 1)

/*******************************************************************
 一文字送信
 *******************************************************************/

void uart0_putc(unsigned char data)
{
	//バッファが開くまで待つ
	while((UCSR0B & (1 << UDRIE0))&&(TXbufptr==TXbufendptr));
	TXbuf[TXbufendptr]=data;	//データをバッファへ格納
    
	//送信バッファ終端ポインタ移動
	UCSR0B &= ~(1 << UDRIE0);
	TXbufendptr = (TXbufendptr + 1) & ( UART0_TX_BUFFERMASK );
	//送信可能割り込みenable
	UCSR0B |= (1 << UDRIE0);
}

/*******************************************************************
 一文字アスキーコードに変換して送信
 *******************************************************************/
unsigned char uart0_putc_a(unsigned int ch)
{
    unsigned char i , tmps[8];
	itoa(ch , (char*)tmps , 10);
	for(i = 0; tmps[i] != 0; i++)
	{
		uart0_putc(tmps[i]);
	}
	return i;
}

/*******************************************************************
 //指定された配列の値を指定された文字数だけバッファに送る
 *******************************************************************/
void uart0_puts( unsigned char *msg , unsigned char msgsize)
{
	for(; msgsize; msgsize--,msg++)
	{
		uart0_putc(*msg);
	}
}

/*******************************************************************
 //送信可能割り込みベクター
 *******************************************************************/
ISR(USART0_UDRE_vect)
{
	UDR0=TXbuf[TXbufptr];	//送信バッファのデータを送信
	//送信バッファポインタ移動
	TXbufptr = (TXbufptr + 1) & ( UART0_TX_BUFFERMASK );
	//送信するデータがなくなったら
	if( TXbufptr == TXbufendptr )
	{
		UCSR0B &= ~(1 << UDRIE0);	//送信可能割り込みdisable
	}
}

#endif


/*******************************************************************
 //受信用関数群
 *******************************************************************/

#if (UART0_RX_BUFFERSIZE > 1)

/*******************************************************************
 //受信データがなければ0を返す関数
 *******************************************************************/
unsigned char uart0_test_rxbuf()
{
	return (RXbufendptr - RXbufptr);
}

/*******************************************************************
 //受信データ1byte格納
 *******************************************************************/
unsigned char uart0_getc()
{
	unsigned char msg;
	msg = RXbuf[RXbufptr];	//データ格納
    
	//受信バッファポインタ移動
	UCSR0B &= ~(1<<RXCIE0);
	RXbufptr = (RXbufptr+1) & ( UART0_RX_BUFFERMASK );
	UCSR0B |= (1<<RXCIE0);
	return msg;
}

/*******************************************************************
 //受信割り込みベクター
 *******************************************************************/
ISR(USART0_RX_vect)
{
	RXbuf[RXbufendptr] = UDR0;	//受信データをバッファに格納
	//受信バッファ終端ポインタ移動
	RXbufendptr = (RXbufendptr + 1) & ( UART0_RX_BUFFERMASK );
}

#endif
