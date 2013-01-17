#include <iostream>
#include "MyFunctional.h"
using namespace std;

enum Logon {
    Username,
    Password,
    Timestamp
};

typedef Protocol<Logon> LogonP;

typedef LogonP::Message<LogonP::Field<const char*, Username>, LogonP::Field<int, Timestamp>> messageType;

int main()
{
    const char* data = "hello world";
    int a = 1;
    messageType m;
    m.set<Username>(data);
    m.set<Timestamp>(a);


    //message m;
    //m(data, identity<Logon, Username>());
    //t.getValue<Password>() = "secret";
    //t.setValue<Timestamp>(1234);
    cout << "value is: " << m.get<Username>() << endl;
    cout << "value is: " << m.get<Timestamp>() << endl;
    //cout << "value is: " << t.getValue<Timestamp>() << endl;
    return 0;
}
