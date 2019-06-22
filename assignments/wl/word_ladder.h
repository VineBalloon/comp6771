#ifndef ASSIGNMENTS_WL_WORD_LADDER_H_
#define ASSIGNMENTS_WL_WORD_LADDER_H_

#include <set>
#include <string>
#include <vector>

const std::vector<std::vector<std::string>> WordLadder(const std::string&, const std::string& ,
                                                        const std::set<std::string>&);
const std::vector<std::string> GetNeighbours(const std::string&, const std::set<std::string>&);

#endif  // ASSIGNMENTS_WL_WORD_LADDER_H_
