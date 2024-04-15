#include "utils.hpp"

std::vector<std::string> split(std::string s, char del) {
    std::vector<std::string> res;

    if (!s.empty()) {
        size_t index = s.find(del), last_index = 0;

        while (index != std::string_view::npos) {
            res.push_back(s.substr(last_index, index - last_index));
            last_index = index + 1;
            index = s.find(del, last_index);
        }

        res.push_back(s.substr(last_index));
    }

    return res;
}
