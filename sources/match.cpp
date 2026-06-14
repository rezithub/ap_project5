#include "match.hpp"
#include <iostream>
#include <iomanip>
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
bool match::get_match_status()
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
void print_history(MatchPlayerState &the_player, MatchPlayerState &the_opponent)
{
    vector<string> player_history = the_player.get_history();
    vector<string> opponent_history = the_opponent.get_history();
    if (player_history.size() != opponent_history.size())
    {
        cout << "Something Went Wrong in moves ! number of moves is not equal!" << endl;
        throw BadRequestException();
    }
    cout << "History:" << endl;
    cout << left << setw(20) << "Opponent's moves:" << "Your moves:" << endl;
    for (int i = 0; i < player_history.size(); i++)
    {
        cout << left << setw(20) << opponent_history[i] << player_history[i] << endl;
    }
    cout << "Your remaining bullets: " << the_player.get_bullets() << endl;
}
void match::print_status(User *player)
{
    MatchPlayerState &the_player = get_my_state(player);
    MatchPlayerState &the_opponent = get_opponent_state(player);
    cout << "Turn " << current_turn << endl;
    cout << "You: " << the_player.get_current_action() << endl;
    string opponent_action = the_opponent.get_current_action();
    if (opponent_action == PENDING_STATUS)
    {
        cout << "Your opponent: pending" << endl;
    }
    else
    {
        cout << "Your opponent: played" << endl;
    }
    print_history(the_player, the_opponent);
    print_rank_status(the_player.get_bullets(),the_player.get_health());
}

void match::resolve_turn()
{
    string player1_action = player1_state.get_current_action();
    string player2_action = player2_state.get_current_action();
    User *player1 = player1_state.get_player();
    User *player2 = player2_state.get_player();
    if (player1_action == PENDING_STATUS || player2_action == PENDING_STATUS)
    {
        return;
    }
    current_turn++;
    player1_state.update_history();
    player2_state.update_history();
    do_action(player1, player1_action);
    do_action(player2, player2_action);
    if (player1_action == SHOOT_ACTION && player2_action == RELOAD_ACTION)
    {
        player2_state.decrease_health();
        if(player2_state.get_health()==0){
            end_game_actions(player1, player2,player1_state.get_health());
        }

    }
    else if (player2_action == SHOOT_ACTION && player1_action == RELOAD_ACTION)
    {
        player1_state.decrease_health();
        if(player1_state.get_health()==0){
            end_game_actions(player2, player1,player2_state.get_health());
        }
    }
    else
    {
        player1_state.set_action(PENDING_STATUS);
        player2_state.set_action(PENDING_STATUS);
    }
}
match::match(User *p1, User *p2, int p1_health, int p1_bullets, int p2_health, int p2_bullets)
    : player1_state(p1, p1_bullets, p1_health),
      player2_state(p2, p2_bullets, p2_health)
{
    current_turn = 1;
    is_match_finished = false;
}