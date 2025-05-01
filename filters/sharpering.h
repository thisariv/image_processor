#pragma once

#include "../filter.h"
#include "../image.h"

class SharperingFilter : public BaseFilter {
public:
    void Apply(Image& image) override;

private:
    const double matrix_[3][3] = {{0.0, -1.0, 0.0}, {-1.0, 5.0, -1.0}, {0.0, -1.0, 0.0}};
};
