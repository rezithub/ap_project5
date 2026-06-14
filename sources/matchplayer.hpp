#ifndef _MATCHPLAYER_HPP
#define _MATCHPLAYER_HPP
#include <string>
#include <vector>
#include "user.hpp"
#include "constants.hpp"
class MatchPlayerState
{
private:
    User *player;
    int bullets;
    int health;
    std::string current_action;
    std::vector<std::string> move_history;
public:
    MatchPlayerState(User *p,int init_health,int init_bullets)
    {
        player = p;
        bullets = init_bullets;
        health=init_health;
        current_action = PENDING_STATUS;
    }
    std::string get_current_action();
    int get_bullets();
    void set_action(std::string action);
    void shoot_bullet();
    void reload_bullet();
    User *get_player();
    void update_history();
    std::vector<std::string> get_history();
};

#endif