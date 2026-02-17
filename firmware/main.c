#include "pico/stdlib.h"
#include <rpc.h>

#define LED_PIN 0  // Common for RP2040-Zero; verify if unsure

extern transport_t pico_transport;

int main(void)
{
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    stdio_init_all();
    rpc_init(&pico_transport);

    while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
        
        rpc_poll();
    }
}
