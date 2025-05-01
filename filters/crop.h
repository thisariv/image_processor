#pragma once

#include "../filter.h"

class CropFilter : public BaseFilter {
public:
    CropFilter(int target_width, int target_height);

    void Apply(Image& image) override;

private:
    int target_width_;
    int target_height_;
};
