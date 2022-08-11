#include "pico/stdlib.h"

int main() {

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

    /*
    Power goes through button. When pressed, button interrupts the signal.
    This causes on to switch to false which will then stop the sensor
    until the button is pressed again.
    */
    const uint PIN_28 = 28;
    gpio_init(PIN_28);
    gpio_set_dir(PIN_28, GPIO_IN);

    char on = 0;

    while (1) {
        if (gpio_get(PIN_28)) {
            on = on ^ 1;
        }
        if (on) {
            gpio_put(LED_PIN, 1);
        } else {
            gpio_put(LED_PIN, 0);
        }
    }

}