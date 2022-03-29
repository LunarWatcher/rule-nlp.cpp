#pragma once

#include <regex>
#include <utility>
#include <string>
#include <vector>
#include <iostream>

#include "SubMatch.hpp"

namespace rnlp {

class Rule {
public:
    const std::regex pattern;
    const std::string category;

    Rule(const std::string& pattern, const std::string& category)
        : pattern(pattern), category(category) {}

    Rule(const std::regex& pattern, const std::string& category)
        : pattern(pattern), category(category) {}

    std::vector<SubMatch> match(std::string& input) {
        const auto end = std::sregex_iterator();
        std::vector<SubMatch> matches;

        for (std::sregex_iterator i = std::sregex_iterator(input.begin(), input.end(), pattern); i != end; ++i) {
            std::smatch m = *i;
            if (m.str().size() == 0) {
                continue;
            }
            matches.push_back({
                static_cast<size_t>(m.position()),
                m.position() + m.str().size() - 1,
                m.str(),
                category
            });
        }

        return matches;
    }
};


}
