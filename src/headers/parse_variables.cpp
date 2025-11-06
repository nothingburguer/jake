#include "parse_variables.hpp"
#include <nlohmann/json.hpp>
#include <string>
#include <stdexcept>

std::string parse_variables(const std::string& command, const nlohmann::json& variables) {
    std::string result = command;

    while (true) {
        size_t pos = result.find("${");
        if (pos == std::string::npos) break;

        size_t end_pos = result.find("}", pos);
        if (end_pos == std::string::npos) {
            throw std::invalid_argument("Invalid variable format: missing '}'");
        }

        std::string var_name = result.substr(pos + 2, end_pos - (pos + 2));

        if (variables.find(var_name) == variables.end()) {
            throw std::runtime_error("Referenced variable not defined: " + var_name);
        }

        const nlohmann::json& jval = variables.at(var_name);
        std::string var_value;
        if (jval.is_string()) {
            var_value = jval.get<std::string>();
        } else {
            var_value = jval.dump();
        }

        result.replace(pos, end_pos - pos + 1, var_value);
    }

    return result;
}
