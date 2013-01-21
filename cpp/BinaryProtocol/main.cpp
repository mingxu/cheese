#include <iostream>
#include "Protocol.h"
#include <boost/mpl/list.hpp>
#include <boost/mpl/fold.hpp>
#include <string.h>

using namespace std;
using namespace boost::mpl;

struct test {
    int a;
    long b;
    char c[10];

    test(int p1, long p2, char const* p3) : a(p1), b(p2) {
        for (unsigned int i = 0; i < min(strlen(p3), 10u); i++)
            c[i] = p3[i];
    }

    test(test const& t) {
        a = t.a;
        b = t.b;
        cout << "test copy constructor!" << endl;
    }
};

enum Logon {
    Username,
    Password,
    Timestamp,
    Test
};

int main()
{
    typedef Protocol<Logon> P;
    typedef list<
        P::Field<long, Username>,
        P::Field<long, Password>,
        P::Field<int, Timestamp>,
        P::Field<test, Test>
    >::type protocol;

    typedef fold<protocol, P::Store<void, void>, P::Store<_1, _2> >::type m;
    typedef fold<protocol, P::Message<void, void>, P::Message<_1, _2> >::type M;


    char *buffer = new char[1024];
    M::set<Username>(buffer, 123L);
    M::set<Password>(buffer, 456L);
    M::set<Timestamp>(buffer, 789);
    test t(1, 2, "hello");
    M::set<Test>(buffer, t);

    cout << M::get<Username>(buffer) << endl;
    cout << M::get<Password>(buffer) << endl;
    cout << M::get<Timestamp>(buffer) << endl;
    test const& tt = M::get<Test>(buffer);
    cout << tt.a << endl;
    cout << tt.b << endl;
    cout << tt.c << endl;


    delete[] buffer;

    return 0;
}
