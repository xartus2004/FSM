#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

class FSM {
private:
    std::vector<std::string> states;
    std::vector<char> alphabet;
    std::map<std::pair<std::string, char>, std::string> transition_function;
    std::string start_state;
    std::vector<std::string> accept_states;
    std::string current_state;

public:
    FSM(std::vector<std::string> states, std::vector<char> alphabet,
        std::map<std::pair<std::string, char>, std::string> transition_function,
        std::string start_state, std::vector<std::string> accept_states)
        : states(states), alphabet(alphabet), transition_function(transition_function),
          start_state(start_state), accept_states(accept_states), current_state(start_state) {}

    bool transition(char input_symbol) {
        auto it = transition_function.find({current_state, input_symbol});
        if (it == transition_function.end()) {
            return false;
        }
        current_state = it->second;
        return true;
    }

    bool run(const std::string& input_string) {
        current_state = start_state;
        for (char symbol : input_string) {
            if (!transition(symbol)) {
                return false;
            }
        }
        return std::find(accept_states.begin(), accept_states.end(), current_state) != accept_states.end();
    }
};

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

FSM build_fsm() {
    std::string input;
    
    std::cout << "Enter states (comma-separated): ";
    std::getline(std::cin, input);
    std::vector<std::string> states = split(input, ',');

    std::cout << "Enter alphabet symbols (comma-separated): ";
    std::getline(std::cin, input);
    std::vector<char> alphabet(input.begin(), input.end());
    alphabet.erase(std::remove(alphabet.begin(), alphabet.end(), ','), alphabet.end());

    std::cout << "Enter start state: ";
    std::string start_state;
    std::getline(std::cin, start_state);

    std::cout << "Enter accept states (comma-separated): ";
    std::getline(std::cin, input);
    std::vector<std::string> accept_states = split(input, ',');

    std::map<std::pair<std::string, char>, std::string> transition_function;
    std::cout << "Enter transition function (format: current_state,input_symbol,next_state):" << std::endl;
    std::cout << "Enter 'done' when finished." << std::endl;
    while (true) {
        std::getline(std::cin, input);
        if (input == "done") break;
        
        auto parts = split(input, ',');
        if (parts.size() != 3) {
            std::cout << "Invalid input. Please try again." << std::endl;
            continue;
        }
        transition_function[{parts[0], parts[1][0]}] = parts[2];
    }

    return FSM(states, alphabet, transition_function, start_state, accept_states);
}

int main() {
    FSM fsm = build_fsm();
    
    std::string input_string;
    while (true) {
        std::cout << "Enter an input string (or 'quit' to exit): ";
        std::getline(std::cin, input_string);
        
        if (input_string == "quit") break;
        
        if (fsm.run(input_string)) {
            std::cout << "Accepted" << std::endl;
        } else {
            std::cout << "Rejected" << std::endl;
        }
    }

    return 0;
}