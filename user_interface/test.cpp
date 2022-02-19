#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include <iostream>

using namespace std;
using namespace cardGameUtil;

bool testCardConstructor(unsigned int def, unsigned int off) {
    bool error = false;
    Card testCard1 = Card(def, off);
    unsigned int card1def = testCard1.defPoint;
    unsigned int card1off = testCard1.offPoint;

    if (card1def != def) {
        cout << "Expected defensie point: 1, Actual defensive point: " << card1def << endl;
        error = true;
    }

    if (card1off != off) {
        cout << "Expected offensive point: 2, Actual defensive point: " << card1off << endl;
        error = true;
    }

    if (testCard1.isUsed != false) {
        cout << "Expected isUsed: false, Actual isUsed: " << testCard1.isUsed << endl;
        error = true;
    }

    return error;
}

bool testCardEqualityOperator(unsigned int def, unsigned int off) {
    bool error = false;

    Card card1 = Card(def, off);
    Card card2 = Card(def, off);
    if (card1 != card2) {
        cout << "Two cards are same but inequality operator said false." << endl;
        cout << "     card1(def, off) = (" << card1.defPoint << ", " << card1.offPoint << ")" << endl;
        cout << "     card2(def, off) = (" << card2.defPoint << ", " << card2.offPoint << ")" << endl;
        error = true;
    }

    Card card3 = Card(off, def);
    if (card1 == card3) {
        cout << "Two cards are different but equality operator said true." << endl;
        cout << "     card1(def, off) = (" << card1.defPoint << ", " << card1.offPoint << ")" << endl;
        cout << "     card3(def, off) = (" << card3.defPoint << ", " << card3.offPoint << ")" << endl;
        error = true;
    }
    return error;
}

bool testCardAttackedBy() {
    bool error = false;
    Card card1 = Card(0, 5);
    Card card2 = Card(2, 0);

    if (card1.attackedBy(card2) != 0) {
        cout << "card2 was a defensive card" << endl;
        cout << "Expected: 0, Actual: " << card1.attackedBy(card2) << endl;
        error = true;
    }

    if (card2.attackedBy(card1) != 3) {
        cout << "card1 attck card2 by point 5" << endl;
        cout << "Expected: 3, Actual: " << card2.attackedBy(card1) << endl;
        error = true;
    }

    Card card3 = Card(2, 4);
    Card card4 = Card(4, 0);

    if (card3.attackedBy(card4) != 0) {
        cout << "card4 was a defensive card" << endl;
        cout << "Expected: 0, Actual: " << card3.attackedBy(card4) << endl;
        error = true;
    }

    if (card4.attackedBy(card3) != 0) {
        cout << "card4 should have defended" << endl;
        cout << "Expected: 0, Actual: " << card4.attackedBy(card3) << endl;
        error = true;
    }

    Card card5 = Card(0, 4);
    Card card6 = Card(0, 3);

    if (card5.attackedBy(card6) != 3) {
        cout << "card6 attacked with 3 offensive point" << endl;
        cout << "Expected: 3, Actual: " << card5.attackedBy(card6) << endl;
        error = true;
    }

    if (card6.attackedBy(card5) != 4) {
        cout << "card5 attacked with 4 offensive point" << endl;
        cout << "Expected: 4, Actual: " << card6.attackedBy(card5) << endl;
        error = true;
    }

    return error;
}

void testDeckConstructor() {
    Deck deck1 = Deck();
    for (int i = 0; i < 13; i++) {
        cout << "     card" << i+1 << " def=" << deck1.cardData[i].defPoint << " off=" << deck1.cardData[i].offPoint <<endl;
    }
    cout << "     numCards=" << deck1.numCards << endl;
}

void testDeckGetCard() {
    Deck deck1 = Deck();
    Card currCard;
    for (int i = 0; i < 13; i++) {
        currCard = deck1.getCard();
        cout << i << ": def= " << currCard.defPoint << " off= " << currCard.offPoint << " numCards= "<< deck1.numCards << endl;
    }
}

void testDeckGetCard2() {
    Deck deck = Deck();
    Card currCard;

    // take 13 cards first
    for (int i = 0; i < 13; i++) {
        currCard = deck.getCard();
    }

    // call getCard one more time
    // should throw an out of range exception
    currCard = deck.getCard();
}

bool testPlayerConstructor() {
    bool error = false;
    Player p1 = Player();
    if (p1.HP != 20) {
        cout << "Player's HP has not been initiallized to 20" << endl;
        error = true;
    }

    if (p1.deck.numCards != 13) {
        cout << "Player's deck does not have 13 cards" << endl;
        error = true;
    }

    return error;
}

bool testPlayerAttckedBy() {
    Player p1 = Player();
    
    p1.attackedBy(4);
    cout << "      HP Remaining: " << p1.HP << endl;
    p1.attackedBy(3);
    cout << "      HP Remaining: " << p1.HP << endl;
    p1.attackedBy(0);
    cout << "      HP Remaining: " << p1.HP << endl;
    p1.attackedBy(5);
    cout << "      HP Remaining: " << p1.HP << endl;
    p1.attackedBy(2);
    cout << "      HP Remaining: " << p1.HP << endl;
    p1.attackedBy(10);
    cout << "      HP Remaining: " << p1.HP << endl;
    p1.attackedBy(2); // should throw an exception
}

int main (void) {
    bool err;

    // Card.cpp test
    cout << "Start Card constructor test..." << endl;
    for (unsigned int i = 0; i < 5; i++) {
        err = testCardConstructor(i, i*2);
    }
    if(!err) { cout << "Passed Card constructor test!" << endl << endl; }

    cout << "Start Card Equality operator test..." << endl;
    for (unsigned int j = 6; j < 10; j++) {
        err = testCardEqualityOperator(j, j-3);
    }
    if(!err) { cout << "Passed Card Equality operator test!" << endl << endl; }

    cout << "Start Card attackedBy function test..." << endl;
    err = testCardAttackedBy();
    if(!err) { cout << "Passed Card attackedBy function test!" << endl << endl; }


    // Deck.cpp test
    cout << "Start Deck constructor test..." << endl;
    testDeckConstructor();
    cout << "Passed Deck constructor test!" << endl << endl;

    cout << "Start Deck getCard test..." << endl;
    testDeckGetCard();
    cout << "Passed Deck getCard test!" << endl << endl;

    cout << "Start Deck getCard test2..." << endl;
    testDeckGetCard2();
    cout << "Passed Deck getCard test!" << endl << endl;

    cout << "Start Player constructor test..." << endl;
    for (int k = 0; k < 10; k++) {
        err = testPlayerConstructor();
        if (err) { cout << "Player constructor test failed at " << k << "th time" << endl; }
    }
    if (!err) { cout << "Passed Player constructor test!" << endl << endl; }

    cout << "Start Player attackedBy function test..." << endl;
    testPlayerAttckedBy();

    return 0;
}

