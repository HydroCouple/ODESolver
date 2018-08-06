#include "stdafx.h"
#include "test/odesolvertest.h"

int main(int argc, char** argv)
{

  qputenv("QTEST_FUNCTION_TIMEOUT", "1000000000");

  int status = 0;

  //Test One
  {
    ODESolverTest odeSolverTest;
    status |= QTest::qExec(&odeSolverTest, argc, argv);
  }

  return status;
}
