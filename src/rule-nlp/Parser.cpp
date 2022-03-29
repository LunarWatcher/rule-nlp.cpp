#include "Parser.hpp"
#include "SubMatch.hpp"
#include <algorithm>

namespace rnlp {

ParsedString Parser::parseString(const std::string& source) {
    std::string current = source;
    std::vector<SubMatch> components{};
    for (auto& rule : rules) {
        auto matches = rule.match(current);
        if (matches.size()) {
            components.insert(components.end(), matches.begin(), matches.end());
        }
    }
    std::vector<size_t> pos{};

    std::sort(components.begin(), components.end());
    auto result = components;

    for (int i = 0; i < components.size(); ++i) {
        size_t prevEnd = i == 0 ? 0 : components.at(i - 1).end;
        size_t currStart = components.at(i).start;

        if (prevEnd + 1 < currStart) {
            auto match = source.substr(prevEnd + (prevEnd == 0 ? 0 : 1), currStart - prevEnd - (prevEnd == 0 ? 0 : 1));
            if (match.find_first_not_of(" ") == std::string::npos) {
                // Let's ignore space-only blocks
                continue;
            }
            result.push_back({
                prevEnd + (prevEnd == 0 ? 0 : 1),
                currStart - 1,
                match,
                "none"
            });
        }
    }
    // Sneak in trailing groups
    if (components.size() > 0 && components.back().end != source.size() - 1) {
        result.push_back({
            components.back().end + 1,
            source.size() - 1,
            source.substr(components.back().end + 1, source.size() - components.back().end),
            "none"
        });
    }

    // And end off with a final sort
    std::sort(result.begin(), result.end());
    return ParsedString(source, result);
}

bool operator<(const SubMatch& lhs, const SubMatch& rhs) {
    return lhs.start < rhs.start;
}


std::vector<SubMatch>* ParsedString::operator->() {
    return &components;
}

}
