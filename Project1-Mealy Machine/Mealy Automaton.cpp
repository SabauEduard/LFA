#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <deque>
#include "Mealy.h"

using namespace std;

ifstream fin("mealy.in");
ofstream fout("mealy.out");

int main()
{
    Mealy Graph;
    int num_states, num_transitions;
    fin >> num_states >> num_transitions;
    Graph.set_num_states(num_states);
    Graph.set_num_trans(num_transitions);
    for (int index = 0; index < num_transitions; index++)
    {
        string state1, state2, transition_word;
        char letter;
        fin >> state1 >> state2 >> letter >> transition_word;
        Graph.add_transition(state1, state2, letter, transition_word);
    }
    string init_state;
    fin >> init_state;
    Graph.set_init_state(init_state);
    int num_fin_states;
    fin >> num_fin_states;
    for (int index = 0; index < num_fin_states; index++)
    {
        string fin_state;
        fin >> fin_state;
        Graph.add_fin_state(fin_state);
    }
    int num_words;
    fin >> num_words;
    for (int index = 0; index < num_words; index++)
    {
        string word;
        fin >> word;
        if (Graph.is_accepted(word))
        {          
            fout << "Accepted" << '\n';
            Graph.show_path(fout);
            Graph.show_encrypt(fout);
            fout << '\n';
        }
        else {
            fout << "Not accepted" << '\n' << '\n';
        }
    }
}

