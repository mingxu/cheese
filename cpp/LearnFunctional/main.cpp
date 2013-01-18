#include <iostream>
#include "MyFunctional.h"
using namespace std;

enum Logon {
    Username,
    Password,
    Timestamp
};

typedef Protocol<Logon> LogonP;

typedef LogonP::MessageAccessor<LogonP::Field<const char*, Username>, LogonP::Field<const char*, Password>,LogonP::Field<int, Timestamp>> messageType;

int main()
{
    messageType m;
    m.set<Username>("hello world");
    m.set<Password>("byte cruel world");
    m.set<Timestamp>(1);


    //message m;
    //m(data, identity<Logon, Username>());
    //t.getValue<Password>() = "secret";
    //t.setValue<Timestamp>(1234);
    cout << "value is: ";
    cout << m.get<Username>() << endl;
    cout << "value is: ";
    cout << m.get<Password>() << endl;
    cout << "value is: ";
    cout << m.get<Timestamp>() << endl;
    //cout << "value is: " << t.getValue<Timestamp>() << endl;
    return 0;
}
