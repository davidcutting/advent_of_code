#include <inc.h>
#include <ostream>

int main(int argc, char* argv[])
{
    // Get text from input file and make it didn't fail.
    //const auto text = dc::get_text_in_file("inputs/2_test.txt");
    const auto text = dc::get_text_in_file("inputs/2_input.txt");
    if (!text.has_value())
    {
        std::cerr << "Failed to get text in file." << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<dc::RockPaperScissors> rounds;

    // Parse out lines into rounds of Rock Paper Scissors
    for (auto line : text.value())
    {
        auto theirs = dc::get_rps(line[0]);
        auto mine = dc::get_should_rps(line[2]);

        if (!theirs.has_value() || !mine.has_value())
        {
            std::cerr << "Failed to parse line: " << line << std::endl;
            return EXIT_FAILURE;
        }

        rounds.emplace_back(dc::RockPaperScissors{
            .theirs = theirs.value(),
            .mine = mine.value(),
            .result = dc::get_result(theirs.value(), mine.value())
        });
    }

    // Calculate score
    uint32_t score = 0;
    for (auto round : rounds)
    {
        score += dc::get_round_score(round.mine, round.result);
    }

    // Gimme the sauce
    std::cout << score << std::endl;

    return EXIT_SUCCESS;
}