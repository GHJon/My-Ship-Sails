#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <ctime>

using namespace std;

class Card{
    public:
    int number;
    Card(){} // Empty Constructor
    Card(int num){ // Modify the Card class based on the amount of cards in the game (in Game Class) 
        number = num;
    }
    int getSuitNumber(){ // Prints our int values for number values (2-9)
        return number/13;
    }
    char getSuit(){ // Get Suit of each card in the deck
        if(number/13 == 0)
            return 'H';
        if(number/13 == 1)
            return 'S';
        if(number/13 == 2)
            return 'C';
        if(number/13 == 3)
            return 'D';
    }
    char getNumber(){ // Get Number Values (Ace - Queen)
        if(number%13 == 0) return 'Q';
        if(number%13 == 1) return 'A';
        if(number%13 == 10) return (int) ('10'); // Tried to Find a way to convert to 10 but couldn't find the issue (0 = 10)
        if(number%13 == 11) return 'J';
        if(number%13 == 12) return 'K';
        
        return number%13 + '0' ;
    }
};
class Player{
    Card cards[7]; // 7 Cards per player
    bool member;
    public:
    Player(bool user, Card C[7]){ // Class Constructor 
        member = user;
        for(int a = 0; a < 7; a++) cards[a] = C[a];
    }
    Card getCard(){
        if(member == false){ // Computer (gets their own set of cards) 
            int hold[4]; // Hold other 4 suits for each player
            for(int i = 0; i < 4; i++) hold[i] = 0;
            for(int i = 0; i < 7; i++){ // Amount of Cards Computer gets
                int suit = cards[i].getSuitNumber();
                hold[suit]++; // Add placeholders for 7 cards for each player
            }
            int compC = 7; // Computer gets 7 cards
            int compPos; // Current position of Cards
            for(int i = 0; i < 4; i++)
                if(hold[i] > 0 && compC > hold[i]){
                    compC = hold[i];
                    compPos = i;
                }
            for(int i = 0; i < 7; i++)
                if(cards[i].getSuitNumber() == compPos) // Position of Card that they want to change
                {
                    swap(cards[i], cards[0]); // Swap Card we don't want in the front of the array
                    break;
                }
            return cards[0];
        }
        displayCards(); // Shows member Cards
        char x = ' '; // Empty Container to hold User Variable (a - g)
        while(x < 'a' || x > 'g')
        {
            cout << "Which one to replace? ";
            cin >> x;
            if(x == '?') return Card(-1); // Show all cards based on '?'
            if (x < 'a' || x > 'g') cout << "Wrong input! ";
        }
        int pos; // Used to designate Card position (For rotation of cards)
        if(x == 'a') pos = 0;
        if(x == 'b') pos = 1;
        if(x == 'c') pos = 2;
        if(x == 'd') pos = 3;
        if(x == 'e') pos = 4;
        if(x == 'f') pos = 5;
        if(x == 'g') pos = 6;

        for(int i = 0; i < 7; i++){
            if(i == pos){
                swap(cards[i], cards[0]); // User-Defined Swap
                break;
            }
        }
        return cards[0];
    }
    bool win(){ // Identify if a player (either a user or AI wins based on Suit)
        for(int i = 1; i < 7; i++){
            if(cards[i].getSuitNumber() != cards[0].getSuitNumber()) return false;
        }
        return true;
    }
    void setCard(Card x){
    	cards[0] = x;
    }
    void displayCards(){ // Function Definition
        cout << "(a)" << cards[0].getSuit() << cards[0].getNumber() << setw(5);
        cout << "(b)" << cards[1].getSuit() << cards[1].getNumber() << setw(5);
        cout << "(c)" << cards[2].getSuit() << cards[2].getNumber() << setw(5);
        cout << "(d)" << cards[3].getSuit() << cards[3].getNumber() << setw(5);
        cout << "(e)" << cards[4].getSuit() << cards[4].getNumber() << setw(5);
        cout << "(f)" << cards[5].getSuit() << cards[5].getNumber() << setw(5);
        cout << "(g)" << cards[6].getSuit() << cards[6].getNumber() << setw(5);
        cout << endl << '\n';
    }
};

class Game{
public:
    Game(){
        Card cards[52]; // Deck of Cards
        srand(time(NULL));
        // vector <int> deck;
        // deck.push_back(cards);
        // random_shuffle (cards[0],cards[i]);
        // random_shuffle (deck.begin(), deck.end()); // Doesn't Work
        for(int i = 0; i < 52; i++){
            cards[i] = Card(i);
         //   random_shuffle (cards[0],cards[i]);
        }
        for(int i = 0; i < 100000; i++) swap(cards[rand()%52], cards[rand()%52]); // Swap two random cards a lot of times (Not Effective but viable)
   		
   		// Print out Cards for Each Player
        Player P0(true, cards); // "True" - Makes User see cards
        Player P1(false, cards+7); // "False" - Makes Comp Cards hidden
        Player P2(false, cards+14);
        Player P3(false, cards+21);
        Player P4(false, cards+28);
        
        while(true) // Check if User or Computer Won
        {
            if(P0.win()){ 
                cout << "My Ship Sails! --- Player 0 Won..." << endl;
                break;
                }
            if(P1.win()){
                cout << "My Ship Sails! --- Player 1 Won..." << endl;
                break;
                }
            if(P2.win()){
                cout << "My Ship Sails! --- Player 2 Won..." << endl;
                break;
                }
            if(P3.win()){
                cout << "My Ship Sails! --- Player 3 Won..." << endl;
                break;
                }
            if(P4.win()){
                cout << "My Ship Sails! --- Player 4 Won..." << endl;
                break;
                }

            Card C0 = P0.getCard();
            if(C0.number == -1){ // Prints out Every Card that the user and Computer have (with '?')
                cout << "Player 0: ";
                P0.displayCards();
                cout << "Player 1: ";
                P1.displayCards();
                cout << "Player 2: ";
                P2.displayCards();
                cout << "Player 3: ";
                P3.displayCards();
                cout << "Player 4: ";
                P4.displayCards();
            }
            else{ // If no one won yet, print:
                Card C1 = P1.getCard();
                Card C2 = P2.getCard();
                Card C3 = P3.getCard();
                Card C4 = P4.getCard();

                cout << "Hint: player 0 passes " << C0.getSuit() << C0.getNumber() << " to player 1" << endl;
                cout << "Hint: player 1 passes " << C1.getSuit() << C1.getNumber() << " to player 2" << endl;
                cout << "Hint: player 2 passes " << C2.getSuit() << C2.getNumber() << " to player 3" << endl;
                cout << "Hint: player 3 passes " << C3.getSuit() << C3.getNumber() << " to player 4" << endl;
                cout << "Hint: player 4 passes " << C4.getSuit() << C4.getNumber() << " to player 0" << endl;
                cout << endl;

                // Put Swapped cards into their 7 cards
                P1.setCard(C0);
                P2.setCard(C1);
                P3.setCard(C2);
                P4.setCard(C3);
                P0.setCard(C4);
            }
        } // If a player or user won, print:
        cout << '\n' << "[ Final card distributions ]" << endl;
        cout << "Player 0: ";
        P0.displayCards();
        cout << "Player 1: ";
        P1.displayCards();
        cout << "Player 2: ";
        P2.displayCards();
        cout << "Player 3: ";
        P3.displayCards();
        cout << "Player 4: ";
        P4.displayCards();
    }
};
int main(){
    Game game; // Starts the game
    return 0;
}