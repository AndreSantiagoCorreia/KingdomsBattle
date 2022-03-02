#ifndef H_card
#define H_card

#include <iostream>

using namespace std;

namespace cardGameUtil {
    class Card {
    public:
        unsigned int defPoint;   /* Defensive point of card */
        unsigned int offPoint;   /* Offensive point of card */
        bool isUsed;

        /* Constructor: Creates a default Card */
        Card();

        /* Constructor: Creates a card with the specified points */
        Card(unsigned int def, unsigned int off); 

        /* Copies content of other card to this card */
        void Copy(Card const & other);

        /* Assign content of other to this card as a copy */
        Card& operator=(Card const & other);
        
        /* Equality operator: checks if two cards are the same */
        bool operator== (Card const & other) const;

        /* Inequality operator: checks if two cards are different (have different points) */
        bool operator!= (Card const & other) const;

        /* Calculate amount of points that this card is attacked by other */
        unsigned int attackedBy(Card const & other);
    };
}

#endif