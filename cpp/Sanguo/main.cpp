#include <iostream>
#include <string>
#include "stringParser.h"

using namespace std;

int main()
{
    std::string data;
    while (true) {
        std::getline(std::cin, data);
        if (data.empty()) break;
        Listener l;
        Parser<raw, std::string, Listener>::parse(data, l);
    }


    return 0;
}
