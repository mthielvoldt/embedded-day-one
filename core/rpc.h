#ifndef RPC_H
#define RPC_H

#include "transport.h"

void rpc_init(transport_t *transport);
void rpc_poll(void);

#endif
