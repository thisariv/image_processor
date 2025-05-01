#pragma once

#include <exception>
#include <string>

class ImageProcessorException : public std::exception {
public:
    explicit ImageProcessorException(const std::string& message) : message_(message) {
    }

    const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

class ParserException : public ImageProcessorException {
public:
    explicit ParserException(const std::string& message) : ImageProcessorException("Ошибка в парсинге: " + message) {
    }
};

class IOException : public ImageProcessorException {
public:
    explicit IOException(const std::string& message)
        : ImageProcessorException("Ошибка в чтении/выводе файла: " + message) {
    }
};

class ControllerException : public ImageProcessorException {
public:
    explicit ControllerException(const std::string& message)
        : ImageProcessorException("Ошибка в аргументах фильтра: " + message) {
    }
};
