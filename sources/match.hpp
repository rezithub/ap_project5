#ifndef _MATCH_HPP
#define _MATCH_HPP
#include "matchplayer.hpp"
#include "exceptions.hpp"
#include <string>
class match
{
protected:
    MatchPlayerState player1_state;
    MatchPlayerState player2_state;
    int current_turn;
    bool is_match_finished;
    virtual void resolve_turn() = 0;
    virtual void end_game_actions(User *winner, User *loser) = 0;
    void do_action(User *player, std::string action);
    MatchPlayerState &get_my_state(User *player);
    MatchPlayerState &get_opponent_state(User *player);

public:
    match(User *p1, User *p2, int p1_health, int p1_bullets, int p2_health, int p2_bullets);
    void register_action(User *player, std::string action);
    bool is_finished();
    virtual void print_status(User *player)=0;
};

#endif