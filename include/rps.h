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

auto get_result(const RockPaperScissorChoice& theirs, const RockPaperScissorChoice& mine) -> GameResult
{
    if (theirs == mine) return GameResult::TIE;
    else if (theirs == RockPaperScissorChoice::ROCK && mine == RockPaperScissorChoice::PAPER)
        return GameResult::WIN;
    else if (theirs == RockPaperScissorChoice::PAPER && mine == RockPaperScissorChoice::SCISSORS)
        return GameResult::WIN;
    else if (theirs == RockPaperScissorChoice::SCISSORS && mine == RockPaperScissorChoice::ROCK)
        return GameResult::WIN;
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