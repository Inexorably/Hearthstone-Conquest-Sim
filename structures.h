#ifndef STRUCTURES
#define STRUCTURES

#include <string>
#include <vector>

struct deck{
	std::string name;
    //Obviously class is a keyword.
    bool sameClass(deck other);
    //Returns the class (rogue, priest etc) as a string.
    std::string hero();
	double winRate(){
		return double(wins) / losses;
	}
	int wins = 0;
	int losses = 0;
    //For use in bias.  Returns the index in the biasDecks1,2,3 combo boxes of the given deck.
    int currentIndex();

    //We create a comparison operator so we can sort decks alphabetically.
    bool operator < (const deck& d) const;
};

struct player{
	deck decks[3];
	int wins = 0;
	int losses = 0;
	int position;
	std::vector<int> placings;
	//If you're x-2 this is two obviously.  This lets us pair people with the same record.
	int currentLosses = 0;

	//This function will let us compare if two players are running the same decks.
	bool same(player other);

    //Debug function
    void printDecks();

    double winRate();

    std::string getTops();
    //Only used in the vect<player> result.  Counts number of occurrences of given combination of decks.
    int occurrences = 0;

    //Only used in the bias vector.  % of tourney composition,
    double bias = 0;
    std::string name;

    //Returns the number of tournaments topped.
    double topPercent();
};

#endif //STRUCTURES
