#include "structures.h"
#include "globals.h"
#include <QDebug>

//Player member functions
bool player::same(player other){
    //qDebug() << QString::fromStdString("Player One Decks");
    //printDecks();
    //qDebug() << QString::fromStdString("Player Two Decks");
    other.printDecks();

	for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (decks[i].name == other.decks[j].name){
                break;
            }
            if (j == 2){
                //qDebug() << QString::fromStdString("False");
				return false;
            }
		}
	}
    //qDebug() << QString::fromStdString("True");
	return true;
}

int deck::currentIndex(){
    if (name == md)
        return 0;
    else if (name == ad)
        return 1;
    else if (name == te)
        return 2;
    else if (name == fm)
        return 3;
    else if (name == mp)
        return 4;
    else if (name == sp)
        return 5;
    else if (name == cp)
        return 6;
    else if (name == oi)
        return 7;
    else if (name == as)
        return 8;
    //Locks
    else if (name == rl)
        return 9;
    else if (name == ml)
        return 10;
    else if (name == zl)
        return 11;
    else if (name == pw)
        return 12;
    //Can add more decks here in the future.  Would be better to use a loop and compare but I don't think I can access the ui->chooseBias sadly.
    return -1;
}

double player::topPercent(){
    return (double)placings.size()/(double)occurrences;
}

bool deck::operator < (const deck& d) const{
    return (name[0] < d.name[0]);
}

void player::printDecks(){
    for (int i = 0; i < 3; i++){
        //qDebug() << QString::fromStdString(decks[i].name);
    }
}

std::string deck::hero(){
    if (name.find("Druid") != std::string::npos){
            return "Druid";
    }
    else if (name.find("Mage") != std::string::npos){
        return "Mage";
    }
    else if (name.find("Mage") != std::string::npos){
        return "Mage";
    }
    else if (name.find("Paladin") != std::string::npos){
        return "Paladin";
    }
    else if (name.find("Priest") != std::string::npos){
        return "Priest";
    }
    else if (name.find("Rogue") != std::string::npos){
        return "Rogue";
    }
    else if (name.find("Shaman") != std::string::npos){
        return "Shaman";
    }
    else if (name.find("lock") != std::string::npos){
        return "Warlock";
    }
    else if (name.find("Warrior") != std::string::npos){
        return "Warrior";
    }
    else if (name.find("Hunter") != std::string::npos){
        return "Hunter";
    }
    //Never gets here.
    return "Error";
}

bool deck::sameClass(deck other){
    if (hero() == other.hero())
        return true;
    return false;
}

double player::winRate(){
    double totalGames = wins + losses;
    return (double)wins/totalGames;
}

std::string player::getTops(){
    std::string str;
    if (placings.size() > 0)
        //qDebug() << placings.size();
    for (int i = 0; i < placings.size(); i++){
        if (i != 0)
            str.append(", ");
        str.append(std::to_string(placings[i]));
    }
    return str;
}

