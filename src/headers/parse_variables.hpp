
#ifndef PARSE_VARIABLES_HPP
#define PARSE_VARIABLES_HPP

#include <string>
#include <stdexcept>
#include <nlohmann/json.hpp>

std::string parse_variables(const std::string& command, const nlohmann::json& variables);

#endif // PARSE_VARIABLES_HPP
