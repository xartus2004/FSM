#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

class FSM {
  private:
    vector<string> states;
    vector<char> alphabets;
    map<pair<string,char>,string> transition_function;
    string start_state;
    vector<string> accept_states;
    string current_state;

  public:
    FSM(vector<string> states,vector<char> alphabets,map<pair<string,char>,string> transition_function,string start_state,vector<string> accept_states):states(states),alphabets(alphabets),transition_function(transition_function),start_state(start_state),accept_states(accept_states) {}

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
      return find(accept_states.begin(),accept_states.end(),current_state) != accept_states.end();
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

  cout<<"Enter states(separated by comma): ";
  getline(cin,input);
  vector<string> states = split(input,',');

  cout<<"Enter alphabets(separated by comma): ";
  getline(cin,input);
  vector<char> alphabet(input.begin(),input.end());
  alphabet.erase(remove(alphabet.begin(),alphabet.end(),','),alphabet.end());

  cout<<"Enter Start State: ";
  string start_state;
  getline(cin,start_state);

  cout<<"Enter the accept states(seperated by commas): ";
  getline(cin,input);
  vector<string> accept_states = split(input,',');

  map<pair<string,char>,string> transition_function;
  cout<<"Enter transition function(current_state,input_symbol,next_state)"<<endl;
  cout<<"Enter 'ok' when finished"<<endl;
  while(true) {
    getline(cin,input);
    if(input=="ok") break;

    auto parts = split(input,',');
    if(parts.size() != 3) {
      cout<<"Invalid Input"<<endl;
      continue;
    }
    transition_function[{parts[0],parts[1][0]}]=parts[2];
  }
  return FSM(states,alphabet,transition_function,start_state,accept_states);
}

int main()
{
  FSM fsm = build_fsm();
  string input_string;

  while(true) {
    cout<<"Enter an Input String('quit' to exit)";
    getline(cin,input_string);

    if(input_string == "quit")  break;

    if(fsm.run(input_string)) cout<<"Accepted"<<endl;
    else  cout<<"Rejected"<<endl;
  }
  return 0;
}