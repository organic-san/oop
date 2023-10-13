#include <vector>
#include <iostream>
#include <utility>
#include <cstdlib>
#include "Table.h"
#include "Card.h"
using namespace std;

Table::Table() {
    for(int i = 0; i < kNSuit; i++) {
        for(int j = 0; j < kNPip; j++) {
            Card t(Card::IDConverter(i, j));
            deckArr.push_back(t);
        }
    }

    for(int i = 0; i < kNSuit * kNPip; i++) {
        int index = rand() % (kNSuit * kNPip - i);
        deckArr.push_back(deckArr[index]);
        deckArr.erase(deckArr.begin() + index);
    }
}

Card Table::getCard() {
    if(deckArr.size() < 0) throw "err: Table::getCard(): no more card on the table.";
    auto iter = deckArr.begin();
    Card temp = *iter;
    deckArr.erase(deckArr.begin());
    return temp;
}

int Table::getSize() const {
    return deckArr.size();
}

//debug tool
void Table::getInfo(int i) const {
    cout << "[";
    i = min(i, int(deckArr.size()));
    for(auto iter = deckArr.begin(); iter != deckArr.begin() + i; ++iter) {
        if (iter != deckArr.begin()) cout << ", ";
        cout << "(" << iter->getSuit() << " " << iter->getPip() << ")";
    }
    cout << "]";
}

Table& Table::getInstance() {
    static Table instance;
    return instance;
}