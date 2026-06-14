#include "user.hpp"

using namespace std;

User::User(string _username, string _password)
{
    username = _username;
    password = _password;
    next_item_id = 0;
}
string User::get_password()
{
    return password;
}
string User::get_username()
{
    return username;
}
void User::bullet_penalty(int amount, int number_of_matches)
{
    throw PermissionDeniedException();
}
void User::health_penalty(int amount, int number_of_matches)
{
    throw PermissionDeniedException();
}
string User::get_player_status()
{
    throw PermissionDeniedException();
}
string User::get_level()
{
    throw PermissionDeniedException();
}
int User::get_rp()
{
    throw PermissionDeniedException();
}
bool User::check_block(User *user_type)
{
    throw PermissionDeniedException();
}
void User::remove_invitation(Invitation *the_invitation)
{
    throw PermissionDeniedException();
}
void User::show_received_invitations()
{
    throw PermissionDeniedException();
}
void User::set_xp(int newxp)
{
    throw PermissionDeniedException();
}
int User::get_xp()
{
    throw PermissionDeniedException();
}
void User::win_match()
{
    throw PermissionDeniedException();
}
void User::lose_match()
{
    throw PermissionDeniedException();
}
void User::set_readiness_status(string the_status)
{
    throw PermissionDeniedException();
}
void User::add_invitation(Invitation *the_invitation)
{
    throw PermissionDeniedException();
}
void User::set_player_status(std::string the_status)
{
    throw PermissionDeniedException();
}

void User::print_detailes()
{
    throw PermissionDeniedException();
}
void User::block(User *the_user, string status)
{
    throw PermissionDeniedException();
}
int User::get_health_penalty_amount()
{
    throw PermissionDeniedException();
}
int User::get_bullet_penalty_amount()
{
    throw PermissionDeniedException();
}
void User::consume_penalties()
{
    throw PermissionDeniedException();
}
void User::set_rp(int newrp)
{
    throw PermissionDeniedException();
}