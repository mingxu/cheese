#ifndef PROTOCOL_H_INCLUDED
#define PROTOCOL_H_INCLUDED
#include <boost/mpl/int_fwd.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/at.hpp>

using namespace boost::mpl;

template <class E>
struct Protocol {
template <class T, E e>
struct Field;

template <E e>
struct enum_ : int_<e> {
    typedef enum_<e> type;
};


template <class Parent, class T>
struct Store {
    typedef Store<void,void> type;
    typedef map<> thisType;
    typedef map<> valueType;
};

template <E e, class T, class Parent>
struct Store<Parent,  Field<T, e> > : Parent {
    typedef Store<Parent,  Field<T, e> > type;
    typedef typename insert<typename Parent::thisType, pair<enum_<e>, Store<Parent,  Field<T, e> > > >::type thisType;
    typedef typename insert<typename Parent::valueType, pair<enum_<e>, T > >::type valueType;

    T value;

    template <E f>
    void set(typename at<valueType, enum_<f> >::type const& v) {
        static_cast<typename at<thisType, enum_<f> >::type *>(this)->value = v;
    }

    template <E f>
    typename at<valueType, enum_<f> >::type get()  const {
        return static_cast<typename at<thisType, enum_<f> >::type const *>(this)->value;
    }
};


template <class Parent, class T>
struct Message {
    enum { offset = 0, size = 0 };
    typedef map<> typeMap;
    typedef map<> offsetMap;
    typedef Message<Parent, T> type;
};

template <class Parent, E e, class T>
struct Message<Parent, Field<T, e> > {
    typedef Message<Parent, Field<T, e> > type;
    enum { offset = Parent::offset + Parent::size, size = sizeof(T) };
    typedef typename insert<typename Parent::offsetMap, pair<enum_<e>, int_<offset> > >::type offsetMap;
    typedef typename insert<typename Parent::typeMap, pair<enum_<e>, T > >::type typeMap;

    template <E f>
    static typename at<typeMap, enum_<f> >::type const& get(char const* buffer) {
        typedef typename at<typeMap, enum_<f> >::type R;
        typedef typename at<offsetMap, enum_<f> >::type O;
        return *(reinterpret_cast<R const *>(buffer + O::value));
    }

    template <E f>
    static void set(char* buffer, typename at<typeMap, enum_<f> >::type const& v) {
        typedef typename at<typeMap, enum_<f> >::type R;
        typedef typename at<offsetMap, enum_<f> >::type O;
        *(reinterpret_cast<R *>(buffer + O::value)) = v;
    }
};
};

#endif // PROTOCOL_H_INCLUDED
