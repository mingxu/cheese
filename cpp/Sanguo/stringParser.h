#ifndef STRINGPARSER_H_INCLUDED
#define STRINGPARSER_H_INCLUDED

#include "parser.h"
#include <string>

template <class ListenerT>
class Parser<raw, std::string, ListenerT>  {
public:
    static void parse(std::string const& data, ListenerT& listener)
    {
        switch (data[0])
        {
            case 'p': Parser<player, std::string, ListenerT>::parse(data.substr(1), listener); break;
            case 'c': Parser<card, std::string, ListenerT>::parse(data.substr(1), listener); break;
            case 'a': Parser<play, std::string, ListenerT>::parse(data.substr(1), listener); break;
            case 'd': Parser<deal, std::string, ListenerT>::parse(data.substr(1), listener); break;

            default: listener.process(data); break;
        }
    }
};

class Player {
public:
    int id;
    std::string name;
};

enum Suite { heart, spade, diamond, club };
enum CardValue { cA = 'a', c2 = '2', c3 = '3', c4 = '4', c5 = '5', c6 = '6', c7 = '7', c8 = '8', c9 = '9', c10 = '0', cJ = 'j', cQ = 'q', cK ='k' };

class Card {
public:
    int id;
    Suite suite;
    CardValue cValue;
};

template <class ListenerT>
class Parser<player, std::string, ListenerT> {
public:
    static void parse(std::string const& data, ListenerT& listener) {
        Player p;
        p.id = data[0] - '0';
        p.name = data.substr(1);
        listener.process(p);
    }
};

template <class ListenerT>
class Parser<card, std::string, ListenerT> {
public:
    static void parse(std::string const& data, ListenerT& listener) {
        Card c;
        c.id = data[0] - '0';
        c.suite = Suite(data[1] - '0');
        c.cValue = CardValue(data[2]);
        listener.process(c);
    }
};

class Action {
public:
    int sourceId;
    int destId;
    int cardId;
};

template <class ListenerT>
class Parser<play, std::string, ListenerT> {
public:
    static void parse(std::string const& data, ListenerT& listener) {
        Action a;
        a.sourceId = data[0] - '0';
        a.destId = data[1] - '0';
        a.cardId = data[2] - '0';
        listener.process(a);
    }
};

class Deal {
public:
    int playerId;
    int cardId;
};

template <class ListenerT>
class Parser<deal, std::string, ListenerT> {
public:
    static void parse(std::string const& data, ListenerT& listener) {
        Deal a;
        a.playerId = data[0] - '0';
        a.cardId = data[1] - '0';
        listener.process(a);
    }
};

#endif // STRINGPARSER_H_INCLUDED
