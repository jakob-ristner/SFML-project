#include "../headers/Perks.h"

PerkTree::PerkTree() {
    // ManaCostOff is a perk for mana reduction 
    // for all offensive spells
    // level 1: 10%
    // level 2: 20%
    // level 3: every fifth consecutive offensive
    // spell gets its mana reduced by 50% of
    // the total mana cost of the previous 4 offensive spells
    Perk manaCostOff;
    manaCostOff.name = "manaCostOff";
    manaCostOff.costs = {1, 1, 2};
    manaCostOff.reqPerk = "";
    manaCostOff.type = "offensive";
    manaCostOff.maxPerkLevel = 3;
    perklist.push_back(manaCostOff);
}

PerkTree::~PerkTree() {

}

std::vector<Perk>* PerkTree::getPerks() {
    return &perklist;
}

Perk* PerkTree::findPerk(std::string name) {
    for (int i = 0; i < perklist.size(); i++) {
        if (perklist[i].name == name) {
            return &perklist[i];
        }

    }
}




