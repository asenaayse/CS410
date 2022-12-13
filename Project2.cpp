#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map> //hash map
#include <set>

using namespace std;


void generic_print(const auto& container)
{
    for(auto& item : container){
        cout<<item<<", ";
    }
    cout<<endl;
}

struct CFG
{
    set<string> VARIABLES;
    set<string> TERMINALS;
    set<string> RULES;
    string S;

    void print()
    {
        cout<<"***** CFG *****" <<endl;
        cout<<"Variables:"<<endl;
        generic_print(VARIABLES);
        cout<<"Terminals:"<<endl;
        generic_print(TERMINALS);
        cout<<"Rules:"<<endl;
        generic_print(RULES);
        cout<<"S:"<<endl;
        cout<<S<<endl;

    }
};

#define READ_NON_TERMINALS 0
#define READ_TERMINALS 1
#define READ_RULES 2
#define READ_S 3

//read the file for a CFG object
auto read_file(auto& filename){
    int state=0;
    fstream myfile;
    myfile.open(filename, ios::in);
    CFG my_cfg;
    if (myfile.is_open()) {
        string line;
        while (!myfile.eof()) {
            getline(myfile, line);

            if (line == "NON-TERMINAL")
            {
                state = READ_NON_TERMINALS;
                continue;
            }
            else if (line == "TERMINAL")
            {
                state = READ_TERMINALS;
                continue;
            }
            else if (line == "RULES")
            {
                state = READ_RULES;
                continue;
            }
            else if (line == "START")
            {
                state = READ_S;
                continue;
            }

            switch(state){
            case READ_NON_TERMINALS:
                my_cfg.VARIABLES.insert(line);
                break;
            case READ_TERMINALS:
                my_cfg.TERMINALS.insert(line);
                break;
            case READ_S:
                my_cfg.S = line;
                break;
            case READ_RULES:
                my_cfg.RULES.insert(line);
                break;
            }
        }
        myfile.close();

    }
    return my_cfg;
}


//coverts a given CFG object to its chomsky normal form
auto convert_CNF(const auto& cfg)
{

    //step I
    CFG my_cfg_cnf;
    //step II
    my_cfg_cnf.S = "$";
    auto old_S = cfg.S;
    my_cfg_cnf.RULES.insert("$:"+old_S);
    //step III
    my_cfg_cnf.VARIABLES = cfg.VARIABLES;
    my_cfg_cnf.TERMINALS = cfg.TERMINALS;
    my_cfg_cnf.RULES = cfg.RULES;
    //step IV
    for (auto& rule: cfg.RULES)
    {
        auto LHS = rule.substr(0, rule.find(":"));
        auto RHS = rule.substr(rule.find(":")+1, rule.length());
        if(RHS.compare("e")==0) //This is an epsilon rule
        {
            if(LHS.compare("$")==0) //epsilon rule is for the start variable
                continue;

        }
    }
    //step V
    //step VI

    return my_cfg_cnf;
}

int main (int argc, char* argv[])
{
    auto path = "G1.txt";
    auto my_cfg = read_file(path);
    my_cfg.print();
    auto my_cfg_cnf = convert_CNF(my_cfg);
    my_cfg_cnf.print();

}
