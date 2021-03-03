//
//  Deck.hpp
//  Solitaire Prime
//
//  Created by Min Kyaw on 2/8/20.
//  Copyright © 2020 Min Kyaw. All rights reserved.
//

#ifndef DECK_H
#define DECK_H


#include "Card.h"
class Deck {
private:
    Card storage[52];
    int top;
    
public:
    Deck();
    int CardsLeft();
    void shuffle();
    Card deal();
    void showDeck();
    void refreshDeck();
};

#endif /* Deck_h */
