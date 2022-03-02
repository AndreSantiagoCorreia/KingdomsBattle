#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include <iostream>

using namespace std;
using namespace cardGameUtil;

#define MAXROUND 10
#define NUMCARDSONTABLE 3

/* Function to get valid number of players */
int getNumPlayers(void) {
    int numPlayers;
    // TODO:minimum is two because could not connect AI yet
    cout << "How many players are there (choose between 2 and 5): ";
    cin >> numPlayers;

    // until user provide valid number of players, repeatedly ask for number of players
    while (numPlayers < 2 || numPlayers > 5) {
        cout << "   Invalid number of players; Please provide number between 2 and 5: ";
        cin >> numPlayers;
    }

    cout << endl;
    return numPlayers;
}

/* Function to initialize cards on table*/
void initCardsOnTable(vector<vector<Card>> &cardsOnTable, int numPlayers, vector<Player> &players) {
    cardsOnTable.resize(numPlayers);

    for (int i = 0; i < numPlayers; i++) {
        cardsOnTable[i].resize(NUMCARDSONTABLE);

        for (int j = 0; j < NUMCARDSONTABLE; j++) {
            cardsOnTable[i][j] = players[i].deck.getCard();
        }
    }
}

int main (void) {
    int player, round; // iterators

    int numPlayers = getNumPlayers();

    vector<Player> players;
    players.resize(numPlayers);
    for (player = 0; player < numPlayers; player++) {
        players[player] = Player();
    }

    vector<vector<Card>> cardsOnTable;
    initCardsOnTable(cardsOnTable, numPlayers, players);
    
    vector<Card> cardsOfRound;
    cardsOfRound.resize(numPlayers);
    for (round = 0; round < MAXROUND; round++) {
        cout << endl<< "Round " << round << ":" << endl;

        for (player = 0; player < numPlayers; player++) {
            // add timelimit?
            int chosenCard;

            // let player choose card
            cout << "   Player" << player << "'s cards on table" << endl;
            cout << "       card1: " << "(" << cardsOnTable[player][0].defPoint << "," << cardsOnTable[player][0].offPoint << ")" << endl;
            cout << "       card2: " << "(" << cardsOnTable[player][1].defPoint << "," << cardsOnTable[player][1].offPoint << ")" << endl;
            cout << "       card3: " << "(" << cardsOnTable[player][2].defPoint << "," << cardsOnTable[player][2].offPoint << ")" << endl;
            cout << "   Player" << player << " choose your cards: ";

            // save index
            cin >> chosenCard;

            while (chosenCard < 0 || chosenCard > 2) {
                cout << "   Invalid card number; Please choose between 1 and 3: ";
                cin >> chosenCard;
            }

            // save card on cardsOfRound vector
            cardsOfRound[player] = cardsOnTable[player][chosenCard-1];

            // replace chosenCard with new random Card
            cardsOnTable[player][chosenCard-1] = players[player].deck.getCard();
            cout << endl << endl;
        }

        for (player = 0; player < numPlayers; player++) {
            int sumAttackedPt = 0;
            for (int i = 0; i < numPlayers; i++) {
                if (player != i) {
                    sumAttackedPt += cardsOfRound[player].attackedBy(cardsOfRound[i]);
                }
            }
            players[player].attackedBy(sumAttackedPt);

            cout << "   Player" << player << " attacked by " << sumAttackedPt;
            cout << " remaining HP is " << players[player].HP << endl;
        }

        cout << endl;
    } 

    
    return 0;
}

