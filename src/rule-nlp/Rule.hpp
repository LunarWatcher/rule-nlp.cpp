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

    /**
     * The original pattern.
     * Primarily stored to enable sanity-checks in complex programs
     */
    const std::string source;
    const std::string category;
    const int64_t score;

    Rule(const std::string& pattern, const std::string& category, const int64_t& score = 0)
        : pattern(pattern, std::regex_constants::icase), source(pattern), category(category), score(score) {}

    Rule(const std::regex& pattern, const std::string& category, const int64_t& score = 0)
        : pattern(pattern), source(""), category(category), score(score) {}


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
                category,
                score
            });
        }

        return matches;
    }
};


}
