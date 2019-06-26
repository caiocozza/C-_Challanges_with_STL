#include <vector>
#include <map>
#include <numeric>
#include <algorithm>

//This is a series of challanges that I'll be solving using STL

//1 - Given an int container, count the repeating numbers once.
//example 1 2 1 3 4 1 2 > results in 2. The 1 and 2 appears more than once
auto challange1(std::vector<int> const& c) {
    std::vector<int> temp(c); //makes a copy
    std::sort(std::begin(temp), std::end(temp)); //sorts the temp container

    //creates the difference between a and a - 1
    std::adjacent_difference(std::cbegin(temp),
                             std::cend(temp),
                             std::begin(temp));

    //counts how many times zero appears, which means, when the
    //container is sorted, and we use adjacent difference
    //if a and a - 1 are equals, the result will be 0
    //counting the 0's we have out answer
    return std::count_if(std::next(std::cbegin(temp)),
                         std::cend(temp),
                         [](int a) { return a == 0;});
}