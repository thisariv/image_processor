#pragma once

#include <fstream>
#include <string>
#include "exceptions.h"
#include "image.h"
#include <cstdint>

constexpr size_t ByteSize = 8;
constexpr unsigned char ByteMask = 0xFF;
constexpr uint16_t BmpSignature = 0x4D42;
constexpr uint16_t BmpPlanes = 1;
constexpr uint16_t BmpBitCount = 24;
constexpr int RgbFormat = 255;

#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};

struct BMPInfoHeader {
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};
#pragma pack(pop)

class BMPReader {
public:
    explicit BMPReader(const std::string& path);
    Image ReadBMP();

private:
    std::ifstream in_;
};

class BMPWriter {
public:
    explicit BMPWriter(const std::string& path);
    void WriteBMP(const Image& image);

private:
    std::ofstream out_;
};
