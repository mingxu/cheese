#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

enum Types {
    raw,
    player,
    card,
    sanguoCard
};

template <Types t, class DataT, class ListenerT>
class Parser {
public:
    static void parse(DataT const& data, ListenerT& listener)
    {
    }
};


#endif // PARSER_H_INCLUDED
