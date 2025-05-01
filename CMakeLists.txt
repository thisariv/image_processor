set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    image_processor
    image_processor.cpp
    controller.cpp
    parser.cpp
    exceptions.h
    image.cpp
    filters/crop.cpp
    filters/grayscale.cpp
    filters/negative.cpp
    filters/sharpering.cpp
    filters/edge_detection.cpp
    filters/blur.cpp
    filters/affine_tile.cpp
    io.cpp
    text.h
)

add_executable(
    test_parser
    test_parser.cpp
    parser.cpp
)

add_executable(
    test_io
    test_io.cpp
    io.cpp
    image.cpp
    exceptions.h
)

add_executable(
    test_controller
    test_controller.cpp
    controller.cpp
    image.cpp
    filters/crop.cpp
    filters/grayscale.cpp
    filters/negative.cpp
    filters/sharpering.cpp
    filters/edge_detection.cpp
    filters/blur.cpp
    filters/affine_tile.cpp
)
