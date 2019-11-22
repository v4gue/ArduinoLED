#define F_CPU 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#include <avr/io.h>
#include <util/delay.h>

void USART_Init(unsigned int);
void USART_Transmit(unsigned char);
unsigned char USART_Receive(void);

void main(void)
{

    USART_Init(MYUBRR)

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

void USART_Transmit(unsigned char data)
{
    /* Wait for empty transmit buffer */
    while (!(UCSRnA & (1<<UDREn)));
    /* Put data into buffer, sends the data */
    UDRn = data;
}

unsigned char USART_Receive(void)
{
    /* Wait for data to be received */
    while (!(UCSRnA & (1<<RXCn)));
    /* Get and return received data from buffer */
    return UDRn;
 }