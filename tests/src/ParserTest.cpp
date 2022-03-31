#include "catch2/catch_test_macros.hpp"

#include "rule-nlp/Parser.hpp"

TEST_CASE("Basic sentences", "[Basic]") {
    const std::string str = "Yes. Thank you!";
    rnlp::Parser p(std::vector<rnlp::Rule>{
        {
            std::regex("thanks? you", std::regex_constants::icase),
            "gratitude"
        }
    });
    rnlp::ParsedString result = p.parseString(str);
    REQUIRE(result.original == str);
    REQUIRE(result.components.size() == 3);
    REQUIRE(result.components.at(1).content == "Thank you");

    REQUIRE(result.components.at(1).start == str.find('T'));
    REQUIRE(str.substr(result.components.at(1).start, result.components.at(1).content.size()) == "Thank you");

    // Testing the none components
    REQUIRE(result.components.at(0).content == "Yes. ");
    REQUIRE(result.components.at(2).content == "!");

    REQUIRE(str.substr(result.components.at(0).start, result.components.at(0).content.size()) == "Yes. ");
    REQUIRE(str.at(result.components.at(2).end) == '!');


}

TEST_CASE("Overlap and empty intervals", "[EmptyWithOverlap]") {
    const std::string str = "No. Thank you and have a nice day, Olivia";

    rnlp::Parser p({
        {
            std::regex("thanks? you", std::regex_constants::icase),
            "gratitude"
        },
        {
            std::regex("have a nice day", std::regex_constants::icase),
            "fluff"
        },
        {
            std::regex("((and|or) ?)+"),
            "binder"
        }
    });

    rnlp::ParsedString result = p.parseString(str);

    //for (auto& component : result.components) {
        //std::cout << component.content << std::endl;
    //}

    REQUIRE(result.components.size() == 5);
    REQUIRE(result->at(0).content == "No. ");
    REQUIRE(result->at(1).content == "Thank you");
    REQUIRE(result->at(2).content == "and ");
    REQUIRE(result->at(3).content == "have a nice day");
    REQUIRE(result->at(4).content == ", Olivia");

    REQUIRE(result.components.back().end == str.size() - 1);
}

TEST_CASE("Verify score", "[ScoreTest]") {
    const std::string str = "No. Thank you and have a nice day, Olivia";

    rnlp::Parser p({
        {
            std::regex("thanks? you", std::regex_constants::icase),
            "gratitude",
            15
        },
        {
            std::regex("have a nice day", std::regex_constants::icase),
            "fluff",
            9
        },
        {
            std::regex("((and|or) ?)+"),
            "binder",
            0
        }
    });

    rnlp::ParsedString result = p.parseString(str);
    // gratitude + fluff - 2 * unidentified
    REQUIRE(result.sum == 15 + 9 - 2);
    REQUIRE(result.reasonCounts["none"] == 2);
    REQUIRE(result.reasonCounts["fluff"] == 1);
    REQUIRE(result.reasonCounts["gratitude"] == 1);

}
