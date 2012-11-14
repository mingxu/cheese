
#include "../common/stopWatch.h"
#include <cstdlib>

using namespace std;

int main()
{
    volatile int result;
    StopWatch sw;
    sw.run([&](){ for (int i = 0; i < 10000; ++i) result = atoi("12345"); });
    sw.printResults();
    return 0;
}
