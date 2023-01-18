// 0. std::pair is a struct template that provides a way to store two heterogeneous objects as a single unit.
// 1. map, multimap, unorder_map, unorder_multimap can use pair to insert data into their structures.

#include <vector>
#include <string>
#include <iostream>
#include <utility>



int main(int argc, char const *argv[])
{
    std::vector< std::pair<std::string, int> > vect;
    vect.push_back(std::make_pair("one", 1));
    vect.push_back(std::make_pair<std::string, int>("two", 2));
    vect.push_back({"three", 3});
    vect.push_back(std::pair<std::string, int>("four", 4));

    for(const auto& au : vect) std::cout << au.first << " - " << au.second << '\n';
    //////// output //////////
    // one - 1
    // two - 2
    // three - 3
    // four - 4
    // ///////////////////////

    return 0;
}
