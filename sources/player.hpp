#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include <string>
#include <vector>
#include <set>

#include "constants.hpp"
#include "user.hpp"
#include "invitation.hpp"
struct Penalty
{
    int amount = 0;
    int remaining_matches = 0;
};

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
    std::set<User *> blocked_users;
    Penalty health_penalties;
    Penalty bullet_penalties;

public:
    Player(std::string _username, std::string _password, int _xp, int _rp);
    void set_readiness_status(std::string the_status) override;
    void set_player_status(std::string the_status) override;
    bool get_readiness_status() override;
    int get_xp() override;
    int get_rp() override;
    bool check_block(User *the_opponent) override;
    std::string get_level() override;
    void set_xp(int newxp) override;
    void set_rp(int newrp) override;
    void add_invitation(Invitation *the_invitation) override;
    void remove_invitation(Invitation *the_invitation) override;
    std::string get_user_type() override;
    std::string get_player_status() override;
    std::string get_detailes() override;
    void win_match() override;
    void lose_match() override;
    void show_received_invitations() override;
    void block(User *the_user, std::string status) override;
    int get_health_penalty_amount() override;
    int get_bullet_penalty_amount() override;
    void consume_penalties() override;
    void health_penalty(int amount, int number_of_matches) override;
    void bullet_penalty(int amount, int number_of_matches) override;
};

#endif