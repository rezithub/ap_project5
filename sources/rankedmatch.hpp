#ifndef _RANKEDMATCH_HPP
#define _RANKEDMATCH_HPP
#include "match.hpp"
#include "constants.hpp"

class rankedmatch : public match
{
private:
    void end_game_actions(User *winner, User *loser, int winner_health) override;

public:
    rankedmatch(User *player1, User *player2);
    std::string get_match_type() override;
};

#endif