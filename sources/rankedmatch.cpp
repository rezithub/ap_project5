#include "rankedmatch.hpp"
using namespace std;
#include <iostream>

rankedmatch::rankedmatch(User *player1, User *player2)
    : match(player1, player2,
            INTIAL_RN_HEALTH - player1->get_health_penalty_amount(),
            INTIAL_RN_BULLET - player1->get_bullet_penalty_amount(),
            INTIAL_RN_BULLET - player2->get_health_penalty_amount(),
            INTIAL_RN_BULLET - player2->get_bullet_penalty_amount())
{
    player1->consume_penalties();
    player2->consume_penalties();
}
int calculate_delta_rp(string level)
{
    int delta_rp = 0;
    if (level == BORONZE_LEVEL)
    {
        delta_rp = 75;
    }
    else if (level == SILVER_LEVEL)
    {
        delta_rp = 100;
    }
    else if (level == GOLD_LEVEL)
    {
        delta_rp = 125;
    }
    else if (level == PLATINUM_LEVEL)
    {
        delta_rp = 150;
    }
    else
    {
        throw BadRequestException();
    }
}
void rankedmatch::end_game_actions(User *winner, User *loser, int winner_health)
{
    string players_level = winner->get_level();
    int delta_rp = calculate_delta_rp(players_level);
    int winner_new_rp = winner->get_rp() + delta_rp + (winner_health * 25);
    winner->set_rp(winner_new_rp);
    int loser_new_rp = loser->get_rp() - delta_rp;
    loser->set_rp(loser_new_rp);
}
void rankedmatch::print_rank_status(int bullets, int health)
{
    cout << "Your remaining bullets: " << bullets << endl;
    cout << "Your remaining health: " << health << endl;
}