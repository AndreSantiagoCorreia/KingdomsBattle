#include "card.h"
#include <iostream>

using namespace std;

namespace cardGameUtil {
    /* Constructor: Creates an empty Card */
    Card::Card() {
        defPoint = 0;
        offPoint = 0;
        isUsed = false;
    }

    /* Constructor: Creates a card with the specified points */
    Card::Card(unsigned int def, unsigned int off) {
        defPoint = def;
        offPoint = off;
        isUsed = false;
    }

    /* Copies content of other card to this card */
    void Card::Copy(const Card & other) {
        defPoint = other.defPoint;
        offPoint = other.offPoint;
        isUsed = other.isUsed;
    }

    /* Assign content of other to this card as a copy */
    Card& Card::operator=(const Card & other) {
        if (this != &other) {
            Copy(other);
        }
        return *this;
    }
    
    /* Equality operator: checks if two cards are the same */
    bool Card::operator==(Card const & other) const {
        if (defPoint != other.defPoint) {return false;}
        if (offPoint != other.offPoint) {return false;}

        return true;
    }

    /* Inequality operator: checks if two cards are different (have different points) */
    bool Card::operator!= (Card const & other) const {
        return !(*this == other);
    }

    /* Calculate amount of points that this card is attacked by other */
    unsigned int Card::attackedBy(Card const & other) {
        // other card could not attack this card
        if (defPoint >= other.offPoint) {
            return 0;
        }
        // points that other card attacked this card by
        return other.offPoint - defPoint;
    }
}