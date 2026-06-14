#ifndef _CASUALMATCH_HPP
#define _CASUALMATCH_HPP
#include "match.hpp"

#include "exceptions.hpp"
#include "constants.hpp"

class CasualMatch : public match
{
private:
    void resolve_turn() override;
    void end_game_actions(User *winner, User *loser) override;

public:
    CasualMatch(User *player1, User *player2);
    void print_status(User *player) override;
};
#endif