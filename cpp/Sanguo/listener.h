#ifndef LISTENER_H_INCLUDED
#define LISTENER_H_INCLUDED

#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

class Listener {
public:

template <class T>
void process(T const& data) {
    std::cout << "generic data:" << data << std::endl;
}

void process(Player const& p) {
    std::cout << "player data: id:" << p.id << " name:" << p.name << std::endl;
    players[p.id] = p;
}

void process(Card const& c) {
    std::cout << "card data: id: " << c.id << " suite: " << c.suite << " value:" << (char)c.cValue << std::endl;
    cards[c.id] = c;
}

void process(Action const& a) {
    auto i = playerHands[a.sourceId].find(a.cardId);
    if (i == playerHands[a.sourceId].end())
    {
        std::cout << "error! player ";
        process(players[a.sourceId]);
        std::cout << " doesn't have ";
        process(cards[a.cardId]);
        std::cout << std::endl;
        return;
    }

    playerHands[a.sourceId].erase(i);
    std::cout << "action:" << std::endl;
    std::cout << "\tfrom:";
    process(players[a.sourceId]);
    std::cout << "\tto:";
    process(players[a.destId]);
    std::cout << "\tusing:";
    process(cards[a.cardId]);
    std::cout << std::endl;
}

void process(Deal const& d) {
    std::cout << "deal:" << std::endl;
    std::cout << "\tfor:";
    process(players[d.playerId]);
    std::cout << "\t";
    process(cards[d.cardId]);
    std::cout << std::endl;
    playerHands[d.playerId].insert(d.cardId);
}

private:
    std::unordered_map<int, Player> players;
    std::unordered_map<int, Card> cards;
    std::unordered_map<int, std::unordered_set<int>> playerHands;
};

#endif // LISTENER_H_INCLUDED
