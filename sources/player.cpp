#include "player.hpp"
#include <algorithm>
#include <iostream>
using namespace std;
Player::Player(string _username, string _password, int _xp, int _rp) : User(_username, _password)
{
    total_loses = 0;
    total_wins = 0;
    xp = _xp;
    rp = _rp;
    player_status = NOT_IN_GAME_STATUS;
    is_ready_cs_match = false;
    if (rp < 1400)
    {
        level = BORONZE_LEVEL;
    }
    else if (rp >= 1400 && rp < 1750)
    {
        level = SILVER_LEVEL;
    }
    else if (rp >= 1750 && rp < 2250)
    {
        level = GOLD_LEVEL;
    }
    else
    {
        level = PLATINUM_LEVEL;
    }
}
void Player::set_readiness_status(string the_status)
{
    this->is_ready_cs_match = (the_status == "true");
}
bool Player::get_readiness_status()
{
    return is_ready_cs_match;
}
string Player::get_player_status()
{
    return player_status;
}
string Player::get_level()
{
    return level;
}
int Player::get_rp(){
    return rp;
}
bool Player::check_block(User* the_opponent){
    for(auto the_user : blocked_users){
        if(the_user==the_opponent){
            return true;
        }
    }
    return false;
}
void Player::set_player_status(string the_status)
{
    player_status = the_status;
}
int Player::get_xp()
{
    return xp;
}
void Player::set_xp(int newxp)
{
    xp = newxp;
}
void Player::win_match()
{
    total_wins += 1;
}
void Player::lose_match()
{
    total_loses += 1;
}
void Player::remove_invitation(Invitation *the_invitation)
{
    auto invitation_iterator = find(received_invitations.begin(), received_invitations.end(), the_invitation);
    if (invitation_iterator != received_invitations.end())
    {
        received_invitations.erase(invitation_iterator);
    }
}
void Player::add_invitation(Invitation *the_invitation)
{
    received_invitations.push_back(the_invitation);
}
string Player::user_type()
{
    return PLAYER_USER;
}
void Player::show_received_invitations()
{
    if (received_invitations.empty())
    {
        throw EmptyException();
    }
    for (Invitation *the_invitation : received_invitations)
    {
        the_invitation->print_detailes();
    }
}
void Player::print_detailes()
{
    cout << "username: " << '"' << username << '"' << endl
         << "Level: " << level << endl
         << "RP: " << rp << endl
         << "XP: " << xp << endl
         << "Total wins: " << total_wins << endl
         << "Total losses: " << total_loses << endl;
}