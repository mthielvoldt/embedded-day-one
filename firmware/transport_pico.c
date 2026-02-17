#include <transport.h>
#include <pico/stdlib.h>
#include <tusb.h>

static int pico_read(uint8_t *byte)
{
    if (tud_cdc_available()) {
        *byte = tud_cdc_read_char();
        return 1;
    }
    return 0;
}

static void pico_write(const uint8_t *data, size_t len)
{
    tud_cdc_write(data, len);
    tud_cdc_write_flush();
}

// Note: a non-static global
transport_t pico_transport = {
    .read_byte  = pico_read,
    .write_bytes = pico_write,
};
