#pragma once

#include <string>

namespace rnlp {

typedef struct SubMatch {
    size_t start;
    size_t end;
    std::string content;
    std::string category;
    int64_t score;
} SubMatch;

bool operator<(const SubMatch& lhs, const SubMatch& rhs);

}
