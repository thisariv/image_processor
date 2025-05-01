#include "grayscale.h"

void GrayScaleFilter::Apply(Image& image) {
    for (int32_t y = 0; y < image.GetHeight(); ++y) {
        for (int32_t x = 0; x < image.GetWidth(); ++x) {
            Pixel pixel = image.GetOnePixel(x, y);

            double gray = RedGrayscale * pixel.red + GreenGrayscale * pixel.green + BlueGrayscale * pixel.blue;
            pixel.red = gray;
            pixel.green = gray;
            pixel.blue = gray;

            image.WriteOnePixel(x, y, pixel);
        }
    }
}