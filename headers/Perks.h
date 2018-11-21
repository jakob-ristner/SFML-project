#pragma once 
#include<string>
#include<vector>

struct Perk;
class PerkTree {
public:
    PerkTree();
    ~PerkTree();
    
    Perk* findPerk(std::string name);
    std::vector<Perk>* getPerks();
    

private:
    std::string name;
    std::vector<Perk> perklist;
};

struct Perk {
    std::string name;
    std::vector<int> costs; 
    std::string reqPerk;
    std::string type; 
    int maxPerkLevel;
    int reqPlayerLevel;
    int currPerkLevel = 0;
    bool active = false;
};






