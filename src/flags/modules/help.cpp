#include <iostream>
#include <nlohmann/json.hpp>
#include <iomanip>
#include "help.hpp"

namespace jake {

using json = nlohmann::json;

void display_help(const json& processes) {
    const int FLAG_WIDTH = 25;

    std::cout << "Usage: jake [target] [options]..." << std::endl;

    std::cout << "\nOptions:" << std::endl;
    std::cout << std::setw(FLAG_WIDTH) << std::left << " -h, --help"
              << "Print this message and exit." << std::endl;
    if (processes.empty()) {
        std::cout << "\nNo available Targets reached (Jakefile.json)";
    } else {
        std::cout << "\nAvailable Targets (Jakefile.json):" << std::endl;
        for (json::const_iterator it = processes.begin(); it != processes.end(); ++it) {
            std::cout << " " << std::setw(FLAG_WIDTH - 1) << std::left << it.key()
                    << "Defined execution rule." << std::endl;
        }
        std::cout << "\nIf no 'target' is specified, the 'all' target is executed." << std::endl;
    }

    std::cout << "\nJake - A JSON Build tool." << std::endl;
    std::cout << "This program is free software; redistribute it under the terms of the GNU GPLv2." << std::endl;
    std::cout << "This program was built for C++17." << std::endl;
}

} // namespace jake
