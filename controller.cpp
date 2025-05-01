#include "controller.h"
#include "exceptions.h"
#include <iostream>

bool IsInteger(const std::string& str) {
    if (str.empty()) {
        return false;
    }

    size_t start = 0;
    if (str[0] == '-' || str[0] == '+') {
        if (str.size() == 1) {
            return false;
        }
        start = 1;
    }

    for (size_t i = start; i < str.size(); ++i) {
        if (!std::isdigit(str[i])) {
            return false;
        }
    }

    return true;
}

bool IsDouble(const std::string& str) {
    if (str.empty()) {
        return false;
    }

    try {
        size_t pos = 0;
        std::stod(str, &pos);

        while (pos < str.size() && std::isspace(str[pos])) {
            ++pos;
        }

        return pos == str.size();
    } catch (const std::exception&) {
        return false;
    }
}

void ApplyFilters(const std::vector<std::unique_ptr<BaseFilter>>& filters, Image& image) {
    for (const auto& filter : filters) {
        filter->Apply(image);
    }
}

std::vector<std::unique_ptr<BaseFilter>> CreateFilters(const std::vector<InputFilter>& input_filters) {
    std::vector<std::unique_ptr<BaseFilter>> filters;

    for (const auto& filter_desc : input_filters) {
        if (filter_desc.filter_name == "crop") {
            if (filter_desc.filter_params.size() != 2) {
                throw ControllerException("crop должен иметь два аргумента");
            }

            if (!IsInteger(filter_desc.filter_params[0]) || !IsInteger(filter_desc.filter_params[1])) {
                throw ControllerException("размеры должны быть целыми числами");
            }

            int width = std::stoi(filter_desc.filter_params[0]);
            int height = std::stoi(filter_desc.filter_params[1]);

            if (width < 0 || height < 0) {
                throw ControllerException("размеры должны быть больше нуля");
            }

            filters.push_back(std::make_unique<CropFilter>(width, height));
        } else if (filter_desc.filter_name == "gs") {
            if (!filter_desc.filter_params.empty()) {
                throw ControllerException("gs - фильтр без аргументов");
            }
            filters.push_back(std::make_unique<GrayScaleFilter>());
        } else if (filter_desc.filter_name == "neg") {
            if (!filter_desc.filter_params.empty()) {
                throw ControllerException("neg - фильтр без аргументов");
            }
            filters.push_back(std::make_unique<NegativeFilter>());
        } else if (filter_desc.filter_name == "sharp") {
            if (!filter_desc.filter_params.empty()) {
                throw ControllerException("sharp - фильтр без аргументов");
            }
            filters.push_back(std::make_unique<SharperingFilter>());
        } else if (filter_desc.filter_name == "edge") {
            if (filter_desc.filter_params.size() != 1) {
                throw ControllerException("edge должен иметь ровно один аргумент");
            }

            if (!IsDouble(filter_desc.filter_params[0])) {
                throw ControllerException("threshold должен быть double");
            }

            double threshold = std::stod(filter_desc.filter_params[0]);

            if (threshold < 0.0 || threshold > 1.0) {
                throw ControllerException("threshold должен быть от 0 до 1");
            }

            filters.push_back(std::make_unique<EdgeDetectionFilter>(threshold));
        } else if (filter_desc.filter_name == "blur") {
            if (filter_desc.filter_params.size() != 1) {
                throw ControllerException("blur нужен ровно один аргумент");
            }

            if (!IsDouble(filter_desc.filter_params[0])) {
                throw ControllerException("sigma должна быть числом double");
            }

            double sigma = std::stod(filter_desc.filter_params[0]);

            if (sigma <= 0.0) {
                throw ControllerException("В фильтре blur sigma должна быть больше нуля");
            }

            filters.push_back(std::make_unique<BlurFilter>(sigma));
        } else if (filter_desc.filter_name == "afftile") {
            if (!filter_desc.filter_params.empty()) {
                throw ControllerException("afftile - фильтр без аргументов");
            }
            filters.push_back(std::make_unique<AffineTileFilter>());
        }
    }
    return filters;
}
