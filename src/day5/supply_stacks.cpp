#pragma once

#include <bits/stdc++.h>
#include <util.h>

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

    for (auto line : text.value())
    {
        // Do something
    }
}