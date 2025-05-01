#include "affine_tile.h"
#include <cmath>
#include <algorithm>

AffineTileFilter::AffineTileFilter(double a, double b, double c, double d, double tx, double ty)
    : a_(a), b_(b), c_(c), d_(d), tx_(tx), ty_(ty) {
}

double AffineTileFilter::Mod(double value, double modulus) const {
    double r = std::fmod(value, modulus);
    if (r < 0) {
        r += modulus;
    }
    return r;
}

void AffineTileFilter::Apply(Image& image) {
    int32_t width = image.GetWidth();
    int32_t height = image.GetHeight();

    Image result(width, height);

    for (int32_t y = 0; y < height; ++y) {
        for (int32_t x = 0; x < width; ++x) {

            double u = a_ * x + b_ * y + tx_;
            double v = c_ * x + d_ * y + ty_;

            u = Mod(u, static_cast<double>(width));
            v = Mod(v, static_cast<double>(height));

            Pixel p = image.GetOnePixel(static_cast<int>(u), static_cast<int>(v));
            result.WriteOnePixel(x, y, p);
        }
    }
    image = result;
}
