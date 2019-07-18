/*

   Overall approach:
    - Unit testing all parts of the class implementation
        - Testing if behaviour of implementation matches specification
        - Covering all parts of class implementation increases code coverage
    - Exception Testing
        - Test that exceptions are thrown when they should be

*/

// "assignments/ev/euclidean_vector"
#include <cmath>
#include <sstream>
#include <string>
#include <utility>

#include "assignments/ev/euclidean_vector.h"
#include "catch.h"

const int correct_size = 3;
const int another_size = 4;
const double some_double = 1.5;

/* constructor testing */
SCENARIO("Using EuclideanVector constructors") {
  GIVEN("A size") {
    const int siz = correct_size;
    WHEN("I use it to construct a Euclidean Vector") {
      EuclideanVector ev(siz);
      THEN("Size of the Euclidean Vector is the size I started with") {
        REQUIRE(ev.GetNumDimensions() == siz);
      }
      THEN("All magnitudes are initialised to 0.") {
        REQUIRE(ev.at(0) == static_cast<double>(0));
        REQUIRE(ev.at(1) == static_cast<double>(0));
        REQUIRE(ev.at(2) == static_cast<double>(0));
      }
    }
  }

  GIVEN("A size and a double") {
    WHEN("I use the two-argument constructor") {
      const int siz = correct_size;
      EuclideanVector ev(siz, 1.5);
      THEN("Size of the Euclidean Vector is the size I started with") {
        REQUIRE(ev.GetNumDimensions() == siz);
      }
      THEN("All magnitudes in the Euclidean Vector are initialised to 1.5.") {
        REQUIRE(ev.at(0) == static_cast<double>(1.5));
        REQUIRE(ev.at(1) == static_cast<double>(1.5));
        REQUIRE(ev.at(2) == static_cast<double>(1.5));
      }
    }
  }

  GIVEN("A Vector of doubles") {
    WHEN("I use the vector constructor to construct a Euclidean Vector") {
      std::vector<double> vec = {0, 1, 2};
      EuclideanVector ev{vec.begin(), vec.end()};
      THEN("Size of the Euclidean Vector is the size I started with") {
        REQUIRE(ev.GetNumDimensions() == vec.size());
      }
      THEN("The new Euclidean Vector has the same magnitudes as the Vector.") {
        REQUIRE(ev.at(0) == vec[0]);
        REQUIRE(ev.at(1) == vec[1]);
        REQUIRE(ev.at(2) == vec[2]);
      }
    }
  }

  GIVEN("Two Euclidean Vectors of equal size") {
    EuclideanVector rv(correct_size, some_double);
    WHEN("I use the copy constructor") {
      EuclideanVector lv{rv};
      THEN("All magnitudes of the LHS will be equal to the RHS") {
        REQUIRE(lv[0] == rv[0]);
        REQUIRE(lv[1] == rv[1]);
        REQUIRE(lv[2] == rv[2]);
      }
    }
  }

  GIVEN("Two Euclidean Vectors of equal size") {
    EuclideanVector rv(correct_size, some_double);
    WHEN("I use the move constructor") {
      EuclideanVector lv{std::move(rv)};
      THEN("All magnitudes of the LHS will be equal to the old RHS") {
        REQUIRE(lv[0] == some_double);
        REQUIRE(lv[1] == some_double);
        REQUIRE(lv[2] == some_double);
      }
    }
  }
}

/* destructor testing */
SCENARIO("Using the EuclideanVector destructor") {
  GIVEN("A non-zero EuclideanVector") {
    EuclideanVector ev(correct_size);
    WHEN("I delete it") {
      THEN("We don't crash.") { ev.~EuclideanVector(); }
    }
  }
}

/* operator testing */
SCENARIO("Using the EuclideanVector overloaded operators") {
  GIVEN("Two Euclidean Vector variables with the same size") {
    EuclideanVector lv(correct_size);
    EuclideanVector rv(correct_size, some_double);

    WHEN("I use the = operator") {
      lv = rv;
      THEN("The LHS will take on the RHS's internal values") {
        REQUIRE(lv[0] == rv[0]);
        REQUIRE(lv[1] == rv[1]);
        REQUIRE(lv[2] == rv[2]);
      }
    }
  }

  GIVEN("Two Euclidean Vector variables with the same size") {
    EuclideanVector lv(correct_size);
    EuclideanVector rv(correct_size, some_double);

    WHEN("I use the move assignment operator") {
      lv = std::move(rv);
      THEN("The LHS will take on the RHS's internal values"
           " and RHS will be cleared.") {
        REQUIRE(lv[0] == some_double);
        REQUIRE(lv[1] == some_double);
        REQUIRE(lv[2] == some_double);
      }
    }
  }

  /* operators */
  GIVEN("Two non-zero Euclidean Vectors of equal size") {
    EuclideanVector lv(correct_size, some_double);
    EuclideanVector rv(correct_size, some_double);

    WHEN("I use the + operator") {
      EuclideanVector rt = lv + rv;
      THEN("The correct vector is returned") {
        REQUIRE(rt[0] == 3.0);
        REQUIRE(rt[1] == 3.0);
        REQUIRE(rt[2] == 3.0);
      }
    }

    WHEN("I use the - operator") {
      EuclideanVector rt = lv + rv;
      THEN("The correct vector is returned") {
        REQUIRE(rt[0] == 3.0);
        REQUIRE(rt[1] == 3.0);
        REQUIRE(rt[2] == 3.0);
      }
    }

    WHEN("I use the * operator to perform dot product") {
      double rt = lv * rv;
      THEN("The correct dot product result is returned") { REQUIRE(rt == 6.75); }
    }
  }

  GIVEN("A Euclidean Vector and a scalar") {
    EuclideanVector ev(correct_size, some_double);
    double scalar = 2.0;

    WHEN("I perform scalar multiplication") {
      auto rt = ev * scalar;
      THEN("The correct vector is returned.") {
        REQUIRE(rt[0] == 3.0);
        REQUIRE(rt[1] == 3.0);
        REQUIRE(rt[2] == 3.0);
      }
    }

    WHEN("I perform scalar multiplication the other way") {
      auto rt = ev * scalar;
      THEN("The correct vector is returned.") {
        REQUIRE(rt[0] == 3.0);
        REQUIRE(rt[1] == 3.0);
        REQUIRE(rt[2] == 3.0);
      }
    }

    WHEN("I use the / operator to perform scalar division") {
      EuclideanVector rt = ev / scalar;
      THEN("The correct vector is returned") {
        REQUIRE(rt[0] == 0.75);
        REQUIRE(rt[1] == 0.75);
        REQUIRE(rt[2] == 0.75);
      }
    }
  }

  /* dimension exception testing */
  GIVEN("Two Euclidean Vector variables with different sizes") {
    EuclideanVector lv(correct_size);
    EuclideanVector rv(another_size);

    WHEN("I use the += operator") {
      THEN("An exception will be thrown") {
        REQUIRE_THROWS_WITH(lv += rv, "Dimensions of LHS(" + std::to_string(correct_size) +
                                          ") and RHS(" + std::to_string(another_size) +
                                          ") do not match");
      }
    }

    WHEN("I use the -= operator") {
      THEN("An exception will be thrown") {
        REQUIRE_THROWS_WITH(lv -= rv, "Dimensions of LHS(" + std::to_string(correct_size) +
                                          ") and RHS(" + std::to_string(another_size) +
                                          ") do not match");
      }
    }

    WHEN("I use the + operator") {
      THEN("An exception will be thrown") {
        REQUIRE_THROWS_WITH(lv + rv, "Dimensions of LHS(" + std::to_string(correct_size) +
                                         ") and RHS(" + std::to_string(another_size) +
                                         ") do not match");
      }
    }

    WHEN("I use the - operator") {
      THEN("An exception will be thrown") {
        REQUIRE_THROWS_WITH(lv - rv, "Dimensions of LHS(" + std::to_string(correct_size) +
                                         ") and RHS(" + std::to_string(another_size) +
                                         ") do not match");
      }
    }

    WHEN("I use the * operator") {
      THEN("An exception will be thrown") {
        REQUIRE_THROWS_WITH(lv - rv, "Dimensions of LHS(" + std::to_string(correct_size) +
                                         ") and RHS(" + std::to_string(another_size) +
                                         ") do not match");
      }
    }
  }

  GIVEN("A non-zero length Euclidean Vector") {
    EuclideanVector ev(correct_size);

    /* divide by zero exception testing */
    WHEN("I try to divide the vector by 0") {
      THEN("An exception will be thrown") {
        REQUIRE_THROWS_WITH(ev / 0, "Invalid vector division by 0");
      }
    }

    WHEN("I try to divide-assign the vector with 0") {
      THEN("An exception will be thrown") {
        REQUIRE_THROWS_WITH(ev /= 0, "Invalid vector division by 0");
      }
    }
  }
}

/* member function testing */
SCENARIO("Using member functions of the class") {
  /* norm testing */
  GIVEN("A non-zero length and non-zero magnitude Euclidean Vector") {
    EuclideanVector ev(correct_size);
    ev[0] = 3;
    ev[1] = 4;
    ev[2] = 12;

    WHEN("I try to get the Euclidean Norm") {
      THEN("The correct Euclidean Vector's Norm is returned") {
        REQUIRE(ev.GetEuclideanNorm() == 13);
      }
    }

    /* at testing */
    WHEN("I try to index the vector using the at method") {
      THEN("The correct element will be returned.") {
        REQUIRE(ev.at(0) == 3);
        REQUIRE(ev.at(1) == 4);
        REQUIRE(ev.at(2) == 12);
      }
    }

    /* at exception testing */
    WHEN("I try to index the vector using the at method with invalid index") {
      THEN("An exception will be thrown") {
        REQUIRE_THROWS_WITH(ev.at(-1), "Index -1 is not valid for this "
                                       "EuclideanVector object");
        REQUIRE_THROWS_WITH(ev.at(3), "Index 3 is not valid for this "
                                      "EuclideanVector object");
      }
    }

    WHEN("I try to create a Unit Vector") {
      auto uv = ev.CreateUnitVector();
      THEN("The correct Unit Vector is returned") {
        REQUIRE(uv[0] == (3.0 / 13.0));
        REQUIRE(uv[1] == (4.0 / 13.0));
        REQUIRE(uv[2] == (12.0 / 13.0));
      }
    }
  }

  /* norm and unit vector exception testing */
  GIVEN("A zero length Euclidean Vector") {
    EuclideanVector ev(0, some_double);

    WHEN("I try to get the Euclidean Norm") {
      THEN("An exception will be thrown") {
        REQUIRE_THROWS_WITH(ev.GetEuclideanNorm(), "EuclideanVector with no"
                                                   " dimensions does not have"
                                                   " a norm");
      }
    }

    WHEN("I try to create the unit vector") {
      THEN("An exception will be thrown") {
        REQUIRE_THROWS_WITH(ev.CreateUnitVector(), "EuclideanVector with"
                                                   " no dimensions does not"
                                                   " have a unit vector");
      }
    }
  }

  /* unit vector exception testing */
  GIVEN("A zero magnitude Euclidean Vector") {
    EuclideanVector ev(correct_size, 0);

    WHEN("I try to create the unit vector") {
      THEN("An exception will be thrown.") {
        REQUIRE_THROWS_WITH(ev.CreateUnitVector(), "EuclideanVector with"
                                                   " euclidean normal of 0"
                                                   " does not have a unit"
                                                   " vector");
      }
    }
  }

  /* unit vector exception testing */
  GIVEN("A zero-dimension Euclidean Vector") {
    EuclideanVector ev(0);
    WHEN("I use the CreateUnitVector method") {
      THEN("An exception is thrown.") {
        REQUIRE_THROWS_WITH(ev.CreateUnitVector(), "EuclideanVector with no"
                                                   " dimensions does not have"
                                                   " a unit vector");
      }
    }
  }

  /* output stream testing */
  GIVEN("A non-zero vector and an output stream") {
    EuclideanVector ev(correct_size, some_double);
    std::ostringstream buf;

    WHEN("I use the << operator to write the vector to a stream") {
      buf << ev;
      THEN("The vector is correctly printed to the output stream.") {
        REQUIRE(buf.str() == "[1.5 1.5 1.5]");
      }
    }
  }

  GIVEN("A single-dimensional vector and an output stream") {
    EuclideanVector ev(1, some_double);
    std::ostringstream buf;

    WHEN("I use the << operator to write the vector to a stream") {
      buf << ev;
      THEN("The vector is correctly printed to the output stream.") {
        REQUIRE(buf.str() == "[1.5]");
      }
    }
  }
}
