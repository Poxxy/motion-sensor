#include "pico/stdlib.h"

void startup();
int detect_motion();
void trigger_light();
void trigger_buzzer();

//red LED triggered by GP15
//motion sensor powered by GP16, send signal to GP17
//buzzer powered by gp18

const uint LIGHT_PIN = 15;
const uint MOTION_PIN_IN = 17;
const uint MOTION_PIN_OUT = 16;
const uint BUZZER_PIN = 18;




int main() {

    startup();

    int detected;

    while (1) {
        detected = detect_motion();
        if (detected) {
            for (int i = 0; i <= 10; i++) {
                trigger_light();
                trigger_buzzer();
            }
        } sleep_ms(100);
        
    }

}

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

    gpio_put(LED_PIN, 1);

}

void trigger_light() {
    gpio_init(LIGHT_PIN);
    gpio_set_dir(LIGHT_PIN, GPIO_OUT);
    gpio_put(LIGHT_PIN, 1);
    sleep_ms(100);
    gpio_put(LIGHT_PIN, 0);
    
}

void trigger_buzzer() {
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    gpio_put(BUZZER_PIN, 1);
    sleep_ms(100);
    gpio_put(BUZZER_PIN, 0);
}

int detect_motion() {
    /*
    Setup PIR sensor. If a signal gets read from AOUT, turn off sensor
    and send the info forward.
    */
    gpio_init(MOTION_PIN_OUT);
    gpio_set_dir(MOTION_PIN_OUT, GPIO_OUT);
    gpio_init(MOTION_PIN_IN);
    gpio_set_dir(MOTION_PIN_IN, GPIO_IN);
    gpio_put(MOTION_PIN_OUT, 1);

    if (gpio_get(MOTION_PIN_IN)) {
        // gpio_put(MOTION_PIN_OUT, 0);
        return 1;
    } else {
        return 0;
    }
}
