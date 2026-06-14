#include "CasualMatch.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

CasualMatch::CasualMatch(User *p1, User *p2) 
    : match(p1, p2, FIRST_CS_HEALTH, FIRST_CS_BULLET, FIRST_CS_HEALTH, FIRST_CS_BULLET){}
void CasualMatch::end_game_actions(User *winner, User *loser)
{
    int winner_xp = winner->get_xp();
    int loser_xp = loser->get_xp();
    int delta_xp = max(5, int(50 - (0.1 * (winner_xp - loser_xp))));
    winner->set_xp(winner_xp + delta_xp);
    loser->set_xp(loser_xp - delta_xp);
    winner->win_match();
    loser->lose_match();
}
void CasualMatch::resolve_turn()
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
        player1->set_player_status(NOT_IN_GAME_STATUS);
        player2->set_player_status(NOT_IN_GAME_STATUS);
        is_match_finished = true;
        end_game_actions(player1, player2);
    }
    else if (player2_action == SHOOT_ACTION && player1_action == RELOAD_ACTION)
    {
        player1->set_player_status(NOT_IN_GAME_STATUS);
        player2->set_player_status(NOT_IN_GAME_STATUS);
        is_match_finished = true;
        end_game_actions(player2, player1);
    }
    else
    {
        player1_state.set_action(PENDING_STATUS);
        player2_state.set_action(PENDING_STATUS);
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
void CasualMatch::print_status(User *player)
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
}
