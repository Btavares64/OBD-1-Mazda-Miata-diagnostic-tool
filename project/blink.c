#include "pico/stdlib.h"

/*
 * This is for reference, this has nothing to do with the current project
 * I made a  4 bit counter and this was the aftermath :)
*/
#define USER_INPUT 15  // Input Pin
#define LED1 10 // this controlls 2^0
#define LED2 11 // this controlls 2^1
#define LED3 12 // this controls 2^2
#define LED4 13 // this controls 2^3


int main() 
{
    gpio_init(USER_INPUT); // initilize pin 15 as input
    gpio_set_dir(USER_INPUT, GPIO_IN); //set pin 15

    gpio_init(LED1);                // Initialize GPIO pin 10
    gpio_set_dir(LED1, GPIO_OUT);   // Set GPIO pin 10 as an output

    gpio_init(LED2);                // Initialize GPIO pin 11
    gpio_set_dir(LED2, GPIO_OUT);   // Set GPIO pin 11 as an output

    gpio_init(LED3);                // Initialize GPIO pin 12
    gpio_set_dir(LED3, GPIO_OUT);   // Set GPIO pin 12 as an output

    gpio_init(LED4);                // Initialize GPIO pin 13
    gpio_set_dir(LED4, GPIO_OUT);   // Set GPIO pin 13 as an output

    // while loop for reference
}
