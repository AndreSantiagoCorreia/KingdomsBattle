#ifndef H_Deck
#define H_Deck

#include <random>
#include <vector>
#include "Card.h"

using namespace std;

namespace cardGameUtil {
    class Deck {
    public:
        /* Constructor: Creates a Deck with full set of cards */
        Deck();

        /* Equality operator: checks if two cards are the same */
        bool operator== (Deck const & other) const;

        /* Inequality operator: checks if two cards are different (have different points) */
        bool operator!= (Deck const & other) const;

        /* Get random card from the deck */
        Card getCard();

        /* Get number of cards in the deck */
        int getNumCards();

    private:
        vector<Card> cardData;   /* Vector with cards; 
                                        cardData[0]-cardData[4] = defensive 
                                        cardData[5]-cardData[9] = offensive
                                        cardData[10]-cardData[12] = multi */
        int numCards;              /* number of Cards in the deck */
    };
    
}

#endif