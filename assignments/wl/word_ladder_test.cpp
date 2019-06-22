/*
 * Testing Methodology:
 * - Unit test
 *  - Make simple tests
 *  - Get coverage
 *  - Test intended behaviour
 */
#include "assignments/wl/lexicon.h"
#include "assignments/wl/word_ladder.h"
#include "catch.h"

// SetInLexicon checks if all elements of the neighbours set are in
bool SetInLexicon(const std::set<std::string>& lexicon, const std::set<std::string>& neighbours) {
  for (const auto& item : neighbours) {
    if (lexicon.find(item) == lexicon.end())
      return false;
  }
  return true;
}

// SetInLexicon overloaded to handle set of ladders
bool SetInLexicon(const std::set<std::string>& lexicon,
                  const std::set<std::vector<std::string>>& ladders) {
  for (const auto& ladder : ladders) {
    for (const auto& item : ladder) {
      if (lexicon.find(item) == lexicon.end())
        return false;
    }
  }
  return true;
}

// LaddersSameSize checks if all ladders have the same size
bool LaddersSameSize(const std::set<std::vector<std::string>>& ladders) {
  std::vector<std::string>::size_type size = ladders.begin()->size();
  for (const auto& ladder : ladders) {
    if (ladder.size() != size) {
      return false;
    }
  }
  return true;
}

SCENARIO("GetNeighbours returns valid members of the lexicon", "[GetNeighbours]") {
  GIVEN("A small lexicon with words that have and don't have neighbours") {
    auto lexicon = std::set<std::string>{"cat", "cot", "rat", "can", "con", "dog", "zzz"};

    REQUIRE(lexicon.size() > 1);

    WHEN("giving word with no neighbours") {
      auto got = GetNeighbours(lexicon, "zzz");
      THEN("returns an empty set") { REQUIRE(got.empty()); }
    }

    WHEN("giving word with neighbours") {
      auto got = GetNeighbours(lexicon, "cat");
      THEN("return only elements in lexicon") {
        REQUIRE(!got.empty());
        REQUIRE(SetInLexicon(lexicon, got));
      }
    }
  }
}

SCENARIO("WordLadder works correctly", "[WordLadder]") {
  GIVEN("The proper lexicon") {
    auto lexicon = GetLexicon("data/words.txt");

    WHEN("con -> cat") {
      THEN("there should be 2 valid ladders of size 3") {
        auto got = WordLadder(lexicon, "con", "cat");

        REQUIRE(SetInLexicon(lexicon, got));
        REQUIRE(got.size() == 2);
        REQUIRE(got.begin()->size() == 3);
        REQUIRE(LaddersSameSize(got));
      }
    }

    WHEN("cat -> dog") {
      THEN("there should be 2 valid ladders of size 4") {
        auto got = WordLadder(lexicon, "cat", "dog");

        REQUIRE(SetInLexicon(lexicon, got));
        REQUIRE(got.size() == 2);
        REQUIRE(got.begin()->size() == 4);
        REQUIRE(LaddersSameSize(got));
      }
    }

    WHEN("bean -> make") {
      THEN("there should be 19 valid ladders of size 7") {
        auto got = WordLadder(lexicon, "bean", "make");

        REQUIRE(SetInLexicon(lexicon, got));
        REQUIRE(got.size() == 19);
        REQUIRE(got.begin()->size() == 7);
        REQUIRE(LaddersSameSize(got));
      }
    }
  }
}
