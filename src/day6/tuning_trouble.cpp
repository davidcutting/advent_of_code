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

int main(int argc, char* argv[])
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
        std::vector<char> last_stack;
        uint32_t unique_char_count = 0;
        uint32_t start_packet_marker = 0;
        char last_c = 0;
        const uint32_t UNIQUE_CHAR_DESIRED = 4;
        //std::string line = text.value()[0];
        for (auto c : line)
        {
            std::cout << c;
            // Check to see if we have all the characters found
            if (unique_char_count == UNIQUE_CHAR_DESIRED)
            {
                // End
                break;
            }
            // Is this c the same as the last one we saw?
            else if (c == last_c)
            {
                // Empty stack and restart.
                last_stack.clear();
                unique_char_count = 1;
                last_stack.emplace_back(c);
                start_packet_marker++;
                continue;
            }
            // Different from last one... Lets check the stack
            else if (is_char_in_stack(c, last_stack))
            {
                slice_out_of_stack(c, last_stack);
                last_c = c;
                unique_char_count = last_stack.size() + 1;
                last_stack.emplace_back(c);
                start_packet_marker++;
            }
            else
            {
                // Add this new found character to the stack
                last_stack.emplace_back(c);
                unique_char_count++;
                start_packet_marker++;
            }
        }
        std::cout << std::endl;

        for (auto c : last_stack)
        {
            std::cout << c;
        }

        std::cout << " " << start_packet_marker << std::endl;

        std::string processed = line.substr(0, start_packet_marker);
        std::string message = line.substr(start_packet_marker);

        std::cout << processed << " - " << message << std::endl;
    }

    return EXIT_SUCCESS;
}