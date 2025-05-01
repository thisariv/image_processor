#include "parser.h"
#include "exceptions.h"

ParserResults Parse(int argc, const char* const* argv) {
    if (argc < 3) {
        throw ParserException("Недостаточно аргументов. (<input>, <output>, [filetrs...])");
    }

    ParserResults results;
    results.input_file = argv[1];
    results.output_file = argv[2];

    for (int index = 3; index < argc; ++index) {
        std::string arg = argv[index];
        if (arg[0] == '-') {
            if (arg.size() == 1) {
                throw ParserException("Неправильное имя аргумента: '-'");
            }
            InputFilter filter;
            filter.filter_name = arg.substr(1);
            while (index + 1 < argc && argv[index + 1][0] != '-') {
                filter.filter_params.push_back(argv[++index]);
            }
            results.input_filters.push_back(filter);
        } else {
            throw ParserException("Неправильное имя аргумента: " + arg);
        }
    }

    return results;
}
