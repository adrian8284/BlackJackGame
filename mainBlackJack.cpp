#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

string playBlackJack();

int main()
{
    string input = "";
    int cash = 1000, bet = 0, winStreak = 0, highScore = 0;

    cout << "\nWelcome to Black Jack! \n";
    while (input != "q")
    {
        if (cash < -3000)
        {
            cout << "\nYou owe over 3000$ and the casino has took notice! You've been kicked out of the casino! \n\n";
            break;
        }

        if (cash > highScore)
        {
            highScore = cash;
        }

        cout << "\n**| Highest Cash: " << highScore << "$ | Win Streak: " << winStreak << " |**";

        if (cash > 1000000)
        {
            cout << "\n{{{ HIGHROLLER }}} ";
        }
        else if (cash > 100000)
        {
            cout << "\n{{{ BALLER }}} ";
        }
        else if (cash > 10000)
        {
            cout << "\n{{{ LUCKY }}} ";
        }
        else if (cash > 1500)
        {
            cout << "\n{{{ WINNER }}} ";
        }

        if (cash < -500)
        {
            cout << "\n{{{ NEED REHAB }}} ";
        }
        else if (cash < 0)
        {
            cout << "\n{{{ IN THE HOLE }}} ";
        }
        else if (cash == 0)
        {
            cout << "\n{{{ BROKE }}} ";
        }
        else if (cash < 500)
        {
            cout << "\n{{{ UNLUCKY }}} ";
        }

        cout << "\nCash: " << cash << "$ \n";
        cout << "\nHow much would you like to bet?: (Enter 'q' to quit)\n";

        cin >> input;

        if (input == "q")
        {
            cout << "\n Thanks for playing! \n\n";
            break;
        }

        try
        {
            bet = stoi(input);

            if (bet < 0)
            {
                cout << "\nYou can't bet a negative amount! \n";
            }
            else if (bet > cash)
            {
                cout << "\nLooks like you bet more than you have, if you lose you'll be in debt! \n";
            }
            else
            {
                if (bet < cash || bet < 100)
                {
                    cout << "\nYou've bet " << bet << "$, good luck! \n";
                }
                else
                {
                    cout << "\nWow, you're a risk taker huh? Well, good luck! \n";
                }
            }
        }
        catch (const invalid_argument &)
        {
            cout << "Invalid input! Please enter a valid number or 'q' to quit. \n";
        }
        cout << "\n";

        cash -= bet;

        this_thread::sleep_for(chrono::seconds(1));

        string result = playBlackJack();
       
        this_thread::sleep_for(chrono::seconds(2));
        if (result == "win" && (cash + bet) == bet)
        {
            cout << "\nYou doubled your cash! \n";
            cash += bet * 2;
            winStreak++;
        }
        else if (result == "win" && (cash + bet) < bet)
        {
            cout << "\nWhew, that was risky! \n";
            cash += bet * 2;
            winStreak++;
        }
        else if (result == "win")
        {
            cash += bet * 2;
            winStreak++;
        }
        else if (result == "draw")
        {
            cash += bet;
        }
        else if (result == "lose" && cash < 0)
        {
            cout << "\nWow, looks like you're in the hole. \n";
            winStreak = 0;
        }
        else if (result == "lose" && cash == 0)
        {
            cout << "\nWow, looks like you're broke. \n";
            cout << "Tip: You can loan money and bet what you don't have, but if you lose you could get yourself deeper in the hole! \n";
            winStreak = 0;
        }
        else if (result == "lose")
        {
            winStreak = 0;
        }
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}

string playBlackJack()
{

    vector<int> userHand, dealerHand;
    string deck[] = {"A♠", "2♠", "3♠", "4♠", "5♠", "6♠", "7♠", "8♠", "9♠", "10♠", "J♠", "Q♠", "K♠"};
    string option = "";
    int userValue = 0, dealerValue = 0, blackJack = 21;
    string result = "draw";

    srand(time(0));
    int lowerDeck = 0, upperDeck = 12;
    int userAce = 0, dealerAce = 0;

    cout << "\nYour Hand:     ";
    for (int i = 0; i < 2; i++)
    {
        int randomVal = lowerDeck + rand() % (upperDeck - lowerDeck + 1);
        userHand.push_back(randomVal);
        cout << deck[randomVal] << " ";

        if (randomVal == 0)
        {
            userValue += 11;
            userAce++;
        }
        else if (randomVal <= 8)
        {
            userValue += randomVal + 1;
        }
        else
        {
            userValue += 10;
        }
    }
    
    while (userValue > blackJack && userAce > 0)
    {
        userValue -= 10;
        userAce--;
    }

    cout << "\nDealer's Hand: ";
    int randomVal = lowerDeck + rand() % (upperDeck - lowerDeck + 1);
    dealerHand.push_back(randomVal);
    cout << deck[randomVal] << " ";

    if (randomVal == 0)
    {
        dealerValue += 11;
        dealerAce++;
    }
    else if (randomVal <= 8)
    {
        dealerValue += randomVal + 1;
    }
    else
    {
        dealerValue += 10;
    }
    cout << "?? \n";
    this_thread::sleep_for(chrono::milliseconds(300));

    bool gameOver = false;

    while (!gameOver)
    {
        if (userValue == blackJack)
        {
            this_thread::sleep_for(chrono::seconds(1));
            cout << "\nBlackjack!!! $$$ \n";
            result = "win";
            gameOver = true;
            break;
        }

        if (userValue > blackJack)
        {
            this_thread::sleep_for(chrono::seconds(1));
            cout << "\nBusted!!! *** \n";
            result = "lose";
            gameOver = true;
            break;
        }

        cout << "\nWould you like to hit or stand?: (Enter 'h' for hit, 's' for stand) \n";
        cin >> option;

        if (option == "H" || option == "h") option = "h";
        else if (option == "S" || option == "s") option = "s";
        else
        {
            cout << "Invalid input, please try again! \n";
            continue;
        }

        if (option == "s")
        {
            cout << "\nYour Hand:     ";
            for (int i = 0; i < userHand.size(); i++)
            {
                cout << deck[userHand[i]] << " ";
            }

            cout << "\n\nDealer is playing...";
            cout << "\nDealer's Hand: ";
            cout << deck[dealerHand[0]] << " ";

            while (dealerValue < 17)
            {
                int randomVal = lowerDeck + rand() % (upperDeck - lowerDeck + 1);
                dealerHand.push_back(randomVal);
                cout << deck[randomVal] << " ";

                if (randomVal == 0)
                {
                    dealerAce++;
                    if ((dealerValue + 11) > blackJack && dealerAce > 0)
                    {
                        dealerValue += 1;
                        dealerAce--;
                    }
                    else
                    {
                        dealerValue += 11;
                    }
                }
                else if (randomVal <= 8)
                {
                    if ((dealerValue + randomVal + 1) > blackJack && dealerAce > 0)
                    {
                        dealerValue -= 10;
                        dealerAce--;
                    }
                    dealerValue += randomVal + 1;
                }
                else
                {
                    if ((dealerValue + 10) > blackJack && dealerAce > 0)
                    {
                        dealerValue -= 10;
                        dealerAce--;
                    }
                    dealerValue += 10;
                }
            }

            this_thread::sleep_for(chrono::seconds(2));
            if (dealerValue > blackJack)
            {
                cout << "\n\nDealer busts, you win!!! $$$ \n";
                result = "win";
                gameOver = true;
                break;
            }
            else if (dealerValue == userValue)
            {
                cout << "\n\nIt's a draw!!! --- \n";
                result = "draw";
                gameOver = true;
                break;
            }
            else if (dealerValue > userValue)
            {
                cout << "\n\nYou lose!!! *** \n";
                result = "lose";
                gameOver = true;
                break;
            }
            else if (dealerValue < userValue)
            {
                cout << "\n\nYou win!!! $$$ \n";
                result = "win";
                gameOver = true;
                break;
            }
        }

        if (option == "h")
        {
            cout << "\nYour Hand:     ";
            for (int i = 0; i < userHand.size(); i++)
            {
                cout << deck[userHand[i]] << " ";
            }

            int randomVal = lowerDeck + rand() % (upperDeck - lowerDeck + 1);
            userHand.push_back(randomVal);
            cout << deck[randomVal] << " ";
            cout << "\n";

            cout << "Dealer's Hand: ";
            cout << deck[dealerHand[0]] << " ";
            cout << "?? \n";
            this_thread::sleep_for(chrono::milliseconds(300));

            if (randomVal == 0)
            {
                userValue += 11;
                userAce++;
            }
            else if (randomVal <= 8)
            {
                userValue += randomVal + 1;
            }
            else
            {
                userValue += 10;
            }

            if (userValue > blackJack && userAce > 0)
            {
                userValue -= 10;
                userAce--;
            }
        }
    }

    return result;
}

// future deck improvement::

/*
// Map card names to their corresponding values
map<string, int> cardValues = {
    {"A♠", 11}, {"2♠", 2}, {"3♠", 3}, {"4♠", 4}, {"5♠", 5}, {"6♠", 6}, {"7♠", 7}, {"8♠", 8}, {"9♠", 9}, {"10♠", 10}, {"J♠", 10}, {"Q♠", 10}, {"K♠", 10},
    {"A♥", 11}, {"2♥", 2}, {"3♥", 3}, {"4♥", 4}, {"5♥", 5}, {"6♥", 6}, {"7♥", 7}, {"8♥", 8}, {"9♥", 9}, {"10♥", 10}, {"J♥", 10}, {"Q♥", 10}, {"K♥", 10},
    {"A♦", 11}, {"2♦", 2}, {"3♦", 3}, {"4♦", 4}, {"5♦", 5}, {"6♦", 6}, {"7♦", 7}, {"8♦", 8}, {"9♦", 9}, {"10♦", 10}, {"J♦", 10}, {"Q♦", 10}, {"K♦", 10},
    {"A♣", 11}, {"2♣", 2}, {"3♣", 3}, {"4♣", 4}, {"5♣", 5}, {"6♣", 6}, {"7♣", 7}, {"8♣", 8}, {"9♣", 9}, {"10♣", 10}, {"J♣", 10}, {"Q♣", 10}, {"K♣", 10}
};

int main() {
    // Initialize deck with all cards
    vector<string> deck = {
        "A♠", "2♠", "3♠", "4♠", "5♠", "6♠", "7♠", "8♠", "9♠", "10♠", "J♠", "Q♠", "K♠",
        "A♥", "2♥", "3♥", "4♥", "5♥", "6♥", "7♥", "8♥", "9♥", "10♥", "J♥", "Q♥", "K♥",
        "A♦", "2♦", "3♦", "4♦", "5♦", "6♦", "7♦", "8♦", "9♦", "10♦", "J♦", "Q♦", "K♦",
        "A♣", "2♣", "3♣", "4♣", "5♣", "6♣", "7♣", "8♣", "9♣", "10♣", "J♣", "Q♣", "K♣"
    };

    // Shuffle the deck
    srand(time(0));
    random_shuffle(deck.begin(), deck.end());

    // Deal two cards to the player
    cout << "Dealing two cards to the player: \n";
    string card1 = deck.back();
    deck.pop_back();
    string card2 = deck.back();
    deck.pop_back();

    cout << card1 << " and " << card2 << "\n";

    // Get the value of the cards from the map
    int card1Value = cardValues[card1];
    int card2Value = cardValues[card2];

    cout << "The value of " << card1 << " is " << card1Value << "\n";
    cout << "The value of " << card2 << " is " << card2Value << "\n";

    return 0;
}
*/