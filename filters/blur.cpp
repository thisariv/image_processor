#include "blur.h"
#include <cmath>
#include <algorithm>

BlurFilter::BlurFilter(double sigma) {
    ComputeMatrix(sigma);
}

void BlurFilter::ComputeMatrix(double sigma) {
    const double dim = 3.0;
    radius_ = static_cast<int>(std::ceil(dim * sigma));
    int size = 2 * radius_ + 1;
    matrix_.resize(size);

    double sum = 0.0;
    const double two_sigma_sq = 2.0 * sigma * sigma;
    for (int i = -radius_; i <= radius_; ++i) {
        double value = std::exp(-(i * i) / two_sigma_sq);
        matrix_[i + radius_] = value;
        sum += value;
    }
    for (int i = 0; i < size; ++i) {
        matrix_[i] /= sum;
    }
}

void BlurFilter::BlurHorizontal(Image& image) {
    Image temp = image;
    int32_t width = image.GetWidth();
    int32_t height = image.GetHeight();

    for (int32_t y = 0; y < height; ++y) {
        for (int32_t x = 0; x < width; ++x) {
            double sum_r = 0.0;
            double sum_g = 0.0;
            double sum_b = 0.0;

            for (int dx = -radius_; dx <= radius_; ++dx) {
                int32_t nx = std::clamp(x + dx, 0, width - 1);
                double weight = matrix_[dx + radius_];
                Pixel neighbor = temp.GetOnePixel(nx, y);
                sum_r += neighbor.red * weight;
                sum_g += neighbor.green * weight;
                sum_b += neighbor.blue * weight;
            }
            image.WriteOnePixel(x, y, {sum_r, sum_g, sum_b});
        }
    }
}

void BlurFilter::BlurVertical(Image& image) {
    Image temp = image;
    int32_t width = image.GetWidth();
    int32_t height = image.GetHeight();

    for (int32_t x = 0; x < width; ++x) {
        for (int32_t y = 0; y < height; ++y) {
            double sum_r = 0.0;
            double sum_g = 0.0;
            double sum_b = 0.0;

            for (int dy = -radius_; dy <= radius_; ++dy) {
                int32_t ny = std::clamp(y + dy, 0, height - 1);
                double weight = matrix_[dy + radius_];
                Pixel neighbor = temp.GetOnePixel(x, ny);
                sum_r += neighbor.red * weight;
                sum_g += neighbor.green * weight;
                sum_b += neighbor.blue * weight;
            }
            image.WriteOnePixel(x, y, {sum_r, sum_g, sum_b});
        }
    }
}

void BlurFilter::Apply(Image& image) {
    BlurHorizontal(image);
    BlurVertical(image);
}
