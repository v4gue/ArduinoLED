#define FOSC 16000000UL // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#define BLINK_DELAY_MS 1000

#include <avr/io.h>
#include <util/delay.h>

void USART_Init(unsigned int);
void USART_Transmit(unsigned char);
unsigned char USART_Receive(void);

void main(void)
{

    USART_Init(MYUBRR);

    /* set pin 5 of PORTB for output*/
    DDRB |= _BV(DDB5);
    while(1)
    {
    if (USART_Receive() == 'A')
    {
        /* set pin 5 high to turn led on */
        PORTB |= _BV(PORTB5);
        _delay_ms(BLINK_DELAY_MS);
    }
    else if(USART_Receive() == 'E')
    {
        /* set pin 5 low to turn led off */
        PORTB &= ~_BV(PORTB5);
        _delay_ms(BLINK_DELAY_MS);
    }
    }
    
}

void USART_Init(unsigned int ubrr)
{
    /* Set baud rate */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    /* Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    /* Set frame format: 8data, 2stop bit */
    UCSR0C = (1<<USBS0)|(2<<UCSZ00);
}

//void USART_Transmit(unsigned char data)
//{
    /* Wait for empty transmit buffer */
  //  while (!(UCSR0A & (1<<UDRE0)));
    /* Put data into buffer, sends the data */
    //UDR0 = data;
//}

unsigned char USART_Receive(void)
{
    /* Wait for data to be received */
    while (!(UCSR0A & (1<<RXC0)));
    /* Get and return received data from buffer */
    return UDR0;
 }