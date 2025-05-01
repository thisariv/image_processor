#include <catch.hpp>
#include "parser.h"
#include "exceptions.h"

TEST_CASE("все ок") {
    const char* argv[] = {"./app", "input.bmp", "output.bmp", "-blur", "2.0", "-sharpen"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    REQUIRE_NOTHROW(Parse(argc, argv));

    ParserResults result = Parse(argc, argv);

    REQUIRE(result.input_file == "input.bmp");
    REQUIRE(result.output_file == "output.bmp");
    REQUIRE(result.input_filters.size() == 2);
    REQUIRE(result.input_filters[0].filter_name == "blur");
    REQUIRE(result.input_filters[0].filter_params[0] == "2.0");
    REQUIRE(result.input_filters[1].filter_name == "sharpen");
}

TEST_CASE("не хватает аргументов") {
    const char* argv[] = {"./app", "input.bmp"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    REQUIRE_THROWS_AS(Parse(argc, argv), ParserException);
}

TEST_CASE("неверный формат фильтра") {
    const char* argv[] = {"./app", "input.bmp", "output.bmp", "-", "2.0"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    REQUIRE_THROWS_AS(Parse(argc, argv), ParserException);
}

TEST_CASE("неожиданный формат") {
    const char* argv[] = {"./app", "input.bmp", "output.bmp", "unexpected_arg"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    REQUIRE_THROWS_AS(Parse(argc, argv), ParserException);
}
