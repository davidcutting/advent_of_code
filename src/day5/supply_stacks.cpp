#include <algorithm>
#include <bits/stdc++.h>
#include <cstddef>
#include <optional>
#include <util.h>
#include <vector>

using Stack = std::vector<char>;

struct Command
{
    int count;
    int from;
    int to;
};

class SupplyStacks
{
private:
    std::vector<std::string> lines;
    std::vector<std::string> stack_lines;
    std::vector<std::string> command_lines;

    std::vector<Stack> stacks{};
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

        for (size_t i = 0; i < lines.size(); ++i)
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
        std::vector<uint32_t> supply_indices;

        std::string supply_stack_numbers = stack_lines.back();
        stack_lines.pop_back();

        int char_count = 0;
        for (auto character : supply_stack_numbers)
        {
            if (character == '[' || character == ']')
            {
                char_count++;
                continue;
            }
            else if (character == ' ')
            {
                char_count++;
                continue;
            }
            else
            {
                // Found a supply character
                supply_indices.emplace_back(char_count);
                char_count++;
            }
        }

        stacks.reserve(supply_indices.size());

        for (size_t stack_count = 0; stack_count < stacks.capacity(); stack_count++)
        {
            Stack stack;
            for (auto line : stack_lines)
            {
                // Get the character in the line at the index of this current stack
                char supply = line[supply_indices[stack_count]];
                if (supply != ' ')
                {
                    stack.emplace_back(supply);
                }
            }

            // Reverse so top of stack is last element in vector
            std::reverse(stack.begin(), stack.end());
            stacks.emplace_back(stack);
        }
    }

    auto split(std::string line, const std::string& delimiter) -> std::vector<std::string>
    {
        std::vector<std::string> tokens;
        size_t it = 0;
        while ((it = line.find(delimiter)) != std::string::npos)
        {
            std::string token = line.substr(0, it);
            tokens.push_back(token);
            line.erase(0, it + delimiter.length());
        }
        // Add the last token to the list
        tokens.emplace_back(line);
        return tokens;
    }

    auto populate_commands() noexcept -> void
    {
        for(auto command : command_lines)
        {
            std::vector<std::string> tokens = split(command, " ");

            // Convert just the numbers into a command list
            commands.emplace_back(
                Command{
                    std::stoi(tokens[1]),
                    std::stoi(tokens[3]),
                    std::stoi(tokens[5])
                });
        }
    }

    auto check_populated() noexcept -> void
    {
        assert(!stacks.empty());

        std::cout << "Stacks: " << std::endl;
        for (auto stack : stacks)
        {
            for (auto character : stack)
            {
                std::cout << character;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        assert(!commands.empty());

        std::cout << "Commands: " << std::endl;
        for (auto[num, from, to] : commands)
        {
            std::cout << "move " << int(num)
                      << " from " << int(from)
                      << " to " << int(to) << std::endl;
        }
        std::cout << std::endl;
    }

    auto execute_commands() noexcept -> void
    {
        for (auto command : commands)
        {
            // Move number of supplies from command
            for (int i = 0; i < command.count; ++i)
            {
                Stack& from = stacks.at(command.from - 1);
                Stack& to = stacks.at(command.to - 1);
                char supply = from.back();
                from.pop_back();

                std::cout << "   supply " << supply << std::endl;
                std::cout << "   from " << command.from << std::endl;
                std::cout << "   to " << command.to << std::endl;

                to.emplace_back(supply);
            }
        }
        
    }

    auto get_answer() noexcept -> std::string
    {
        std::string output = "";
        for (auto& stack : stacks)
        {
            output += stack.back();
        }
        return output;
    }
};

int main()
{
    // Get text from input file and make it didn't fail.
    //const auto text = dc::get_text_in_file("inputs/5_test.txt");
    const auto text = dc::get_text_in_file("inputs/5_input.txt");
    if (!text.has_value())
    {
        std::cerr << "Failed to get text in file." << std::endl;
        return EXIT_FAILURE;
    }

    SupplyStacks problem;
    problem.add_lines(text.value());
    problem.parse_lines();
    problem.populate_stacks();
    problem.populate_commands();
    problem.check_populated();
    problem.execute_commands();
    auto answer = problem.get_answer();

    std::cout << answer << std::endl;

    return EXIT_SUCCESS;
}