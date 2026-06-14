#ifndef _RANKEDMATCH_HPP
#define _RANKEDMATCH_HPP
#include "match.hpp"

class rankedmatch : public match
{
private:
    void resolve_turn() override;
    void end_game_actions(User *winner, User *loser) override;
public:
    rankedmatch(User* p1,User* p2);
    void print_status(User *player) override;
};


#endif