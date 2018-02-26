#include "scanner.h"
#include <sstream>
#include <iomanip>
#include <cctype>
#include <algorithm>

/**
 * C++ Starter code for CS241 A3
 * Written by Sean Harrap in Winter 2018
 * All code requires C++14, so if you're getting
 * compile errors make sure to use -std=c++14.
 *
 * This file contains helpers for asm.cc and
 * should not need to be modified by you.
 */

namespace CS241 {
Token::Token(std::string kind, std::string lexeme):kind(kind), lexeme(lexeme) {}

std::string Token::getKind() const { return kind; }
std::string Token::getLexeme() const { return lexeme; }




ScanningFailure::ScanningFailure(std::string message):message(message) {}

std::string ScanningFailure::getMessage() const { return message; }

AsmDFA::AsmDFA() {
  acceptingStates = {"ID", "NUM", "FINISH", "LGE", "DIVIDE", "COMMENT", "WHITESPACE"};
  //Non-accepting states are "START", "NOT, "ERROR"
}

// The transition function for the DFA. Could be implemented
// using a map or something more fancy, but this is implemented using nested
// if statements for simplicity.
std::string AsmDFA::transition(std::string state, char nextChar, std::string sofar) const {
  if (state == "START") {
    if (isalpha(nextChar))      return "ID";
    else if (nextChar == '(' || nextChar == ')' || nextChar == '{' ||
             nextChar == '}' || nextChar == '0' || nextChar == '+' ||
             nextChar == '-' || nextChar == '*' || nextChar == '%' ||
             nextChar == ',' || nextChar == ';')    return "FINISH";
    else if (nextChar == '/') return "DIVIDE";
    else if (isdigit(nextChar)) return "NUM";
    else if (nextChar == '!')   return "NOT"; // got up to here did 3 so far
    else if (nextChar == '=' || nextChar == '<' || nextChar == '>')   return "LGE";
    else if (isspace(nextChar)) return "WHITESPACE";
  } else if (state == "ID") {
    std::string check = sofar+nextChar;
    if (check == "int" || check == "if" || check == "else" ||
        check == "while" || check == "return" || check == "wain")	return "FINISH";
    else if (isalnum(nextChar))      return "ID";
  } else if (state == "NUM") {
      if (isdigit(nextChar)) return "NUM";
  } else if (state == "NOT") {
      if (nextChar == '=')     return "FINISH";
  } else if (state == "LGE") {
      if (nextChar == '=')     return "FINISH";
  } else if (state == "DIVIDE" && nextChar == '/') { 
    return "COMMENT";
  } else if (state == "COMMENT") {
    if (nextChar != '\n')       return "COMMENT";
  } else if (state == "WHITESPACE") {
    if (isspace(nextChar))      return "WHITESPACE";
  } else if (state == "FINISH") {
//   if (!isspace(nextChar) && (sofar == "int"  ||
//			       sofar == "if"   ||
//			       sofar == "else" ||
//			       sofar == "while"||
//			       sofar == "return")) return "ID";
  }
  return "FAIL";
}

bool AsmDFA::failed(std::string state) const {
  return state == "FAIL";
}

bool AsmDFA::accept(std::string state) const {
  return acceptingStates.count(state) > 0;
}

std::string AsmDFA::start() const {
  return "START";
}

std::vector<Token> AsmDFA::simplifiedMaximalMunch(std::string input) const {
  std::vector<Token> result;

  std::string state = start();
  std::string munched_input;

  // We can't use a range-based for loop effectively here
  // since the iterator doesn't always increment.
  for (std::string::iterator input_posn = input.begin();
       input_posn != input.end();) {

    std::string old_state = state;
    state = transition(state, *input_posn, munched_input);
    
    if (!failed(state)) {
      munched_input += *input_posn;
      old_state = state;

      ++input_posn;
    }
     
    if (input_posn == input.end() || failed(state)) {
      if (accept(old_state)) {
        result.push_back(Token(old_state, munched_input));

        munched_input = "";
        state = start();
      } else {
        if (failed(state)) {
          munched_input += *input_posn;
        }
        throw ScanningFailure("ERROR: Simplified maximal munch failed on input: -"
                             + munched_input + "-" + old_state + " " + state);
      }
    } 
  }

  return result;
}
std::vector<Token> AsmDFA::scan(std::string input) const {
  std::vector<Token> tokens = simplifiedMaximalMunch(input);
  // We need to:
  // * Convert "ZERO" tokens to "INT" tokens.
  // * Convert "DOTID" tokens to "WORD" tokens if they're ".word",
  //   and throw an exception otherwise.
  // * Verify that INTs, HEXINTs, and REGs occupy the proper ranges:
  //   * -2^31 to 2^32-1 for INT (both signed and unsigned INT are supported)
  //   * 0 to 2^32-1 for HEXINT
  //   * 0 to 31 for REG
  // * Remove WHITESPACE and COMMENT tokens entirely.
  std::vector<Token> newTokens;
  for (auto &token : tokens) {
    if (token.getKind() == "ID" || token.getKind() == "NUM") {
      newTokens.push_back(token);
    } else if (token.getKind() == "FINISH" || token.getKind() == "DIVIDE") {
        if (token.getLexeme() == "0") newTokens.push_back(Token("NUM",token.getLexeme()));
        else if (token.getLexeme() == "int") newTokens.push_back(Token("INT",token.getLexeme()));
        else if (token.getLexeme() == "return") newTokens.push_back(Token("RETURN",token.getLexeme()));
        else if (token.getLexeme() == "if") newTokens.push_back(Token("IF",token.getLexeme()));
        else if (token.getLexeme() == "else") newTokens.push_back(Token("ELSE",token.getLexeme()));
        else if (token.getLexeme() == "while") newTokens.push_back(Token("WHILE",token.getLexeme()));
        else if (token.getLexeme() == "int") newTokens.push_back(Token("INT",token.getLexeme()));
        else if (token.getLexeme() == "wain") newTokens.push_back(Token("ID", token.getLexeme()));
        else if (token.getLexeme() == "{") newTokens.push_back(Token("LBRACE",token.getLexeme()));
        else if (token.getLexeme() == "}") newTokens.push_back(Token("RBRACE",token.getLexeme()));
        else if (token.getLexeme() == "(") newTokens.push_back(Token("LPAREN",token.getLexeme()));
        else if (token.getLexeme() == ")") newTokens.push_back(Token("RPAREN",token.getLexeme()));
        else if (token.getLexeme() == "+") newTokens.push_back(Token("PLUS",token.getLexeme()));
        else if (token.getLexeme() == "-") newTokens.push_back(Token("MINUS",token.getLexeme()));
        else if (token.getLexeme() == "*") newTokens.push_back(Token("STAR",token.getLexeme()));
        else if (token.getLexeme() == "/") newTokens.push_back(Token("SLASH",token.getLexeme()));
        else if (token.getLexeme() == "%") newTokens.push_back(Token("PCT",token.getLexeme()));
        else if (token.getLexeme() == ",") newTokens.push_back(Token("COMMA",token.getLexeme()));
        else if (token.getLexeme() == ";") newTokens.push_back(Token("SEMI",token.getLexeme()));
        else if (token.getLexeme() == "!=") newTokens.push_back(Token("NE",token.getLexeme()));
        else if (token.getLexeme() == "<=") newTokens.push_back(Token("LE",token.getLexeme()));
        else if (token.getLexeme() == ">=") newTokens.push_back(Token("GE",token.getLexeme()));
        else if (token.getLexeme() == "==") newTokens.push_back(Token("EQ",token.getLexeme()));
    } else if (token.getKind() == "LGE") { 
        if (token.getLexeme() == "<") newTokens.push_back(Token("LT",token.getLexeme()));
        else if (token.getLexeme() == ">") newTokens.push_back(Token("GT",token.getLexeme()));
	else if (token.getLexeme() == "=") newTokens.push_back(Token("BECOMES", token.getLexeme()));
    }
  }
  return newTokens;
}
}

