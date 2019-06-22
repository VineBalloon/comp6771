#ifndef ASSIGNMENTS_WL_WORD_LADDER_H_
#define ASSIGNMENTS_WL_WORD_LADDER_H_

#include <set>
#include <string>
#include <unordered_set>
#include <vector>

const std::set<std::string> GetNeighbours(const std::unordered_set<std::string>& lexicon,
                                          const std::string& str);

const std::set<std::vector<std::string>>
WordLadder(const std::unordered_set<std::string>& lexicon,
                                                    const std::string& start,
                                                    const std::string& dest);

#endif  // ASSIGNMENTS_WL_WORD_LADDER_H_
