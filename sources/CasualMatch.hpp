#ifndef _CASUALMATCH_HPP
#define _CASUALMATCH_HPP
#include "match.hpp"
#include "constants.hpp"

class CasualMatch : public match
{
private:
    void end_game_actions(User *winner, User *loser, int winner_health) override;

public:
    CasualMatch(User *player1, User *player2);
    std::string get_match_type() override;
};
#endif