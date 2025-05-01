#pragma once

#include <vector>
#include "filter.h"
#include "parser.h"
#include "filters/crop.h"
#include "filters/grayscale.h"
#include "filters/negative.h"
#include "filters/sharpering.h"
#include "filters/edge_detection.h"
#include "filters/blur.h"
#include "filters/affine_tile.h"
#include <memory>

void ApplyFilters(const std::vector<std::unique_ptr<BaseFilter>>& filters, Image& image);
std::vector<std::unique_ptr<BaseFilter>> CreateFilters(const std::vector<InputFilter>& input_filters);
