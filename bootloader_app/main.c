#include <msp430.h> 


/**
 * main.c
 */
void initTimer();
unsigned int count;
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= BIT0;
	initTimer();
	count = 0;
	_enable_interrupts();
//	_bis_SR_register(LPM3_bits);
	while(1);
	return 0;
}

void initTimer() {
    TA0CTL |= 0x01 << 2;
    TA0CTL = (0x02 << 8) + (0x03 << 6) + (0x01 << 4); //125000
    TA0CCTL0 |= 0x01 << 4;
    TA0CCR0 = 62500; //0.5s
}

void __attribute__((interrupt(TIMER0_A0_VECTOR))) TIME_ISR(){
    count ++;
    if(count >= 2){
        P1OUT ^= BIT0;
        count = 0;
    }
}
