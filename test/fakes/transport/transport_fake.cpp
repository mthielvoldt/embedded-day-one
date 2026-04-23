#include <CppUTestExt/MockSupport.h>

extern "C"
{
#include <transport.h>
#include <string.h>
}


static int mock_read_byte(uint8_t *byte)
{
  return mock().actualCall("read_byte").withOutputParameter("byte", byte).returnIntValue();
}

static void mock_write_bytes(const uint8_t *data, size_t len)
{
  mock().actualCall("write_bytes").withMemoryBufferParameter("data", data, len);
}

transport_t mock_transport = {
    .read_byte = mock_read_byte,
    .write_bytes = mock_write_bytes
};
