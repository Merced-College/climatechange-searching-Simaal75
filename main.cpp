#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

struct State {
    int fips;
    int year;
    float tempF;
    float tempC;
};

int main() {
    // Create a vector to hold the states
    std::vector<State> states;
    std::ifstream inputFile("climdiv_state_year.csv"); // Updated to use the correct file name
    std::string line;

    // Read the data from the file and store it in the states vector
    while (std::getline(inputFile, line)) {
        State s;
        std::istringstream stream(line);
        char ch; // to discard commas
        stream >> ch >> s.fips >> ch >> s.year >> ch >> s.tempF >> ch >> s.tempC;
        states.push_back(s); // Add state to vector
    }

    // Prompt user for FIPS code input
    while (true) {
        std::cout << "Enter a state name to search (or 'exit' to quit): ";
        std::string input;
        std::cin >> input;
        
        if (input == "exit") {
            break; // Exit the loop if the user types 'exit'
        }
        
        // Convert the input to an integer (FIPS code)
        int searchFips = std::stoi(input);
        int mostRecentYear = -1;
        State mostRecentState;

        // Search through the states for the matching FIPS code and most recent year
        for (const auto& state : states) {
            if (state.fips == searchFips) {
                if (state.year > mostRecentYear) {
                    mostRecentYear = state.year;
                    mostRecentState = state; // Update to the most recent state
                }
            }
        }

        // Output the results or state not found
        if (mostRecentYear == -1) {
            std::cout << "State not found. Enter a valid FIPS code." << std::endl;
        } else {
            std::cout << "FIPS: " << mostRecentState.fips << ", Year: " << mostRecentState.year
                      << ", Temp (F): " << mostRecentState.tempF << ", Temp (C): " << mostRecentState.tempC << std::endl;
        }
    }

    return 0;
}
