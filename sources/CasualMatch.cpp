#include "CasualMatch.hpp"
#include <string>
#include <algorithm>
using namespace std;

CasualMatch::CasualMatch(User *p1, User *p2)
    : match(p1, p2, INTIAL_CS_HEALTH, INTIAL_CS_BULLET, INTIAL_CS_HEALTH, INTIAL_CS_BULLET) {}
void CasualMatch::end_game_actions(User *winner, User *loser, int winner_health)
{
    winner->set_player_status(NOT_IN_GAME_STATUS);
    loser->set_player_status(NOT_IN_GAME_STATUS);
    is_match_finished = true;
    int winner_xp = winner->get_xp();
    int loser_xp = loser->get_xp();
    int delta_xp = max(5, int(50 - (0.1 * (winner_xp - loser_xp))));
    winner->set_xp(winner_xp + delta_xp);
    loser->set_xp(loser_xp - delta_xp);
    winner->win_match();
    loser->lose_match();
}