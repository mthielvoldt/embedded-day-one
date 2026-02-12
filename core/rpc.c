#include "rpc.h"
#include <string.h>

static transport_t *g_transport = NULL;

#define VERSION_STRING "RP2040-Zero v1.0\n"

void rpc_init(transport_t *transport)
{
    g_transport = transport;
}

void rpc_poll(void)
{
    if (!g_transport) return;

    uint8_t byte;

    if (g_transport->read_byte(&byte)) {
        switch (byte) {

        case 'v':   // version command
            g_transport->write_bytes(
                (const uint8_t *)VERSION_STRING,
                strlen(VERSION_STRING)
            );
            break;

        default:
            break;
        }
    }
}
