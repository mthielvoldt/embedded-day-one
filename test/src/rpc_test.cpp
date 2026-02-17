#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

extern "C"
{
#include <rpc.h>
#include <transport_fake.h>
#include <signal.h> // for debugging tests: raise(SIGINT);
}

TEST_GROUP(Rpc)
{
  void setup()
  {
    rpc_init(&mock_transport);
  };
  void teardown()
  {
    mock().checkExpectations();
    mock().clear();
  };
};


TEST(Rpc, initComms_succeeds)
{
  // CHecks just setup.
};

TEST(Rpc, VersionCommand_RespondsWithVersionString)
{
    uint8_t cmd = 'v';
    uint8_t expectedString[] = "RP2040-Zero v1.0\n";
    mock().expectOneCall("read_byte").withOutputParameterReturning("byte", &cmd, 1).andReturnValue(1);
    mock().expectOneCall("write_bytes").withMemoryBufferParameter("data", expectedString, sizeof(expectedString) - 1);
    rpc_poll();

};

TEST(Rpc, NoCommand_NoResponse)
{
    uint8_t cmd = '\0';
    mock().expectOneCall("read_byte").withOutputParameterReturning("byte", &cmd, 0).andReturnValue(0);
    rpc_poll();
};

TEST(Rpc, UnknownCommand_NoResponse)
{
    uint8_t cmd = 'x';
    mock().expectOneCall("read_byte").withOutputParameterReturning("byte", &cmd, 1).andReturnValue(1);
    mock().expectNoCall("write_bytes");
    rpc_poll();
};
