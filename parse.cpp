#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <sys/stat.h>
#include "parse.h"
using namespace std;

int dataType;
const char* validNames[10] = {"pokemon", "moves", "pokemon_moves", "pokemon_species", "experience", "type_names", "pokemon_stats", "stats", "pokemon_types"};

class pokemonStats {
    public:
        int id;
        int stat_id;
        int base_stat;
        int effort;
};

class stats {
    public:
        string id;
        string damage_class_id;
        string identifier;
        string is_battle_only;
        string game_index;
};

class typeNames {
    public:
        int type_id;
        int local_language_id;
        string name;
};

class experience {
    public:
        int growth_rate_id;
        int level;
        int experience;
};

class moves {
    public:
        int id;
        string identifier;
        int generation_id;
        int type_id;
        int power;
        int pp;
        int accuracy;
        int priority;
        int target_id;
        int damage_class_id;
        int effect_id;
        int effect_chance;
        int contest_type_id;
        int contest_effect_id;
        int super_contest_effect_id;
};

class pokemonMoves {
    public:
        int pokemon_id;
        int version_group_id;
        int move_id;
        int pokemon_move_method_id;
        int level;
        int order;
};

class pokemonSpecies {
    public:
        int id;
        string identifier;
        int generation_id;
        int evolves_from_species_id;
        int evolution_chain_id;
        int color_id;
        int shape_id;
        int habitat_id;
        int gender_rate;
        int capture_rate;
        int base_happiness;
        int is_baby;
        int hatch_counter;
        int has_gender_differences;
        int growth_rate_id;
        int forms_switchable;
        int is_legendary;
        int is_mythical;
        int order;
        int conquest_order;
};

class pokemonTypes {
    public:
        int pokemon_id;
        int type_id;
        int slot;
};

class pokemon {
    public:
        int id;
        string identifier;
        int species_id;
        int height;
        int weight;
        int base_experience;
        int order;
        int is_default;
};

int verifyFileName(const char* fileName) {
    int retVal = 0;

    for (int i = 0; i < 9; i++) {
        if (strcmp(fileName, validNames[i]) == 0) {
            retVal = 1;
            dataType = i;
        }
    }

    return retVal;
}

int parseFile(const char* fileName) {
    string file = fileName;

    string path1 = "/share/cs327/pokedex/pokedex/data/csv/";
    string path2 = getenv("HOME");
    path2 += "/.poke327/pokedex/pokedex/data/csv/";

    struct stat sb;

    if (stat("/share/cs327/pokedex/pokedex/data/csv/", &sb) == 0) {
        readFile(path1 + file + ".csv");
    } else if (stat(strcat(getenv("HOME"), "/.poke327/pokedex/pokedex/data/csv/"), &sb) == 0) {
        readFile(path2 + file + ".csv");
    } else {
        cout << "Database not found";
    }

    return 0;
}

void readFile(string fileName) {
    ifstream csvFile;
    csvFile.open(fileName);

    std::string segment;
    std::vector<std::string> seglist;

    getline(csvFile, segment);
    if(strcmp(validNames[dataType], "stats") == 0) {
        std::vector<stats> objVec;

        // Parse all lines of file into seglist. Adding each line as a std::string 'segment'
        while(getline(csvFile, segment)) {
            seglist.push_back(segment);
        }

        // For each std::string 'segment' in seglist, split the line by commas, 
        for (auto & element : seglist) {
            stats statsObj;
            std::vector<std::string> elements;

            std::string delimiter = ",";

            size_t pos = 0;
            std::string token;
            int elementPos = 0;
            while ((pos = element.find(delimiter)) != std::string::npos) {
                token = element.substr(0, pos);
                element.erase(0, pos + delimiter.length());

                switch(elementPos) {
                    case 0 :
                        statsObj.id = token;
                        break;
                    case 1 :
                        statsObj.damage_class_id = token;
                        break;
                    case 2 :
                        statsObj.identifier = token;
                        break;
                    case 3 :
                        statsObj.is_battle_only = token;
                        break;
                }
                elementPos++;
            }
            statsObj.game_index = element;
            objVec.push_back(statsObj);
        }

        for (auto & element : objVec) {
            cout << "ID: " << element.id << endl;
            cout << "Damage Class ID: " << element.damage_class_id << endl;
            cout << "Identifier: " << element.identifier << endl;
            cout << "Is Battle Only: " << element.is_battle_only << endl;
            cout << "Game Index: " << element.game_index << endl;
            cout << "\n";
        }
    }

    csvFile.close();
}
