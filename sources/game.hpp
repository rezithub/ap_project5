#ifndef _GAME_HPP
#define _GAME_HPP

#include <map>
#include <string>
#include <vector>

#include "user.hpp"
#include "player.hpp"
#include "admin.hpp"
#include "CasualMatch.hpp"
#include "invitation.hpp"
#include "report.hpp"
#include "exceptions.hpp"
#include "constants.hpp"

class Game
{
private:
    std::map<std::string, User *> users;
    std::vector<Report *> reports;
    std::map<int, Invitation *> invitations;
    std::map<std::string, CasualMatch *> users_matches;
    int next_invitation_id;
    int next_report_id;
    User *logged_in_user;
    void remove_match(CasualMatch *the_match);
    void Game::fill_opponents_map(User *the_opponent, map<string, int> &opponents_detailes, bool &opponent_exist, string match_type);

public:
    ~Game();
    Game();
    void register_user(std::string username, std::string password);
    void login_user(std::string entered_username, std::string entered_password);
    void logout_user();
    void start_match(std::string id);
    void reject_invitation(std::string id);
    void change_status(std::string user_status);
    void show_opponents(std::string show_type, std::string match_type);
    void post_inviation(std::string opponent_username, std::string match_type);
    void do_action(std::string action);
    void show_match_status();
    void load_players(const std::string &filepath);
    void load_admins(const std::string &filepath);
    void add_report(std::string username, std::string reason);
    void report_profile(std::string username, bool show_own);
    void show_user_invitations();
    void show_reports();
    bool check_invitation(std::string intivation_id);
    bool user_exists(std::string the_username);
};
#endif