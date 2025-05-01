#pragma once

#include <vector>
#include <cstdint>

struct Pixel {
    double red = 0;
    double green = 0;
    double blue = 0;

    Pixel() : red(0), green(0), blue(0) {
    }
    Pixel(double r, double g, double b) : red(r), green(g), blue(b) {
    }
};

class Image {
public:
    Image() = default;
    Image(int32_t width, int32_t height, Pixel fill_color = Pixel{0.0, 0.0, 0.0});

    int32_t GetWidth() const;
    int32_t GetHeight() const;

    Pixel GetOnePixel(int32_t x, int32_t y) const;
    void WriteOnePixel(int32_t x, int32_t y, const Pixel& pixel);
    void SetPixels(const std::vector<std::vector<Pixel>>& new_pixels);

    Image& operator=(const Image& other) = default;
    bool operator==(const Image& other) const;

private:
    std::vector<std::vector<Pixel>> pixels_;
    int32_t width_ = 0;
    int32_t height_ = 0;
};
