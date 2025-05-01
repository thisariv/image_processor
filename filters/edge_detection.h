#pragma once

#include "../filter.h"
#include "../image.h"

class EdgeDetectionFilter : public BaseFilter {
public:
    explicit EdgeDetectionFilter(double threshold);
    void Apply(Image& image) override;

private:
    double threshold_;
    const double matrix_[3][3] = {{0.0, -1.0, 0.0}, {-1.0, 4.0, -1.0}, {0.0, -1.0, 0.0}};
};
