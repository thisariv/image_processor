#include <catch.hpp>
#include "io.h"
#include "image.h"
#include "exceptions.h"

TEST_CASE("файл не существует") {
    REQUIRE_THROWS_AS(BMPReader("nonexistent.bmp"), IOException);
}

TEST_CASE("входной файл не .bmp 1") {
    std::ofstream fake_file("fake.txt");
    fake_file << "входной файл не .bmp";
    fake_file.close();

    REQUIRE_THROWS_AS(BMPReader("fake.txt"), IOException);

    std::remove("fake.txt");
}

TEST_CASE("пустой файл") {
    std::ofstream empty_file("empty.bmp");
    empty_file.close();

    REQUIRE_THROWS_AS(BMPReader("empty.bmp"), IOException);

    std::remove("empty.bmp");
}

TEST_CASE("входной файл не .bmp 2") {
    REQUIRE_THROWS_AS(BMPReader("image.png"), IOException);
}

TEST_CASE("все ок") {
    const double for_example = 0.5;
    Image img(2, 2);
    img.WriteOnePixel(0, 0, {for_example, for_example, for_example});
    img.WriteOnePixel(1, 0, {1.0, 0.0, 0.0});
    img.WriteOnePixel(0, 1, {0.0, 1.0, 0.0});
    img.WriteOnePixel(1, 1, {0.0, 0.0, 1.0});

    BMPWriter writer("test_output.bmp");
    REQUIRE_NOTHROW(writer.WriteBMP(img));

    std::ifstream test_file("test_output.bmp");
    REQUIRE(test_file.good());
    test_file.close();

    std::remove("test_output.bmp");
}

TEST_CASE("выходной файл не .bmp") {
    REQUIRE_THROWS_AS(BMPWriter("output.png"), IOException);
}
