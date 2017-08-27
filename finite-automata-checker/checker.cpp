/*Automaton checker to accept a string based on the automata provided in class.
  input.txt format is 
  no. of states
  no. of final states 
  intial state
  final states
  transition state matrix
  note: the states are 0 indexed
  also if case-insensitivity is desired add tolower where ever required.
*/


#include<bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i =a;i<b;i++)

unsigned int n, f; // n- no.of states, f- no. of final states;
const vector<char> input_domain = {'a', 'b'}; // valid char set
string in; //input string
vector<int> ini, final; //vectors of initial states and final states
vector<vector<int>> next_state; //transition table

fstream fin("input.txt"); // file to read from (input.txt)

void build_transition_table(unsigned int n) {
    next_state.resize(n, vector<int>(input_domain.size(), -1));
    rep(i, 0, n) {
        {
            cout<<i<<"\t";
            rep(j, 0, input_domain.size()) {
                fin >> next_state[i][j];
                cout<<next_state[i][j]<<"\t";
            }
            cout<<endl;
        }
    }
}

//transition
int transition(char input, int curr_state) {
    int idx = input - 'a';
    if (idx > input_domain.size())
        return -1;
    return next_state[curr_state][idx];

};

bool final_state(int state, int pos) {
    for (int i = 0; i < final.size(); i++) {
        if (final[i] == state and pos == in.size() - 1)
            return true;
    }
    return false;
}

void display(){
    cout<<"\tTransition table: \n";
    cout<<"states\t";
    for(int i=0;i<input_domain.size();i++){
        cout<<input_domain[i]<<"\t";
    }
    cout<<"\n--------------------\n";
}

int main(void) {

    fin >> n >> f;
    int temp;
    fin >> temp;
    ini.push_back(temp);

    rep(i, 0, f) {
        fin >> temp;
        final.push_back(temp);
    }
    display();
    build_transition_table(n);

    //automata simulation

    cout << "input a string: ";
    cin >> in;
    int pos = 0, flag = 0, curr = ini[0];

    while (pos < in.length()) {
        int next = transition(in[pos], curr);
        if (next == -1) {
            flag = -1;
            cout << "String Rejected\n";
            break;
        } else {
            curr = next;
            if (final_state(curr, pos)) {
                flag = 1;
                cout << "String Accepted\n";
                break;
            }
        }
        pos++;
    }
    if (flag == 0) {
        cout << "String Rejected\n";
    }
}
