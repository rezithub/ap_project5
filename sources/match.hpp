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
    virtual void resolve_turn();
    virtual void end_game_actions(User *winner, User *loser, int winner_health) = 0;
    void do_action(User *player, std::string action);
    MatchPlayerState &get_my_state(User *player);
    MatchPlayerState &get_opponent_state(User *player);
    virtual void print_rank_status(int bullets, int health) = 0;

public:
    match(User *player1, User *p2, int player1_health, int player1_bullets, int player2_health, int player2_bullets);
    void register_action(User *player, std::string action);
    bool get_match_status();
    void print_status(User *player);
};

#endif