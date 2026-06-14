#include "invitation.hpp"
#include <iostream>
using namespace std;
Invitation::Invitation(User *_origin_player, User *_destination_player, string _match_type, int _id) : origin_player(_origin_player), destination_player(_destination_player)
{
    match_type = _match_type;
    id = _id;
}
User *Invitation::get_origin_user()
{
    return origin_player;
}
string Invitation::get_match_type()
{
    return match_type;
}
User *Invitation::get_destination_user()
{
    return destination_player;
}
int Invitation::get_id()
{
    return id;
}
void Invitation::print_detailes()
{
    cout << id << ": Invitation from " << '"' << origin_player->get_username() << '"' << " for a " << '"' << match_type << '"' << " match" << endl;
}