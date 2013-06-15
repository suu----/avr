/******************************************************
 user definitions
 !!edit properly!!
 ******************************************************/
#define UART0_TX_BUFFERSIZE 32
#define UART0_RX_BUFFERSIZE 32
#define BAUDRATE0 9600

#define ENABLE_U2X0 0

#define UBRR0_VALUE ( ( ( F_CPU / BAUDRATE0 ) / (8*(2-ENABLE_U2X0)) ) - 1)
/******************************************************
 functions
 ******************************************************/
void uart0_init();	//initialize uart0

//transmittion functions
#if (UART0_TX_BUFFERSIZE > 1)

//1Byte 送信
void uart0_putc(unsigned char data);

//10進アスキーコードに変換して送信、送信した文字数を返す
unsigned char uart0_putc_a(unsigned int ch);

//文字列送信
void uart0_puts( unsigned char *msg , unsigned char msgsize);

#endif



//receive functions
#if (UART0_RX_BUFFERSIZE > 1)

//受信バッファが空なら0、そうでないなら1が返る
unsigned char uart0_test_rxbuf();

//1Byte受信
unsigned char uart0_getc();

#endif

/******************************************************
 definitions
 ******************************************************/

#define UART0_TX_BUFFERMASK (UART0_TX_BUFFERSIZE-1)
#define UART0_RX_BUFFERMASK (UART0_RX_BUFFERSIZE-1)

#if (BAUDRATE0==0)
#error specify baudrate0
#endif


//改行を送るマクロ
#define CRLF0() do{uart0_putc('¥r');uart0_putc('¥n');}while(0)







/******************************************************
 device definitions
 ******************************************************/



#if defined(__AVR_AT90PWM3__) | defined(__AVR_AT90PWM2__)\
| defined(__AVR_AT90PWM1__) | defined(__AVR_ATmega168P__)\
| defined(__AVR_ATmega328P__) | defined(__AVR_ATmega48P__)\
| defined(__AVR_ATmega8535__) | defined(__AVR_ATmega88P__)\
| defined(__AVR_ATmega168__) | defined(__AVR_ATmega48__)\
| defined(__AVR_ATmega88__) | defined(__AVR_ATtiny2313__)
#define USART0_UDRE_vect USART_UDRE_vect
#define USART0_RX_vect USART_RX_vect
#endif

#if defined(__AVR_AT90Tiny2313__) | defined(__AVR_ATtiny2313__)
#define USART0_UDRE_vect USART_UDRE_vect
#define USART0_RX_vect USART_RX_vect
#define UBRR0H UBRRH
#define UBRR0L UBRRL
#define UCSR0A UCSRA
#define UCSR0B UCSRB
#define UCSR0C UCSRC
#define RXCIE0 RXCIE
#define UDRIE0 UDRIE
#define TXEN0 TXEN
#define RXEN0 RXEN
#define UDR0 UDR
#define U2X0 U2X
#endif
