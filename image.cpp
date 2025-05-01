#include "image.h"

Image::Image(int32_t width, int32_t height, Pixel fill_color)
    : pixels_(static_cast<size_t>(height), std::vector<Pixel>(static_cast<size_t>(width), fill_color)),
      width_(width),
      height_(height) {
}

int32_t Image::GetWidth() const {
    return width_;
}

int32_t Image::GetHeight() const {
    return height_;
}

Pixel Image::GetOnePixel(int32_t x, int32_t y) const {
    return pixels_[static_cast<size_t>(y)][static_cast<size_t>(x)];
}

void Image::WriteOnePixel(int32_t x, int32_t y, const Pixel &pixel) {
    pixels_[static_cast<size_t>(y)][static_cast<size_t>(x)] = pixel;
}

void Image::SetPixels(const std::vector<std::vector<Pixel>> &new_pixels) {
    pixels_ = new_pixels;
    height_ = static_cast<int32_t>(new_pixels.size());
    if (new_pixels.empty()) {
        width_ = 0;
    } else {
        width_ = static_cast<int32_t>(new_pixels[0].size());
    }
}

bool Image::operator==(const Image &other) const {
    for (int32_t row = 0; row < height_; ++row) {
        for (int32_t col = 0; col < width_; ++col) {
            const Pixel &p1 = pixels_[static_cast<size_t>(row)][static_cast<size_t>(col)];
            const Pixel &p2 = other.pixels_[static_cast<size_t>(row)][static_cast<size_t>(col)];
            if (p1.red != p2.red || p1.green != p2.green || p1.blue != p2.blue) {
                return false;
            }
        }
    }
    return true;
}
