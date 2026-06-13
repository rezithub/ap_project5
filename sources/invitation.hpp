#ifndef _INVITATION_HPP
#define _INVITATION_HPP
#include "user.hpp"
#include <string>

class Invitation
{
private:
    User *origin_player;
    User *destination_player;
    std::string match_type;
    int id;

public:
    Invitation(User *_origin_player, User *_destination_player, std::string _match_type, int _id);
    User *get_origin_user();
    User *get_destination_user();
    int get_id();
    void print_detailes();
    std::string get_match_type();
};

#endif