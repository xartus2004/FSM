#include <bits/stdc++.h>

using namespace std;

class FSM {
    public:
    vector<string> states;
    vector<char> alphabets;
    map<pair<string,char>,string> transition_function;
    string start_state;
    vector<string> final_states;
    string current_state;

    FSM(vector<string> states,vector<char> alphabets,map<pair<string,char>,string> transition_function,string start_state,vector<string> final_states):states(states),alphabets(alphabets),transition_function(transition_function),start_state(start_state),final_states(final_states) {}

    bool transition(char input_symbol) {
      auto it = transition_function.find({current_state,input_symbol});
      if(it == transition_function.end()) return false;
      current_state = it->second;
      return true;
    }

    bool run(const string& input_string) {
      current_state = start_state;
      for(char symbol:input_string){
        if(!transition(symbol)) return false;
      }
      return find(final_states.begin(),final_states.end(),current_state) != final_states.end();
    }
};

vector<string> split(const string& s,char delimiter) {
  vector<string> tokens;
  string token;
  istringstream tokenStream(s);
  while(getline(tokenStream,token,delimiter))
    tokens.push_back(token);
  return tokens;
}

FSM build_fsm() {
  string input;

  cout<<"Enter states: ";
  getline(cin,input);
  vector<string> states = split(input,',');

  cout<<"Enter alphabets: ";
  getline(cin,input);
  vector<char> alphabet(input.begin(),input.end());
  alphabet.erase(remove(alphabet.begin(),alphabet.end(),','),alphabet.end());

  cout<<"Enter Start State: ";
  string start_state;
  getline(cin,start_state);

  cout<<"Enter the final states: ";
  getline(cin,input);
  vector<string> final_states = split(input,',');

  map<pair<string,char>,string> transition_function;
  cout<<"Enter transition function(current_state,input_symbol,next_state)"<<endl;
  cout<<"Enter 'done' when finished"<<endl;

  while(true) {
    getline(cin,input);
    if(input=="done") break;

    auto parts = split(input,',');
    if(parts.size() != 3) {
      cout<<"Invalid Input"<<endl;
      continue;
    }
    transition_function[{parts[0],parts[1][0]}]=parts[2];
  }
  return FSM(states,alphabet,transition_function,start_state,final_states);
}

int main()
{
  FSM fsm = build_fsm();
  string input_string;

  while(true) {
    cout<<"Enter an Input String";
    getline(cin,input_string);

    if(input_string == "quit")  break;

    if(fsm.run(input_string)) cout<<"Accepted"<<endl;
    else  cout<<"Rejected"<<endl;
  }
  return 0;
}