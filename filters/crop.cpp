#include "crop.h"
#include "../image.h"
#include <algorithm>
#include <cstddef>
#include <vector>

CropFilter::CropFilter(int target_width, int target_height)
    : target_width_(target_width), target_height_(target_height) {
}

void CropFilter::Apply(Image& image) {
    int64_t current_width = image.GetWidth();
    int64_t current_height = image.GetHeight();

    int64_t new_width = std::min<int64_t>(current_width, target_width_);
    int64_t new_height = std::min<int64_t>(current_height, target_height_);

    std::vector<std::vector<Pixel>> new_pixels;
    new_pixels.reserve(static_cast<size_t>(new_height));
    for (int32_t row = 0; row < new_height; ++row) {
        std::vector<Pixel> new_row;
        new_row.reserve(static_cast<size_t>(new_width));
        for (int32_t col = 0; col < new_width; ++col) {
            new_row.push_back(image.GetOnePixel(col, row));
        }
        new_pixels.push_back(new_row);
    }
    image.SetPixels(new_pixels);
}
