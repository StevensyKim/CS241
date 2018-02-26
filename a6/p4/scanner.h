#ifndef SCANNER_H
#define SCANNER_H
#include <string>
#include <vector>
#include <set>
#include <cstdint>

/**
 * C++ Starter code for CS241 A3
 * Written by Sean Harrap in Winter 2018
 * All code requires C++14, so if you're getting
 * compile errors make sure to use -std=c++14.
 *
 * This file contains helpers for asm.cc and
 * should not need to be modified by you.
 * However, its comments contain important information
 * and it is recommended that you read the entire file
 * before you start modifying asm.cc.
 */

namespace CS241 {
/* A scanned token produced by the scanner.
 * The "kind" tells us what kind of token it is
 * (see the AsmDFA::scan() function for a full list),
 * while the "lexeme" tells us exactly what text
 * the programmer typed. For example, the token
 * "abc" might have kind "ID" and lexeme "abc".
 *
 * While you can create tokens with any kind and
 * lexeme, the list of kinds produced by the
 * starter code can be found in the documentation
 * for AsmDFA::scan below.
 */
class Token {
  private:
    /* It would be more efficient to manage kinds as
     * an enum, but we use strings for simplicity.
     */
    std::string kind;
    std::string lexeme;

  public:
    Token(std::string kind, std::string lexeme);

    std::string getKind() const;
    std::string getLexeme() const;

};
/* An exception class thrown when the AsmDFA class
 * encounters an error while scanning.
 */
class ScanningFailure {
  std::string message;
  public:
    ScanningFailure(std::string message);

    std::string getMessage() const;
};

/* Represents a DFA (which you will see formally in class
 * around the time of Assignment 5) to handle the scanning
 * process. You should not need to interact with this directly:
 * it is handled through the starter code.
 */
class AsmDFA {
  private:
    /* A set of all accepting states for the DFA.
     * Currently non-accepting states are not actually present anywhere
     * in memory, but a list can be found in scanner.cc if you're interested.
     */
    std::set<std::string> acceptingStates;

    /* Tokenizes an input string according to the SMM algorithm.
     * You will learn the SMM algorithm in class around the time of Assignment 6.
     */
    std::vector<Token> simplifiedMaximalMunch(std::string input) const;

  public:
    /* Initializes the accepting states for the DFA.
     */
    AsmDFA();

    /* Returns the state corresponding to following a transition
     * from the given starting state on the given character,
     * or a special fail state if the transition does not exist.
     */
    std::string transition(std::string state, char nextChar, std::string sofar) const;

    /* Checks whether the state returned by transition
     * corresponds to failure to transition.
     */
    bool failed(std::string state) const;

    /* Checks whether the state returned by transition
     * is an accepting state.
     */
    bool accept(std::string state) const;

    /* Returns the starting state of the DFA
     */
    std::string start() const;

    /* Scans some input (can be the entire file or just one line)
     * and produces the corresponding list of tokens.
     * 
     * Scan returns tokens of the following kinds:
     * ID: Identifiers and keywords.
     * NUM: a string consisting of a single digit (in the range 0-9)
            or two or more digits, the first of which is nonzero.
     * LPAREN: the string "("
     * RPAREN: the string ")"
     * LBRACE: the string "{"
     * RBRACE: the string "}"
     * RETURN: the string "return"
     * IF: the string "if"
     * ELSE: the string "else"
     * WHILE: the string "while"
     * INT: the string "int"
     * BECOMES: the string "="
     * EQ: the string "=="
     * NE: the string "!="
     * LT: the string "<"
     * GT: the string ">"
     * LE: the string "<="
     * GE: the string ">="
     * PLUS: the string "+"
     * MINUS: the string "-"
     * STAR: the string "*"
     * SLASH: the string "/"
     * PCT: the string "%"
     * COMMA: the string ","
     * SEMI: the string ";"
     */
    std::vector<Token> scan(std::string input) const;
};
}

#endif

