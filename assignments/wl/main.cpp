#include <iostream>

#include "assignments/wl/lexicon.h"
#include "assignments/wl/word_ladder.h"

int main() {
  auto lexicon = GetLexicon("data/words.txt");
  std::string start, dest;

  std::cout << "Enter start word (RETURN to quit): ";
  std::cin >> start;
  if (start.size() <= 1) {
    std::cout << "Bye\n";
    return 0;
  }

  std::cout << "Enter destination word: ";
  std::cin >> dest;

  if (start == dest) {
    std::cerr << "words are the same\n";
    return 1;
  }

  if (lexicon.find(start) == lexicon.end() ||
      lexicon.find(dest) == lexicon.end()) {
    std::cerr << "words are not in lexicon\n";
    return 1;
  }

  /*
  for (const auto& word : lexicon) {
    std::cout << word + " ";
  }
  */

  /*
  auto neighbours = GetNeighbours(start, lexicon);
  for (const auto& neighbour : neighbours) {
    std::cout << neighbour + " ";
  }
   */

  std::cout << "Found ladder: ";
  auto ladders = WordLadder(start, dest, lexicon);
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
