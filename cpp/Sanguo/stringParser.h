#ifndef STRINGPARSER_H_INCLUDED
#define STRINGPARSER_H_INCLUDED

#include "parser.h"
#include <string>
#include <iostream>

template <class ListenerT>
class Parser<raw, std::string, ListenerT>  {
public:
    static void parse(std::string const& data, ListenerT& listener)
    {
        switch (data[0])
        {
            case 'p': Parser<player, std::string, ListenerT>::parse(data.substr(1), listener); break;
            case 'c': Parser<card, std::string, ListenerT>::parse(data.substr(1), listener); break;
            default: listener.process(data); break;
        }
    }
};

class Player {
public:
    std::string name;
};

enum Suite { heart, spade, diamond, club };
enum CardValue { cA = 'a', c2 = '2', c3 = '3', c4 = '4', c5 = '5', c6 = '6', c7 = '7', c8 = '8', c9 = '9', c10 = '0', cJ = 'j', cQ = 'q', cK ='k' };

class Card {
public:
    Suite suite;
    CardValue cValue;
};

template <class ListenerT>
class Parser<player, std::string, ListenerT> {
public:
    static void parse(std::string const& data, ListenerT& listener) {
        Player p;
        p.name = data;
        listener.process(p);
    }
};

template <class ListenerT>
class Parser<card, std::string, ListenerT> {
public:
    static void parse(std::string const& data, ListenerT& listener) {
        Card c;
        c.suite = Suite(data[0] - '0');
        c.cValue = CardValue(data[1]);
        listener.process(c);
    }
};


class Listener {
public:

template <class T>
void process(T const& data) { std::cout << "generic data:" << data << std::endl; }

void process(Player const& p) { std::cout << "player data: name:" << p.name << std::endl; }

void process(Card const& c) { std::cout << "card data: suite: " << c.suite << " value:" << c.cValue << std::endl; }
};
#endif // STRINGPARSER_H_INCLUDED
