#pragma once

#include <optional>
#include <string>

namespace dc
{

enum RockPaperScissorChoice
{
    ROCK = 1,
    PAPER = 2,
    SCISSORS = 3
};

enum GameResult
{
    WIN,
    LOSS,
    TIE
};

struct RockPaperScissors
{
    RockPaperScissorChoice theirs;
    RockPaperScissorChoice mine;
    GameResult result;
};

auto get_rps(const char& input) -> std::optional<RockPaperScissorChoice>
{
    switch (input)
    {
        case 'A': return RockPaperScissorChoice::ROCK;
        case 'B': return RockPaperScissorChoice::PAPER;
        case 'C': return RockPaperScissorChoice::SCISSORS;
        default: return std::nullopt;
    }
}

auto get_winning_hand(const RockPaperScissorChoice& thrown) -> RockPaperScissorChoice
{
    switch (thrown)
    {
        case RockPaperScissorChoice::ROCK: return RockPaperScissorChoice::PAPER;
        case RockPaperScissorChoice::PAPER: return RockPaperScissorChoice::SCISSORS;
        case RockPaperScissorChoice::SCISSORS: return RockPaperScissorChoice::ROCK;
    }
}

auto get_losing_hand(const RockPaperScissorChoice& thrown) -> RockPaperScissorChoice
{
    switch (thrown)
    {
        case RockPaperScissorChoice::ROCK: return RockPaperScissorChoice::SCISSORS;
        case RockPaperScissorChoice::PAPER: return RockPaperScissorChoice::ROCK;
        case RockPaperScissorChoice::SCISSORS: return RockPaperScissorChoice::PAPER;
    }
}

#ifdef PART1
auto get_should_rps(const char& input) -> std::optional<RockPaperScissorChoice>
{
    switch (input)
    {
        case 'X': return RockPaperScissorChoice::ROCK;
        case 'Y': return RockPaperScissorChoice::PAPER;
        case 'Z': return RockPaperScissorChoice::SCISSORS;
        default: return std::nullopt;
    }
}
#else
auto get_should_rps(const char& input) -> std::optional<GameResult>
{
    switch (input)
    {
        case 'X': return GameResult::LOSS;
        case 'Y': return GameResult::TIE;
        case 'Z': return GameResult::WIN;
        default: return std::nullopt;
    }
}
#endif

auto get_result(const RockPaperScissorChoice& theirs, const RockPaperScissorChoice& mine) -> GameResult
{
    if (theirs == mine) return GameResult::TIE;
    else if (mine == get_winning_hand(theirs)) return GameResult::WIN;
    else return GameResult::LOSS;
}

auto get_choice_score(const RockPaperScissorChoice& choice) -> int
{
    return static_cast<int>(choice);
}

auto get_result_score(const GameResult& result) -> int
{
    if (result == GameResult::WIN) return 6;
    else if (result == GameResult::LOSS) return 0;
    else if (result == GameResult::TIE) return 3;
}

auto get_round_score(const RockPaperScissorChoice& choice, const GameResult& result) -> int
{
    return get_choice_score(choice) + get_result_score(result);
}

}