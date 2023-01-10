#include <string>
#include <set>
#include <iostream>
#include <functional>

int main(int argc, char *argv[])
{
    std::set<std::string> ls;
    std::string s = "12255";
    if (argc == 2) { s = argv[1]; }

    // in place rotation, examples: first = 1, last = 3, s = 'abcd' -> 'adbc'; with 0, 3, 'abcd' -> 'cabd'
    auto rotate = [](std::string &s, int first, int last) {
        auto b = s.begin(); std::reverse(b + first, b + last - 1); std::reverse(b + first, b + last);
    };

    std::function<void(std::set<std::string>&, std::string&, int, int)>
    // note: we need to capture rotate and permutate itself, so I used [&]
    permutate = [&](std::set<std::string> &ls, std::string &s, int first, int len) {

        if (len > 1) {
            for (int i = 0; i < len; i++) {
                permutate(ls, s, first+1, len-1);
                rotate(s, first, first + len);
            }
        }
        else { ls.emplace(s); }
    };

    permutate(ls, s, 0, s.size());
    std::cout << "number of results: " << ls.size() << "\n";
    for (auto &p : ls) {
        std::cout << p << "\n";
    }
}

