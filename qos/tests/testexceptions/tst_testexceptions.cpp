#include "tst_testexceptions.h"
#include "src/config/exceptions.h"
#include "src/config/errorcode.h"


TestExceptions::TestExceptions() {}

TestExceptions::~TestExceptions() {}

void TestExceptions::initTestCase() {}

void TestExceptions::cleanupTestCase() {}

void TestExceptions::test_case1()
{
    BaseException::generateErrorCodeHFile (
        ("../../../../qosbrowser/static/docs/errorcode.csv"),
        ("../../../../qosbrowser/src/config/errorcode.h")
    );
}
