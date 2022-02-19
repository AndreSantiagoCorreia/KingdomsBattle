#ifndef H_Player
#define H_Player

#include "Deck.h"
#include <stdexcept>

namespace cardGameUtil {
    class Player {
    public:    
        unsigned int HP;
        Deck deck;
        // string name;

        /* Constructor: Create player */
        Player() {
            HP = 20;
            deck = Deck();
        };

        /* Function to reduce HP of player by point amount */
        void attackedBy(unsigned int point) {
            if (HP == 0) {
                throw out_of_range ("Player does not have remaining HP");
            }

            if (HP < point) {
                HP = 0;
            } else {
                HP -= point;
            }
        }
    };
}

#endif