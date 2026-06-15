#include "matchplayer.hpp"
using namespace std;
MatchPlayerState::MatchPlayerState(User *_player, int init_health, int init_bullets)
{
    player = _player;
    bullets = init_bullets;
    health = init_health;
    current_action = status::PENDING;
}
string MatchPlayerState::get_current_action()
{
    return current_action;
}
int MatchPlayerState::get_bullets()
{
    return bullets;
}
void MatchPlayerState::set_action(string action)
{
    current_action = action;
}
User *MatchPlayerState::get_player()
{
    return player;
}
int MatchPlayerState::get_health()
{
    return health;
}
void MatchPlayerState::shoot_bullet()
{
    bullets -= 1;
}
void MatchPlayerState::decrease_health()
{
    health--;
}
void MatchPlayerState::reload_bullet()
{
    bullets += 1;
}
void MatchPlayerState::update_history()
{
    move_history.push_back(current_action);
}
vector<string> MatchPlayerState::get_history()
{
    return move_history;
}