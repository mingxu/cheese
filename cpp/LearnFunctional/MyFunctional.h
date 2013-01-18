#ifndef MYFUNCTIONAL_H_INCLUDED
#define MYFUNCTIONAL_H_INCLUDED

#include <boost/tuple/tuple.hpp>
#include <boost/mpl/list.hpp>

template <class E>
struct Protocol {
template <class T, E e>
struct Field;

struct BadType;

template <typename... Ts>
struct Message{};


template <class T, E e, typename... Ts>
struct Message<Field<T, e>, Ts...> : Message<Ts...>  {
    template <E f, class S = void>
    struct Value {
        typedef typename Message<Ts...>::template Value<f>::type type;
        typedef S dummy;
    };

    template <E f, class S = void>
    struct Target {
        typedef typename Message<Ts...>::template Target<f>::type type;
    };

    template <class S>
    struct Value<e, S> {
        typedef T type;
        typedef S dummy;
    };

    T value;

    template <class S>
    struct Target<e, S> {
        typedef Message<Field<T,e>, Ts...> type;
        typedef S dummy;
    };

};

template <typename... Ts>
struct MessageAccessor : Message<Ts...> {

    template <E f>
    typename Message<Ts...>::template Value<f>::type get() const {
        return static_cast<typename Message<Ts...>::template Target<f>::type const*>(this)->value;
    }

    template <E f>
    void set(typename Message<Ts...>::template Value<f>::type const& v) {
        static_cast<typename Message<Ts...>::template Target<f>::type*>(this)->value = v;
    }


};

};


#endif // MYFUNCTIONAL_H_INCLUDED
