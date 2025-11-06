#ifndef JAKE_HELP_HPP
#define JAKE_HELP_HPP

#include <nlohmann/json.hpp>

namespace jake {

using json = nlohmann::json;

void display_help(const json& processes);

} // namespace jake

#endif // JAKE_HELP_HPP
