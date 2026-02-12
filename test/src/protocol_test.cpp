#include <CppUTest/TestHarness.h>
#include "CppUTestExt/MockSupport.h"

extern "C"
{
#include <serial.h>
#include <signal.h> // for debugging tests: raise(SIGINT);
}

TEST_GROUP(fmt_base)
{
  void setup()
  {
  };
  void teardown()
  {
    mock().checkExpectations();
    mock().clear();
  };
};


TEST(fmt_base, initComms_succeeds)
{
  // CHecks just setup.
}

