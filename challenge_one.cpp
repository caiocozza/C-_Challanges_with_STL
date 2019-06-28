#include <vector>
#include <map>
#include <numeric>
#include <algorithm>

//This is a series of challenges that I'll be solving using STL

//[std::max_element, std::partial_sum, std::inner_product]
//(4) Given a int container representing an elevation map where the with
//of each box is 1, grab how much water can we fit on it.
//I'll consider the following container as the map:
//[2, 1, 2, 0, 4, 2, 1, 4]
//You can test with different containers.
auto challenge4() -> int {
    //this is our map
    std::vector<int> const v0{2, 1, 2, 0, 4, 2, 1, 4};
    std::vector<int> v1(v0.size(), 0);

    //Grab the maximum element of the container
    auto max = std::max_element(std::cbegin(v0), std::cend(v0));
    //run from the start of v0 to the maximum plus one and get the maximum
    //from a and b. this is going to fill the v1 whith the maximum values
    //until the max element.
    std::partial_sum(std::cbegin(v0), std::next(max), std::begin(v1),
                     [](int a, int b) {
                         return std::max(a, b);
                     });

    //now, the reverse, from the end until the maximum value.
    std::partial_sum(std::crbegin(v0), std::reverse_iterator(max), std::rbegin(v1),
                     [](int a, int b) {
                         return std::max(a, b);
                     });
    //now for each pair from v0 and v1 we will check the max until now
    //and the current, then sum the size with the total.
    return std::inner_product(std::cbegin(v1), std::cend(v1), std::cbegin(v0), 0,
                              [](int total, int size) {
                                  return total + size;
                              },
                              [](int max_until_now, int current) {
                                  return max_until_now - current;
                              });
}

//[std::sort, std::minmax_element]
//(3) Given an int container, grab the sum of the min and the max element.
auto challenge3(std::vector<int> const& c) -> int {
    //creates a copy and sort it, in case the container is not sorted
    std::vector<int> temp(c);
    std::sort(std::begin(c), std::end(c));

    auto [min, max] = std::minmax_element(std::cbegin(temp),
                                          std::cend(temp));
    return *min + *max;                                          
}

//[std::inner_product]
//(2) Given an int container, count its elements that repeats sequentially.
//Example: 1 2 2 3 4 4 5 > results in 2.
auto challenge2(std::vector<int> const& c) {
    //with 2 containers, check from the first to the previous of the last
    //put the second one starting from the beggining plus one until the end
    //since the elements are repeated sequentially, we check if they are equal
    //if true, sum.
    //consider the vector  1 2 2 3 4 4 5
    //                   > 1 2 2 3 4 4
    //                   > 2 2 3 4 4 5
    //                   > 0 1 0 0 1 0 = 2
    //two elements repeats sequentially
    return std::inner_product(std::cbegin(c),
                              std::prev(std::cend(c)),
                              std::next(std::cbegin(c)),
                              0,
                              std::plus{},
                              std::equal_to{});
}

//[std::sort, std::adjacent_difference, std::count_if]
//(1) Given an int container, create a sum of the elements that appears
//more than once.
//Example: 1 2 1 3 2 > results in 2. The 1 and 2 appears more than once
auto challenge1(std::vector<int> const& c) {
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
