#pragma once

#include <string>
#include <vector>
#if __has_include(<format>)
#include <format>
using fmt = std;

#define HAS_FMT
#elif __has_include(<fmt/format.h>)
#include <fmt/format.h>

#define HAS_FMT
#endif
#ifdef HAS_FMT
#include <sstream>
#endif

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
    friend std::ostream& operator<<(std::ostream& os, const ParsedString& p);
};

inline std::ostream& operator<<(std::ostream& os, const ParsedString& p) {
    os << "ParsedString[" << p.components.size()
        << ",\n"
        << "Original: " << p.original << "\n";
    for (auto& component : p.components) {
        os << "\tMatch[" << component.category << ", " << component.score << "]: "
            << std::to_string(component.start) << "-" << component.end
            << ": " << component.content << "\n";
    }

    return os << "]";
}


}

#ifdef HAS_FMT
template <> 
struct fmt::formatter<rnlp::ParsedString>: fmt::formatter<string_view> {

    template <typename FormatContext>
    auto format(const rnlp::ParsedString& c, FormatContext& ctx) {
        std::stringstream s;
        s << c;
        return formatter<string_view>::format(s.str(), ctx);
    }
};
#endif
