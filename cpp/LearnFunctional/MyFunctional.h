#ifndef MYFUNCTIONAL_H_INCLUDED
#define MYFUNCTIONAL_H_INCLUDED

template <class E>
struct Protocol {
template <class T, E e>
struct Field;

template <typename... Ts>
struct Message;

template <class T, E e, typename... Ts>
struct Message<Field<T, e>, Ts...> : Message<Ts...> {
    template <E f, class S = void>
    struct Value {
        typedef typename Message<Ts...>::template Value<f>::type type;

        static type get(Message<Ts...> const& m) {
            return m.template get<f>();
        }

        static void set(Message<Ts...> & m, type const& v) {
            m.template set<f>(v);
        }
    };

    template <class S>
    struct Value<e, S> {
        typedef  T type;
        typedef  S dummy;

        static T get(Message<Field<T, e>, Ts...> const& m)  {
            return m.value;
        }

        static void set(Message<Field<T, e>, Ts...> & m, T const& v) {
            m.value = v;
        }
    };

    T value;

    template <E f>
    typename Value<f>::type get() const {
        return Value<f>::get(*this);
    }

    template <E f>
    void set(typename Value<f>::type const& v) {
        Value<f>::set(*this, v);
    }
};

template <class T, E e>
struct Message<Field<T, e>> {
    template <E f, class S = void>
    struct Value {
        typedef void type;
    };

    T value;

    template <class S>
    struct Value<e, S> {
        typedef T type;
        typedef S dummy;

        static T get(Message<Field<T, e>> const & m) {
            return m.value;
        }

        static void set(Message<Field<T, e>> & m, T const& v) {
            m.value = v;
        }
    };

    template <E f>
    typename Value<f>::type get() const {
        return Value<f>::get(*this);
    }

    template <E f>
    void set(typename Value<f>::type const& v) {
        Value<f>::set(*this, v);
    }
};

};


#endif // MYFUNCTIONAL_H_INCLUDED
