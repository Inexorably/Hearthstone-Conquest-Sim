#include "globals.h"

using namespace std;

vector<deck> possibleDecks;
int tourneySize = 400;

//This is the vector mentioned before runSimulation();.  For each possible combination of decks we will record the placings and win rates of the deck./////
vector<player> result;

//This is the number of players that will make the top cut.  When equal to -1, the top cut will be generated automatically based on tourney size.//////////
int topCut = -1;

//Best of what.
int bestOf = 5;

bool addScrubs = true;

bool singleElim = false;
bool doubleElim = false;

//Sets the win rate between two decks to default value.
void setWRDefault(QString deckA, QString deckB){
    setWRDefault(deckB, deckA, true);
    //We used std::string not qstring for our globals as ported from vs.
    std::string a = deckA.toStdString();
    std::string b = deckB.toStdString();

    //Won't happen.  Here to stop compiler complaining.
    if (a == b)
        return;

    if (a == sp){
        if (b == md)
            spVmd = spVmdDefault;
        if (b == ad)
            spVad = spVadDefault;
        if (b == te)
            spVte = spVteDefault;
        if (b == fm)
            spVfm = spVfmDefault;
        if (b == mp)
            spVmp = spVmpDefault;
        if (b == cp)
            spVcp = spVcpDefault;
        if (b == oi)
            spVor = spVorDefault;
        if (b == as)
            spVas = spVasDefault;
        if (b == rl)
            spVrl = spVrlDefault;
        if (b == ml)
            spVml = spVmlDefault;
        if (b == zl)
            spVzl = spVzlDefault;
        if (b == pw)
            spVpw = spVpwDefault;
    }
    else if (a == as){
        if (b == md)
            asVmd = asVmdDefault;
        if (b == ad)
            asVad = asVadDefault;
        if (b == te)
            asVte = asVteDefault;
        if (b == fm)
            asVfm = asVfmDefault;
        if (b == mp)
            asVmp = asVmpDefault;
        if (b == cp)
            asVcp = asVcpDefault;
        if (b == oi)
            asVor = asVorDefault;
        if (b == sp)
            asVsp = asVspDefault;
        if (b == rl)
            asVrl = asVrlDefault;
        if (b == ml)
            asVml = asVmlDefault;
        if (b == zl)
            asVzl = asVzlDefault;
        if (b == pw)
            asVpw = asVpwDefault;
    }
    else if (a == md){
        if (b == as)
            mdVas = mdVasDefault;
        if (b == ad)
            mdVad = mdVadDefault;
        if (b == te)
            mdVte = mdVteDefault;
        if (b == fm)
            mdVfm = mdVfmDefault;
        if (b == mp)
            mdVmp = mdVmpDefault;
        if (b == cp)
            mdVcp = mdVcpDefault;
        if (b == oi)
            mdVor = mdVorDefault;
        if (b == sp)
            mdVsp = mdVspDefault;
        if (b == rl)
            mdVrl = mdVrlDefault;
        if (b == ml)
            mdVml = mdVmlDefault;
        if (b == zl)
            mdVzl = mdVzlDefault;
        if (b == pw)
            mdVpw = mdVpwDefault;
    }
    else if (a == rl){
        if (b == as)
            rlVas = rlVasDefault;
        if (b == ad)
            rlVad = rlVadDefault;
        if (b == te)
            rlVte = rlVteDefault;
        if (b == fm)
            rlVfm = rlVfmDefault;
        if (b == mp)
            rlVmp = rlVmpDefault;
        if (b == cp)
            rlVcp = rlVcpDefault;
        if (b == oi)
            rlVor = rlVorDefault;
        if (b == sp)
            rlVsp = rlVspDefault;
        if (b == md)
            rlVmd = rlVmdDefault;
        if (b == ml)
            rlVml = rlVmlDefault;
        if (b == zl)
            rlVzl = rlVzlDefault;
        if (b == pw)
            rlVpw = rlVpwDefault;
    }
    else if (a == mp){
        if (b == as)
            mpVas = mpVasDefault;
        if (b == ad)
            mpVad = mpVadDefault;
        if (b == te)
            mpVte = mpVteDefault;
        if (b == fm)
            mpVfm = mpVfmDefault;
        if (b == rl)
            mpVrl = mpVrlDefault;
        if (b == cp)
            mpVcp = mpVcpDefault;
        if (b == oi)
            mpVor = mpVorDefault;
        if (b == sp)
            mpVsp = mpVspDefault;
        if (b == md)
            mpVmd = mpVmdDefault;
        if (b == ml)
            mpVml = mpVmlDefault;
        if (b == zl)
            mpVzl = mpVzlDefault;
        if (b == pw)
            mpVpw = mpVpwDefault;
    }
    else if (a == oi){
        if (b == as)
            orVas = orVasDefault;
        if (b == ad)
            orVad = orVadDefault;
        if (b == te)
            orVte = orVteDefault;
        if (b == fm)
            orVfm = orVfmDefault;
        if (b == rl)
            orVrl = orVrlDefault;
        if (b == cp)
            orVcp = orVcpDefault;
        if (b == mp)
            orVmp = orVmpDefault;
        if (b == sp)
            orVsp = orVspDefault;
        if (b == md)
            orVmd = orVmdDefault;
        if (b == ml)
            orVml = orVmlDefault;
        if (b == zl)
            orVzl = orVzlDefault;
        if (b == pw)
            orVpw = orVpwDefault;
    }
    else if (a == pw){
        if (b == as)
            pwVas = pwVasDefault;
        if (b == ad)
            pwVad = pwVadDefault;
        if (b == te)
            pwVte = pwVteDefault;
        if (b == fm)
            pwVfm = pwVfmDefault;
        if (b == rl)
            pwVrl = pwVrlDefault;
        if (b == cp)
            pwVcp = pwVcpDefault;
        if (b == mp)
            pwVmp = pwVmpDefault;
        if (b == sp)
            pwVsp = pwVspDefault;
        if (b == md)
            pwVmd = pwVmdDefault;
        if (b == ml)
            pwVml = pwVmlDefault;
        if (b == zl)
            pwVzl = pwVzlDefault;
        if (b == oi)
            pwVor = pwVorDefault;
    }
    else if (a == te){
        if (b == as)
            teVas = teVasDefault;
        if (b == ad)
            teVad = teVadDefault;
        if (b == pw)
            teVpw = teVpwDefault;
        if (b == fm)
            teVfm = teVfmDefault;
        if (b == rl)
            teVrl = teVrlDefault;
        if (b == cp)
            teVcp = teVcpDefault;
        if (b == mp)
            teVmp = teVmpDefault;
        if (b == sp)
            teVsp = teVspDefault;
        if (b == md)
            teVmd = teVmdDefault;
        if (b == ml)
            teVml = teVmlDefault;
        if (b == zl)
            teVzl = teVzlDefault;
        if (b == oi)
            teVor = teVorDefault;
    }
    else if (a == ad){
        if (b == as)
            adVas = adVasDefault;
        if (b == te)
            adVte = adVteDefault;
        if (b == pw)
            adVpw = adVpwDefault;
        if (b == fm)
            adVfm = adVfmDefault;
        if (b == rl)
            adVrl = adVrlDefault;
        if (b == cp)
            adVcp = adVcpDefault;
        if (b == mp)
            adVmp = adVmpDefault;
        if (b == sp)
            adVsp = adVspDefault;
        if (b == md)
            adVmd = adVmdDefault;
        if (b == ml)
            adVml = adVmlDefault;
        if (b == zl)
            adVzl = adVzlDefault;
        if (b == oi)
            adVor = adVorDefault;
    }
    else if (a == cp){
        if (b == as)
            cpVas = cpVasDefault;
        if (b == te)
            cpVte = cpVteDefault;
        if (b == pw)
            cpVpw = cpVpwDefault;
        if (b == fm)
            cpVfm = cpVfmDefault;
        if (b == rl)
            cpVrl = cpVrlDefault;
        if (b == ad)
            cpVad = cpVadDefault;
        if (b == mp)
            cpVmp = cpVmpDefault;
        if (b == sp)
            cpVsp = cpVspDefault;
        if (b == md)
            cpVmd = cpVmdDefault;
        if (b == ml)
            cpVml = cpVmlDefault;
        if (b == zl)
            cpVzl = cpVzlDefault;
        if (b == oi)
            cpVor = cpVorDefault;
    }
    else if (a == fm){
        if (b == as)
            fmVas = fmVasDefault;
        if (b == te)
            fmVte = fmVteDefault;
        if (b == pw)
            fmVpw = fmVpwDefault;
        if (b == cp)
            fmVcp = fmVcpDefault;
        if (b == rl)
            fmVrl = fmVrlDefault;
        if (b == ad)
            fmVad = fmVadDefault;
        if (b == mp)
            fmVmp = fmVmpDefault;
        if (b == sp)
            fmVsp = fmVspDefault;
        if (b == md)
            fmVmd = fmVmdDefault;
        if (b == ml)
            fmVml = fmVmlDefault;
        if (b == zl)
            fmVzl = fmVzlDefault;
        if (b == oi)
            fmVor = fmVorDefault;
    }
    else if (a == ml){
           if (b == as)
            mlVas = mlVasDefault;
        if (b == te)
            mlVte = mlVteDefault;
        if (b == pw)
            mlVpw = mlVpwDefault;
        if (b == cp)
            mlVcp = mlVcpDefault;
        if (b == rl)
            mlVrl = mlVrlDefault;
        if (b == ad)
            mlVad = mlVadDefault;
        if (b == mp)
            mlVmp = mlVmpDefault;
        if (b == sp)
            mlVsp = mlVspDefault;
        if (b == md)
            mlVmd = mlVmdDefault;
        if (b == fm)
            mlVfm = mlVfmDefault;
        if (b == zl)
            mlVzl = mlVzlDefault;
        if (b == oi)
            mlVor = mlVorDefault;
    }
    else if (a == zl){
        if (b == as)
            zlVas = zlVasDefault;
        if (b == te)
            zlVte = zlVteDefault;
        if (b == pw)
            zlVpw = zlVpwDefault;
        if (b == cp)
            zlVcp = zlVcpDefault;
        if (b == rl)
            zlVrl = zlVrlDefault;
        if (b == ad)
            zlVad = zlVadDefault;
        if (b == mp)
            zlVmp = zlVmpDefault;
        if (b == sp)
            zlVsp = zlVspDefault;
        if (b == md)
            zlVmd = zlVmdDefault;
        if (b == fm)
            zlVfm = zlVfmDefault;
        if (b == ml)
            zlVml = zlVmlDefault;
        if (b == oi)
            zlVor = zlVorDefault;
    }
}

//Evil overloaded cousin.
void setWRDefault(QString deckA, QString deckB, bool overloaded){
    if (!overloaded)
        return;
    //We used std::string not qstring for our globals as ported from vs.
    std::string a = deckA.toStdString();
    std::string b = deckB.toStdString();

    //Won't happen.  Here to stop compiler complaining.
    if (a == b)
        return;

    if (a == sp){
        if (b == md)
            spVmd = spVmdDefault;
        if (b == ad)
            spVad = spVadDefault;
        if (b == te)
            spVte = spVteDefault;
        if (b == fm)
            spVfm = spVfmDefault;
        if (b == mp)
            spVmp = spVmpDefault;
        if (b == cp)
            spVcp = spVcpDefault;
        if (b == oi)
            spVor = spVorDefault;
        if (b == as)
            spVas = spVasDefault;
        if (b == rl)
            spVrl = spVrlDefault;
        if (b == ml)
            spVml = spVmlDefault;
        if (b == zl)
            spVzl = spVzlDefault;
        if (b == pw)
            spVpw = spVpwDefault;
    }
    else if (a == as){
        if (b == md)
            asVmd = asVmdDefault;
        if (b == ad)
            asVad = asVadDefault;
        if (b == te)
            asVte = asVteDefault;
        if (b == fm)
            asVfm = asVfmDefault;
        if (b == mp)
            asVmp = asVmpDefault;
        if (b == cp)
            asVcp = asVcpDefault;
        if (b == oi)
            asVor = asVorDefault;
        if (b == sp)
            asVsp = asVspDefault;
        if (b == rl)
            asVrl = asVrlDefault;
        if (b == ml)
            asVml = asVmlDefault;
        if (b == zl)
            asVzl = asVzlDefault;
        if (b == pw)
            asVpw = asVpwDefault;
    }
    else if (a == md){
        if (b == as)
            mdVas = mdVasDefault;
        if (b == ad)
            mdVad = mdVadDefault;
        if (b == te)
            mdVte = mdVteDefault;
        if (b == fm)
            mdVfm = mdVfmDefault;
        if (b == mp)
            mdVmp = mdVmpDefault;
        if (b == cp)
            mdVcp = mdVcpDefault;
        if (b == oi)
            mdVor = mdVorDefault;
        if (b == sp)
            mdVsp = mdVspDefault;
        if (b == rl)
            mdVrl = mdVrlDefault;
        if (b == ml)
            mdVml = mdVmlDefault;
        if (b == zl)
            mdVzl = mdVzlDefault;
        if (b == pw)
            mdVpw = mdVpwDefault;
    }
    else if (a == rl){
        if (b == as)
            rlVas = rlVasDefault;
        if (b == ad)
            rlVad = rlVadDefault;
        if (b == te)
            rlVte = rlVteDefault;
        if (b == fm)
            rlVfm = rlVfmDefault;
        if (b == mp)
            rlVmp = rlVmpDefault;
        if (b == cp)
            rlVcp = rlVcpDefault;
        if (b == oi)
            rlVor = rlVorDefault;
        if (b == sp)
            rlVsp = rlVspDefault;
        if (b == md)
            rlVmd = rlVmdDefault;
        if (b == ml)
            rlVml = rlVmlDefault;
        if (b == zl)
            rlVzl = rlVzlDefault;
        if (b == pw)
            rlVpw = rlVpwDefault;
    }
    else if (a == mp){
        if (b == as)
            mpVas = mpVasDefault;
        if (b == ad)
            mpVad = mpVadDefault;
        if (b == te)
            mpVte = mpVteDefault;
        if (b == fm)
            mpVfm = mpVfmDefault;
        if (b == rl)
            mpVrl = mpVrlDefault;
        if (b == cp)
            mpVcp = mpVcpDefault;
        if (b == oi)
            mpVor = mpVorDefault;
        if (b == sp)
            mpVsp = mpVspDefault;
        if (b == md)
            mpVmd = mpVmdDefault;
        if (b == ml)
            mpVml = mpVmlDefault;
        if (b == zl)
            mpVzl = mpVzlDefault;
        if (b == pw)
            mpVpw = mpVpwDefault;
    }
    else if (a == oi){
        if (b == as)
            orVas = orVasDefault;
        if (b == ad)
            orVad = orVadDefault;
        if (b == te)
            orVte = orVteDefault;
        if (b == fm)
            orVfm = orVfmDefault;
        if (b == rl)
            orVrl = orVrlDefault;
        if (b == cp)
            orVcp = orVcpDefault;
        if (b == mp)
            orVmp = orVmpDefault;
        if (b == sp)
            orVsp = orVspDefault;
        if (b == md)
            orVmd = orVmdDefault;
        if (b == ml)
            orVml = orVmlDefault;
        if (b == zl)
            orVzl = orVzlDefault;
        if (b == pw)
            orVpw = orVpwDefault;
    }
    else if (a == pw){
        if (b == as)
            pwVas = pwVasDefault;
        if (b == ad)
            pwVad = pwVadDefault;
        if (b == te)
            pwVte = pwVteDefault;
        if (b == fm)
            pwVfm = pwVfmDefault;
        if (b == rl)
            pwVrl = pwVrlDefault;
        if (b == cp)
            pwVcp = pwVcpDefault;
        if (b == mp)
            pwVmp = pwVmpDefault;
        if (b == sp)
            pwVsp = pwVspDefault;
        if (b == md)
            pwVmd = pwVmdDefault;
        if (b == ml)
            pwVml = pwVmlDefault;
        if (b == zl)
            pwVzl = pwVzlDefault;
        if (b == oi)
            pwVor = pwVorDefault;
    }
    else if (a == te){
        if (b == as)
            teVas = teVasDefault;
        if (b == ad)
            teVad = teVadDefault;
        if (b == pw)
            teVpw = teVpwDefault;
        if (b == fm)
            teVfm = teVfmDefault;
        if (b == rl)
            teVrl = teVrlDefault;
        if (b == cp)
            teVcp = teVcpDefault;
        if (b == mp)
            teVmp = teVmpDefault;
        if (b == sp)
            teVsp = teVspDefault;
        if (b == md)
            teVmd = teVmdDefault;
        if (b == ml)
            teVml = teVmlDefault;
        if (b == zl)
            teVzl = teVzlDefault;
        if (b == oi)
            teVor = teVorDefault;
    }
    else if (a == ad){
        if (b == as)
            adVas = adVasDefault;
        if (b == te)
            adVte = adVteDefault;
        if (b == pw)
            adVpw = adVpwDefault;
        if (b == fm)
            adVfm = adVfmDefault;
        if (b == rl)
            adVrl = adVrlDefault;
        if (b == cp)
            adVcp = adVcpDefault;
        if (b == mp)
            adVmp = adVmpDefault;
        if (b == sp)
            adVsp = adVspDefault;
        if (b == md)
            adVmd = adVmdDefault;
        if (b == ml)
            adVml = adVmlDefault;
        if (b == zl)
            adVzl = adVzlDefault;
        if (b == oi)
            adVor = adVorDefault;
    }
    else if (a == cp){
        if (b == as)
            cpVas = cpVasDefault;
        if (b == te)
            cpVte = cpVteDefault;
        if (b == pw)
            cpVpw = cpVpwDefault;
        if (b == fm)
            cpVfm = cpVfmDefault;
        if (b == rl)
            cpVrl = cpVrlDefault;
        if (b == ad)
            cpVad = cpVadDefault;
        if (b == mp)
            cpVmp = cpVmpDefault;
        if (b == sp)
            cpVsp = cpVspDefault;
        if (b == md)
            cpVmd = cpVmdDefault;
        if (b == ml)
            cpVml = cpVmlDefault;
        if (b == zl)
            cpVzl = cpVzlDefault;
        if (b == oi)
            cpVor = cpVorDefault;
    }
    else if (a == fm){
        if (b == as)
            fmVas = fmVasDefault;
        if (b == te)
            fmVte = fmVteDefault;
        if (b == pw)
            fmVpw = fmVpwDefault;
        if (b == cp)
            fmVcp = fmVcpDefault;
        if (b == rl)
            fmVrl = fmVrlDefault;
        if (b == ad)
            fmVad = fmVadDefault;
        if (b == mp)
            fmVmp = fmVmpDefault;
        if (b == sp)
            fmVsp = fmVspDefault;
        if (b == md)
            fmVmd = fmVmdDefault;
        if (b == ml)
            fmVml = fmVmlDefault;
        if (b == zl)
            fmVzl = fmVzlDefault;
        if (b == oi)
            fmVor = fmVorDefault;
    }
    else if (a == ml){
           if (b == as)
            mlVas = mlVasDefault;
        if (b == te)
            mlVte = mlVteDefault;
        if (b == pw)
            mlVpw = mlVpwDefault;
        if (b == cp)
            mlVcp = mlVcpDefault;
        if (b == rl)
            mlVrl = mlVrlDefault;
        if (b == ad)
            mlVad = mlVadDefault;
        if (b == mp)
            mlVmp = mlVmpDefault;
        if (b == sp)
            mlVsp = mlVspDefault;
        if (b == md)
            mlVmd = mlVmdDefault;
        if (b == fm)
            mlVfm = mlVfmDefault;
        if (b == zl)
            mlVzl = mlVzlDefault;
        if (b == oi)
            mlVor = mlVorDefault;
    }
    else if (a == zl){
        if (b == as)
            zlVas = zlVasDefault;
        if (b == te)
            zlVte = zlVteDefault;
        if (b == pw)
            zlVpw = zlVpwDefault;
        if (b == cp)
            zlVcp = zlVcpDefault;
        if (b == rl)
            zlVrl = zlVrlDefault;
        if (b == ad)
            zlVad = zlVadDefault;
        if (b == mp)
            zlVmp = zlVmpDefault;
        if (b == sp)
            zlVsp = zlVspDefault;
        if (b == md)
            zlVmd = zlVmdDefault;
        if (b == fm)
            zlVfm = zlVfmDefault;
        if (b == ml)
            zlVml = zlVmlDefault;
        if (b == oi)
            zlVor = zlVorDefault;
    }
}

void setWR(QString deckA, QString deckB, double wr){
    //We set the inverse matchups data.
    setWR(deckB, deckA, 1 - wr, true);

    //We used std::string not qstring for our globals as ported from vs.
    std::string a = deckA.toStdString();
    std::string b = deckB.toStdString();

    if (a == b)
        return;
    if (a == sp){
        if (b == md)
            spVmd = wr;
        if (b == ad)
            spVad = wr;
        if (b == te)
            spVte = wr;
        if (b == fm)
            spVfm = wr;
        if (b == mp)
            spVmp = wr;
        if (b == cp)
            spVcp = wr;
        if (b == oi)
            spVor = wr;
        if (b == as)
            spVas = wr;
        if (b == rl)
            spVrl = wr;
        if (b == ml)
            spVml = wr;
        if (b == zl)
            spVzl = wr;
        if (b == pw)
            spVpw = wr;
    }
    else if (a == as){
        if (b == md)
            asVmd = wr;
        if (b == ad)
            asVad = wr;
        if (b == te)
            asVte = wr;
        if (b == fm)
            asVfm = wr;
        if (b == mp)
            asVmp = wr;
        if (b == cp)
            asVcp = wr;
        if (b == oi)
            asVor = wr;
        if (b == sp)
            asVsp = wr;
        if (b == rl)
            asVrl = wr;
        if (b == ml)
            asVml = wr;
        if (b == zl)
            asVzl = wr;
        if (b == pw)
            asVpw = wr;
    }
    else if (a == md){
        if (b == as)
            mdVas = wr;
        if (b == ad)
            mdVad = wr;
        if (b == te)
            mdVte = wr;
        if (b == fm)
            mdVfm = wr;
        if (b == mp)
            mdVmp = wr;
        if (b == cp)
            mdVcp = wr;
        if (b == oi)
            mdVor = wr;
        if (b == sp)
            mdVsp = wr;
        if (b == rl)
            mdVrl = wr;
        if (b == ml)
            mdVml = wr;
        if (b == zl)
            mdVzl = wr;
        if (b == pw)
            mdVpw = wr;
    }
    else if (a == rl){
        if (b == as)
            rlVas = wr;
        if (b == ad)
            rlVad = wr;
        if (b == te)
            rlVte = wr;
        if (b == fm)
            rlVfm = wr;
        if (b == mp)
            rlVmp = wr;
        if (b == cp)
            rlVcp = wr;
        if (b == oi)
            rlVor = wr;
        if (b == sp)
            rlVsp = wr;
        if (b == md)
            rlVmd = wr;
        if (b == ml)
            rlVml = wr;
        if (b == zl)
            rlVzl = wr;
        if (b == pw)
            rlVpw = wr;
    }
    else if (a == mp){
        if (b == as)
            mpVas = wr;
        if (b == ad)
            mpVad = wr;
        if (b == te)
            mpVte = wr;
        if (b == fm)
            mpVfm = wr;
        if (b == rl)
            mpVrl = wr;
        if (b == cp)
            mpVcp = wr;
        if (b == oi)
            mpVor = wr;
        if (b == sp)
            mpVsp = wr;
        if (b == md)
            mpVmd = wr;
        if (b == ml)
            mpVml = wr;
        if (b == zl)
            mpVzl = wr;
        if (b == pw)
            mpVpw = wr;
    }
    else if (a == oi){
        if (b == as)
            orVas = wr;
        if (b == ad)
            orVad = wr;
        if (b == te)
            orVte = wr;
        if (b == fm)
            orVfm = wr;
        if (b == rl)
            orVrl = wr;
        if (b == cp)
            orVcp = wr;
        if (b == mp)
            orVmp = wr;
        if (b == sp)
            orVsp = wr;
        if (b == md)
            orVmd = wr;
        if (b == ml)
            orVml = wr;
        if (b == zl)
            orVzl = wr;
        if (b == pw)
            orVpw = wr;
    }
    else if (a == pw){
        if (b == as)
            pwVas = wr;
        if (b == ad)
            pwVad = wr;
        if (b == te)
            pwVte = wr;
        if (b == fm)
            pwVfm = wr;
        if (b == rl)
            pwVrl = wr;
        if (b == cp)
            pwVcp = wr;
        if (b == mp)
            pwVmp = wr;
        if (b == sp)
            pwVsp = wr;
        if (b == md)
            pwVmd = wr;
        if (b == ml)
            pwVml = wr;
        if (b == zl)
            pwVzl = wr;
        if (b == oi)
            pwVor = wr;
    }
    else if (a == te){
        if (b == as)
            teVas = wr;
        if (b == ad)
            teVad = wr;
        if (b == pw)
            teVpw = wr;
        if (b == fm)
            teVfm = wr;
        if (b == rl)
            teVrl = wr;
        if (b == cp)
            teVcp = wr;
        if (b == mp)
            teVmp = wr;
        if (b == sp)
            teVsp = wr;
        if (b == md)
            teVmd = wr;
        if (b == ml)
            teVml = wr;
        if (b == zl)
            teVzl = wr;
        if (b == oi)
            teVor = wr;
    }
    else if (a == ad){
        if (b == as)
            adVas = wr;
        if (b == te)
            adVte = wr;
        if (b == pw)
            adVpw = wr;
        if (b == fm)
            adVfm = wr;
        if (b == rl)
            adVrl = wr;
        if (b == cp)
            adVcp = wr;
        if (b == mp)
            adVmp = wr;
        if (b == sp)
            adVsp = wr;
        if (b == md)
            adVmd = wr;
        if (b == ml)
            adVml = wr;
        if (b == zl)
            adVzl = wr;
        if (b == oi)
            adVor = wr;
    }
    else if (a == cp){
        if (b == as)
            cpVas = wr;
        if (b == te)
            cpVte = wr;
        if (b == pw)
            cpVpw = wr;
        if (b == fm)
            cpVfm = wr;
        if (b == rl)
            cpVrl = wr;
        if (b == ad)
            cpVad = wr;
        if (b == mp)
            cpVmp = wr;
        if (b == sp)
            cpVsp = wr;
        if (b == md)
            cpVmd = wr;
        if (b == ml)
            cpVml = wr;
        if (b == zl)
            cpVzl = wr;
        if (b == oi)
            cpVor = wr;
    }
    else if (a == fm){
        if (b == as)
            fmVas = wr;
        if (b == te)
            fmVte = wr;
        if (b == pw)
            fmVpw = wr;
        if (b == cp)
            fmVcp = wr;
        if (b == rl)
            fmVrl = wr;
        if (b == ad)
            fmVad = wr;
        if (b == mp)
            fmVmp = wr;
        if (b == sp)
            fmVsp = wr;
        if (b == md)
            fmVmd = wr;
        if (b == ml)
            fmVml = wr;
        if (b == zl)
            fmVzl = wr;
        if (b == oi)
            fmVor = wr;
    }
    else if (a == ml){
        if (b == as)
            mlVas = wr;
        if (b == te)
            mlVte = wr;
        if (b == pw)
            mlVpw = wr;
        if (b == cp)
            mlVcp = wr;
        if (b == rl)
            mlVrl = wr;
        if (b == ad)
            mlVad = wr;
        if (b == mp)
            mlVmp = wr;
        if (b == sp)
            mlVsp = wr;
        if (b == md)
            mlVmd = wr;
        if (b == fm)
            mlVfm = wr;
        if (b == zl)
            mlVzl = wr;
        if (b == oi)
            mlVor = wr;
    }
    else if (a == zl){
        if (b == as)
            zlVas = wr;
        if (b == te)
            zlVte = wr;
        if (b == pw)
            zlVpw = wr;
        if (b == cp)
            zlVcp = wr;
        if (b == rl)
            zlVrl = wr;
        if (b == ad)
            zlVad = wr;
        if (b == mp)
            zlVmp = wr;
        if (b == sp)
            zlVsp = wr;
        if (b == md)
            zlVmd = wr;
        if (b == fm)
            zlVfm = wr;
        if (b == ml)
            zlVml = wr;
        if (b == oi)
            zlVor = wr;
    }
}

void setWR(QString deckA, QString deckB, double wr, bool overloaded){
    if (!overloaded)
        return;
    //Overload of the function.
    //We used std::string not qstring for our globals as ported from vs.
    std::string a = deckA.toStdString();
    std::string b = deckB.toStdString();

    if (a == b)
        return;
    if (a == sp){
        if (b == md)
            spVmd = wr;
        if (b == ad)
            spVad = wr;
        if (b == te)
            spVte = wr;
        if (b == fm)
            spVfm = wr;
        if (b == mp)
            spVmp = wr;
        if (b == cp)
            spVcp = wr;
        if (b == oi)
            spVor = wr;
        if (b == as)
            spVas = wr;
        if (b == rl)
            spVrl = wr;
        if (b == ml)
            spVml = wr;
        if (b == zl)
            spVzl = wr;
        if (b == pw)
            spVpw = wr;
    }
    else if (a == as){
        if (b == md)
            asVmd = wr;
        if (b == ad)
            asVad = wr;
        if (b == te)
            asVte = wr;
        if (b == fm)
            asVfm = wr;
        if (b == mp)
            asVmp = wr;
        if (b == cp)
            asVcp = wr;
        if (b == oi)
            asVor = wr;
        if (b == sp)
            asVsp = wr;
        if (b == rl)
            asVrl = wr;
        if (b == ml)
            asVml = wr;
        if (b == zl)
            asVzl = wr;
        if (b == pw)
            asVpw = wr;
    }
    else if (a == md){
        if (b == as)
            mdVas = wr;
        if (b == ad)
            mdVad = wr;
        if (b == te)
            mdVte = wr;
        if (b == fm)
            mdVfm = wr;
        if (b == mp)
            mdVmp = wr;
        if (b == cp)
            mdVcp = wr;
        if (b == oi)
            mdVor = wr;
        if (b == sp)
            mdVsp = wr;
        if (b == rl)
            mdVrl = wr;
        if (b == ml)
            mdVml = wr;
        if (b == zl)
            mdVzl = wr;
        if (b == pw)
            mdVpw = wr;
    }
    else if (a == rl){
        if (b == as)
            rlVas = wr;
        if (b == ad)
            rlVad = wr;
        if (b == te)
            rlVte = wr;
        if (b == fm)
            rlVfm = wr;
        if (b == mp)
            rlVmp = wr;
        if (b == cp)
            rlVcp = wr;
        if (b == oi)
            rlVor = wr;
        if (b == sp)
            rlVsp = wr;
        if (b == md)
            rlVmd = wr;
        if (b == ml)
            rlVml = wr;
        if (b == zl)
            rlVzl = wr;
        if (b == pw)
            rlVpw = wr;
    }
    else if (a == mp){
        if (b == as)
            mpVas = wr;
        if (b == ad)
            mpVad = wr;
        if (b == te)
            mpVte = wr;
        if (b == fm)
            mpVfm = wr;
        if (b == rl)
            mpVrl = wr;
        if (b == cp)
            mpVcp = wr;
        if (b == oi)
            mpVor = wr;
        if (b == sp)
            mpVsp = wr;
        if (b == md)
            mpVmd = wr;
        if (b == ml)
            mpVml = wr;
        if (b == zl)
            mpVzl = wr;
        if (b == pw)
            mpVpw = wr;
    }
    else if (a == oi){
        if (b == as)
            orVas = wr;
        if (b == ad)
            orVad = wr;
        if (b == te)
            orVte = wr;
        if (b == fm)
            orVfm = wr;
        if (b == rl)
            orVrl = wr;
        if (b == cp)
            orVcp = wr;
        if (b == mp)
            orVmp = wr;
        if (b == sp)
            orVsp = wr;
        if (b == md)
            orVmd = wr;
        if (b == ml)
            orVml = wr;
        if (b == zl)
            orVzl = wr;
        if (b == pw)
            orVpw = wr;
    }
    else if (a == pw){
        if (b == as)
            pwVas = wr;
        if (b == ad)
            pwVad = wr;
        if (b == te)
            pwVte = wr;
        if (b == fm)
            pwVfm = wr;
        if (b == rl)
            pwVrl = wr;
        if (b == cp)
            pwVcp = wr;
        if (b == mp)
            pwVmp = wr;
        if (b == sp)
            pwVsp = wr;
        if (b == md)
            pwVmd = wr;
        if (b == ml)
            pwVml = wr;
        if (b == zl)
            pwVzl = wr;
        if (b == oi)
            pwVor = wr;
    }
    else if (a == te){
        if (b == as)
            teVas = wr;
        if (b == ad)
            teVad = wr;
        if (b == pw)
            teVpw = wr;
        if (b == fm)
            teVfm = wr;
        if (b == rl)
            teVrl = wr;
        if (b == cp)
            teVcp = wr;
        if (b == mp)
            teVmp = wr;
        if (b == sp)
            teVsp = wr;
        if (b == md)
            teVmd = wr;
        if (b == ml)
            teVml = wr;
        if (b == zl)
            teVzl = wr;
        if (b == oi)
            teVor = wr;
    }
    else if (a == ad){
        if (b == as)
            adVas = wr;
        if (b == te)
            adVte = wr;
        if (b == pw)
            adVpw = wr;
        if (b == fm)
            adVfm = wr;
        if (b == rl)
            adVrl = wr;
        if (b == cp)
            adVcp = wr;
        if (b == mp)
            adVmp = wr;
        if (b == sp)
            adVsp = wr;
        if (b == md)
            adVmd = wr;
        if (b == ml)
            adVml = wr;
        if (b == zl)
            adVzl = wr;
        if (b == oi)
            adVor = wr;
    }
    else if (a == cp){
        if (b == as)
            cpVas = wr;
        if (b == te)
            cpVte = wr;
        if (b == pw)
            cpVpw = wr;
        if (b == fm)
            cpVfm = wr;
        if (b == rl)
            cpVrl = wr;
        if (b == ad)
            cpVad = wr;
        if (b == mp)
            cpVmp = wr;
        if (b == sp)
            cpVsp = wr;
        if (b == md)
            cpVmd = wr;
        if (b == ml)
            cpVml = wr;
        if (b == zl)
            cpVzl = wr;
        if (b == oi)
            cpVor = wr;
    }
    else if (a == fm){
        if (b == as)
            fmVas = wr;
        if (b == te)
            fmVte = wr;
        if (b == pw)
            fmVpw = wr;
        if (b == cp)
            fmVcp = wr;
        if (b == rl)
            fmVrl = wr;
        if (b == ad)
            fmVad = wr;
        if (b == mp)
            fmVmp = wr;
        if (b == sp)
            fmVsp = wr;
        if (b == md)
            fmVmd = wr;
        if (b == ml)
            fmVml = wr;
        if (b == zl)
            fmVzl = wr;
        if (b == oi)
            fmVor = wr;
    }
    else if (a == ml){
        if (b == as)
            mlVas = wr;
        if (b == te)
            mlVte = wr;
        if (b == pw)
            mlVpw = wr;
        if (b == cp)
            mlVcp = wr;
        if (b == rl)
            mlVrl = wr;
        if (b == ad)
            mlVad = wr;
        if (b == mp)
            mlVmp = wr;
        if (b == sp)
            mlVsp = wr;
        if (b == md)
            mlVmd = wr;
        if (b == fm)
            mlVfm = wr;
        if (b == zl)
            mlVzl = wr;
        if (b == oi)
            mlVor = wr;
    }
    else if (a == zl){
        if (b == as)
            zlVas = wr;
        if (b == te)
            zlVte = wr;
        if (b == pw)
            zlVpw = wr;
        if (b == cp)
            zlVcp = wr;
        if (b == rl)
            zlVrl = wr;
        if (b == ad)
            zlVad = wr;
        if (b == mp)
            zlVmp = wr;
        if (b == sp)
            zlVsp = wr;
        if (b == md)
            zlVmd = wr;
        if (b == fm)
            zlVfm = wr;
        if (b == ml)
            zlVml = wr;
        if (b == oi)
            zlVor = wr;
    }
}


vector<player> bias;

const std::string md = "Midrange Druid";
const std::string ad = "Aggro Druid";
const std::string te = "Tempo Mage";
const std::string fm = "Freeze Mage";
const std::string sp = "Secret Paladin";
const std::string mp = "Midrange Paladin";
const std::string cp = "Control Priest";

const std::string as = "Aggro Shaman";
const std::string rl = "Renolock";
const std::string ml = "Malylock";
const std::string zl = "Zoolock";
const std::string pw = "Patron Warrior";

const std::string oi = "Oil Rogue"; //Apparently in qt or is a keyword.

std::vector<std::string> deckNames;


//The rate for a beating b in aVb.  Example: sp == secret paladin, and md = midrange druid.
//Could do a hash table or something for this but would rather have easily accessible single variable names for gui.
//https://tempostorm.com/hearthstone/meta-snapshot/meta-snapshot-42-uther-home-for-the-holidays
///////////////////////////////////////////////////////////////////////////////////////////////////
double spVmd = 0.55;
double spVad = 0.4;
double spVte = 0.55;
double spVfm = 0.3;
double spVmp = 0.5;
double spVcp = 0.35;
double spVor = 0.55;
double spVas = 0.4;
double spVrl = 0.55;
double spVml = 0.6;
double spVzl = 0.45;
double spVpw = 0.5;

double asVmd = 0.55;
double asVad = 0.5;
double asVfm = 0.6;
double asVte = 0.4;
double asVmp = 0.6;
double asVsp = 0.6;
double asVcp = 0.65;
double asVor = 0.7;
double asVml = 0.6;
double asVzl = 0.45;
double asVrl = 0.4;
double asVpw = 0.4;

double mdVad = 0.4;
double mdVfm = 0.75;
double mdVte = 0.3;
double mdVmp = 0.45;
double mdVsp = 0.45;
double mdVcp = 0.5;
double mdVor = 0.45;
double mdVas = 0.45;
double mdVml = 0.55;
double mdVzl = 0.35;
double mdVrl = 0.75;
double mdVpw = 0.35;

double rlVmd = 0.25;
double rlVad = 0.35;
double rlVfm = 0.5;
double rlVte = 0.5;
double rlVsp = 0.45;
double rlVmp = 0.45;
double rlVcp = 0.75;
double rlVor = 0.65;
double rlVas = 0.6;
double rlVml = 0.4;
double rlVzl = 0.45;
double rlVpw = 0.6;

double mpVmd = 0.55;
double mpVad = 0.65;
double mpVfm = 0.2;
double mpVte = 0.5;
double mpVsp = 0.5;
double mpVcp = 0.3;
double mpVor = 0.3;
double mpVas = 0.4;
double mpVml = 0.35;
double mpVzl = 0.55;
double mpVrl = 0.55;
double mpVpw = 0.55;

double orVmd = 0.55;
double orVad = 0.5;
double orVfm = 0.3;
double orVte = 0.45;
double orVmp = 0.7;
double orVsp = 0.45;
double orVcp = 0.7;
double orVas = 0.3;
double orVml = 0.4;
double orVzl = 0.65;
double orVrl = 0.35;
double orVpw = 0.55;

double pwVmd = 0.65;
double pwVad = 0.6;
double pwVte = 0.55;
double pwVfm = 0.65;
double pwVmp = 0.45;
double pwVsp = 0.5;
double pwVcp = 0.55;
double pwVor = 0.45;
double pwVas = 0.6;
double pwVrl = 0.4;
double pwVml = 0.3;
double pwVzl = 0.6;

double teVmd = 0.6;
double teVad = 0.7;
double teVfm = 0.3;
double teVmp = 0.5;
double teVsp = 0.45;
double teVcp = 0.35;
double teVor = 0.55;
double teVas = 0.6;
double teVml = 0.55;
double teVzl = 0.3;
double teVrl = 0.5;
double teVpw = 0.45;

double adVmd = 0.6;
double adVfm = 0.55;
double adVte = 0.4;
double adVmp = 0.35;
double adVsp = 0.6;
double adVcp = 0.35;
double adVor = 0.5;
double adVas = 0.5;
double adVml = 0.6;
double adVzl = 0.4;
double adVrl = 0.65;
double adVpw = 0.4;

double cpVmd = 0.5;
double cpVad = 0.65;
double cpVfm = 0.3;
double cpVte = 0.65;
double cpVmp = 0.7;
double cpVsp = 0.65;
double cpVor = 0.3;
double cpVas = 0.35;
double cpVml = 0.25;
double cpVzl = 0.6;
double cpVrl = 0.25;
double cpVpw = 0.45;

double fmVmd = 0.25;
double fmVad = 0.45;
double fmVte = 0.7;
double fmVmp = 0.8;
double fmVsp = 0.7;
double fmVcp = 0.7;
double fmVor = 0.7;
double fmVas = 0.4;
double fmVml = 0.6;
double fmVzl = 0.8;
double fmVrl = 0.5;
double fmVpw = 0.35;

double mlVmd = 0.45;
double mlVad = 0.4;
double mlVfm = 0.4;
double mlVte = 0.45;
double mlVmp = 0.65;
double mlVsp = 0.4;
double mlVcp = 0.75;
double mlVor = 0.6;
double mlVas = 0.4;
double mlVzl = 0.6;
double mlVrl = 0.6;
double mlVpw = 0.7;

double zlVmd = 0.65;
double zlVad = 0.6;
double zlVfm = 0.2;
double zlVte = 0.7;
double zlVmp = 0.45;
double zlVsp = 0.55;
double zlVcp = 0.4;
double zlVor = 0.35;
double zlVas = 0.55;
double zlVml = 0.4;
double zlVrl = 0.55;
double zlVpw = 0.4;

//Now we add the defaults to all of these.
//=======================================
//=======================================
//=======================================
double spVmdDefault = 0.55;
double spVadDefault = 0.4;
double spVteDefault = 0.55;
double spVfmDefault = 0.3;
double spVmpDefault = 0.5;
double spVcpDefault = 0.35;
double spVorDefault = 0.55;
double spVasDefault = 0.4;
double spVrlDefault = 0.55;
double spVmlDefault = 0.6;
double spVzlDefault = 0.45;
double spVpwDefault = 0.5;

double asVmdDefault = 0.55;
double asVadDefault = 0.5;
double asVfmDefault = 0.6;
double asVteDefault = 0.4;
double asVmpDefault = 0.6;
double asVspDefault = 0.6;
double asVcpDefault = 0.65;
double asVorDefault = 0.7;
double asVmlDefault = 0.6;
double asVzlDefault = 0.45;
double asVrlDefault = 0.4;
double asVpwDefault = 0.4;

double mdVadDefault = 0.4;
double mdVfmDefault = 0.75;
double mdVteDefault = 0.3;
double mdVmpDefault = 0.45;
double mdVspDefault = 0.45;
double mdVcpDefault = 0.5;
double mdVorDefault = 0.45;
double mdVasDefault = 0.45;
double mdVmlDefault = 0.55;
double mdVzlDefault = 0.35;
double mdVrlDefault = 0.75;
double mdVpwDefault = 0.35;

double rlVmdDefault = 0.25;
double rlVadDefault = 0.35;
double rlVfmDefault = 0.5;
double rlVteDefault = 0.5;
double rlVspDefault = 0.45;
double rlVmpDefault = 0.45;
double rlVcpDefault = 0.75;
double rlVorDefault = 0.65;
double rlVasDefault = 0.6;
double rlVmlDefault = 0.4;
double rlVzlDefault = 0.45;
double rlVpwDefault = 0.6;

double mpVmdDefault = 0.55;
double mpVadDefault = 0.65;
double mpVfmDefault = 0.2;
double mpVteDefault = 0.5;
double mpVspDefault = 0.5;
double mpVcpDefault = 0.3;
double mpVorDefault = 0.3;
double mpVasDefault = 0.4;
double mpVmlDefault = 0.35;
double mpVzlDefault = 0.55;
double mpVrlDefault = 0.55;
double mpVpwDefault = 0.55;

double orVmdDefault = 0.55;
double orVadDefault = 0.5;
double orVfmDefault = 0.3;
double orVteDefault = 0.45;
double orVmpDefault = 0.7;
double orVspDefault = 0.45;
double orVcpDefault = 0.7;
double orVasDefault = 0.3;
double orVmlDefault = 0.4;
double orVzlDefault = 0.65;
double orVrlDefault = 0.35;
double orVpwDefault = 0.55;

double pwVmdDefault = 0.65;
double pwVadDefault = 0.6;
double pwVteDefault = 0.55;
double pwVfmDefault = 0.65;
double pwVmpDefault = 0.45;
double pwVspDefault = 0.5;
double pwVcpDefault = 0.55;
double pwVorDefault = 0.45;
double pwVasDefault = 0.6;
double pwVrlDefault = 0.4;
double pwVmlDefault = 0.3;
double pwVzlDefault = 0.6;

double teVmdDefault = 0.6;
double teVadDefault = 0.7;
double teVfmDefault = 0.3;
double teVmpDefault = 0.5;
double teVspDefault = 0.45;
double teVcpDefault = 0.35;
double teVorDefault = 0.55;
double teVasDefault = 0.6;
double teVmlDefault = 0.55;
double teVzlDefault = 0.3;
double teVrlDefault = 0.5;
double teVpwDefault = 0.45;

double adVmdDefault = 0.6;
double adVfmDefault = 0.55;
double adVteDefault = 0.4;
double adVmpDefault = 0.35;
double adVspDefault = 0.6;
double adVcpDefault = 0.35;
double adVorDefault = 0.5;
double adVasDefault = 0.5;
double adVmlDefault = 0.6;
double adVzlDefault = 0.4;
double adVrlDefault = 0.65;
double adVpwDefault = 0.4;

double cpVmdDefault = 0.5;
double cpVadDefault = 0.65;
double cpVfmDefault = 0.3;
double cpVteDefault = 0.65;
double cpVmpDefault = 0.7;
double cpVspDefault = 0.65;
double cpVorDefault = 0.3;
double cpVasDefault = 0.35;
double cpVmlDefault = 0.25;
double cpVzlDefault = 0.6;
double cpVrlDefault = 0.25;
double cpVpwDefault = 0.45;

double fmVmdDefault = 0.25;
double fmVadDefault = 0.45;
double fmVteDefault = 0.7;
double fmVmpDefault = 0.8;
double fmVspDefault = 0.7;
double fmVcpDefault = 0.7;
double fmVorDefault = 0.7;
double fmVasDefault = 0.4;
double fmVmlDefault = 0.6;
double fmVzlDefault = 0.8;
double fmVrlDefault = 0.5;
double fmVpwDefault = 0.35;

double mlVmdDefault = 0.45;
double mlVadDefault = 0.4;
double mlVfmDefault = 0.4;
double mlVteDefault = 0.45;
double mlVmpDefault = 0.65;
double mlVspDefault = 0.4;
double mlVcpDefault = 0.75;
double mlVorDefault = 0.6;
double mlVasDefault = 0.4;
double mlVzlDefault = 0.6;
double mlVrlDefault = 0.6;
double mlVpwDefault = 0.7;

double zlVmdDefault = 0.65;
double zlVadDefault = 0.6;
double zlVfmDefault = 0.2;
double zlVteDefault = 0.7;
double zlVmpDefault = 0.45;
double zlVspDefault = 0.55;
double zlVcpDefault = 0.4;
double zlVorDefault = 0.35;
double zlVasDefault = 0.55;
double zlVmlDefault = 0.4;
double zlVrlDefault = 0.55;
double zlVpwDefault = 0.4;
