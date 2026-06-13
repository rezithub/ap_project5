#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include <string>
#include <vector>

#include "constants.hpp"
#include "user.hpp"
#include "invitation.hpp"
class Player : public User
{
private:
    int xp;
    int rp;
    int total_wins;
    int total_loses;
    bool is_ready_cs_match;
    std::string player_status;
    std::vector<Invitation *> received_invitations;

public:
    Player(std::string _username, std::string _password, int _xp,int _rp);
    void set_readiness_status(std::string the_status) override;
    void set_player_status(std::string the_status) override;
    bool get_readiness_status() override;
    int get_xp() override;
    void set_xp(int newxp) override;
    void add_invitation(Invitation *the_invitation) override;
    void remove_invitation(Invitation *the_invitation) override;
    std::string user_type() override;
    std::string get_player_status() override;
    void print_detailes() override;
    void win_match() override;
    void lose_match() override;
    void show_received_invitations() override;
};
#endif