#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <deque>

using namespace std;

class Mealy
{
    struct Letter_Word
    {
        char letter;
        string output_word;
    };
    struct Transition
    {
        string next_state;
        vector <Letter_Word> letters;
    };
    struct State
    {
        string state_name;
        vector <Transition> transitions;
    };
public:
    bool is_accepted(string);
    void set_num_states(int);
    void set_num_trans(int);
    void set_init_state(string);
    int get_num_states();
    int get_num_trans();
    string get_init_state();
    void add_fin_state(string);
    void add_transition(string, string, char, string);
    void show_encrypt(ofstream&);
    void show_path(ofstream&);
    void clear();
    Mealy();

protected:
    bool is_final_state(string);
    void DFS(string, int, string, bool&);
    bool is_transition(string, string, string&, int, string);

public:
    int num_states, num_trans;
    string init_state;
    vector <State> states;
    vector <string> fin_states;
    deque <string> states_deq;
    deque <string> output_deq;
    bool was_accepted;
};
