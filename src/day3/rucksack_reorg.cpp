#pragma once

#include <algorithm>
#include <bits/stdc++.h>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <util.h>
#include <utility>
#include <vector>

/**
    ASCII:  [a,z] = [97,122], [A,Z] = [65,90]
    Item Priority: [a,z] = [1,26], [A,Z] = [27,52]

    IP[a,z] = A[a - 96, z - 96]
    IP[A,Z] = A[A - 38, Z - 38]
*/
auto get_priority(const char& item) -> uint8_t
{
    uint8_t priority = 0;
    if (item >= 'a' && item <= 'z')
    {
        priority = item - 96;
    }
    else if (item >= 'A' && item <= 'Z')
    {
        priority = item - 38;
    }
    return priority;
}

using Compartments = std::vector<std::string>;

auto get_compartments(const std::string& rucksack, const uint8_t& num_compartments = 2) -> Compartments
{
    // Make sure the number of compartments we have is even possible
    assert(rucksack.length() % num_compartments == 0);

    // Should be divisible, therefore integral result from division
    int compartment_size = rucksack.length() / num_compartments;
    Compartments compartments(num_compartments, "");

    // Put items into appropriate compartment using compartment size as a delimiter
    int item_count = 0;
    for (auto item : rucksack)
    {
        compartments[std::floor(item_count / compartment_size)] += item;
        item_count++;
    }

    return compartments;
}

auto find_common_items(const Compartments& compartments) -> std::vector<char>
{
    // Maps containing a count of each possible item
    // (Count of characters in a string by value in ASCII table)
    std::vector<std::vector<uint8_t>> item_counts;

    // Loop through compartments and count up occurances of item into map
    for (auto compartment : compartments)
    {
        std::vector<uint8_t> item_count(256, 0);
        for (auto item : compartment)
        {
            item_count[int(item)]++;
        }
        item_counts.emplace_back(item_count);
    }

    // Loop through both maps and find minimum occurances of each item in maps
    std::vector<char> common;
    for (uint32_t i = 0; i < 256; ++i)
    {
        // Want to know if an item is common to all counts
        // If one of the counts does not have an item break
        for (auto item_count : item_counts)
        {
            if (!(item_count[i] > 0))
            {
                goto next_item;
            }
        }
        // We will emplace back this found common item if the above loop
        // fails to find a count which is not common and fails to goto
        // the next_item tag.
        common.emplace_back(char(i));

        // Next iteration label
        next_item:
            continue;
    }

    return common;
}

int main(int argc, char* argv[])
{
    // Get text from input file and make it didn't fail.
    //const auto text = dc::get_text_in_file("inputs/3_test.txt");
    const auto text = dc::get_text_in_file("inputs/3_input.txt");
    if (!text.has_value())
    {
        std::cerr << "Failed to get text in file." << std::endl;
        return EXIT_FAILURE;
    }

#define PART2
#ifndef PART2
    // Iterate through rucksacks
    std::vector<Compartments> compartments;
    for (auto line : text.value())
    {
        compartments.emplace_back(get_compartments(line));
    }
#else
    // Compartments are 3 lines in Part2
    assert(text.value().size() % 3 == 0);
    std::vector<Compartments> compartments(text.value().size()/3, std::vector<std::string>());

    int count = 0;
    for (auto line : text.value())
    {
        compartments[std::floor(count / 3)].emplace_back(line);
        count++;
    }
#endif
    std::vector<uint8_t> priorities;
    for (auto compartment : compartments)
    {
        auto common_items = find_common_items(compartment);

        uint32_t priority = 0;
        for (auto item : common_items)
        {
            priority += get_priority(item);
        }
        priorities.emplace_back(priority);
    }

    uint32_t total_priority = 0;
    for (auto priority : priorities)
    {
        total_priority += priority;
    }

    std::cout << total_priority << std::endl;

    return EXIT_SUCCESS;
}