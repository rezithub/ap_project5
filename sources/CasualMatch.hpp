#ifndef _CASUALMATCH_HPP
#define _CASUALMATCH_HPP
#include "match.hpp"

#include "exceptions.hpp"
#include "constants.hpp"

class CasualMatch : public match
{
private:
    void end_game_actions(User *winner, User *loser,int winner_health) override;
public:
    CasualMatch(User *player1, User *player2);
    void print_rank_status(int bullets,int health) override {};
};
#endif