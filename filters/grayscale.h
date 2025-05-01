#pragma once

#include "../filter.h"
#include "../image.h"

constexpr double RedGrayscale = 0.299;
constexpr double GreenGrayscale = 0.587;
constexpr double BlueGrayscale = 0.114;

class GrayScaleFilter : public BaseFilter {
public:
    void Apply(Image& image) override;
};
