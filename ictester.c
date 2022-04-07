#include <msp430.h>             // Header file for MSP430, which includes all library related msp430
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    volatile long int cs=0;     // For Checking Status of the IC
    volatile long int i;        // Variable created for loop
    //Output Ports_IC 7400
    P3DIR |= 0xFF;              // Configure Port 3 as Output
    P3SEL &= ~0x00;             // Configure Port 3 as I/O Port function

    //Input Port_IC 7400
    P2DIR &= ~0xFF;             // Configure Port 2 as Input
    P2SEL &= ~0x00;             // Setup Port 2 as I/O Port function
    P2REN |= 0xFF;              // Setup Port 2 as REN enable
    P2OUT |= 0xFF;              // Configure Port 2 as Pull-up resistor

    //Output Port_7SD
    P6DIR |= 0xFF;              // Configure Port 6 as Output
    P6SEL &= ~0x00;             // Configure Port 6 as I/O Port function
    while(1)
    {
        cs=0;                   // To reset the value of CS
        //CASE_1
        P3OUT |= 0x00;          // Port 3 writes 00000000 to IC
        P3OUT &= ~0xFF;         // Inverted version of 0x00,0xFF i.e 11111111
        //(Used to make sure that previously used port P3 is turned to 0)
        if((P2IN & 0x35) == 0x35)      // Check input of Port2 equal to 00110101
        {
            cs++;               // CS is incremented by 1
        }
        //CASE_2
        P3OUT |= 0x55;          // port 3 writes 01010101 to IC
        P3OUT &= ~0xAA;         // Inverted version of 0x55, 0xAA i.e 10101010
        if((P2IN & 0x35) == 0x35)      // Check input of Port2 equal to 00110101
        {
            cs++;               // CS is incremented by 1
        }
        //CASE_3
        P3OUT |= 0xAA;          // Port 3 writes 10101010 to IC
        P3OUT &= ~0x55;         // Inverted version of 0xAA, 0x55 i.e 01010101
        if((P2IN & 0x35) == 0x35)      // Check input of Port2 equal to 00110101
        {
            cs++;               // CS is incremented by 1
        }
        

	//CASE_4
        P3OUT |= 0xFF;            // Port 3 writes 11111111 to IC
        P3OUT &= ~0x00;           // Inverted version of 0xFF, 0x00 i.e 00000000
        if((P2IN & 0x00) == 0x00)    // Check input of Port2 is equal to 00000000
        {
            cs++;                 // CS is incremented by 1
        }
        P6OUT |= 0xFF;          // Turn off the 7 segment display or reset the SSD
        if(cs == 4)               // Checking all cases are right or wrong
        {
            P6OUT &= ~0x6F;       // Displays "g" for good
        }
	    else
	    {
	        P6OUT &= ~0x7C;     // Displays "b" for bad
	    }
    }
	return 0;                   // Returns null
}