#ifndef SIM_H
#define SIM_H

#include "structures.h"

using namespace std;

int genRand(int low, int high);

//Loads the relevant decks.
void loadDecks();

//We have a seperate function for generating the decks such that it is simple to generate different meta simulations by just changing this function to change the tourney comp.
//Note that you may manually change n players deck choices after the for loop in order to test deck choices you're considering that would might be unique.
void genDecks(vector<player> &players);

//Returns true with rate d where 0 < d < 1.
bool truth(double d);


//Returns if deck a beats deck b, following tempostorm's meta snapshot odds.  Now returns a double [0 1] instead of a bool.
double wins(deck aD, deck bD);
//Overload with strings.
double wins(string a, string b);

//Chooses the best deck for the next round.
int chooseDeck(vector<deck> avaliableA, vector<deck> avaliableB);


//This will modify the wins and losses of the players, simulating a best of x played between them.
void duel(player &a, player &b);

int rounds(int tourneySize);

int cut(int tourneySize);

int factorial(int num);

int combinations(int n, int r);


void s(int in);

//Single and double elimination branch functions.
void runSingle();
void runDouble();

//We will modify a matrix with a win / loss ratio for each possible deck combination.
void runSimulation();
void orderResults();
#endif // SIM_H
