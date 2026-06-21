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
    player_status = status::NOT_IN_GAME;
    is_ready_cs_match = false;
}
int Player::get_health_penalty_amount()
{
    return (health_penalties.remaining_matches > 0) ? health_penalties.amount : 0;
}
void Player::consume_penalties()
{
    if (health_penalties.remaining_matches > 0)
    {
        health_penalties.remaining_matches--;
    }
    if (bullet_penalties.remaining_matches > 0)
    {
        bullet_penalties.remaining_matches--;
    }
}
void Player::set_rp(int new_rp)
{
    rp = new_rp;
}
int Player::get_bullet_penalty_amount()
{
    return (bullet_penalties.remaining_matches > 0) ? bullet_penalties.amount : 0;
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
    string level;
    if (rp < 1400)
    {
        level = level::BRONZE;
    }
    else if (rp >= 1400 && rp < 1750)
    {
        level = level::SILVER;
    }
    else if (rp >= 1750 && rp < 2250)
    {
        level = level::GOLD;
    }
    else
    {
        level = level::PLATINUM;
    }
    return level;
}
int Player::get_rp()
{
    return rp;
}
bool Player::check_block(User *the_opponent)
{
    for (auto the_user : blocked_users)
    {
        if (the_user == the_opponent)
        {
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
    return user::PLAYER;
}
void Player::show_received_invitations()
{
    if (received_invitations.empty())
    {
        throw EmptyException();
    }
    for (Invitation *the_invitation : received_invitations)
    {
        cout << the_invitation->get_detailes() << endl;
    }
}
string Player::get_detailes()
{

    string detail = "username: " + '"' + username + '"' + "\n" + "Level: " + get_level() + "\n" + "RP: " + to_string(rp) + "\n" + "XP: " + to_string(xp) + "\n" + "Total wins: " + to_string(total_wins) + "\n" + "Total losses: " + to_string(total_loses);
    return detail;
}
void Player::block(User *the_user, string status)
{
    if (status == status::BLOCKED)
    {
        blocked_users.insert(the_user);
    }
    else if (status == status::UNBLOCKED)
    {
        blocked_users.erase(the_user);
    }
}
void Player::health_penalty(int amount, int number_of_matches)
{
    health_penalties.amount = amount;
    health_penalties.remaining_matches = number_of_matches;
}
void Player::bullet_penalty(int amount, int number_of_matches)
{
    bullet_penalties.amount = amount;
    bullet_penalties.remaining_matches = number_of_matches;
}