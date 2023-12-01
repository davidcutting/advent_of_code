#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <optional>

namespace dc
{

using File = std::vector<std::string>;

auto get_text_in_file(const std::string& file_path) -> std::optional<File>
{
    std::ifstream input_file;
    input_file.open(file_path);

    if (input_file.is_open())
    {
        std::string line;
        std::vector<std::string> document;

        while(std::getline(input_file, line))
        {
            document.emplace_back(line);
        }

        input_file.close();
        return document;
    }
    else
    {
        return std::nullopt;
    }
}

} // namespace dc