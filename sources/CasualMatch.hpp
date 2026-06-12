#ifndef _CASUALMATCH_HPP
#define _CASUALMATCH_HPP
#include "matchplayer.hpp"
#include "exceptions.hpp"
#include "constants.hpp"

class CasualMatch
{
private:
    MatchPlayerState player1_state;
    MatchPlayerState player2_state;
    int current_turn;
    bool is_match_finished;
    MatchPlayerState &get_my_state(User *player);
    MatchPlayerState &get_opponent_state(User *player);
    void resolve_turn();
    void do_action(User *player, std::string action);
    void end_game_actions(User *winner, User *loser);

public:
    CasualMatch(User *player1, User *player2);
    void register_action(User *player, std::string action);
    void print_status(User *player);
    bool is_finished();
};
#endif