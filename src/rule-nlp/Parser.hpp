#pragma once

#include <string>
#include <vector>

#include "Rule.hpp"
#include "SubMatch.hpp"

namespace rnlp {

class ParsedString;

class Parser {
public:
    std::vector<Rule> rules;

    Parser(const std::vector<Rule>& rules) : rules(rules) {}
    
    ParsedString parseString(const std::string& source);
};

class ParsedString {
public:
    const std::string original;

    std::vector<SubMatch> components;
    const long long sum;

    ParsedString(const std::string& original, const std::vector<SubMatch>& components, long long sum)
        : original(original), components(components), sum(sum) {}

    std::vector<SubMatch>* operator->();
};

}
