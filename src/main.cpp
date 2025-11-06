#include <nlohmann/json.hpp>
#include "headers/parse_variables.hpp"
#include "flags/flags.hpp"
#include <filesystem>
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <csignal>
#include <vector>

namespace fs = std::filesystem;
using json = nlohmann::json;

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"

volatile sig_atomic_t interrupted = 0;

void signal_handler(int signum) {
    if (signum == SIGINT) {
        interrupted = 1;
        std::cerr << "\n" << ANSI_COLOR_YELLOW << "[JAKE] >>> SIGINT for terminate the execution (Ctrl+C)." 
            << ANSI_COLOR_RESET << std::endl;
    }
}

int execution_level = 0;

std::string get_indentation_prefix() {
    std::string prefix = "";

    for (int i = 0; i < execution_level; ++i) {
        prefix += "│  │";
    }

    return prefix;
}


int main(int argc, char **argv) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL); 

    if (std::signal(SIGINT, signal_handler) == SIG_ERR) {
        std::cerr << ANSI_COLOR_YELLOW << "[JAKE] >>> Warn: Signal Handler not activated for Ctrl+C." << ANSI_COLOR_RESET << std::endl;
    }

    std::string target = "all";
    std::vector<std::string> flags;
    int process_status = 0;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg.rfind("--jake-level=", 0) == 0) {
            try {
                execution_level = std::stoi(arg.substr(13)) + 1;
            } catch (...) {
                 std::cerr << ANSI_COLOR_YELLOW << "[JAKE] >>> Warning: Failed to parse internal --jake-level flag. Continuing with default level." << ANSI_COLOR_RESET << std::endl;
            }
            continue; 
        }

        if (arg == "--help" || arg == "-h") {
            flags.push_back(arg);
        } else {
            if (target == "all" && flags.empty()) {
                 target = arg;
            }
        }
    }

    bool run_help = std::find(
             flags.begin(), flags.end(), "--help") != flags.end() ||
                     std::find(flags.begin(), flags.end(), "-h") != flags.end();

    std::string json_filename = "Jakefile.json";
    std::ifstream input_file(json_filename);

    if (input_file.fail()) {
        if (run_help || argc == 1) { 
             std::cout << ANSI_COLOR_YELLOW << "[JAKE] >>> Jakefile.json not found in current path: " 
                       << fs::current_path().string() << ANSI_COLOR_RESET << std::endl;
             jake::display_help({}); 
             return 0;
        }

        std::cerr << ANSI_COLOR_RED << "Error: Failed to open " << json_filename 
                  << " on the current path: " << fs::current_path().string() << ANSI_COLOR_RESET << std::endl;
        return 1;
    }

    json json_data;
    try {
        input_file >> json_data;
    } catch (const json::parse_error& e) {
        std::cerr << ANSI_COLOR_RED << "Error: Failed to parse Jakefile.json: " 
                  << e.what() << ANSI_COLOR_RESET << std::endl;
        return 1;
    }

    try {
        if (json_data.find("variables") == json_data.end()) {
            throw std::runtime_error("Variables section not found in the configuration file.");
        }
        if (json_data.find("processes") == json_data.end()) {
            throw std::runtime_error("Processes section not found in the configuration file.");
        }

        json variables = json_data["variables"];
        json processes = json_data["processes"];

        if (run_help || target == "help") {
            jake::display_help(processes);
            return 0;
        }

        if (processes.find(target) == processes.end()) {
            throw std::runtime_error("Target '" + target
                            + "' not found in processes section.");
        }

        std::string current_indent = get_indentation_prefix();

        json selected_process = processes[target];
        for (size_t i = 0; i < selected_process.size(); ++i) {
            if (interrupted) {
                process_status = 1;
                break;
            }

            std::string command = selected_process[i];
            std::string final_command = parse_variables(command, variables);

            bool is_internal_jake_call = false;
            bool silent_command = false;
            int status = 0;

            if (final_command.front() == '@') {
                final_command = final_command.substr(1);
                silent_command = true;
            } else if (final_command.front() == '#') {
                final_command = final_command.substr(1);
                std::cout << current_indent << "    " << final_command << std::endl;
                continue;
            }

            if (final_command.rfind("jake ", 0) == 0) {
                final_command += " --jake-level=" + std::to_string(execution_level);
                is_internal_jake_call = true;
            }

            if (!silent_command) {
                std::string line_prefix = ">──";
                std::cout << current_indent << line_prefix;

                if (is_internal_jake_call) {
                     std::string called_target = final_command.substr(
                             final_command.find(" ") + 1);

                     called_target = called_target.substr(
                             0, called_target.find(" --jake-level="));

                     std::cout << "+\e[1m[JAKE]\e[0m >>> "<< ANSI_COLOR_GREEN << 
                             "(" << called_target << ")" << ANSI_COLOR_RESET << std::endl;
                } else {
                     std::cout << "* " << final_command << std::endl;
                }
            }

            if (!is_internal_jake_call) {
                status = system(final_command.c_str());
            } else {
                status = system(final_command.c_str());
            }

            if (status != 0) {
                process_status = 1; 
                break; 
            }
        }

        if (execution_level >= 0 && !interrupted) {
            std::string final_prefix_indent = get_indentation_prefix();
            std::string color = (process_status == 0) ? ANSI_COLOR_GREEN : ANSI_COLOR_RED;
            std::string symbol = (process_status == 0) ? "•" : "x";

            if (execution_level == 0) {
                if (selected_process.size() > 0) {
                     std::cout << final_prefix_indent << "└── " << color << symbol << ANSI_COLOR_RESET << std::endl;
                } else {
                     std::cout << final_prefix_indent << "• " << color << symbol << ANSI_COLOR_RESET << std::endl;
                }

                if (process_status == 0) {
                    std::cout << "\e[1m[JAKE]\e[0m >>> " << ANSI_COLOR_GREEN << 
                       "Build completed successfully." << ANSI_COLOR_RESET << std::endl;
                } else {
                    std::cerr << "\e[1m[JAKE]\e[0m >>> " << ANSI_COLOR_RED << 
                       "Build failed." << ANSI_COLOR_RESET << std::endl;
                }
            } else {
                std::cout << final_prefix_indent << "   └── " << color << symbol << ANSI_COLOR_RESET << std::endl;
            }

            if (process_status != 0) {
                return 1;
            }
        }

    } catch (const std::exception& e) {
        std::cerr << ANSI_COLOR_RED << "Error: " << e.what() << ANSI_COLOR_RESET << std::endl;
        return 1;
    }

    return process_status;
}
