#include "pico/stdlib.h"

void startup() {
    /*
    Blink 3 times to make it clear the program has started.
    */

   // On board LED pin
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Signal program is starting.
    for (int i = 0; i < 3; i++) {
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
    }

}

void led_switch(bool enabled) {
    /*
    Refers to on board LED
    */
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    if (enabled) {
        gpio_put(LED_PIN, 1);
    } else {
        gpio_put(LED_PIN,0);
    }
}

void flicker_led2() {
    /*
    GPI14 is associated with external LED
    */
    const uint PIN_14 = 14;
    gpio_init(PIN_14);
    gpio_set_dir(PIN_14, GPIO_OUT);

    gpio_put(PIN_14, 1);
    sleep_ms(250);
    gpio_put(PIN_14,0);
}


void detect_motion(bool enabled) {
    
    /*
    GPIO1 and GPIO2 are associated with the motion sensor
    */
    const uint PIN_01 = 1;
    gpio_init(PIN_01);
    gpio_set_dir(PIN_01, GPIO_OUT);

    const uint PIN_02 = 2;
    gpio_init(PIN_02);
    gpio_set_dir(PIN_02, GPIO_IN);

    if (enabled) {
        gpio_put(PIN_01, 1);
    } else {
        gpio_put(PIN_01, 0);
    }

    if (gpio_get(PIN_02)) {
        flicker_led2();
    }

}

int main() {

    startup();

    /*
    Power goes through button. When pressed, button interrupts the signal.
    This causes on to switch to false which will then stop the sensor
    until the button is pressed again.
    */

   /*
   GPIO28 is associated with the button.
   */
    const uint PIN_28 = 28;
    gpio_init(PIN_28);
    gpio_set_dir(PIN_28, GPIO_IN);

    char on = 0;

    while (1) {

        led_switch(on);

        detect_motion(on);

        if (gpio_get(PIN_28)) {
            on = on ^ 1;
        }
    }

}
