#include "rankedmatch.hpp"
using namespace std;
#include <iostream>

rankedmatch::rankedmatch(User *player1, User *player2)
    : match(player1, player2,
            INITIAL_RN_HEALTH - player1->get_health_penalty_amount(),
            INITIAL_RN_BULLET - player1->get_bullet_penalty_amount(),
            INITIAL_RN_HEALTH - player2->get_health_penalty_amount(),
            INITIAL_RN_BULLET - player2->get_bullet_penalty_amount())
{
    player1->consume_penalties();
    player2->consume_penalties();
}
int calculate_delta_rp(string level)
{
    int delta_rp = 0;
    if (level == level::BRONZE)
    {
        delta_rp = deltarp::BRONZE;
    }
    else if (level == level::SILVER)
    {
        delta_rp = deltarp::SILVER;
    }
    else if (level == level::GOLD)
    {
        delta_rp = deltarp::GOLD;
    }
    else if (level == level::PLATINUM)
    {
        delta_rp = deltarp::PLATINUM;
    }
    else
    {
        throw BadRequestException();
    }
    return delta_rp;
}
void rankedmatch::end_game_actions(User *winner, User *loser, int winner_health)
{
    winner->set_player_status(status::NOT_IN_GAME);
    loser->set_player_status(status::NOT_IN_GAME);
    is_match_finished = true;
    string players_level = winner->get_level();
    int delta_rp = calculate_delta_rp(players_level);
    int winner_new_rp = winner->get_rp() + delta_rp + (winner_health * 25);
    winner->set_rp(winner_new_rp);
    winner->win_match();
    int loser_new_rp = loser->get_rp() - delta_rp;
    loser->set_rp(loser_new_rp);
    loser->lose_match();
}
string rankedmatch::get_match_type()
{
    return Match::RANKED;
}