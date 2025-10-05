#include "UNO.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <sstream>
using namespace std;

// ---------- internal state
struct InternalGameState {
    vector<Card> deck;
    vector<Card> discardPile;
    vector<vector<Card>> players;
    int currentPlayer = 0;
    bool directionClockwise = true;
    int winnerIndex = -1;
    int numPlayers = 0;
    bool stalemate = false;
};

static InternalGameState state;

// ---------------- constructor
UNOGame::UNOGame(int numPlayers) {
    state.numPlayers = numPlayers;
}

// ---------------- shuffle discard into deck if empty
void reshuffleDeck() {
    if (state.deck.empty() && state.discardPile.size() > 1) {
        Card top = state.discardPile.back();
        state.discardPile.pop_back();
        state.deck = state.discardPile;
        state.discardPile.clear();
        state.discardPile.push_back(top);

        mt19937 rng(1234);
        shuffle(state.deck.begin(), state.deck.end(), rng);
    }
}

// ---------------- initialize deck
void UNOGame::initialize() {
    state.deck.clear();
    state.discardPile.clear();
    state.players.clear();
    state.winnerIndex = -1;
    state.currentPlayer = 0;
    state.directionClockwise = true;
    state.stalemate = false;

    vector<string> colors = {"Red", "Green", "Blue", "Yellow"};
    vector<string> values = {"0","1","2","3","4","5","6","7","8","9","Skip","Reverse","Draw Two"};

    // build deck
    for (auto c : colors) {
        for (auto v : values) {
            int copies = (v == "0") ? 1 : 2;
            for (int i = 0; i < copies; i++) {
                state.deck.push_back({c, v});
            }
        }
    }

    // shuffle deck with fixed seed
    mt19937 rng(1234);
    shuffle(state.deck.begin(), state.deck.end(), rng);

    // deal 7 cards each
    state.players.resize(state.numPlayers);
    for (int i = 0; i < 7; i++) {
        for (int p = 0; p < state.numPlayers; p++) {
            state.players[p].push_back(state.deck.back());
            state.deck.pop_back();
        }
    }

    // first discard
    state.discardPile.push_back(state.deck.back());
    state.deck.pop_back();
}

// ---------------- play turn
void UNOGame::playTurn() {
    if (isGameOver()) {
        return;
    }

    Card top = state.discardPile.back();
    vector<Card> &hand = state.players[state.currentPlayer];
    int idx = -1;

    // 1) play first matching color
    for (int i = 0; i < (int)hand.size(); i++) {
        if (hand[i].color == top.color) {
            idx = i;
            break;
        }
    }

    // 2) if no color match, play first matching value
    if (idx == -1) {
        for (int i = 0; i < (int)hand.size(); i++) {
            if (hand[i].value == top.value) {
                idx = i;
                break;
            }
        }
    }

    // 3) if no match, play action cards in order Skip → Reverse → Draw Two
    if (idx == -1) {
        vector<string> actions = {"Skip","Reverse","Draw Two"};
        for (auto action : actions) {
            for (int i = 0; i < (int)hand.size(); i++) {
                if (hand[i].value == action) {
                    idx = i;
                    break;
                }
            }
            if (idx != -1) {
                break;
            }
        }
    }

    // ---------- if a card is playable
    if (idx != -1) {
        Card c = hand[idx];
        state.discardPile.push_back(c);
        hand.erase(hand.begin() + idx);

        // handle Skip
        if (c.value == "Skip") {
            if (state.directionClockwise) {
                state.currentPlayer = (state.currentPlayer + 2) % state.numPlayers;
            } else {
                state.currentPlayer = (state.currentPlayer - 2 + state.numPlayers) % state.numPlayers;
            }
            return;
        }

        // handle Reverse
        if (c.value == "Reverse") {
            state.directionClockwise = !state.directionClockwise;
        }

        // handle Draw Two
        if (c.value == "Draw Two") {
            int next = 0;
            if (state.directionClockwise) {
                next = (state.currentPlayer + 1) % state.numPlayers;
            } else {
                next = (state.currentPlayer - 1 + state.numPlayers) % state.numPlayers;
            }

            // give 2 cards to next player
            for (int j = 0; j < 2; j++) {
                if (state.deck.empty()) {
                    reshuffleDeck();
                }
                if (!state.deck.empty()) {
                    state.players[next].push_back(state.deck.back());
                    state.deck.pop_back();
                }
            }

            // skip next player
            if (state.directionClockwise) {
                state.currentPlayer = (next + 1) % state.numPlayers;
            } else {
                state.currentPlayer = (next - 1 + state.numPlayers) % state.numPlayers;
            }
            return;
        }
    }
    // ---------- if no playable card, draw one
    else {
        if (state.deck.empty()) {
            reshuffleDeck();
        }

        if (!state.deck.empty()) {
            Card draw = state.deck.back();
            state.deck.pop_back();
            if (draw.color == top.color || draw.value == top.value) {
                state.discardPile.push_back(draw);
            } else {
                hand.push_back(draw);
            }
        } else {
            state.stalemate = true;
            return;
        }
    }

    // ---------- UNO alert
    if (hand.size() == 1) {
        cout << "UNO for Player " << state.currentPlayer << "!\n";
    }

    // ---------- check winner
    if (hand.empty()) {
        state.winnerIndex = state.currentPlayer;
    }

    // ---------- move to next player if game not over
    if (!isGameOver()) {
        if (state.directionClockwise) {
            state.currentPlayer = (state.currentPlayer + 1) % state.numPlayers;
        } else {
            state.currentPlayer = (state.currentPlayer - 1 + state.numPlayers) % state.numPlayers;
        }
    }
}

// ---------------- check game over
bool UNOGame::isGameOver() const {
    return (state.winnerIndex != -1 || state.stalemate);
}

// ---------------- winner
int UNOGame::getWinner() const {
    return state.winnerIndex;
}

// ---------------- get state string
string UNOGame::getState() const {
    stringstream ss;
    ss << "Player " << state.currentPlayer << "'s turn, Direction: ";
    if (state.directionClockwise) {
        ss << "Clockwise";
    } else {
        ss << "Counter-clockwise";
    }
    ss << ", Top: " << state.discardPile.back().color << " " << state.discardPile.back().value;
    ss << ", Players cards: ";
    for (int i = 0; i < state.numPlayers; i++) {
        ss << "P" << i << ":" << state.players[i].size();
        if (i != state.numPlayers - 1) {
            ss << ", ";
        }
    }
    return ss.str();
}
