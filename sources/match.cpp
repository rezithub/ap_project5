#include "match.hpp"
using namespace std;
MatchPlayerState &match::get_my_state(User *p)
{
    if (player1_state.get_player() == p)
    {
        return player1_state;
    }
    else if (player2_state.get_player() == p)
    {
        return player2_state;
    }
    else
    {
        throw PermissionDeniedException();
    }
}
MatchPlayerState &match::get_opponent_state(User *p)
{
    if (player1_state.get_player() == p)
    {
        return player2_state;
    }
    else if (player2_state.get_player() == p)
    {
        return player1_state;
    }
    else
    {
        throw PermissionDeniedException();
    }
}
bool match::is_finished()
{
    return is_match_finished;
}
void match::register_action(User *p, string action)
{
    MatchPlayerState &my_state = get_my_state(p);
    if (my_state.get_current_action() != PENDING_STATUS)
    {
        throw PermissionDeniedException();
    }
    if (action == SHOOT_ACTION && my_state.get_bullets() == 0)
    {
        throw BadRequestException();
    }
    my_state.set_action(action);
    resolve_turn();
}
void match::do_action(User *p, string action)
{
    MatchPlayerState &my_state = get_my_state(p);
    if (action == SHOOT_ACTION)
    {
        my_state.shoot_bullet();
    }
    else if (action == RELOAD_ACTION)
    {
        my_state.reload_bullet();
    }
}
match::match(User *p1, User *p2, int p1_health, int p1_bullets, int p2_health, int p2_bullets)
    : player1_state(p1, p1_bullets, p1_health),
      player2_state(p2, p2_bullets, p2_health)
{
    current_turn = 1;
    is_match_finished = false;
}