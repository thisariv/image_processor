#pragma once

#include "../filter.h"
#include "../image.h"

class NegativeFilter : public BaseFilter {
public:
    void Apply(Image& image) override;
};
