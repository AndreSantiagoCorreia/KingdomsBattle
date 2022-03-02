#include "Deck.h"

#include <stdexcept>
#include <cstdlib>    // to return random card from deck
#include <time.h>

namespace cardGameUtil {
    /* Constructor: Creates a Deck with full set of cards */
    Deck::Deck() {
        cardData.reserve(13);

        // initialize 5 defensive cards
        for (int i = 0; i < 5; i++) {
            cardData[i] = Card(i+1, 0);
        }

        // initialize 5 offensive cards
        for (int j = 0; j < 5; j++) {
            cardData[j+5] = Card(0, j+1);
        }

        // initialize 3 multi cards
        cardData[10] = Card(2,2);
        cardData[11] = Card(2,4);
        cardData[12] = Card(4,4);

        // initialize numCards
        numCards = 13;
    }

    /* Equality operator: checks if two cards are the same */
    bool Deck::operator==(Deck const & other) const {
        if (numCards != other.numCards) { return false; }
        for (unsigned int i = 0; i < cardData.size(); i++) {
            if (cardData[i] != other.cardData[i]) {return false; }
        }

        return true;
    }

    /* Inequality operator: checks if two cards are different (have different points) */
    bool Deck::operator!=(Deck const & other) const {
        return !(*this==other);
    }

    /* Get random card from the deck */
    Card Deck::getCard() {
        if (numCards == 0) {
            throw out_of_range ("Deck is empty. Cannot pick another card from deck.");
        }

        // get random card
        int rndIndex;
        do {
            rndIndex = rand() % 13;   // 13 = max number of cards
        } while (cardData[rndIndex].isUsed);

        cardData[rndIndex].isUsed = true;
        numCards--;

        return cardData[rndIndex];
    }
}