//
//  Card.hpp
//  Solitaire Prime
//
//  Created by Min Kyaw on 2/8/20.
//  Copyright © 2020 Min Kyaw. All rights reserved.
//

#ifndef CARD_H
#define CARD_H

#include <stdio.h>

class Card {
private:
    char rank;
    char suit;
    
public:
    Card(char rank,char suit);
    Card();
    int getValue();
    void showCard();
    void setCard(char rank,char suit);
    
};

#endif /* Card_h */
