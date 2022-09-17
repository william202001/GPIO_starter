// This application uses button 1 and LED 1
// The operation is such that if you press the left button, as long as you keep the button pressed,
// the LED is on. As soon as you release the button, LED is off and stays off until the button is pressed again.
// This example use memory-mapped registers to communicate with GPIO peripherals.
// This example doesn't use any Driverlib function. It does not build a Hardware Abstraction Layer (HAL).


// According to the schematics on page 37 of the Launchpad user guide,
// left button (button 1 or S1) is connected to pin 1 (bit1)
#define S1_MASK (1<<1)

// According to the schematics on page 37 of the Launchpad user guide,
// left LED (LED 1) is connected to pin 0 (bit0)
#define LED1_MASK (1<<0)

// According to the schematics on page 37 of the Launchpad user guide,
// When a button is pressed, it is grounded (logic 0)
#define PRESSED 0


 // This example does not use a HAL and therefore, it is hard to read, and hard to port to other platforms.
 // It does not use Driverlib functions, so it is very hard to write as well!
int main(void)
{

    unsigned char *P1IN_address;
    unsigned char *P1OUT_address;
    unsigned char *P1REN_address;
    unsigned char *P1DIR_address;

    P1IN_address = (unsigned char *)0x40004C00;
    P1OUT_address = (unsigned char *)0x40004C02;
    P1REN_address = (unsigned char *)0x40004C06;
    P1DIR_address = (unsigned char *)0x40004C04;

    // Initializing LED1
    // According to table 12.1 on page 678 of MSP432 User guide,
    // to create an output, all you need is to write a 1 to PxDIR for the specific bit you want
    // A common mistake is to write P1DIR = LED1_MASK instead of P1DIR |= LED1_MASK;
    *P1DIR_address = LED1_MASK;

    // Initializing S1 (switch 1 or button 1)
    // According to the table on page 678 of MSP432 User guide,
    // to create an input with pull-up resistor, you need to do three things


    // write a 0 to PxDIR for the specific bit you want
    *P1DIR_address &= ~S1_MASK;
    // write a 1 to PxREn for the specific bit you want (to enable a pull resistor)
    *P1REN_address |= S1_MASK;
    // write a 1 to PxOUT for the specific bit you want (to make the resistor a pull-up)
    *P1OUT_address |= S1_MASK;

    while (1) {
        // If the button is not pressed, keep the LED off
    	if ((*P1IN_address & S1_MASK) == 0)
             // write a 0 to the output register to turn off the LED
    		*P1OUT_address |= LED1_MASK;
        // otherwise, turn the LED on
    	else
            // write a 1 to the output register to turn on the LED
    		*P1OUT_address &= ~LED1_MASK;
    }
}


