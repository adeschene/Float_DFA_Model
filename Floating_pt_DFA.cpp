/*
    Alec Deschene
    Floating point DFA model
    CS311
    Ely
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

const int MAX = 101;

bool fp_DFA(ifstream&);
char **build_table();
void destroy_table(char**);

int main()
{
    bool        err = false; // Returns 1 from main if error occured during execution
    char        choice = '1'; // Manages loop through main menu
    char        *file_name = new char[MAX]; // Holds the filename w/input strings
    ifstream    input_strings; // Holds file w/input strings
    
    while(choice != '0')
    {
        cout << "\n\nFloating Point DFA\n\n"
             << "   1: Run DFA with a local file\n"
             << "   0: Quit\n\n"
             << "Enter selection: ";
        cin >> choice;
        cin.ignore(MAX, '\n');
        if(choice == '1')
        {
            cout << "\n\n[ Input string file must be in same location as this src file! ]\n\n"
                 << "Enter Input file name: ";
            cin.get(file_name, MAX);
            input_strings.open(file_name);
            if(input_strings.good())
                err = fp_DFA(input_strings); // Returns true if file wasn't opened
            else
                cout << "\n\nInvalid filename!\n";
            
            if(input_strings.is_open())
                input_strings.close();
        }
        else if(choice != '0')
            cout << "\n\nInvalid selection!\n\n";
    }
    delete [] file_name;
    file_name = NULL;
    return err;
}

bool fp_DFA(ifstream &input_strings)
{
    char    **transition_table, *curr_string = new char[MAX], curr_symbol;
    bool    accepted;
    int     length, curr_state;
    
    if(!input_strings.is_open())
        return true; // Returning true signifies there was a file error
    
    // Building DFA transition table in 2D-array
    transition_table = build_table();
    
    // Actual DFA modeling occurs within this while loop
    while(input_strings.getline(curr_string, MAX, '\n'))
    {
        curr_state = 0; // Setting starting state
        length = strlen(curr_string);
        for(int i = 0; i < length; ++i)
        {
            accepted = false; // Resetting acceptance determiner w/each string
            curr_symbol = curr_string[i]; // Taking symbols from string to evaluate individually
            // Actual DFA state transitions occur in this switch-case block
            switch(curr_symbol)
            {
                case '0': curr_state = transition_table[curr_state][0] - 48; break;
                case '1': curr_state = transition_table[curr_state][1] - 48; break;
                case '2': curr_state = transition_table[curr_state][2] - 48; break;
                case '3': curr_state = transition_table[curr_state][3] - 48; break;
                case '4': curr_state = transition_table[curr_state][4] - 48; break;
                case '5': curr_state = transition_table[curr_state][5] - 48; break;
                case '6': curr_state = transition_table[curr_state][6] - 48; break;
                case '7': curr_state = transition_table[curr_state][7] - 48; break;
                case '8': curr_state = transition_table[curr_state][8] - 48; break;
                case '9': curr_state = transition_table[curr_state][9] - 48; break;
                case '+': curr_state = transition_table[curr_state][10] - 48; break;
                case '-': curr_state = transition_table[curr_state][11] - 48; break;
                case '.': curr_state = transition_table[curr_state][12] - 48; break;
                case 'e': curr_state = transition_table[curr_state][13] - 48; break;
                case 'E': curr_state = transition_table[curr_state][14] - 48; break;
                default : curr_state = 'D' - 48; // Go dead if any other ASCII symbol
            }
            if(curr_state == 'D' - 48)
                break; // If dead, immediately end evaluation and reject string
        }
        if(curr_state == 2 || curr_state == 4 || curr_state == 7)
            accepted = true; // Accept string if ended in an accept state (States 2, 4, & 7)
        cout << "\n\n--> " << curr_string;
        accepted? cout << " : ACCEPTED" : cout << " : REJECTED";
    }
    
    // Deallocating DFA transition table
    destroy_table(transition_table);
    
    cout << "\n\nPress any key to continue...";
    cin.get(curr_symbol); // Just pausing the program, essentially
    cin.ignore(MAX, '\n');
    delete [] curr_string;
    curr_string = NULL;
    return false; // Returning false signifies no file error occured
}

// Below is the transition table for the DFA represented by the 2D-array
/*
    | State | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | + | - | . | e | E |
    ---------------------------------------------------------------------
    |   0   | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 1 | 1 | 3 | D | D |
    |   1   | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | D | D | 3 | D | D |
    | A 2   | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | D | D | 4 | 5 | 5 |
    |   3   | 4 | 4 | 4 | 4 | 4 | 4 | 4 | 4 | 4 | 4 | D | D | D | D | D |
    | A 4   | 4 | 4 | 4 | 4 | 4 | 4 | 4 | 4 | 4 | 4 | D | D | D | 5 | 5 |
    |   5   | 7 | 7 | 7 | 7 | 7 | 7 | 7 | 7 | 7 | 7 | 6 | 6 | D | D | D |
    |   6   | 7 | 7 | 7 | 7 | 7 | 7 | 7 | 7 | 7 | 7 | D | D | D | D | D |
    | A 7   | 7 | 7 | 7 | 7 | 7 | 7 | 7 | 7 | 7 | 7 | D | D | D | D | D |
*/

char **build_table(void)
{
    int     i; // Multipurpose iterator
    char    **table_arr;
    
    // Allocating 8 x 15 array of chars
    // 15 symbols to consider for each of the 8 states in the DFA
    table_arr = new char*[8];
    for(i = 0; i < 8; ++i)
        table_arr[i] = new char[15];
    
    // Populating DFA transition table with correct values
    for(i = 0; i <= 9; ++i) // Setting same transitions for 0-9
    {
        table_arr[0][i] = '2';
        table_arr[1][i] = '2';
        table_arr[2][i] = '2';
        table_arr[3][i] = '4';
        table_arr[4][i] = '4';
        table_arr[5][i] = '7';
        table_arr[6][i] = '7';
        table_arr[7][i] = '7';
    }
    for(i = 10; i <= 11; ++i) // Setting same transitions for +/-
    {
        table_arr[0][i] = '1';
        table_arr[1][i] = 'D';
        table_arr[2][i] = 'D';
        table_arr[3][i] = 'D';
        table_arr[4][i] = 'D';
        table_arr[5][i] = '6';
        table_arr[6][i] = 'D';
        table_arr[7][i] = 'D';
    }
    // Setting the transitions for '.'
    table_arr[0][i] = '3';
    table_arr[1][i] = '3';
    table_arr[2][i] = '4';
    table_arr[3][i] = 'D';
    table_arr[4][i] = 'D';
    table_arr[5][i] = 'D';
    table_arr[6][i] = 'D';
    table_arr[7][i] = 'D';
    
    for(i = 13; i <= 14; ++i) // Setting same transitions for e/E
    {
        table_arr[0][i] = 'D';
        table_arr[1][i] = 'D';
        table_arr[2][i] = '5';
        table_arr[3][i] = 'D';
        table_arr[4][i] = '5';
        table_arr[5][i] = 'D';
        table_arr[6][i] = 'D';
        table_arr[7][i] = 'D';
    }
    return table_arr;
}

void destroy_table(char **table_arr)
{
    if(!table_arr)
        return;
    for(int i = 0; i < 8; ++i)
    {
        delete [] table_arr[i];
        table_arr[i] = NULL;
    }
    delete [] table_arr;
    table_arr = NULL;
    return;
}