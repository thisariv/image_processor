#pragma once

#include "../filter.h"
#include "../image.h"
#include <vector>
#include <cstdint>

class BlurFilter : public BaseFilter {
public:
    explicit BlurFilter(double sigma);
    void Apply(Image& image) override;

private:
    int radius_;
    std::vector<double> matrix_;

    void ComputeMatrix(double sigma);
    void BlurHorizontal(Image& image);
    void BlurVertical(Image& image);
};
