#include <vector>
#include <algorithm>
#include <math.h>
#include "structures.h"
#include "globals.h"
#include "sim.h"
#include <time.h>
#include <random>

#include <QDebug>

extern bool singleElim;
extern bool doubleElim;

using namespace std;

int genRand(int low, int high){
	typedef std::mt19937 rng_type;
	std::uniform_int_distribution<rng_type::result_type> udist(low, high);
	rng_type rng;
	rng_type::result_type const seedval = rand();
	rng.seed(seedval);
	rng_type::result_type randomInt = udist(rng);
	return randomInt;
}

//Loads the relevant decks.
void loadDecks(){
	//Constructors are just a myth.
    possibleDecks.clear();
	deck midrangeDruid;
	midrangeDruid.name = md;
	possibleDecks.push_back(midrangeDruid);
	deck aggroDruid;
	aggroDruid.name = ad;
	possibleDecks.push_back(aggroDruid);
	deck tempoMage;
    tempoMage.name = te;
	possibleDecks.push_back(tempoMage);
	deck freezeMage;
	freezeMage.name = fm;
	possibleDecks.push_back(freezeMage);
	deck midrangePaladin;
	midrangePaladin.name = mp;
	possibleDecks.push_back(midrangePaladin);
	deck secretPaladin;
	secretPaladin.name = sp;
	possibleDecks.push_back(secretPaladin);	
	deck controlPriest;
	controlPriest.name = cp;
    possibleDecks.push_back(controlPriest);
	deck oilRogue;
    oilRogue.name = oi;
	possibleDecks.push_back(oilRogue);
	deck aggroShaman;
	aggroShaman.name = as;
	possibleDecks.push_back(aggroShaman);
	deck renoLock;
	renoLock.name = rl;
	possibleDecks.push_back(renoLock);
	deck malyLock;
	malyLock.name = ml;
	possibleDecks.push_back(malyLock);
	deck zooLock;
	zooLock.name = zl;
	possibleDecks.push_back(zooLock);
	deck patronWarrior;
	patronWarrior.name = pw;
	possibleDecks.push_back(patronWarrior);
    for (int i = 0; i < (int)possibleDecks.size(); i++){
        deckNames.push_back(possibleDecks[i].name);
    }
	//All decks have been pushed into the possible deck array.  Upon initialization have zero wins and losses.
}

//We have a seperate function for generating the decks such that it is simple to generate different meta simulations by just changing this function to change the tourney comp.
//Note that you may manually change n players deck choices after the for loop in order to test deck choices you're considering that would might be unique.
void genDecks(vector<player> &players){
	loadDecks();
	for (int i = 0; i < tourneySize; i++){
		player genericToBePushed;
        genericToBePushed.position = i;

        //With the bias probabilities for players we will add them based on the truth(double).
        double prob = 1;
        bool pushed = false;
        for (int j = 0; j < (int)bias.size(); j++){
            if (prob != 1)
                prob = bias[j].bias / (1 - prob);
            else
                prob = bias[j].bias;
           //qDebug()() << "J: " << j;
           //qDebug()() << "Bias: " << bias[j].bias;
           //qDebug()() << "Prob: " << prob;
            if (prob > 1)
                prob = 1;
            if (truth(prob)){
                bias[j].position = i;
                players.push_back(bias[j]);
                pushed = true;
                break;
            }
        }
        if (pushed)
            continue;

		for (int j = 0; j < 3; j++){
			//Give the players random decks.  If we wish to test for specific metas, we may change this.
            int chosen = genRand(0, (int)possibleDecks.size() - 1);
            //Debug() << QString::fromStdString(possibleDecks[chosen].name);
            bool good = true;
            for (int k = 0; k < j; k++){
                if (possibleDecks[chosen].sameClass(genericToBePushed.decks[k]))
                    good = false;
            }
            if (good)
                genericToBePushed.decks[j] = possibleDecks[chosen];
            else
                j--;
		}
		players.push_back(genericToBePushed);
	}
}

//Returns true with rate d where 0 < d < 1.
std::knuth_b rand_engine;

bool truth(double prob){

    std::bernoulli_distribution d(prob);
        return d(rand_engine);
}


//Returns if deck a beats deck b, following tempostorm's meta snapshot odds.  Now returns a double [0 1] instead of a bool.
double wins(deck aD, deck bD){
	string a = aD.name;
	string b = bD.name;
	//In a mirror match you have an even winrate.
	if (a == b)
		return (0.5);
	if (a == sp){
		if (b == md)
			return (spVmd);
		if (b == ad)
			return (spVad);
        if (b == te)
            return (spVte);
		if (b == fm)
			return (spVfm);
		if (b == mp)
			return (spVmp);
		if (b == cp)
			return (spVcp);
        if (b == oi)
			return (spVor);
		if (b == as)
			return (spVas);
		if (b == rl)
			return (spVrl);
		if (b == ml)
			return (spVml);
		if (b == zl)
			return (spVzl);
		if (b == pw)
			return (spVpw);
	}
	else if (a == as){
		if (b == md)
			return (asVmd);
		if (b == ad)
			return (asVad);
        if (b == te)
            return (asVte);
		if (b == fm)
			return (asVfm);
		if (b == mp)
			return (asVmp);
		if (b == cp)
			return (asVcp);
        if (b == oi)
			return (asVor);
		if (b == sp)
			return (asVsp);
		if (b == rl)
			return (asVrl);
		if (b == ml)
			return (asVml);
		if (b == zl)
			return (asVzl);
		if (b == pw)
			return (asVpw);
	}
	else if (a == md){
		if (b == as)
			return (mdVas);
		if (b == ad)
			return (mdVad);
        if (b == te)
            return (mdVte);
		if (b == fm)
			return (mdVfm);
		if (b == mp)
			return (mdVmp);
		if (b == cp)
			return (mdVcp);
        if (b == oi)
			return (mdVor);
		if (b == sp)
			return (mdVsp);
		if (b == rl)
			return (mdVrl);
		if (b == ml)
			return (mdVml);
		if (b == zl)
			return (mdVzl);
		if (b == pw)
			return (mdVpw);
	}
	else if (a == rl){
		if (b == as)
			return (rlVas);
		if (b == ad)
			return (rlVad);
        if (b == te)
            return (rlVte);
		if (b == fm)
			return (rlVfm);
		if (b == mp)
			return (rlVmp);
		if (b == cp)
			return (rlVcp);
        if (b == oi)
			return (rlVor);
		if (b == sp)
			return (rlVsp);
		if (b == md)
			return (rlVmd);
		if (b == ml)
			return (rlVml);
		if (b == zl)
			return (rlVzl);
		if (b == pw)
			return (rlVpw);
	}
	else if (a == mp){
		if (b == as)
			return (mpVas);
		if (b == ad)
			return (mpVad);
        if (b == te)
            return (mpVte);
		if (b == fm)
			return (mpVfm);
		if (b == rl)
			return (mpVrl);
		if (b == cp)
			return (mpVcp);
        if (b == oi)
			return (mpVor);
		if (b == sp)
			return (mpVsp);
		if (b == md)
			return (mpVmd);
		if (b == ml)
			return (mpVml);
		if (b == zl)
			return (mpVzl);
		if (b == pw)
			return (mpVpw);
	}
    else if (a == oi){
		if (b == as)
			return (orVas);
		if (b == ad)
			return (orVad);
        if (b == te)
            return (orVte);
		if (b == fm)
			return (orVfm);
		if (b == rl)
			return (orVrl);
		if (b == cp)
			return (orVcp);
		if (b == mp)
			return (orVmp);
		if (b == sp)
			return (orVsp);
		if (b == md)
			return (orVmd);
		if (b == ml)
			return (orVml);
		if (b == zl)
			return (orVzl);
		if (b == pw)
			return (orVpw);
	}
	else if (a == pw){
		if (b == as)
			return (pwVas);
		if (b == ad)
			return (pwVad);
        if (b == te)
            return (pwVte);
		if (b == fm)
			return (pwVfm);
		if (b == rl)
			return (pwVrl);
		if (b == cp)
			return (pwVcp);
		if (b == mp)
			return (pwVmp);
		if (b == sp)
			return (pwVsp);
		if (b == md)
			return (pwVmd);
		if (b == ml)
			return (pwVml);
		if (b == zl)
			return (pwVzl);
        if (b == oi)
			return (pwVor);
	}
    else if (a == te){
		if (b == as)
            return (teVas);
		if (b == ad)
            return (teVad);
		if (b == pw)
            return (teVpw);
		if (b == fm)
            return (teVfm);
		if (b == rl)
            return (teVrl);
		if (b == cp)
            return (teVcp);
		if (b == mp)
            return (teVmp);
		if (b == sp)
            return (teVsp);
		if (b == md)
            return (teVmd);
		if (b == ml)
            return (teVml);
		if (b == zl)
            return (teVzl);
        if (b == oi)
            return (teVor);
	}
	else if (a == ad){
		if (b == as)
			return (adVas);
        if (b == te)
            return (adVte);
		if (b == pw)
			return (adVpw);
		if (b == fm)
			return (adVfm);
		if (b == rl)
			return (adVrl);
		if (b == cp)
			return (adVcp);
		if (b == mp)
			return (adVmp);
		if (b == sp)
			return (adVsp);
		if (b == md)
			return (adVmd);
		if (b == ml)
			return (adVml);
		if (b == zl)
			return (adVzl);
        if (b == oi)
			return (adVor);
	}
	else if (a == cp){
		if (b == as)
			return (cpVas);
        if (b == te)
            return (cpVte);
		if (b == pw)
			return (cpVpw);
		if (b == fm)
			return (cpVfm);
		if (b == rl)
			return (cpVrl);
		if (b == ad)
			return (cpVad);
		if (b == mp)
			return (cpVmp);
		if (b == sp)
			return (cpVsp);
		if (b == md)
			return (cpVmd);
		if (b == ml)
			return (cpVml);
		if (b == zl)
			return (cpVzl);
        if (b == oi)
			return (cpVor);
	}
	else if (a == fm){
		if (b == as)
			return (fmVas);
        if (b == te)
            return (fmVte);
		if (b == pw)
			return (fmVpw);
		if (b == cp)
			return (fmVcp);
		if (b == rl)
			return (fmVrl);
		if (b == ad)
			return (fmVad);
		if (b == mp)
			return (fmVmp);
		if (b == sp)
			return (fmVsp);
		if (b == md)
			return (fmVmd);
		if (b == ml)
			return (fmVml);
		if (b == zl)
			return (fmVzl);
        if (b == oi)
			return (fmVor);
	}
	else if (a == ml){
		if (b == as)
			return (mlVas);
        if (b == te)
            return (mlVte);
		if (b == pw)
			return (mlVpw);
		if (b == cp)
			return (mlVcp);
		if (b == rl)
			return (mlVrl);
		if (b == ad)
			return (mlVad);
		if (b == mp)
			return (mlVmp);
		if (b == sp)
			return (mlVsp);
		if (b == md)
			return (mlVmd);
		if (b == fm)
			return (mlVfm);
		if (b == zl)
			return (mlVzl);
        if (b == oi)
			return (mlVor);
	}
	else if (a == zl){
		if (b == as)
			return (zlVas);
        if (b == te)
            return (zlVte);
		if (b == pw)
			return (zlVpw);
		if (b == cp)
			return (zlVcp);
		if (b == rl)
			return (zlVrl);
		if (b == ad)
			return (zlVad);
		if (b == mp)
			return (zlVmp);
		if (b == sp)
			return (zlVsp);
		if (b == md)
			return (zlVmd);
		if (b == fm)
			return (zlVfm);
		if (b == ml)
			return (zlVml);
        if (b == oi)
			return (zlVor);
	}
	//Should never get here.
    //cout << "error, (0.5)\n";
	return (0.5);

}

double wins(string a, string b){
    //In a mirror match you have an even winrate.
    if (a == b)
        return (0.5);
    if (a == sp){
        if (b == md)
            return (spVmd);
        if (b == ad)
            return (spVad);
        if (b == te)
            return (spVte);
        if (b == fm)
            return (spVfm);
        if (b == mp)
            return (spVmp);
        if (b == cp)
            return (spVcp);
        if (b == oi)
            return (spVor);
        if (b == as)
            return (spVas);
        if (b == rl)
            return (spVrl);
        if (b == ml)
            return (spVml);
        if (b == zl)
            return (spVzl);
        if (b == pw)
            return (spVpw);
    }
    else if (a == as){
        if (b == md)
            return (asVmd);
        if (b == ad)
            return (asVad);
        if (b == te)
            return (asVte);
        if (b == fm)
            return (asVfm);
        if (b == mp)
            return (asVmp);
        if (b == cp)
            return (asVcp);
        if (b == oi)
            return (asVor);
        if (b == sp)
            return (asVsp);
        if (b == rl)
            return (asVrl);
        if (b == ml)
            return (asVml);
        if (b == zl)
            return (asVzl);
        if (b == pw)
            return (asVpw);
    }
    else if (a == md){
        if (b == as)
            return (mdVas);
        if (b == ad)
            return (mdVad);
        if (b == te)
            return (mdVte);
        if (b == fm)
            return (mdVfm);
        if (b == mp)
            return (mdVmp);
        if (b == cp)
            return (mdVcp);
        if (b == oi)
            return (mdVor);
        if (b == sp)
            return (mdVsp);
        if (b == rl)
            return (mdVrl);
        if (b == ml)
            return (mdVml);
        if (b == zl)
            return (mdVzl);
        if (b == pw)
            return (mdVpw);
    }
    else if (a == rl){
        if (b == as)
            return (rlVas);
        if (b == ad)
            return (rlVad);
        if (b == te)
            return (rlVte);
        if (b == fm)
            return (rlVfm);
        if (b == mp)
            return (rlVmp);
        if (b == cp)
            return (rlVcp);
        if (b == oi)
            return (rlVor);
        if (b == sp)
            return (rlVsp);
        if (b == md)
            return (rlVmd);
        if (b == ml)
            return (rlVml);
        if (b == zl)
            return (rlVzl);
        if (b == pw)
            return (rlVpw);
    }
    else if (a == mp){
        if (b == as)
            return (mpVas);
        if (b == ad)
            return (mpVad);
        if (b == te)
            return (mpVte);
        if (b == fm)
            return (mpVfm);
        if (b == rl)
            return (mpVrl);
        if (b == cp)
            return (mpVcp);
        if (b == oi)
            return (mpVor);
        if (b == sp)
            return (mpVsp);
        if (b == md)
            return (mpVmd);
        if (b == ml)
            return (mpVml);
        if (b == zl)
            return (mpVzl);
        if (b == pw)
            return (mpVpw);
    }
    else if (a == oi){
        if (b == as)
            return (orVas);
        if (b == ad)
            return (orVad);
        if (b == te)
            return (orVte);
        if (b == fm)
            return (orVfm);
        if (b == rl)
            return (orVrl);
        if (b == cp)
            return (orVcp);
        if (b == mp)
            return (orVmp);
        if (b == sp)
            return (orVsp);
        if (b == md)
            return (orVmd);
        if (b == ml)
            return (orVml);
        if (b == zl)
            return (orVzl);
        if (b == pw)
            return (orVpw);
    }
    else if (a == pw){
        if (b == as)
            return (pwVas);
        if (b == ad)
            return (pwVad);
        if (b == te)
            return (pwVte);
        if (b == fm)
            return (pwVfm);
        if (b == rl)
            return (pwVrl);
        if (b == cp)
            return (pwVcp);
        if (b == mp)
            return (pwVmp);
        if (b == sp)
            return (pwVsp);
        if (b == md)
            return (pwVmd);
        if (b == ml)
            return (pwVml);
        if (b == zl)
            return (pwVzl);
        if (b == oi)
            return (pwVor);
    }
    else if (a == te){
        if (b == as)
            return (teVas);
        if (b == ad)
            return (teVad);
        if (b == pw)
            return (teVpw);
        if (b == fm)
            return (teVfm);
        if (b == rl)
            return (teVrl);
        if (b == cp)
            return (teVcp);
        if (b == mp)
            return (teVmp);
        if (b == sp)
            return (teVsp);
        if (b == md)
            return (teVmd);
        if (b == ml)
            return (teVml);
        if (b == zl)
            return (teVzl);
        if (b == oi)
            return (teVor);
    }
    else if (a == ad){
        if (b == as)
            return (adVas);
        if (b == te)
            return (adVte);
        if (b == pw)
            return (adVpw);
        if (b == fm)
            return (adVfm);
        if (b == rl)
            return (adVrl);
        if (b == cp)
            return (adVcp);
        if (b == mp)
            return (adVmp);
        if (b == sp)
            return (adVsp);
        if (b == md)
            return (adVmd);
        if (b == ml)
            return (adVml);
        if (b == zl)
            return (adVzl);
        if (b == oi)
            return (adVor);
    }
    else if (a == cp){
        if (b == as)
            return (cpVas);
        if (b == te)
            return (cpVte);
        if (b == pw)
            return (cpVpw);
        if (b == fm)
            return (cpVfm);
        if (b == rl)
            return (cpVrl);
        if (b == ad)
            return (cpVad);
        if (b == mp)
            return (cpVmp);
        if (b == sp)
            return (cpVsp);
        if (b == md)
            return (cpVmd);
        if (b == ml)
            return (cpVml);
        if (b == zl)
            return (cpVzl);
        if (b == oi)
            return (cpVor);
    }
    else if (a == fm){
        if (b == as)
            return (fmVas);
        if (b == te)
            return (fmVte);
        if (b == pw)
            return (fmVpw);
        if (b == cp)
            return (fmVcp);
        if (b == rl)
            return (fmVrl);
        if (b == ad)
            return (fmVad);
        if (b == mp)
            return (fmVmp);
        if (b == sp)
            return (fmVsp);
        if (b == md)
            return (fmVmd);
        if (b == ml)
            return (fmVml);
        if (b == zl)
            return (fmVzl);
        if (b == oi)
            return (fmVor);
    }
    else if (a == ml){
        if (b == as)
            return (mlVas);
        if (b == te)
            return (mlVte);
        if (b == pw)
            return (mlVpw);
        if (b == cp)
            return (mlVcp);
        if (b == rl)
            return (mlVrl);
        if (b == ad)
            return (mlVad);
        if (b == mp)
            return (mlVmp);
        if (b == sp)
            return (mlVsp);
        if (b == md)
            return (mlVmd);
        if (b == fm)
            return (mlVfm);
        if (b == zl)
            return (mlVzl);
        if (b == oi)
            return (mlVor);
    }
    else if (a == zl){
        if (b == as)
            return (zlVas);
        if (b == te)
            return (zlVte);
        if (b == pw)
            return (zlVpw);
        if (b == cp)
            return (zlVcp);
        if (b == rl)
            return (zlVrl);
        if (b == ad)
            return (zlVad);
        if (b == mp)
            return (zlVmp);
        if (b == sp)
            return (zlVsp);
        if (b == md)
            return (zlVmd);
        if (b == fm)
            return (zlVfm);
        if (b == ml)
            return (zlVml);
        if (b == oi)
            return (zlVor);
    }
    //Should never get here.
    //cout << error, (0.5)\n;
    return (0.5);

}

//Chooses the best deck for the next round.
int chooseDeck(vector<deck> avaliableA, vector<deck> avaliableB){
	
	double bestWR = 0;
	int positionOfChoice = 0;
	for (int i = 0; i < (int)avaliableA.size(); i++){
		//For each possible choice player A can make, we average the win rates and find the highest.
		double currentWR = 0;
		for (int j = 0; j < (int)avaliableB.size(); j++){
			currentWR += wins(avaliableA[i], avaliableB[j])/avaliableB.size();
		}
		if (currentWR > bestWR){
			bestWR = currentWR;
			positionOfChoice = i;
		}
	}
	return positionOfChoice;
}


//This will modify the wins and losses of the players, simulating a best of x played between them.
void duel(player &a, player &b){
	//Number of wins for a and b respectively.
	int numA = 0, numB = 0;

	//Current decks for each player (position in vector).
	int curA = 0, curB = 0;

	//We will create a vector of the avaliable decks for each player.
	vector<deck> avaliableA, avaliableB;
	for (int i = 0; i < 3; i++){
		avaliableA.push_back(a.decks[i]);
		avaliableB.push_back(b.decks[i]);
	}

    //Player A and B both choose the deck that will have best matchup on average based on opponent's avaliable decks.
    curA = chooseDeck(avaliableA, avaliableB);
    curB = chooseDeck(avaliableB, avaliableA);

	while (numA < bestOf / 2 + 1 && numB < bestOf / 2 + 1){
		//While loop is more illustrative than for(;;) break;.
		//Round starts.
		//If this is the first round.
        //qDebug() << wins(a.decks[curA], b.decks[curB]);
		if (truth(wins(a.decks[curA], b.decks[curB]))){
			//Player a wins the round.
            //qDebug() << "Player a wins.";
			numA++;
			//Both players are now able to switch decks.  Player a may not play his deck again.
			avaliableA.erase(avaliableA.begin() + curA);
			curA = chooseDeck(avaliableA, avaliableB);
			curB = chooseDeck(avaliableB, avaliableA);	
		}
		else{
			//Player b wins the round.
            //qDebug() << "Player b wins.";
			numB++;
			avaliableB.erase(avaliableB.begin() + curB);
			curA = chooseDeck(avaliableA, avaliableB);
			curB = chooseDeck(avaliableB, avaliableA);
		}
	}
	if (numA > numB){
		//Player a won.
		a.wins++;
		b.losses++;
		b.currentLosses++;
	}
	else{
		b.wins++;
		a.losses++;
		a.currentLosses++;
	}
}

int rounds(int tourneySize){
	//Note log == ln, and we cast to int.
	return int(log(tourneySize) / log(2));
}

int cut(int tourneySize){
    if (tourneySize <= 32)
        return 4;
    else if (tourneySize <= 128)
        return 8;
    else if (tourneySize <= 512)
        return 16;
    else if (tourneySize <= 2048)
        return 32;
    else
        return 64;
}

int factorial(int num){
    int res = 1;
	for (int i = num; i > 0; i--)
        res = res * num;
    return res;
}

int combinations(int n, int r){
	return factorial(n) / (factorial(r)) / factorial(n - r);
}


void s(int in){
    //For debugging.
    //cout << in << endl;
    return;
}

void runDouble(){//Filler
}

void runSingle(){
    //We now have a function that will be called instead of runSimulation in the case that singleElim == true.  Likewise, there will be a similar for doubleElim.
    vector<player> players;
    //There will be no scrub vector, people who lose simply are dropped from the players vector.
    genDecks(players);

    for (int i = 0; (int)players.size() > 1; i++){
        //We loop until the players vector size hits one.
        duel(players[i], players[(int)players.size()-1-i]);
        //Each time we remove someone from the player vector, we willl add them to the results vector.
        //We remove all of the players whom do not have losses (single Elim).
        vector<player> temp;
        for (int j = 0; j < (int)players.size(); j++){
            if (players[j].losses == 0){
                temp.push_back(players[j]);
                continue;
            }
            else{
                //A player has been eliminated.

            }
            //We need to check if we wish to add the player's placing the result vector.
        }
        //If the combination of decks to be added already exists in the results vector,
    }


}

//We will modify a matrix with a win / loss ratio for each possible deck combination.
void runSimulation(){
	//A vector containing the players in the tournament.
	vector<player> players;

    //A vector containing people who scrub out.
    vector<player> scrubs;

	//Note the tournament will be double elimination.  We now generate each players' decks.
	genDecks(players);

    vector<player> playersLeft;
    vector<player> topPlayers;
    playersLeft.clear(); topPlayers.clear();

    //Legacy
    if (true){

        //The players all now have decks.  We will now simulate the tournament.  We will do it round by round, and then with a top cut.
        //We will have a vector of people who are x-0, x-1, x-2, and x-3.
        vector<int> x0, x1, x2, x3;
        //We preload everyone into the x0 bracket for the first round, as hopefully no one has any losses.
        for (int i = 0; i < (int)players.size(); i++)
            x0.push_back(i);

        //We will make everyone play someone with the same record.  Because the players and their decks are generated in a random order (and we can even shuffle the players vector).
        for (int i = 0; i < rounds(tourneySize); i++){
            s(1);
            //Round starts.  The x0 people play.
            for (int j = 0; j <= (int)x0.size() / 2; j++){
                duel(players[x0[j]], players[x0[x0.size() - 1 - j]]);
                s(2);
            }
            for (int j = 0; j <= (int)x1.size() / 2 && i > 0; j++){
                duel(players[x1[j]], players[x1[x1.size() - 1 - j]]);
                s(3);
            }
            for (int j = 0; j <= (int)x2.size() / 2 && i > 1; j++){
                duel(players[x2[j]], players[x2[x2.size() - 1 - j]]);
                s(4);
            }
            for (int j = 0; j <= (int)x3.size() / 2 && i > 2; j++){
                duel(players[x3[j]], players[x3[x3.size() - 1 - j]]);
                s(5);
            }

            //All players have now played and have had their struct members modified by the duel function.  We now update the x vectors.
            x0.clear(); x1.clear(); x2.clear(); x3.clear();
            s(6);
            for (int j = 0; j < (int)players.size(); j++){
                s(7);
                switch (players[j].currentLosses){
                case 0:
                    x0.push_back(players[j].position);
                    break;
                case 1:
                    x1.push_back(players[j].position);
                    break;
                case 2:
                    x2.push_back(players[j].position);
                    break;
                case 3:
                    x3.push_back(players[j].position);
                    break;
                default:
                    bool goodToAdd = true;
                    for (int eh = 0; eh < (int)scrubs.size(); eh++){
                        if (scrubs[eh].position == players[j].position){
                            goodToAdd = false;
                            break;
                        }
                    }
                    //We avoid adding duplicates of players.
                    if (goodToAdd)
                        scrubs.push_back(players[j]);

                    break;
                }
            }
            s(8);
        }

        s(9);
        //We will now have the x0, x1... vectors which will allow us to generate the top cut.
        if (topCut == -1)
            topCut = cut(tourneySize);
        s(10);

        for (int i = 0; i < topCut; i++){
            if (i < (int)x0.size()){
                topPlayers.push_back(players[x0[i]]);
                continue;
            }
            else if (i - x0.size() < x1.size()){
                topPlayers.push_back(players[x1[i-(int)x0.size()]]);
                continue;
            }
            else if (i - x0.size() - x1.size() < x2.size()){
                topPlayers.push_back(players[x2[i - x0.size() - x1.size()]]);
                continue;
            }
            else if (i - x0.size() - x1.size() - x2.size() < x3.size()){
                topPlayers.push_back(players[x3[i - x0.size() - x1.size() - x2.size()]]);
                continue;
            }
        }

        //Now we push people who didn't make top cut into the scrub vector.
        for (int i = topCut;; i++){
            if (i < (int)x0.size()){
                scrubs.push_back(players[x0[i]]);
                continue;
            }
            else if (i - x0.size() < x1.size()){
                scrubs.push_back(players[x1[i-(int)x0.size()]]);
                continue;
            }
            else if (i - x0.size() - x1.size() < x2.size()){
                scrubs.push_back(players[x2[i - x0.size() - x1.size()]]);
                continue;
            }
            else if (i - x0.size() - x1.size() - x2.size() < x3.size()){
                scrubs.push_back(players[x3[i - x0.size() - x1.size() - x2.size()]]);
                continue;
            }
            break;
        }
        //qDebug() << topPlayers.size();
        s(11);

        playersLeft = topPlayers;
    }
	//We now have our top cut inside a topPlayer vector of type player.
	//We will now simulate a single elimination top cut.
    if (!singleElim && !doubleElim){
        playersLeft = topPlayers;

    }
    vector<player> nextRound;
    //We now account for single elim.
    if (singleElim){
        playersLeft = players;
    }


	s(12);
    for (int k = 0; (int)playersLeft.size() > 1 || k == 0; k++){
        //qDebug() << (int)playersLeft.size();
		//cout << "k: " << k << " || Players left: " << playersLeft.size() << endl;
        for (int i = 0; i < (int)playersLeft.size()/2; i++){
            //qDebug() << playersLeft.size() << " || " << i;
            //Take note of their losses going in.  Guess could have used int / not void but whatever.
            int lossesA = playersLeft[i].currentLosses;
			duel(playersLeft[i], playersLeft[(int)playersLeft.size() - i - 1]);
            //qDebug() << "k: " << k;
            //playersLeft[i].printDecks();
            //qDebug() << QString::fromStdString(" ");
            //playersLeft[(int)playersLeft.size() - i - 1].printDecks();
            //qDebug() << QString::fromStdString("=========");
			if (lossesA == playersLeft[i].currentLosses){
				//Player b lost.  Player a advances.
                //qDebug() << QString::fromStdString("Player A loses.");
				nextRound.push_back(playersLeft[i]);
                if (result.size() == 0){
                    playersLeft[(int)playersLeft.size() - i - 1].placings.push_back((int)playersLeft.size());
                    playersLeft[(int)playersLeft.size() - i - 1].occurrences = 1;
					result.push_back(playersLeft[(int)playersLeft.size() - i - 1]);
					continue;
				}
				for (int j = 0; j < (int)result.size(); j++){
                    //qDebug() << j;
					if (playersLeft[(int)playersLeft.size() - i - 1].same(result[j])){
                        //qDebug() << result[j].wins;
                        result[j].placings.push_back((int)playersLeft.size());
						result[j].wins += playersLeft[(int)playersLeft.size() - i - 1].wins;
						result[j].losses += playersLeft[(int)playersLeft.size() - i - 1].losses;
                        result[j].occurrences++;
						break;
					}
					else if (j == result.size() - 1){
                        //qDebug() << "different";
                        playersLeft[(int)playersLeft.size() - i - 1].placings.push_back((int)playersLeft.size());
                        playersLeft[(int)playersLeft.size() - i - 1].occurrences = 1;
						result.push_back(playersLeft[(int)playersLeft.size() - i - 1]);
						break;
					}
				}
			}
			else{
				//Player a lost.
                //qDebug() << QString::fromStdString("Player B loses.");
				nextRound.push_back(playersLeft[(int)playersLeft.size() - i - 1]);
                if (result.size() == 0){
                    playersLeft[i].placings.push_back((int)playersLeft.size());
                    playersLeft[i].occurrences = 1;
					result.push_back(playersLeft[i]);
					continue;
				}
				for (int j = 0; j < (int)result.size(); j++){
                    if (playersLeft[i].same(result[j])){
                        result[j].placings.push_back((int)playersLeft.size());
						result[j].wins += playersLeft[i].wins;
						result[j].losses += playersLeft[i].losses;
                        result[j].occurrences++;
						break;
					}
					else if (j == result.size() - 1){
                        playersLeft[i].occurrences = 1;
                        playersLeft[i].placings.push_back((int)playersLeft.size());
						result.push_back(playersLeft[i]);
						break;
					}
				}
			}
            //qDebug() << "Result size: " << result.size();
		}
        //qDebug() << nextRound.size();
		playersLeft = nextRound;
		nextRound.clear();
    }
    //Push the winner into the placings bracket.
    for (int j = 0; j < (int)result.size(); j++){
        //qDebug() << j;
        //Keep syntax consistent and simple by adding i = 0;.
        int i = 0;
        if (playersLeft[(int)playersLeft.size() - i - 1].same(result[j])){
            //qDebug() << result[j].wins;
            result[j].placings.push_back((int)playersLeft.size());
            result[j].wins += playersLeft[(int)playersLeft.size() - i - 1].wins;
            result[j].losses += playersLeft[(int)playersLeft.size() - i - 1].losses;
            result[j].occurrences++;
            break;
        }
        else if (j == result.size() - 1){
            //qDebug() << "different";
            playersLeft[(int)playersLeft.size() - i - 1].placings.push_back((int)playersLeft.size());
            playersLeft[(int)playersLeft.size() - i - 1].occurrences = 1;
            result.push_back(playersLeft[(int)playersLeft.size() - i - 1]);
            break;
        }
    }

    //Add scrubs to results.
    for (int z = 0; z < (int)scrubs.size() && addScrubs; z++){
        for (int j = 0; j < (int)result.size(); j++){
            if (scrubs[z].same(result[j])){
                result[j].occurrences++;
                result[j].wins += scrubs[z].wins;
                result[j].losses += scrubs[z].losses;
                break;
            }
            else if (j == result.size() - 1){
                scrubs[z].occurrences++;
                result.push_back(scrubs[z]);
                break;
            }
        }
    }


    //Clear the scrubs vector as good housekeeping.
    scrubs.clear();

    //qDebug() << players.size();
	s(13);
	return;
}

void orderResults(){
    //This orders the results by tops / placings.
    //std::sort(result.begin(), result.end(), [](player a, player b){ return (int)a.placings.size() > (int)b.placings.size(); });
    //std::sort(result.begin(), result.end(), [](player a, player b){ return a.winRate() > b.winRate(); });
    std::sort(result.begin(), result.end(), [](player a, player b){ return a.topPercent() > b.topPercent(); });
}
