/*
Nathan Goldstein 1/19/2026
This code uses an LED and a button using GPIO pins. 
The LED is connected to GPIO pin 4, and the buttons are connected to GPIO pins 10 and 11. 
The program monitors the button state and toggles the LED state (on/off) every 2 times the button is pressed and button2 is also pressed.
The buttons are configured with a pull-up resistor, meaning they read high when not pressed and low when pressed. 
The code includes debouncing logic to make sure the button presses are registered correctly
*/

#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"

#define LED_PIN GPIO_NUM_4       // Choose your LED pin
#define BUTTON_PIN GPIO_NUM_10   // Choose your button pin
#define BUTTON_PIN2 GPIO_NUM_11   // Choose your button pin


bool bstate = false;        
bool pressed = false;
bool pressed2 = false;
bool lstate = false; 
int t = 0 ;


void app_main(void) {
    // TO-DO: Configure LED output
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_pullup_dis(LED_PIN);
    gpio_pulldown_dis(LED_PIN);
    gpio_intr_disable(LED_PIN); 

    // TO-DO: Configure Button input
    gpio_reset_pin(BUTTON_PIN);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_pullup_en(BUTTON_PIN);
    gpio_pulldown_dis(BUTTON_PIN);
    gpio_intr_disable(BUTTON_PIN);

    gpio_reset_pin(BUTTON_PIN2);
    gpio_set_direction(BUTTON_PIN2, GPIO_MODE_INPUT);
    gpio_pullup_en(BUTTON_PIN2);
    gpio_pulldown_dis(BUTTON_PIN2);
    gpio_intr_disable(BUTTON_PIN2);
  
    
    while (1) {
    // TO-DO: Implement LED toggle and button logic here
    pressed = gpio_get_level(BUTTON_PIN) == 0 ;
    pressed2 = gpio_get_level(BUTTON_PIN2) == 0 ;
        if (pressed2){
        if (!bstate && pressed ){
                t = t + 1 ;
                bstate = true ;
            }

            

        if (bstate && !pressed){
            bstate = false;
            if (t == 2) {
                lstate = !lstate;
                gpio_set_level(LED_PIN, lstate);
                vTaskDelay( 500 / portTICK_PERIOD_MS );
                t = 0;
        }
        }
 
        }
        vTaskDelay( 25 / portTICK_PERIOD_MS ); //debouncing delay
        
       
    }
    

}
