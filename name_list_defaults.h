#ifndef NAME_LIST_DEFAULTS_H
#define NAME_LIST_DEFAULTS_H

#include <QString>
#include <vector>
#include "loaddatafiles.h"

class NameListDefaults
{

private: 
    QString speciesName = "Default";

public:
    const std::vector<QString> species_name_categories = {"randomized","alias","ship_names","fleet_names","army_names","planet_names",
                                                   "character_names"};

    const std::vector<QString> army_categories = {"machine_defense", "machine_assault_1", "machine_assault_2", "machine_assault_3", "defense_army",
                                       "assault_army", "slave_army", "clone_army", "undead_army", "robotic_army", "robotic_defense_army",
                                       "psionic_army", "xenomorph_army", "gene_warrior_army", "occupation_army", "robotic_occupation_army",
                                       "primitive_army", "industrial_army", "postatomic_army"};

    const std::vector<QString> planet_categories = {"generic", "pc_desert", "pc_tropical", "pc_arid", "pc_continental", "pc_ocean",
                                       "pc_tundra", "pc_arctic", "pc_savannah", "pc_alpine", "pc_nuked"};

    const std::vector<QString> ship_categories = {"generic", "corvette", "destroyer", "cruiser", "battleship", "titan", "colossus", "constructor",
                                       "colonizer", "science", "transport", "military_station_small", "ion_cannon"};

    const std::vector<QString> character_set_categories = {"first_names_male", "first_names_female", "first_names", "second_names",
                                                     "regnal_first_names_male", "regnal_first_names_female", "regnal_second_names",
                                                     "full_names_male", "full_names_female"};

    const std::vector<QString> random_sequential_categories = {"random_names","sequential_name"};

    const std::vector<QString> misc_categories = {"weight", "names"};

    std::vector<QString> user_defined_categories;

public:
    bool CheckIfKeyIsDefaultCategory(QString k)
    {
        for(auto cat:species_name_categories) if(k==cat) return true;
        for(auto cat:army_categories) if(k==cat) return true;
        for(auto cat:planet_categories) if(k==cat) return true;
        for(auto cat:ship_categories) if(k==cat) return true;
        for(auto cat:character_set_categories) if(k==cat) return true;
        for(auto cat:random_sequential_categories) if(k==cat) return true;
        for(auto cat:misc_categories) if(k==cat) return true;
        return false;
    }

    bool CheckIfKeyIsUserCategory(QString k)
    {
        for(auto cat:user_defined_categories) if(k==cat) return true;
        return false;
    }

    bool CheckIfKeyIsCategory(QString k)
    {
        if(CheckIfKeyIsDefaultCategory(k)) return true;
        else if(CheckIfKeyIsUserCategory(k)) return true;
        return false;
    }

    bool IgnoreCategoryForLocalKeyGeneration(QString k)
    {
        if(k=="weight"||k=="alias"||k=="randomized") return true;
        return false;
    }

    void AddUserCategory(QString cat)
    {
        if(!CheckIfKeyIsDefaultCategory(cat))
        {
            for(auto c:user_defined_categories)
                if(c==cat) return;
            user_defined_categories.push_back(cat);
        }
    }

    void RemoveUserCategory(QString cat)
    {
        int idx = 0;
        for(;idx<user_defined_categories.size();idx++)
            if(user_defined_categories[idx]==cat)
                break;
        if(idx<user_defined_categories.size())
            user_defined_categories.erase(user_defined_categories.begin()+idx);
    }

    void EditUserCategory(QString cat, QString newCat)
    {
        for(int idx=0;idx<user_defined_categories.size();idx++)
            if(user_defined_categories[idx]==cat)
            {
                user_defined_categories[idx]=newCat;
                break;
            }
    }

    TreeItem GenerateDefaultTree()
    {
        TreeItem defaultRoot;
        //Root as species name
        defaultRoot.InsertKey(speciesName);

        //Different categories under root
        for(auto name:species_name_categories)
            defaultRoot.InsertKey(name);

        //Randomized (default is yes anyways; Only required if it is 'no')
        defaultRoot["randomized"].InsertKey("yes");

        //Alias as the default species name
        defaultRoot["alias"].InsertKey(speciesName);

        //Army
        for(auto name:army_categories)
        {
            TreeItem* node = defaultRoot["army_names"].InsertKey(name);
            node->InsertKey("random_names");
            node->InsertKey("sequential_name");
        }

        //Planet
        for(auto name:planet_categories)
        {
           TreeItem* node = defaultRoot["planet_names"].InsertKey(name);
           node->InsertKey("names");
        }

        //Ship
        for(auto name:ship_categories)
            defaultRoot["ship_names"].InsertKey(name);

        //Fleet
        defaultRoot["fleet_names"].InsertKey("random_names");
        defaultRoot["fleet_names"].InsertKey("sequential_name");

        //Character
        TreeItem* characterNode = defaultRoot["character_names"].InsertKey("name1");
        characterNode->InsertKey("weight");
        (*characterNode)["weight"].InsertKey("100");
        for(auto name:character_set_categories)
            characterNode->InsertKey(name);

        return defaultRoot;
    }
};

#endif // NAME_LIST_DEFAULTS_H
