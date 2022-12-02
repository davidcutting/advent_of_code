#include <inc.h>

int main(int argc, char* argv[])
{
    // Get text from input file and make it didn't fail.
    const auto text = dc::get_text_in_file("inputs/1_input.txt");
    if (!text.has_value())
    {
        std::cerr << "Failed to get text in file." << std::endl;
        return EXIT_FAILURE;
    }

    // Get list of calories that each elf has and add them up.
    std::vector<uint32_t> elf_calorie_list;
    uint32_t elf_calorie_total = 0;
    for(auto line : text.value())
    {
        if (line == "")
        {
            // Found space. Add this elf's calories to our list and reset the counter
            elf_calorie_list.emplace_back(elf_calorie_total);
            elf_calorie_total = 0;
        }
        else
        {
            // Add these calories to this elf's total
            elf_calorie_total += std::stoi(line);
        }
    }

    // Sort list in descending order.
    std::sort(elf_calorie_list.begin(), elf_calorie_list.end(), std::greater<uint32_t>());

    // Make sure nothing weird is going on.
    const uint32_t number_of_elves = 3; // Number of top elves to sum
    if (elf_calorie_list.size() < number_of_elves)
    {
        std::cerr << "Number of top elves to sum is larger than number of elves found." << std::endl;
        return EXIT_FAILURE;
    }

    // Get sum of top three elves' calories
    uint32_t top_elf_calories = 0;
    uint32_t elf_count = 0;
    for (auto elf_calorie : elf_calorie_list)
    {
        if (elf_count < number_of_elves)
        {
            top_elf_calories += elf_calorie;
            elf_count++;
        }
        else
        {
            // Gimme the sauce
            std::cout << top_elf_calories << std::endl;
            break;
        }
    }

    return EXIT_SUCCESS;
}