#pragma once

#include <bits/stdc++.h>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <string_view>
#include <sys/types.h>
#include <util.h>
#include <utility>
#include <vector>

using Sections = std::vector<uint8_t>;

struct Elf
{
    uint8_t min;
    uint8_t max;
    Sections sections;

    auto contains(const Elf& other) const noexcept -> bool
    {
        if (min >= other.min && max <= other.max)
        {
            return true;
        }
        return false;
    }
};

class ElfBuilder
{
private:
    Elf elf;
public:
    ElfBuilder& set_bounds(const uint8_t& min, const uint8_t& max) noexcept
    {
        elf.min = min;
        elf.max = max;
        return *this;
    }

    ElfBuilder& generate_sections() noexcept
    {
        if (elf.max - elf.min > elf.sections.max_size())
        {
            std::cout << elf.min << "-" << elf.max << std::endl;
        }
        elf.sections.reserve(elf.max - elf.min + 1);
        std::iota(elf.sections.begin(), elf.sections.end(), elf.min);
        return *this;
    }

    Elf finish() const noexcept
    {
        return elf;
    }
};

class SectionParser
{
private:
    std::string_view line;
    std::pair<Elf, Elf> parsed_elves;
public:
    SectionParser& add_line(const std::string_view& line) noexcept
    {
        this->line = line;
        return *this;
    }

    SectionParser& get_elves() noexcept
    {
        auto comma = line.find(',');
        std::string_view half_one = line.substr(0, comma);
        std::string_view half_two = line.substr(comma + 1, line.length());

        using SectionBounds = std::pair<uint8_t, uint8_t>;

        auto[bound_one, bound_two] = std::invoke([half_one, half_two]() {
            auto delimiter_pos_one = half_one.find('-');
            auto delimiter_pos_two = half_two.find('-');
            SectionBounds bound_one {
                stoi(std::string(half_one.substr(0, delimiter_pos_one))),
                stoi(std::string(half_one.substr(delimiter_pos_one + 1, half_one.length())))
            };
            SectionBounds bound_two {
                stoi(std::string(half_two.substr(0, delimiter_pos_two))),
                stoi(std::string(half_two.substr(delimiter_pos_two + 1, half_two.length())))
            };
            return std::pair<SectionBounds, SectionBounds>{bound_one, bound_two};
        });

        parsed_elves.first = ElfBuilder().set_bounds(bound_one.first, bound_one.second)
                                         .generate_sections()
                                         .finish();

        parsed_elves.second = ElfBuilder().set_bounds(bound_two.first, bound_two.second)
                                          .generate_sections()
                                          .finish();

        return *this;
    }

    std::pair<Elf, Elf> finish() noexcept
    {
        return parsed_elves;
    }
};

int main(int argc, char* argv[])
{
    // Get text from input file and make it didn't fail.
    //const auto text = dc::get_text_in_file("inputs/4_test.txt");
    const auto text = dc::get_text_in_file("inputs/4_input.txt");
    if (!text.has_value())
    {
        std::cerr << "Failed to get text in file." << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<std::pair<Elf, Elf>> elf_pairs;
    for (auto line : text.value())
    {
        elf_pairs.emplace_back(
            SectionParser().add_line(line)
                           .get_elves()
                           .finish());
    }

    assert(!elf_pairs.empty());

    int overlapping_section_count = 0;
    for (auto[elf_one, elf_two] : elf_pairs)
    {
        if (elf_two.contains(elf_one)) overlapping_section_count++;
        else if (elf_one.contains(elf_two)) overlapping_section_count++;
        else continue;
    }

    std::cout << overlapping_section_count << std::endl;

    return EXIT_SUCCESS;
}