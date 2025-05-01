#include "edge_detection.h"
#include "grayscale.h"
#include <algorithm>

EdgeDetectionFilter::EdgeDetectionFilter(double threshold) : threshold_(threshold) {
}

void EdgeDetectionFilter::Apply(Image& image) {
    GrayScaleFilter gs_filter;
    gs_filter.Apply(image);

    Image original = image;

    int32_t width = image.GetWidth();
    int32_t height = image.GetHeight();

    for (int32_t y = 0; y < height; ++y) {
        for (int32_t x = 0; x < width; ++x) {
            double sum = 0.0;

            for (int dy = -1; dy < 2; ++dy) {
                for (int dx = -1; dx < 2; ++dx) {
                    int32_t neighbor_x = std::clamp(x + dx, 0, width - 1);
                    int32_t neighbor_y = std::clamp(y + dy, 0, height - 1);

                    Pixel neighbor = original.GetOnePixel(neighbor_x, neighbor_y);

                    // так как мы применили grayscale, R=G=B, значит можно взять любой цвет
                    double in = neighbor.red;
                    double weight = matrix_[dy + 1][dx + 1];

                    sum += in * weight;
                }
            }

            double color = 0.0;
            if (sum > threshold_) {
                color = 1.0;
            } else {
                color = 0.0;
            }
            image.WriteOnePixel(x, y, {color, color, color});
        }
    }
}