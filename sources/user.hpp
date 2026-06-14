#ifndef _USER_HPP
#define _USER_HPP
#include <string>
#include "exceptions.hpp"
class Invitation;

class User
{
protected:
    std::string username;
    std::string password;
    int next_item_id;

public:
    User(std::string _username, std::string _password);
    virtual ~User() {};
    std::string get_password();
    std::string get_username();
    virtual int get_xp();
    virtual void block(User* the_user,std::string status);
    virtual bool check_block(User *the_user);
    virtual int get_rp();
    virtual void set_xp(int newxp);
    virtual void set_rp(int newrp);
    virtual bool get_readiness_status() = 0;
    virtual void set_readiness_status(std::string the_status);
    virtual std::string get_player_status();
    virtual std::string get_level();
    virtual void add_invitation(Invitation *the_invitation);
    virtual std::string user_type() = 0;
    virtual void set_player_status(std::string the_status);
    virtual void remove_invitation(Invitation *the_invitation);
    virtual void print_detailes();
    virtual void show_received_invitations();
    virtual void win_match();
    virtual void lose_match();
    virtual int get_health_penalty_amount();
    virtual int get_bullet_penalty_amount();
    virtual void consume_penalties();
};
#endif