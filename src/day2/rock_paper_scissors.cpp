#include "rps.h"
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
        auto should_mine = dc::get_should_rps(line[2]);

        if (!theirs.has_value() || !should_mine.has_value())
        {
            std::cerr << "Failed to parse line: " << line << std::endl;
            return EXIT_FAILURE;
        }

#ifdef PART1
        rounds.emplace_back(dc::RockPaperScissors{
            .theirs = theirs.value(),
            .mine = should_mine.value(),
            .result = dc::get_result(theirs.value(), should_mine.value())
        });

#else
        dc::RockPaperScissorChoice thrown;

        switch (should_mine.value())
        {
            case dc::GameResult::WIN:
            {
                thrown = dc::get_winning_hand(theirs.value());
                break;
            }
            case dc::GameResult::LOSS:
            {
                thrown = dc::get_losing_hand(theirs.value());
                break;
            }
            case dc::GameResult::TIE:
            {
                thrown = theirs.value();
                break;
            }
        }

        rounds.emplace_back(dc::RockPaperScissors{
            .theirs = theirs.value(),
            .mine = thrown,
            .result = dc::get_result(theirs.value(), thrown)
        });
#endif
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