#include <iostream>
#include <string>
#include <vector>

// For User UI
#include <thread>
#include <chrono>
#include <bitset>

// For Deck randomization
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

struct Card {
    string cardFace;
    int cardValue;
};

class Deck {
private:
    vector<Card> deck;
    vector<Card> originalDeck = {
        {"A♠", 11}, {"2♠", 2}, {"3♠", 3}, {"4♠", 4}, {"5♠", 5}, {"6♠", 6}, {"7♠", 7}, {"8♠", 8}, {"9♠", 9}, {"10♠", 10}, {"J♠", 10}, {"Q♠", 10}, {"K♠", 10},
        {"A♥", 11}, {"2♥", 2}, {"3♥", 3}, {"4♥", 4}, {"5♥", 5}, {"6♥", 6}, {"7♥", 7}, {"8♥", 8}, {"9♥", 9}, {"10♥", 10}, {"J♥", 10}, {"Q♥", 10}, {"K♥", 10},
        {"A♦", 11}, {"2♦", 2}, {"3♦", 3}, {"4♦", 4}, {"5♦", 5}, {"6♦", 6}, {"7♦", 7}, {"8♦", 8}, {"9♦", 9}, {"10♦", 10}, {"J♦", 10}, {"Q♦", 10}, {"K♦", 10},
        {"A♣", 11}, {"2♣", 2}, {"3♣", 3}, {"4♣", 4}, {"5♣", 5}, {"6♣", 6}, {"7♣", 7}, {"8♣", 8}, {"9♣", 9}, {"10♣", 10}, {"J♣", 10}, {"Q♣", 10}, {"K♣", 10}
    };
    int numberOfDecks;

public:

    Deck(int numDecks = 1) : numberOfDecks(numDecks) {
        refillDeck();
    }

    void refillDeck() {
        deck.clear();
        
        for (int i = 0; i < numberOfDecks; i++) {
            deck.insert(deck.end(), originalDeck.begin(), originalDeck.end());
        }

        shuffleDeck();
    }

    void shuffleDeck() {
        random_device rd;
        mt19937 rng(rd());
        shuffle(deck.begin(), deck.end(), rng);
    }

    Card drawCard() {
        if (deck.empty()) {
            refillDeck();
        }
        Card drawnCard = deck.back();
        deck.pop_back();
        return drawnCard;
    }
};

class Player {
protected:
    vector<Card> hand;
public:
    void addCard(const Card& card) {
        hand.push_back(card);
    }

    vector<Card> getHand() {
        return hand;
    }

    virtual int calculateHandValue() const {
        int totalValue = 0, aceCount = 0;

        for (const auto& card : hand) {
            totalValue += card.cardValue;
            if (card.cardFace[0] == 'A') aceCount++;
        }

        while (totalValue > 21 && aceCount > 0) {
            totalValue -= 10;
            aceCount--;
        }

        return totalValue;
    }

    void resetHand() {
        hand.clear();
    }

    virtual bool wantsToHit() const = 0;
};

class Dealer : public Player { 
private:
    string name = "Dealer";
public:

    void hiddenCard() {
        cout << "Dealer's Hand: ?? " << endl;
    }

    bool wantsToHit() const override { return calculateHandValue() < 17; }
};

class HumanPlayer : public Player {
private:
    int cash, bet;
    int winStreak;
    string name;
public:
    HumanPlayer() : cash(1000), bet(0), winStreak(0) {}

    bool wantsToHit() const override {
        char choice;

        cout << "Would you like to hit (H) or stand (S)?\n";
        cin >> choice;

        return choice == 'H' || choice == 'h';
    }

    void updateStats(Result result) {
        if (result == WIN) {
            cash += bet * 2;
            winStreak++;
        }
        else if (result == LOSE) {
            winStreak = 0;
        }
        else if (result == DRAW) {
            cash += bet;
        }
    }
};

enum Result { WIN, PLAYER_BLACKJACK, DEALER_BUST, LOSE, DEALER_BLACKJACK, PLAYER_BUST, DRAW };

struct GameState {
    vector<Card> playerHand;
    vector<Card> dealerHand;
    Result result;
};

class BlackjackGame {
public:
    // BlackjackGame () {}

    // Game logic, returns game result
    GameState playRound(HumanPlayer& player, Dealer& dealer, Deck& deck) {
        GameState gameState;

        // Reset hands
        player.resetHand();
        dealer.resetHand();

        // Deal initial cards
        player.addCard(deck.drawCard());
        player.addCard(deck.drawCard());
        dealer.addCard(deck.drawCard());
        dealer.addCard(deck.drawCard());

        gameState.playerHand = player.getHand();
        gameState.dealerHand = dealer.getHand();

        dealer.hiddenCard();

        // Player turn
        while(player.wantsToHit()) {
            player.addCard(deck.drawCard());
            player.displayHand();

            if (player.calculateHandValue() == 21) {
                result = PLAYER_BLACKJACK;
                return result;
            }
            else if (player.calculateHandValue() > 21) {
                result = PLAYER_BUST;
                return result;
            }
        }

        // Dealer turn
        while(dealer.wantsToHit()) {
            dealer.addCard(deck.drawCard());
            ui.renderRound();

            if (dealer.calculateHandValue() == 21) {
                result = DEALER_BLACKJACK;
                return result;
            }
            else if (dealer.calculateHandValue() > 21) {
                result = DEALER_BUST;
                return result;
            }
        }

        // Determine winner
        if (dealer.calculateHandValue() > player.calculateHandValue()) {
            result = LOSE;
        }
        else if (dealer.calculateHandValue() < player.calculateHandValue()) {
            result = WIN;
        }
        else if (dealer.calculateHandValue() == player.calculateHandValue()) {
            result = DRAW;
        }

        return result;
    }

};

class GameUI {
public:
    void clearScreen() {
        #if defined(_WIN32) || defined(_WIN64)
            system("cls");
        #else
            system("clear");
        #endif
    }

    void displayWelcome() {
        cout << "\n Welcome to Black Jack! \n";
    }

    void displayAskName(HumanPlayer& player) {
        
    }

    void displayAskBet(HumanPlayer& player) {
        
    }

    void hiddenCard(const string&name) {
         cout << name << "'s Hand: ";
        cout << "?? \n";
    }

    void displayStats(int cash, int bet, int winStreak) const {
        cout << "\n===================================\n";
        cout << "Cash: $"<< cash << "Bet: "<< bet << "Win Streak: " << winStreak << "\n";
        cout << "\n===================================\n";
    }

    void render() {
        clearScreen();
        displayStats();

    }

    void displayHand(const string& name, const vector<Card>& hand) const {
        cout << name << "'s Hand: ";
        for (const auto& card : hand) {
            cout << card.cardFace << " ";
        }
        cout << "\n";
    }

    // bool gameState = "DONE";
    void displayResult(Result result) {
        cout << "\n===================================\n";
        if (result == WIN) {
            cout << "You win! \n";
        }
        else if ()

        cout << "\n===================================\n";
    }

    void renderRound() {
        clearScreen();


    }


};

// (Add GUI), (Add ConsoleUI)
int main() {

    HumanPlayer player;
    Dealer dealer;
    Deck deck(8);
    GameUI ui;
    char input;

    ui.displayWelcome();

    while(input != 'q') {
        ui.render();
        BlackjackGame game;
        player.setBet();
        Result result = game.playRound(player, dealer, deck);
        player.updateStats(result);
        ui.render();
    }

    return 0;
}   