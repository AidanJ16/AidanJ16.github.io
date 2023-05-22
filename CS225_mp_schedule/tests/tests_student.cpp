#include <catch2/catch_test_macros.hpp>

// You may write your own test cases in this file to test your code.
// Test cases in this file are not graded.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "schedule.h"
#include "tests_util.h"
TEST_CASE("My Test Case", "") {
    const V2D roster = {{"CS577", "a"},\ //red
     {"CS591", "a", "b"}, \  //blue
     {"CS386", "b", "c"}, \ //red
     {"CS500", "b", "d", }, \
     {"CS395", }
     };

    std::vector<std::string> timeslots = {"9AM", "11AM"};

    V2D out = schedule(roster, timeslots);

    verifySchedule(roster, out, 2);
}
