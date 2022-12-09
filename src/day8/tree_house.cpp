#include <bits/stdc++.h>
#include <util.h>

struct Tree
{
    uint8_t height;
    bool is_checked = false;
    bool is_visible = false;
};

class OverheadMap
{
public:
    OverheadMap(std::vector<std::string> input_map)
    :   width(input_map[0].length()), height(input_map.size()) 
    {
        for (uint32_t i = 0; i < width; i++)
        {
            for (uint32_t j = 0; j < height; j++)
            {
                overhead_map[i][j] = Tree{ .height = input_map[i][j] - '0' };
            }
        }

        for(uint32_t i = 0; i < width; i++)
        {
            for(uint32_t j = 0; j < height; j++)
            {
                overhead_map[i][j].is_visible = find_is_visible(i, j);
                overhead_map[i][j].is_checked = true;
            }
        }/**/
    }

    auto find_visible_trees() noexcept -> uint32_t
    {
        uint32_t count = 0;
        for(uint32_t i = 0; i < width; i++)
        {
            for(uint32_t j = 0; j < height; j++)
            {
                if (overhead_map[i][j].is_checked
                    && overhead_map[i][j].is_visible)
                {
                    count++;
                }
            }
        }

        return count;
    }

    auto print_debug() const noexcept -> void
    {
        std::cout << "Width: " << width << ", Height: " << height << std::endl;

        std::cout << "Map: " << std::endl;
        for(uint32_t i = 0; i < width; i++)
        {
            for(uint32_t j = 0; j < height; j++)
            {
                std::cout << int(overhead_map[i][j].height);
            }
            std::cout << std::endl;
        }
    }

private:
    auto find_is_visible(const uint32_t x, const uint32_t y) noexcept -> bool
    {
        uint8_t subject = overhead_map[x][y].height;

        if (x == 0 || x == width) return true;
        if (y == 0 || y == height) return true;

        // Raycast Top -> Down
        uint8_t highest_tree = 0;
        for (uint32_t j = 0; j < y; j++)
        {
            highest_tree = std::max(highest_tree, overhead_map[x][j].height);
            if (subject == highest_tree && j == y) return true;
        }
        if (subject > highest_tree) return true;

        // Raycast Bottom -> Up
        highest_tree = 0;
        for (uint32_t j = height - 1; j >= y; j--)
        {
            highest_tree = std::max(highest_tree, overhead_map[x][j].height);
            if (subject == highest_tree && j == y) return true;
        }
        if (subject > highest_tree) return true;

        // Raycast Left -> Right
        highest_tree = 0;
        for (uint32_t i = 0; i < x; i++)
        {
            highest_tree = std::max(highest_tree, overhead_map[i][y].height);
            if (subject == highest_tree && i == x) return true;
        }
        if (subject > highest_tree) return true;

        // Raycast Right -> Left
        highest_tree = 0;
        for (uint32_t i = width - 1; i >= x; i--)
        {
            highest_tree = std::max(highest_tree, overhead_map[i][y].height);
            //if (subject == highest_tree && i == x) return true;
        }
        if (subject > highest_tree) return true;

        return false;
    }

    uint32_t width;
    uint32_t height;
    Tree overhead_map[1024][1024];
};

int main()
{
    // Get text from input file and make it didn't fail.
    //const auto text = dc::get_text_in_file("inputs/8_test.txt");
    const auto text = dc::get_text_in_file("inputs/8_input.txt");
    if (!text.has_value())
    {
        std::cerr << "Failed to get text in file." << std::endl;
        return EXIT_FAILURE;
    }

    for (auto line : text.value())
    {
        for (auto c : line)
        {
            std::cout << c;
        }
        std::cout << std::endl;
    }

    OverheadMap overhead_map(text.value());
    overhead_map.print_debug();

    std::cout << overhead_map.find_visible_trees() << std::endl;

    return EXIT_SUCCESS;
}