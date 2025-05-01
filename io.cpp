#include "io.h"
#include <vector>
#include <stdexcept>
#include <iostream>
#include "exceptions.h"

bool HasBmpExtension(const std::string& path) {
    return path.size() >= 4 && path.substr(path.size() - 4) == ".bmp";
}

BMPReader::BMPReader(const std::string& path) {
    if (!HasBmpExtension(path)) {
        throw IOException("Файл должен иметь расширение .bmp " + path);
    }

    in_.open(path, std::ios::binary);
    if (!in_) {
        throw IOException("Не удалось открыть BMP файл: " + path);
    }

    // проверяем пустой ли файл
    in_.seekg(0, std::ios::end);
    if (in_.tellg() == 0) {
        throw IOException("Файл пустой " + path);
    }
    in_.seekg(0, std::ios::beg);
}

Image BMPReader::ReadBMP() {
    BMPFileHeader file_header;
    BMPInfoHeader info_header;

    in_.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    in_.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));

    if (file_header.bfType != BmpSignature) {
        throw IOException("Неверный формат BMP");
    }

    Image image(info_header.biWidth, std::abs(info_header.biHeight));

    const size_t row_size = ((info_header.biWidth * 3 + 3) & ~3);
    std::vector<unsigned char> row(row_size);

    for (int y = 0; y < std::abs(info_header.biHeight); ++y) {
        in_.read(reinterpret_cast<char*>(row.data()), static_cast<std::streamsize>(row_size));

        if (!in_) {
            throw IOException("Ошибка чтения BMP");
        }

        for (int x = 0; x < info_header.biWidth; ++x) {
            size_t index = x * 3;

            Pixel pixel{static_cast<double>(row[index + 2]) / RgbFormat,
                        static_cast<double>(row[index + 1]) / RgbFormat, static_cast<double>(row[index]) / RgbFormat};

            if (info_header.biHeight > 0) {
                image.WriteOnePixel(x, image.GetHeight() - 1 - y, pixel);
            } else {
                image.WriteOnePixel(x, y, pixel);
            }
        }
    }
    return image;
}

BMPWriter::BMPWriter(const std::string& path) {
    if (!HasBmpExtension(path)) {
        throw IOException("Файл должен иметь расширение .bmp: " + path);
    }

    out_.open(path, std::ios::binary);
    if (!out_) {
        throw IOException("Не удалось создать BMP файл: " + path);
    }
}

void BMPWriter::WriteBMP(const Image& image) {
    BMPFileHeader file_header{};
    BMPInfoHeader info_header{};

    info_header.biWidth = image.GetWidth();
    info_header.biHeight = image.GetHeight();
    info_header.biPlanes = BmpPlanes;
    info_header.biBitCount = BmpBitCount;
    info_header.biSize = sizeof(BMPInfoHeader);
    info_header.biSizeImage = image.GetWidth() * image.GetHeight() * 3;

    file_header.bfType = BmpSignature;
    file_header.bfOffBits = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
    file_header.bfSize = file_header.bfOffBits + info_header.biSizeImage;

    out_.write(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    out_.write(reinterpret_cast<char*>(&info_header), sizeof(info_header));

    const size_t row_size = ((image.GetWidth() * 3 + 3) & ~3);
    std::vector<unsigned char> row(row_size);

    for (int32_t y = image.GetHeight() - 1; y >= 0; --y) {
        for (int32_t x = 0; x < image.GetWidth(); ++x) {
            Pixel pixel = image.GetOnePixel(x, y);

            row[x * 3] = static_cast<unsigned char>(pixel.blue * RgbFormat);
            row[x * 3 + 1] = static_cast<unsigned char>(pixel.green * RgbFormat);
            row[x * 3 + 2] = static_cast<unsigned char>(pixel.red * RgbFormat);
        }

        out_.write(reinterpret_cast<char*>(row.data()), static_cast<std::streamsize>(row_size));

        if (!out_) {
            throw IOException("Ошибка записи BMP");
        }
    }
}
