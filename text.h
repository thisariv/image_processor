#pragma once

#include <string>

namespace text {
const std::string INFO_TEXT =
    "Program interaction protocol:\n"
    "1. The first word in the input is ignored—it is the name of the executable file.\n"
    "2. The path to your input file should be in the format: C:/Users/Username/Downloads/image.bmp\n"
    "3. The path to the output file should follow the same format as the input file.\n"
    "\n"
    "Next comes the filter description. Each filter should be specified in the format:\n"
    "  -{filter_name} {arg1} {arg2} ...\n"
    "\n"
    "Available filters and examples:\n"
    "\n"
    "-gs      Converts the image to grayscale.\n"
    "         Example: -gs\n"
    "\n"
    "-crop    Takes two arguments: width (w) and height (h), and crops the image accordingly.\n"
    "         Example: -crop 800 600\n"
    "\n"
    "-sharp   Increases sharpness.\n"
    "         Example: -sharp\n"
    "\n"
    "-edge    Takes one argument (threshold) and highlights only the edges of objects in the image.\n"
    "         Example: -edge 0.5\n"
    "\n"
    "-blur    Takes one argument (radius) and applies a blur effect.\n"
    "         Example: -blur 5\n"
    "\n"
    "-afftile Applies an affine tile effect to the image.\n"
    "         The image is transformed and repeated using a default affine matrix.\n"
    "         No arguments required.\n"
    "         Example: -afftile\n"
    "\n"
    "Example of multiple filters applied together:\n"
    "\\.image_processor input.bmp output.bmp -gs -crop 500 400 -sharp -blur 1.5";
}
