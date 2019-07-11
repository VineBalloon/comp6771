#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <unordered_set>

#include "assignments/wl/lexicon.h"
#include "assignments/wl/word_ladder.h"

int main() {
<<<<<<< HEAD
  std::string start, dest;

  std::cout << "Enter start word (RETURN to quit): ";
  std::getline(std::cin, start);
  if (start.size() <= 1) {
    return 0;
  }

  std::cout << "Enter destination word: ";
  std::getline(std::cin, dest);

  if (start == dest) {
    std::cerr << "words are the same\n";
    return 1;
  }

  /*
  auto lexicon = GetLexicon("data/words.txt");
   */
=======
  auto lexicon = GetLexicon("assignments/wl/words.txt");
>>>>>>> ccea7138d5ab46b24ebe323bfc80738be31c3ae4

  // cut down lexicon to strings of correct size and put in unordered_set
  const std::string::size_type strlen = start.size();
  auto full_lexicon = GetLexicon("data/words.txt");
  std::unordered_set<std::string> lexicon = {};
  for (const auto& item : full_lexicon) {
    if (item.size() == strlen)
      lexicon.insert(item);
  }

  if (lexicon.find(start) == lexicon.end() || lexicon.find(dest) == lexicon.end()) {
    std::cerr << "words are not in lexicon\n";
    return 1;
  }

  std::cout << "Found ladder: ";
  auto ladders = WordLadder(lexicon, start, dest);
  for (const auto& ladder : ladders) {
    for (const auto& word : ladder) {
      std::cout << word + " ";
    }
    std::cout << "\n";
  }
  /*
   */

  return 0;
}
