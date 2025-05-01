#include "negative.h"

void NegativeFilter::Apply(Image& image) {
    for (int32_t y = 0; y < image.GetHeight(); ++y) {
        for (int32_t x = 0; x < image.GetWidth(); ++x) {
            Pixel pixel = image.GetOnePixel(x, y);

            pixel.red = 1.0 - pixel.red;
            pixel.green = 1.0 - pixel.green;
            pixel.blue = 1.0 - pixel.blue;

            image.WriteOnePixel(x, y, pixel);
        }
    }
}
