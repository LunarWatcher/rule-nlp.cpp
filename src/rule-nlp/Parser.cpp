#include "Parser.hpp"
#include "SubMatch.hpp"
#include <algorithm>
#include <numeric>

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
    size_t prevEnd = 0;

    for (int i = 0; i < components.size(); ++i) {
        size_t currStart = components.at(i).start;

        if (prevEnd + 1 < currStart) {
            auto match = source.substr(prevEnd + (prevEnd == 0 ? 0 : 1), currStart - prevEnd - (prevEnd == 0 ? 0 : 1));
            if (match.find_first_not_of(" ") == std::string::npos) {
                // Let's ignore space-only blocks
                goto esc;
            }
            result.push_back({
                prevEnd + (prevEnd == 0 ? 0 : 1),
                currStart - 1,
                match,
                "none",
                -1
            });
        }
esc:
        // Edge-case management: interval within interval, i.e.
        //   aaabbbbbaaaa
        // a ^^^^^^^^^^^^
        // b    ^^^^^
        prevEnd = std::max(prevEnd, components.at(i).end);
    }
    // Sneak in trailing groups
    if (components.size() > 0 && prevEnd != source.size() - 1) {
        result.push_back({
            prevEnd + 1,
            source.size() - 1,
            source.substr(prevEnd + 1, source.size() - prevEnd),
            "none",
            -1
        });
    }

    // And end off with a final sort
    std::sort(result.begin(), result.end());
    auto p = ParsedString(source, result);
    
    long long sum = 0;
    for (auto& result : result) {
        sum += result.score;
        if (!p.reasonCounts.contains(result.category)) {
            p.reasonCounts[result.category] = 1;
        } else {
            p.reasonCounts[result.category] += 1;
        }
    }

    p.sum = sum;
    return p;
}

bool operator<(const SubMatch& lhs, const SubMatch& rhs) {
    return lhs.start < rhs.start;
}


std::vector<SubMatch>* ParsedString::operator->() {
    return &components;
}

}
