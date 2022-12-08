#include <bits/stdc++.h>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <util.h>
#include <vector>

auto is_char_in_stack(const char& c, const std::vector<char> stack) noexcept -> bool
{
    for (auto in_stack : stack)
    {
        if (c == in_stack)
        {
            return true;
        }
    }
    return false;
}

auto slice_out_of_stack(const char& c, std::vector<char>& stack) noexcept -> void
{
    std::vector<char> out_stack;
    bool repeat_found = false;
    for(auto in_stack : stack)
    {
        if (repeat_found)
        {
            out_stack.emplace_back(in_stack);
        }
        else if (c == in_stack)
        {
            repeat_found = true;
        }
    }
    std::swap(out_stack, stack);
}

auto marker_finder(const std::string& line, std::vector<char>& processed, uint32_t unique_char_desired = 4) noexcept -> uint32_t
{
    uint32_t unique_char_count = 0;
    uint32_t start_marker = 0;
    char last_c = 0;
    for (auto c : line)
    {
        std::cout << c;
        // Check to see if we have all the characters found
        if (unique_char_count == unique_char_desired)
        {
            // End
            break;
        }
        // Is this c the same as the last one we saw?
        else if (c == last_c)
        {
            // Empty stack and restart.
            processed.clear();
            unique_char_count = 1;
            processed.emplace_back(c);
            start_marker++;
            continue;
        }
        // Different from last one... Lets check the stack
        else if (is_char_in_stack(c, processed))
        {
            slice_out_of_stack(c, processed);
            last_c = c;
            unique_char_count = processed.size() + 1;
            processed.emplace_back(c);
            start_marker++;
        }
        else
        {
            // Add this new found character to the stack
            processed.emplace_back(c);
            unique_char_count++;
            start_marker++;
        }
    }
    return start_marker;
}

int main()
{
    // Get text from input file and make it didn't fail.
    //const auto text = dc::get_text_in_file("inputs/6_test.txt");
    const auto text = dc::get_text_in_file("inputs/6_input.txt");
    if (!text.has_value())
    {
        std::cerr << "Failed to get text in file." << std::endl;
        return EXIT_FAILURE;
    }

    for (auto line : text.value())
    {
        // PART 1

        std::vector<char> processed_stack;
        uint32_t start_packet_marker = marker_finder(line, processed_stack);

        /**
        for (auto c : processed_stack)
        {
            std::cout << c;
        }
        std::cout << " " << start_packet_marker << std::endl;
        */

        std::string processed = line.substr(0, start_packet_marker);
        std::string packet = line.substr(start_packet_marker);
        //std::cout << processed << " - " << packet << std::endl;

        // PART 2

        processed_stack.clear();
        uint32_t start_message_marker = marker_finder(packet, processed_stack, 14);

        for (auto c : processed_stack)
        {
            std::cout << c;
        }
        uint32_t processed_chars = start_packet_marker + start_message_marker;
        std::cout << " " << processed_chars << std::endl;

        processed = packet.substr(0, start_message_marker);
        std::string message = packet.substr(start_message_marker);
        std::cout << processed << " - " << message << std::endl;
    }

    return EXIT_SUCCESS;
}