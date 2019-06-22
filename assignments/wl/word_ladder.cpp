#include <algorithm>
#include <deque>
#include <iterator>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

#include <iostream>

#include "assignments/wl/word_ladder.h"

#define ALPHA_LEN 26

// GetNeighbours returns set of neighbours of str in the lexicon
const std::set<std::string> GetNeighbours(const std::unordered_set<std::string>& lexicon,
                                          const std::string& str) {
  std::set<std::string> neighbours;
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
        neighbours.insert(next);
      }
    }
  }
  return neighbours;
}

// WordLadder returns the word ladder(s) from the start to dest words in the lexicon
// assume input generates valid ladder(s)
const std::set<std::vector<std::string>> WordLadder(const std::unordered_set<std::string>& lexicon,
                                                    const std::string& start,
                                                    const std::string& dest) {
  // ladders is our queue of string vectors
  std::deque<std::vector<std::string>> ladders;
  std::set<std::vector<std::string>> output;

  // put a starting ladder into our deque
  std::vector<std::string> begin = {start};
  ladders.push_back(begin);

  // seen bookeeping
  std::vector<std::string>::size_type curr_size = begin.size();
  std::set<std::string> seen;
  std::set<std::string> cache;
  seen.insert(start);

  // same-length path bookeeping
  bool ret_flag = false;

  // BFS
  for (auto curr_ladder = ladders.front(); !ladders.empty(); ladders.pop_front()) {
    // dequeue ladder
    curr_ladder = ladders.front();

    // merge seen cache
    if (curr_ladder.size() != curr_size) {
      if (ret_flag) {
        // hit a longer ladder, return
        return output;
      } else {
        seen.insert(cache.begin(), cache.end());
        curr_size = curr_ladder.size();
      }
    }

    // get first word
    const auto curr_word = curr_ladder.back();

    // check dest
    if (curr_word == dest) {
      // add path to output
      if (!ret_flag) {
        // hit first shortest ladder, set flags
        ret_flag = true;
      }
      // add ladder to output
      output.insert(curr_ladder);
    } else {
      // create new ladders and push onto deque
      const auto neighbours = GetNeighbours(lexicon, curr_word);
      for (const auto& neighbour : neighbours) {
        // avoid adding seen words
        if (seen.find(neighbour) == seen.end()) {
          const std::string& new_word = neighbour;
          std::vector<std::string> new_ladder = curr_ladder;
          new_ladder.push_back(new_word);
          ladders.push_back(new_ladder);
          cache.insert(neighbour);
        }
      }
    }
  }
  return output;
}
