#include "testpoint.h"
#include "testedge.h"
#include "testmodeldata.h"

int main(int argc, char** argv)
{
    int status = 0;
    {
        TestPoint tc;
        status |= QTest::qExec(&tc, argc, argv);
    }
    {
        TestEdge tc;
        status |= QTest::qExec(&tc, argc, argv);
    }
    {
        TestModelData tc;
        status |= QTest::qExec(&tc, argc, argv);
    }

    return status;
}
