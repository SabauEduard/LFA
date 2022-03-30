#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <deque>
#include "Mealy.h"

using namespace std;

Mealy::Mealy()
{
    was_accepted = false;
    num_states = 0;
    num_trans = 0;
}
bool Mealy::is_final_state(string state)
{
    for (auto index = fin_states.begin(); index != fin_states.end(); index++)
        if (state == *index)
            return true;
    return false;
}
bool Mealy::is_accepted(string word)
{
    was_accepted = false;
    states_deq.clear();
    output_deq.clear();
    bool ok = false;
    states_deq.push_back(init_state);
    DFS(init_state, 0, word, ok);
    if (ok == true)
        was_accepted = true;
    return ok;
}
void Mealy::set_num_states(int new_num_states)
{
    num_states = new_num_states;
}
void Mealy::set_init_state(string new_init_state)
{
    init_state = new_init_state;
}
void Mealy::add_fin_state(string state)
{
    fin_states.push_back(state);
}
void Mealy::add_transition(string state1, string state2, char letter, string word)
{
    Letter_Word temp_let;
    temp_let.letter = letter;
    temp_let.output_word = word;
    Transition temp_trans;
    temp_trans.next_state = state2;
    temp_trans.letters.push_back(temp_let);
    State temp_state;
    temp_state.state_name = state1;
    temp_state.transitions.push_back(temp_trans);
    for (auto index1 = states.begin(); index1 != states.end(); index1++) // searching if the state we transition from has already been added to the graph
        if (index1->state_name == state1)
        {
            for (auto index2 = index1->transitions.begin(); index2 != index1->transitions.end(); index2++) // searching if the already is a transition between these two states in the graph
                if (index2->next_state == state2)
                {
                    index2->letters.push_back(temp_let);
                    return;
                }
            index1->transitions.push_back(temp_trans);
            return;
        }
    states.push_back(temp_state);
}
bool Mealy::is_transition(string current_state, string next_state, string& word_of_transition, int letter_index, string word)
{

    for (auto index1 = states.begin(); index1 != states.end(); index1++) // iterating through the states of the machine to find the state we want to transition from
        if (index1->state_name == current_state) 
        {

            for (auto index2 = index1->transitions.begin(); index2 != index1->transitions.end(); index2++) // searching for the state that we want to transition to
                if (index2->next_state == next_state)
                {
                    for (auto index3 = index2->letters.begin(); index3 != index2->letters.end(); index3++) // searching for the letter of the transition that we have to process for our word
                        if (index3->letter == word[letter_index])
                        {
                            word_of_transition = index3->output_word;
                            return true;
                        }
                }
        }
    return false;
}
void Mealy::DFS(string current_state, int letter_index, string word, bool& ok)
{
    if (ok == false)
    {
        if (letter_index == word.length())
        {
            if (is_final_state(current_state))
                ok = true;
            return;
        }
        else
        {
            for (auto index = states.begin(); index != states.end() && ok == false; index++)
            {
                string word_of_transition;
                if (is_transition(current_state, index->state_name, word_of_transition, letter_index, word))
                {
                    states_deq.push_back(index->state_name);
                    output_deq.push_back(word_of_transition);
                    DFS(index->state_name, letter_index + 1, word, ok);
                }
            }
        }
    }


}
void Mealy::set_num_trans(int new_num_trans)
{
    num_trans = new_num_trans;
}
int Mealy::get_num_states()
{
    return num_states;
}
int Mealy::get_num_trans()
{
    return num_trans;
}
void Mealy::show_encrypt(ofstream& stream)
{
    if (was_accepted == true)
    {
        stream << "Encryption: ";
        while (!output_deq.empty())
        {
            stream << output_deq.front();
            output_deq.pop_front();
        }
        stream << '\n';
    }
}
void Mealy::show_path(ofstream& stream)
{
    if (was_accepted == true)
    {
        stream << "Path: ";
        while (!states_deq.empty())
        {
            stream << states_deq.front() << " ";
            states_deq.pop_front();
        }
        stream << '\n';
    }
}
string Mealy::get_init_state()
{
    return init_state;
}
void Mealy::clear()
{
    states.clear();
}
