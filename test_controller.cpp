#include <catch.hpp>
#include "controller.h"
#include "image.h"
#include "exceptions.h"
#include "filters/crop.h"
#include "filters/grayscale.h"
#include "filters/negative.h"
#include "filters/sharpering.h"
#include "filters/edge_detection.h"
#include "filters/blur.h"
#include "filters/affine_tile.h"

TEST_CASE("Неверные аргументы crop") {
    std::vector<InputFilter> input_filters = {{"crop", {"-800", "-600"}}};

    REQUIRE_THROWS_AS(CreateFilters(input_filters), ControllerException);
}

TEST_CASE("Не хватает аргументов crop") {
    std::vector<InputFilter> input_filters = {{"crop", {"800"}}};

    REQUIRE_THROWS_AS(CreateFilters(input_filters), ControllerException);
}

TEST_CASE("Не числовой аргумент crop") {
    std::vector<InputFilter> input_filters = {{"crop", {"abc", "600"}}};

    REQUIRE_THROWS_AS(CreateFilters(input_filters), ControllerException);
}

TEST_CASE("blur не хватает аргумента") {
    std::vector<InputFilter> input_filters = {{"blur", {}}};

    REQUIRE_THROWS_AS(CreateFilters(input_filters), ControllerException);
}

TEST_CASE("blur не числовой аргумент") {
    std::vector<InputFilter> input_filters = {{"blur", {"invalid"}}};

    REQUIRE_THROWS_AS(CreateFilters(input_filters), ControllerException);
}

TEST_CASE("edge не числовой аргумент") {
    std::vector<InputFilter> input_filters = {{"edge", {"not_a_number"}}};

    REQUIRE_THROWS_AS(CreateFilters(input_filters), ControllerException);
}

TEST_CASE("edge без аргумента") {
    std::vector<InputFilter> input_filters = {{"edge", {}}};

    REQUIRE_THROWS_AS(CreateFilters(input_filters), ControllerException);
}
