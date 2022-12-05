#pragma once

#include <bits/stdc++.h>
#include <cstddef>
#include <string>
#include <tuple>
#include <util.h>
#include <vector>

using Command = std::tuple<uint8_t, uint8_t, uint8_t>;

class Parser
{
private:
    std::vector<std::string> lines;
    std::vector<std::string> stack_lines;
    std::vector<std::string> command_lines;

    std::stack<char> stacks;
    std::vector<Command> commands;
public:
    auto add_lines(const std::vector<std::string>& lines) noexcept -> void
    {
        this->lines = lines;
    }

    auto parse_lines() noexcept -> void
    {
        uint32_t commands_start_index = 0;
        for (auto line : lines)
        {
            if (line[0] == 'm')
            {
                break;
            }
            commands_start_index++;
        }

        for (auto i = 0; i < lines.size(); ++i)
        {
            // Get rid of blank line
            if (i == commands_start_index - 1) continue;
            // Throw lines where they belong
            if (i < commands_start_index)
            {
                stack_lines.emplace_back(lines[i]);
            }
            else
            {
                command_lines.emplace_back(lines[i]);
            }
        }
    }

    auto populate_stacks() noexcept -> void
    {
        for(auto stack_line : stack_lines)
        {
            std::cout << "Stack: " << stack_line << std::endl;
        }
    }

    auto populate_commands() noexcept -> void
    {
        for(auto command : command_lines)
        {
            std::cout << command << std::endl;

            // Get all the things that are delimited by spaces
            std::string temp = command;
            std::string delimiter = " ";
            std::vector<std::string> tokens;
            size_t it = 0;
            while ((it = temp.find(delimiter)) != std::string::npos)
            {
                std::string token = temp.substr(0, it);
                tokens.push_back(token);
                temp.erase(0, it + delimiter.length());
            }
            // Add the last token to the list
            tokens.push_back(temp);

            // Convert just the numbers into a command list
            commands.emplace_back(
                std::make_tuple(
                    std::stoi(tokens[1]),
                    std::stoi(tokens[3]),
                    std::stoi(tokens[5])));
        }
    }

    auto get_stacks() -> std::stack<char>
    {
        return stacks;
    }

    auto get_commands() -> std::vector<Command>
    {
        return commands;
    }
};

int main(int argc, char* argv[])
{
    // Get text from input file and make it didn't fail.
    const auto text = dc::get_text_in_file("inputs/5_test.txt");
    //const auto text = dc::get_text_in_file("inputs/5_input.txt");
    if (!text.has_value())
    {
        std::cerr << "Failed to get text in file." << std::endl;
        return EXIT_FAILURE;
    }

    Parser parser;
    parser.add_lines(text.value());
    parser.parse_lines();
    parser.populate_stacks();
    parser.populate_commands();
    auto stacks = parser.get_stacks();
    auto commands = parser.get_commands();

    return EXIT_SUCCESS;
}