#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
bool validWord(const string& word, const set<string>& dict);

void genTheWords(
    string current, // current build/combination of the word
    int index, // index for in
    const string& in, const string& floating, const set<string>& dict, 
    set<string>& valid_words, // set of valid words to find
    map<char, int>& float_usage // map that tracks how many times a floating char has been used (0-1) 
                                // 0 = not used
                                // 1 = used
);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in, /* - string of fixed, correct characters and `-`s to indicate the 
                                length of string and locations that must be filled in */
    const std::string& floating, // - Characters that must be used somewhere in the word
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> valid_words; // set of valid words that fit criteria
    string init_w = in; // taking input of valid letters
    map<char, int> float_usage; 

    genTheWords("", 0, in, floating, dict, valid_words, float_usage);

    return valid_words;
}

// Define any helper functions here

bool validWord(const string& word, const set<string>& dict) {
    return dict.find(word) != dict.end();
}

void genTheWords(
    string current, 
    int index, 
    const string& in, const string& floating, const set<string>& dict, 
    set<string>& valid_words,
    map<char, int>& float_usage) 
{
        // base condition
        if (index == in.length()) {
          
          // check if all floating chars are in current
          for (size_t i = 0; i < floating.length(); i++) {
            char ph = floating[i];
            if (float_usage[ph] == 0) {
              return;
            }
          }

          if (validWord(current, dict)) {
              valid_words.insert(current);
          }

          return;
        }

        char next_char = in[index];
        if (next_char != '-') { // for already predetermined letters
          genTheWords(current + next_char, index + 1, in, floating, dict, valid_words, float_usage);
        } else {
          // for loop handling float chars
          for (size_t i = 0; i < floating.length(); i++) {
            char ph = floating[i];
            if (float_usage[ph] == 0) {
              float_usage[ph]++;
              genTheWords(current + ph, index + 1, in, floating, dict, valid_words, float_usage);
              float_usage[ph]--;
            }
          }

          // for loop handling general alphabet
          for (char ph = 'a'; ph <= 'z'; ph++) {
            genTheWords(current + ph, index + 1, in, floating, dict, valid_words, float_usage);
          }
        }
}