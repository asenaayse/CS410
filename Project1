#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map> //hash map
#include <set>

using namespace std;

struct NFA
{
    set<string> Q;
    set<string> Sigma;
    unordered_map<string, unordered_map<string, set<string> >> delta; //a hash map of hash maps of sets, for transitions
    string q_0;
    set<string> F;
};

struct DFA
{
    set<string> Q;
    set<string> Sigma;
    unordered_map<string, unordered_map<string, string >> delta; //a hash map of hash maps of string, for transitions
    string q_0;
    set<string> F;
};

void print(NFA automata)
{
    cout<<"Q:"<<endl;
    for(auto& item: automata.Q)
    {
        cout<<item<<endl;
    }

    cout<<"Sigma:"<<endl;
    for(auto& item: automata.Sigma)
    {
        cout<<item<<endl;
    }

    cout<<"delta:"<<endl;
    for(auto& state: automata.Q)
    {
        for(auto& alph: automata.Sigma)
        {
            for(auto& target: automata.delta[state][alph])
            {
                cout<<state<<alph<<target<<endl;
            }
        }
    }
    cout<<"F:"<<endl;
    for(auto& item: automata.F)
    {
        cout<<item<<endl;
    }

    cout<<"start state: "<<automata.q_0<<endl;
}

void print(DFA automata)
{
    cout <<"printing DFA"<<endl;
    cout<<"Q:"<<endl;
    for(auto& item: automata.Q)
    {
        cout<<item<<endl;
    }

    cout<<"Sigma:"<<endl;
    for(auto& item: automata.Sigma)
    {
        cout<<item<<endl;
    }

    cout<<"delta:"<<endl;
    for(auto& state: automata.Q)
    {
        for(auto& alph: automata.Sigma)
        {
            string target= automata.delta[state][alph];
            cout<<state<<" "<<alph<<" "<<target<<endl;

        }
    }
    cout<<"F:"<<endl;
    for(auto& item: automata.F)
    {
        cout<<item<<endl;
    }

    cout<<"start state: "<<automata.q_0<<endl;
}


#define READ_ALPHABET 0
#define READ_STATES 1
#define READ_START 2
#define READ_FINAL 3
#define READ_TRANSITIONS 4

NFA read_file(string& filename){
    int state=5;
    fstream myfile;
    myfile.open(filename, ios::in);
    NFA my_NFA;
    if (myfile.is_open()) {
        set<string> Q;
        set<string> Sigma;
        unordered_map<string, unordered_map<string, set<string> >> delta;
        string q_0;
        set<string> F;

        string line;

        while (!myfile.eof()) {
            getline(myfile, line);
            cout<<line<<endl;
            if (line == "STATES")
            {
                state = READ_STATES;
                continue;
            }
            else if (line == "ALPHABET")
            {
                state = READ_ALPHABET;
                continue;
            }
            else if (line == "START")
            {
                state = READ_START;
                continue;
            }
            else if (line == "FINAL")
            {
                state = READ_FINAL;
                continue;
            }
            else if (line == "TRANSITIONS")
            {
                state = READ_TRANSITIONS;
                continue;
            }
            else if (line == "END")
                break;

            switch(state){
            case READ_ALPHABET:
                Sigma.insert(line);
                break;
            case READ_STATES:
                Q.insert(line);
                break;
            case READ_START:
                q_0 = line;
                break;
            case READ_FINAL:
                F.insert(line);
                break;
            case READ_TRANSITIONS:
                char c_state_from = line.at(0);
                char c_alphabet_letter = line.at(2);
                char c_state_to = line.at(4);
                string state_from(1, c_state_from);
                string alphabet_letter(1, c_alphabet_letter);
                string state_to(1, c_state_to);
                delta[state_from][alphabet_letter].insert(state_to);
                break;
            }
        }
        myfile.close();
        my_NFA.Q = Q;
        my_NFA.Sigma = Sigma;
        my_NFA.delta = delta;
        my_NFA.q_0 = q_0;
        my_NFA.F = F;
        print(my_NFA);
    }
    return my_NFA;
}

int main (int argc, char* argv[])
{
    //read the input file and create the NFA
    string path = "NFA1.txt";
    NFA my_NFA = read_file(path);

    // create the DFA
    DFA my_DFA;
    set<string> Q;
    set<string> Sigma;
    unordered_map<string, unordered_map<string, string >> delta; //a hash map of hash maps of string, for transitions
    string q_0;
    set<string> F;

    // set the Sigma and q_0 for the DFA
    my_DFA.Sigma = my_NFA.Sigma;
    my_DFA.q_0 = my_NFA.q_0;

    set <string> new_states;

    // set the states and transitions for the DFA that come directly from the NFA
    for(auto& state: my_NFA.Q)
    {
        for(auto& transition: my_NFA.Sigma)
        {
            string dfa_state;
            string dfa_state_from = state;
            string dfa_transiton = transition;
            for(auto& target: my_NFA.delta[state][transition])
            {
                dfa_state+=target;
                cout<<"Converting: "<<state<<","<<transition<<","<<target<<" to: "<<dfa_state<<endl;

            }
            if(my_NFA.delta[state][transition].size() != 0)
            {
                cout<<"now dfa state is:"<<dfa_state<<endl;
                my_DFA.delta[state][transition]=dfa_state;
                if(dfa_state.length()>0)
                    my_DFA.Q.insert(dfa_state);
                if(my_NFA.Q.find(dfa_state)==my_NFA.Q.end())
                    new_states.insert(dfa_state);
            }
        }
    }


    set <string> temp_new_states;

    // look for the new DFA states, and see where they go
    cout<<"---------------------------------------------------------------------"<<endl;

    while(new_states.size()>0)
    {
        cout<<"new states: ";
        for (auto& item: new_states)
        {
            cout<<" "<<item<<"  ";
        }
        cout<<endl;

        for(auto& state: new_states)
        {
            for(auto& transition: my_NFA.Sigma)
            {

                string states_to="";
                set <string> states_to_set;

                //AB A ve B
                if (my_DFA.Q.find(state)!=my_DFA.Q.end())
                {
                    cout<<"looking for "<<state<<" "<<transition<<endl;
                    for(int i=0; i< state.length(); i++)
                    {
                        cout<<"state.at(i) "<<state.at(i) <<endl;


                        for(auto& target: my_NFA.delta[string(1,state.at(i))][transition])
                        {

                            states_to_set.insert(target);
                        }
                    }

                    for(auto& item: states_to_set)
                    {
                        cout<<"item: "<<item<<endl;
                        states_to+= item;
                    }


                    if(states_to != ""){
                        cout<<"New: "<<state<<transition<<states_to<<endl;
                        my_DFA.delta[state][transition]= states_to;

                        if(new_states.find(states_to)== new_states.end() && my_DFA.Q.find(states_to)==my_DFA.Q.end())
                        {
                            temp_new_states.insert(states_to);
                            cout<<"if here"<<endl;
                            my_DFA.Q.insert(states_to);
                        }
                        else
                            cout<<"already present state: "<<states_to<<endl;
                    }
                }


            }
        }
        new_states.clear();
        new_states = temp_new_states;
        temp_new_states.clear();


    }

    set <string> keys;
    for (auto& key: my_DFA.delta)
    {
        keys.insert(key.first);
    }


    set<string> new_Q;
    for (auto& state: my_DFA.Q)
    {
        // if state not in delta.keys()
        // delete state from Q
        if(keys.find(state)!=keys.end())
        {
            new_Q.insert(state);
        }
    }
    new_Q.insert(my_DFA.q_0);
    new_Q.insert("sink"); //sink state
    my_DFA.Q= new_Q;

    //in the transition is empty, it should go to sink state
    for(auto& state: my_DFA.Q)
    {
        for(auto& alph: my_DFA.Sigma)
        {
            string target= my_DFA.delta[state][alph];
            if(target == "")
            {
                my_DFA.delta[state][alph] = "sink";
                cout<<"Adding transition: "<<state<<" "<<alph<<" "<<"sink"<<endl;
            }

        }
    }

    //set the final states

    for(auto& state: my_DFA.Q)
    {
        for(int i=0; i< state.length(); i++)
        {
            if(my_NFA.F.find(string(1, state.at(i)))!=my_NFA.F.end())
                my_DFA.F.insert(state);
        }
    }


    cout <<"----------------"<<endl;
    print(my_DFA);




}


