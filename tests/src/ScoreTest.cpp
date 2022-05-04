#include "catch2/catch_test_macros.hpp"

#include "rule-nlp/Parser.hpp"

#include <vector>

TEST_CASE("Make sure trailing negatives are handled", "[score]") {
    const std::string x = "This is sparta and rome!";
    rnlp::Parser p{
        std::vector<rnlp::Rule>{{
            "This is sparta",
            "aaaaaaaaaaaaaaaaa",
            10
        }, {
            "and",
            "aaaaaaaaaaaaaaaaa",
            -3
        }},
    };

    auto res = p.parseString(x);
    REQUIRE(res.sum == 6);
}

TEST_CASE("Make sure trailing negatives are handled (rules reversed)", "[score]") {
    const std::string x = "This is sparta and rome!";
    rnlp::Parser p{
        std::vector<rnlp::Rule>{{
            "and",
            "aaaaaaaaaaaaaaaaa",
            -3
        }, {
            "This is sparta",
            "aaaaaaaaaaaaaaaaa",
            10
        }},
    };

    auto res = p.parseString(x);
    REQUIRE(res.sum == 6);
}
