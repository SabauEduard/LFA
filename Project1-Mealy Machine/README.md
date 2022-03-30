# Regular language and finite automata - Mealy Machine

First LFA project. This project reads the construction of a Mealy
Machine and the words to be verified given by the user through an input file.

## Input template and types

The file "mealy.in" contains an input example.

`number_of_states` (integer)
`number_of_transitions`(integer)

`from_state to_state transition_letter encrypt_word` (string string char string)
... --> `number_of_transitions` times. 

`initial_state` (string)

`number_of_final_states` (integer)
`final_state` (string)
... --> `number_of_final_states` times. 

`number_of_words` (integer)
`word` (string)
... --> `number_of_words` times.

## Output

The file "mealy.out" contains an output example for the input "mealy.in".

For each word the message "Accepted" or "Not accepted" will be displayed.
For an accepted word on the next two lines the path and the encryption will be displayed.
The output for each word will be separated by a new line.

## Code

### Struct - Letter

Contains the letter and the encryption word for a Transition

### Struct - Transition

Contains the state that we transition to and a vector of type Letter 
for each transition that has this state as a destination.

### Struct - State

Contains the state that we transition from and a vector of type Transition
for each state that we transition to.

### Data 

1. integers num_states and num_trans

Contain the number of states and the number of transitions in the automaton

2. string init_state

Contains the initial state.

3. vector <State> states

Contains the structure of the machine as described above.

4. vector <string> fin_states

Contains the names of the states that are final.

5. deques <string> states_deq and output_deq

Contain the path and the encryption after a word verification.

6. bool was_accepted

For the last verification, determines whether it was successful or not.

### Public Methods

1. bool is_accepted (string)

Determines whether a word is accepted or not by calling DFS.

2. void set_num_states (int), void set_num_trans (int), void set_init_state (string)

Sets the number of states, sets the number of transition and sets the initial state.

3. int get_num_states(), int get_num_trans(), string get_init_state

Returns number of states, returns number of transitions, returns initial state.

4. void add_fin_state (string)

Adds the final state to the vector of final states.

5. void add_transition (string, string, char, string)

Adds the transition as follows, first argument is the state where
the transition begins, second argument is the transition to state, third argument
is the letter and the fourth is the encryption word.

6. void clear()

Deletes all transitions.

7. void show_encrypt (ofstream&), void show_path (ofstream&)

They output the encrypt/path to the stream given as argument.


### Protected Methods

1. bool is_final_state (string)

Checks if a state is a final state.

2. DFS (string, int, string , bool&)

Finds a path to a final state and checks if the word's letters have been processed

3. bool is_transition (string, string, string&, int, string)

Checks if there is a transition between two states with a specified letter and stores 
the encryption word of said transition in the third argument.

Argument one is the state we transition from, second is the state we are trying to transition to
third will contain the encryption word, fourth the letter index in the word that is processed, and fifth the word that is processed

