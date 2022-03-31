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
    std::map<std::string, size_t> reasonCounts;

    long long sum;

    ParsedString(const std::string& original, const std::vector<SubMatch>& components)
        : original(original), components(components) {}

    std::vector<SubMatch>* operator->();
};

}
