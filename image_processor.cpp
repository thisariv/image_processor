#include <iostream>
#include "parser.h"
#include "io.h"
#include "image.h"
#include "controller.h"

int main(int argc, char** argv) {
    try {
        ParserResults pars = Parse(argc, argv);
        BMPReader reader(pars.input_file);
        Image image = reader.ReadBMP();

        ApplyFilters(CreateFilters(pars.input_filters), image);

        BMPWriter writer(pars.output_file);
        writer.WriteBMP(image);

        std::cout << "Изображение обработано и сохранено в " << pars.output_file << std::endl;

        return 0;
    } catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
        return 1;
    }
}
