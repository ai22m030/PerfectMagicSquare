//
// Created by Adnan Vatric on 18.02.23.
//

#include "program_options.h"

#include <vector>
#include <iostream>

std::string_view program_options::get(
        const std::vector<std::string_view>& args,
        const std::string_view& option_name) {
    for (auto it = args.begin(), end = args.end(); it != end; ++it) {
        if (*it == option_name)
            if (it + 1 != end)
                return *(it + 1);
    }

    return "";
}

bool program_options::has(
        const std::vector<std::string_view>& args,
        const std::string_view& option_name) {
    for (auto arg : args) {
        if (arg == option_name)
            return true;
    }

    return false;
}

void program_options::description() {
    std::cout.setf(std::ios::right, std::ios::adjustfield);
    std::cout.width(50);
    std::cout << "Usage of the MagicSquare generator" << std::endl << std::endl;
    std::cout.setf(std::ios::right, std::ios::adjustfield);
    std::cout.width(31);
    std::cout << "-s <number>: Square dimension" << std::endl;
    std::cout.width(30);
    std::cout << "-p <number>: Population size" << std::endl;
    std::cout.width(31);
    std::cout << "-i <number>: Iterations count" << std::endl;
    std::cout.width(31);
    std::cout << "-o <name>: Output file name" << std::endl;
    std::cout.width(27);
    std::cout << "-v: Verbose mode" << std::endl << std::endl;
}
