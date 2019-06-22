#include <algorithm>
#include <iterator>
#include <deque>
#include <set>
#include <string>
#include <vector>
#include <iterator>

#include <iostream>

#include "assignments/wl/word_ladder.h"

#define ALPHA_LEN 26

// GetNeighbours returns vector of the neighbours of str in the lexicon
const std::vector<std::string> GetNeighbours(const std::string& str, const std::set<std::string>& lexicon) {
  std::vector<std::string> neighbours;
  for (std::string::size_type i = 0; i < str.size(); ++i) {
    for (int offset = 1; offset < ALPHA_LEN; ++offset) {
      // copy string
      auto next = str;
      // offset index
      int ch = next[i] + offset;
      next[i] = (ch <= 'z') ? ch : (ch % 'z') + ('a' - 1);
      // search lexicon
      if (lexicon.find(next) != lexicon.end()) {
        // append candidate
        neighbours.push_back(next);
      }
    }
  }
  return neighbours;
}

// WordLadder returns the word ladder(s) from the start to dest words in the lexicon
// assume input generates valid ladder(s)
const std::vector<std::vector<std::string>> WordLadder(const std::string& start,
    const std::string& dest, const std::set<std::string>& lexicon) {
  // ladders is our queue of string vectors
  std::deque<std::vector<std::string>> ladders;
  std::vector<std::vector<std::string>> output;

  // put a starting ladder into our deque
  std::vector<std::string> begin = {start};
  ladders.push_back(begin);

  // same-length path bookeeping
  std::deque<std::vector<std::string>>::size_type shortest_len = 0;
  bool ret_flag = false;

  // BFS
  for (auto curr_ladder = ladders.front(); !ladders.empty(); ladders.pop_front()) {
    //std::cout << "sladders size: " << ladders.size() << "\n";
    // dequeue ladder
    curr_ladder = ladders.front();
    // get first word
    const auto curr_word = curr_ladder.back();
    //std::cout << "Popped: " + curr_word + "\n";

    if (ret_flag && curr_ladder.size() > shortest_len) {
      // hit a longer ladder, return
      return output;
    }

    // check dest
    if (curr_word == dest) {
      //std::cout << "found\n";
      // add path to output
      if (!ret_flag) {
        // hit first shortest ladder, set flags
        ret_flag = true;
        shortest_len = curr_ladder.size();
      }
      // add ladder to output
      output.push_back(curr_ladder);
    } else {
      // create new ladders and push onto deque
      const auto neighbours = GetNeighbours(curr_word, lexicon);
      for (const auto& neighbour : neighbours) {
        // avoid adding seen words
        if (std::find(neighbours.begin(), neighbours.end(), neighbour) != neighbours.end()) {
          const std::string& new_word = neighbour;
          std::vector<std::string> new_ladder = curr_ladder;
          new_ladder.push_back(new_word);
          ladders.push_back(new_ladder);
        }
      }
    }
  }
  //std::cout << "Exhausted search\n";
  // exhausted search, return
  return output;
}