#ifndef UTILS_HPP
#define UTILS_HPP

#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> split(std::string s, char del);

template <typename Iterator> std::string join(Iterator begin, Iterator end, char sep) {
    std::stringstream ss;

    for (auto it = begin; it != end; it++) {
        if (it != begin)
            ss << sep;

        ss << *it;
    }

    return ss.str();
}

#endif // UTILS_HPP
