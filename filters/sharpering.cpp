#include "sharpering.h"
#include <algorithm>

void SharperingFilter::Apply(Image& image) {
    Image original = image;

    int32_t width = image.GetWidth();
    int32_t height = image.GetHeight();

    for (int32_t y = 0; y < height; ++y) {
        for (int32_t x = 0; x < width; ++x) {
            double sum_red = 0.0;
            double sum_green = 0.0;
            double sum_blue = 0.0;

            for (int dy = -1; dy < 2; ++dy) {
                for (int dx = -1; dx < 2; ++dx) {
                    int32_t neighbor_x = x + dx;
                    int32_t neighbor_y = y + dy;

                    neighbor_x = std::clamp(neighbor_x, 0, width - 1);
                    neighbor_y = std::clamp(neighbor_y, 0, height - 1);

                    Pixel neighbor = original.GetOnePixel(neighbor_x, neighbor_y);

                    double weight = matrix_[dy + 1][dx + 1];

                    sum_red += neighbor.red * weight;
                    sum_green += neighbor.green * weight;
                    sum_blue += neighbor.blue * weight;
                }
            }

            sum_red = std::clamp(sum_red, 0.0, 1.0);
            sum_green = std::clamp(sum_green, 0.0, 1.0);
            sum_blue = std::clamp(sum_blue, 0.0, 1.0);

            image.WriteOnePixel(x, y, {sum_red, sum_green, sum_blue});
        }
    }
}
