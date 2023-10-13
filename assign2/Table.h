#include <vector>
#include "Card.h"

class Table {

public: 
    // get table
    static Table& getInstance();
    
    // get one card and remove one card from the table
    Card getCard();
    int getSize() const;
    void getInfo(int i) const;

private:
    // card list on the table
    static std::vector<Card> deckArr;

    // Constructor
    Table();
};