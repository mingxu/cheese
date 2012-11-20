#include <iostream>
#include <string>
#include "stringParser.h"
#include "listener.h"
using namespace std;

int main()
{
    std::string data[] = {"p0jack", "p1jane","c00k", "d00","a010","a010"};
    Listener l;
    for (int i = 0; i < sizeof(data)/sizeof(std::string); i++)
        Parser<raw, std::string, Listener>::parse(data[i], l);
    return 0;
}
