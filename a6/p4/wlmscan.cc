#include "scanner.h"
#include <iostream>
using std::vector;
using std::string;
using CS241::Token;

/**
 * C++ Starter code for CS241 A3
 * Written by Sean Harrap in Winter 2018
 * All code requires C++14, so if you're getting
 * compile errors make sure to use -std=c++14.
 *
 * This file contains the main function of your program.
 * You will want to begin by modifying the assemble() function,
 * and are welcome to add more functions and files as needed.
 */

// You can throw this class to signal exceptions encountered while assembling
class AssemblingFailure {
  std::string message;
  public:
    AssemblingFailure(std::string message):message(message) {}

    std::string getMessage() const { return message; }
};

void assemble(vector<vector<Token>> &tokenLines) {
  for (auto &line : tokenLines) {
    // For now just print out the tokens, one line at a time.
    // You will probably want to replace this with your code.
    for (auto &token : line) {
      std::cout << token.getKind() << " " << token.getLexeme() << std::endl;
    }
  }
}

// Convert the input into a sequence of tokens.
// This should not need to be modified, but you can if you want to.
int main() {
  CS241::AsmDFA theDFA;
  vector<vector<Token>> tokenLines;
  string line;

  try {
    while (getline(std::cin, line)) {
      tokenLines.push_back(theDFA.scan(line));
    }
  } catch (CS241::ScanningFailure &f) {
    std::cerr << f.getMessage() << std::endl;

    return 1;
  }

  try {
    assemble(tokenLines);
  } catch (AssemblingFailure &f) {
    std::cerr << f.getMessage() << std::endl;

    return 1;
  }

  return 0;
}

