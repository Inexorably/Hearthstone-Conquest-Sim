//So we don't get bodied by a mispelling.
#ifndef GLOBALS
#define GLOBALS

#include <string>
#include <vector>
#include "structures.h"
#include <QString>

using namespace std;

extern vector<deck> possibleDecks;
extern int tourneySize;

//This is the vector mentioned before runSimulation();.  For each possible combination of decks we will record the placings and win rates of the deck./////
extern vector<player> result;

//This is the number of players that will make the top cut.  When equal to -1, the top cut will be generated automatically based on tourney size.//////////
extern int topCut;

//Best of what.
extern int bestOf;

extern bool addScrubs;


//Allows us to modify the tournament composition.
extern vector<player> bias;

//This function will be a bitch.
//Overloads let us cheat recursion.
void setWR(QString deckA, QString deckB, double wr);
void setWR(QString deckA, QString deckB, double wr, bool overloaded);
void setWRDefault(QString deckA, QString deckB);
void setWRDefault(QString deckB, QString deckA, bool overloaded);

extern const std::string md;
extern const std::string ad;
extern const std::string te;
extern const std::string fm;
extern const std::string sp;
extern const std::string mp;
extern const std::string cp;

extern const std::string as;
extern const std::string rl;
extern const std::string ml;
extern const std::string zl;
extern const std::string pw;

extern const std::string oi; //Apparently in qt or is a keyword.

extern std::vector<std::string> deckNames;

//The rate for a beating b in aVb.  Example: sp;
extern double spVmd;
extern double spVad;
extern double spVte;
extern double spVfm;
extern double spVmp;
extern double spVcp;
extern double spVor;
extern double spVas;
extern double spVrl;
extern double spVml;
extern double spVzl;
extern double spVpw;

extern double asVmd;
extern double asVad;
extern double asVfm;
extern double asVte;
extern double asVmp;
extern double asVsp;
extern double asVcp;
extern double asVor;
extern double asVml;
extern double asVzl;
extern double asVrl;
extern double asVpw;

extern double mdVad;
extern double mdVfm;
extern double mdVte;
extern double mdVmp;
extern double mdVsp;
extern double mdVcp;
extern double mdVor;
extern double mdVas;
extern double mdVml;
extern double mdVzl;
extern double mdVrl;
extern double mdVpw;

extern double rlVmd;
extern double rlVad;
extern double rlVfm;
extern double rlVte;
extern double rlVsp;
extern double rlVmp;
extern double rlVcp;
extern double rlVor;
extern double rlVas;
extern double rlVml;
extern double rlVzl;
extern double rlVpw;

extern double mpVmd;
extern double mpVad;
extern double mpVfm;
extern double mpVte;
extern double mpVsp;
extern double mpVcp;
extern double mpVor;
extern double mpVas;
extern double mpVml;
extern double mpVzl;
extern double mpVrl;
extern double mpVpw;

extern double orVmd;
extern double orVad;
extern double orVfm;
extern double orVte;
extern double orVmp;
extern double orVsp;
extern double orVcp;
extern double orVas;
extern double orVml;
extern double orVzl;
extern double orVrl;
extern double orVpw;

extern double pwVmd;
extern double pwVad;
extern double pwVte;
extern double pwVfm;
extern double pwVmp;
extern double pwVsp;
extern double pwVcp;
extern double pwVor;
extern double pwVas;
extern double pwVrl;
extern double pwVml;
extern double pwVzl;

extern double teVmd;
extern double teVad;
extern double teVfm;
extern double teVmp;
extern double teVsp;
extern double teVcp;
extern double teVor;
extern double teVas;
extern double teVml;
extern double teVzl;
extern double teVrl;
extern double teVpw;

extern double adVmd;
extern double adVfm;
extern double adVte;
extern double adVmp;
extern double adVsp;
extern double adVcp;
extern double adVor;
extern double adVas;
extern double adVml;
extern double adVzl;
extern double adVrl;
extern double adVpw;

extern double cpVmd;
extern double cpVad;
extern double cpVfm;
extern double cpVte;
extern double cpVmp;
extern double cpVsp;
extern double cpVor;
extern double cpVas;
extern double cpVml;
extern double cpVzl;
extern double cpVrl;
extern double cpVpw;

extern double fmVmd;
extern double fmVad;
extern double fmVte;
extern double fmVmp;
extern double fmVsp;
extern double fmVcp;
extern double fmVor;
extern double fmVas;
extern double fmVml;
extern double fmVzl;
extern double fmVrl;
extern double fmVpw;

extern double mlVmd;
extern double mlVad;
extern double mlVfm;
extern double mlVte;
extern double mlVmp;
extern double mlVsp;
extern double mlVcp;
extern double mlVor;
extern double mlVas;
extern double mlVzl;
extern double mlVrl;
extern double mlVpw;

extern double zlVmd;
extern double zlVad;
extern double zlVfm;
extern double zlVte;
extern double zlVmp;
extern double zlVsp;
extern double zlVcp;
extern double zlVor;
extern double zlVas;
extern double zlVml;
extern double zlVrl;
extern double zlVpw;

//E f f i c i e n c y B o y z
//We're going to store the default values of each of these so that the user can change the win rates.
extern double spVmdDefault;
extern double spVadDefault;
extern double spVteDefault;
extern double spVfmDefault;
extern double spVmpDefault;
extern double spVcpDefault;
extern double spVorDefault;
extern double spVasDefault;
extern double spVrlDefault;
extern double spVmlDefault;
extern double spVzlDefault;
extern double spVpwDefault;

extern double asVmdDefault;
extern double asVadDefault;
extern double asVfmDefault;
extern double asVteDefault;
extern double asVmpDefault;
extern double asVspDefault;
extern double asVcpDefault;
extern double asVorDefault;
extern double asVmlDefault;
extern double asVzlDefault;
extern double asVrlDefault;
extern double asVpwDefault;

extern double mdVadDefault;
extern double mdVfmDefault;
extern double mdVteDefault;
extern double mdVmpDefault;
extern double mdVspDefault;
extern double mdVcpDefault;
extern double mdVorDefault;
extern double mdVasDefault;
extern double mdVmlDefault;
extern double mdVzlDefault;
extern double mdVrlDefault;
extern double mdVpwDefault;

extern double rlVmdDefault;
extern double rlVadDefault;
extern double rlVfmDefault;
extern double rlVteDefault;
extern double rlVspDefault;
extern double rlVmpDefault;
extern double rlVcpDefault;
extern double rlVorDefault;
extern double rlVasDefault;
extern double rlVmlDefault;
extern double rlVzlDefault;
extern double rlVpwDefault;

extern double mpVmdDefault;
extern double mpVadDefault;
extern double mpVfmDefault;
extern double mpVteDefault;
extern double mpVspDefault;
extern double mpVcpDefault;
extern double mpVorDefault;
extern double mpVasDefault;
extern double mpVmlDefault;
extern double mpVzlDefault;
extern double mpVrlDefault;
extern double mpVpwDefault;

extern double orVmdDefault;
extern double orVadDefault;
extern double orVfmDefault;
extern double orVteDefault;
extern double orVmpDefault;
extern double orVspDefault;
extern double orVcpDefault;
extern double orVasDefault;
extern double orVmlDefault;
extern double orVzlDefault;
extern double orVrlDefault;
extern double orVpwDefault;

extern double pwVmdDefault;
extern double pwVadDefault;
extern double pwVteDefault;
extern double pwVfmDefault;
extern double pwVmpDefault;
extern double pwVspDefault;
extern double pwVcpDefault;
extern double pwVorDefault;
extern double pwVasDefault;
extern double pwVrlDefault;
extern double pwVmlDefault;
extern double pwVzlDefault;

extern double teVmdDefault;
extern double teVadDefault;
extern double teVfmDefault;
extern double teVmpDefault;
extern double teVspDefault;
extern double teVcpDefault;
extern double teVorDefault;
extern double teVasDefault;
extern double teVmlDefault;
extern double teVzlDefault;
extern double teVrlDefault;
extern double teVpwDefault;

extern double adVmdDefault;
extern double adVfmDefault;
extern double adVteDefault;
extern double adVmpDefault;
extern double adVspDefault;
extern double adVcpDefault;
extern double adVorDefault;
extern double adVasDefault;
extern double adVmlDefault;
extern double adVzlDefault;
extern double adVrlDefault;
extern double adVpwDefault;

extern double cpVmdDefault;
extern double cpVadDefault;
extern double cpVfmDefault;
extern double cpVteDefault;
extern double cpVmpDefault;
extern double cpVspDefault;
extern double cpVorDefault;
extern double cpVasDefault;
extern double cpVmlDefault;
extern double cpVzlDefault;
extern double cpVrlDefault;
extern double cpVpwDefault;

extern double fmVmdDefault;
extern double fmVadDefault;
extern double fmVteDefault;
extern double fmVmpDefault;
extern double fmVspDefault;
extern double fmVcpDefault;
extern double fmVorDefault;
extern double fmVasDefault;
extern double fmVmlDefault;
extern double fmVzlDefault;
extern double fmVrlDefault;
extern double fmVpwDefault;

extern double mlVmdDefault;
extern double mlVadDefault;
extern double mlVfmDefault;
extern double mlVteDefault;
extern double mlVmpDefault;
extern double mlVspDefault;
extern double mlVcpDefault;
extern double mlVorDefault;
extern double mlVasDefault;
extern double mlVzlDefault;
extern double mlVrlDefault;
extern double mlVpwDefault;

extern double zlVmdDefault;
extern double zlVadDefault;
extern double zlVfmDefault;
extern double zlVteDefault;
extern double zlVmpDefault;
extern double zlVspDefault;
extern double zlVcpDefault;
extern double zlVorDefault;
extern double zlVasDefault;
extern double zlVmlDefault;
extern double zlVrlDefault;
extern double zlVpwDefault;

#endif //GLOBALS
