#include "game.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <set>
using namespace std;

bool compare_by_asc_value(const pair<string, int> &a, const pair<string, int> &b)
{
    if (a.second == b.second)
    {
        return a.first < b.first;
    }
    return a.second < b.second;
}
bool compare_by_desc_value(const pair<string, int> &a, const pair<string, int> &b)
{
    if (a.second == b.second)
    {
        return a.first < b.first;
    }
    return a.second > b.second;
}
void Game::add_report(std::string username, std::string reason)
{
    if (logged_in_user == nullptr || logged_in_user->get_user_type() == user::ADMIN)
    {
        throw PermissionDeniedException();
    }
    if (!user_exists(username))
    {
        throw NotFoundException();
    }
    Report *the_report = new Report(next_report_id, logged_in_user->get_username(), username, reason);
    reports[next_report_id] = the_report;
    next_report_id++;
}
void Game::show_user_invitations()
{
    if (logged_in_user == nullptr)
    {
        throw PermissionDeniedException();
    }
    logged_in_user->show_received_invitations();
}
void Game::show_reports()
{
    if (logged_in_user == nullptr || logged_in_user->get_user_type() != user::ADMIN)
    {
        throw PermissionDeniedException();
    }
    if (reports.empty())
    {
        throw EmptyException();
    }
    for (auto &[id, the_report] : reports)
    {
        string detail=the_report->get_deatiles();
        cout << detail << endl;
    }
}
void Game::remove_match(match *the_match)
{
    for (auto it = users_matches.begin(); it != users_matches.end();)
    {
        if (it->second == the_match)
        {
            it = users_matches.erase(it);
        }
        else
        {
            ++it;
        }
    }
    delete the_match;
}
void Game::do_action(string action)
{
    if (logged_in_user == nullptr || logged_in_user->get_user_type() == user::ADMIN)
    {
        throw PermissionDeniedException();
    }
    if (logged_in_user->get_player_status() == status::NOT_IN_GAME)
    {
        throw NotFoundException();
    }
    auto it = users_matches.find(logged_in_user->get_username());
    if (it == users_matches.end())
    {
        throw NotFoundException();
    }
    match *the_match = it->second;
    the_match->register_action(logged_in_user, action);
    if (the_match->get_match_status())
    {
        remove_match(the_match);
    }
}
void Game::report_profile(string username, bool show_own)
{
    if (logged_in_user == nullptr)
    {
        throw PermissionDeniedException();
    }
    if (show_own)
    {
        username = logged_in_user->get_username();
    }
    if (!user_exists(username))
    {
        throw NotFoundException();
    }
    User *the_user = users.at(username);
    if (the_user->get_user_type() == user::ADMIN || (show_own == true && logged_in_user->get_user_type() == user::ADMIN))
    {
        throw PermissionDeniedException();
    }
    cout << the_user->get_detailes() << endl;
}
void Game::show_match_status()
{
    if (logged_in_user == nullptr || logged_in_user->get_user_type() == user::ADMIN)
    {
        throw PermissionDeniedException();
    }
    if (logged_in_user->get_player_status() == status::NOT_IN_GAME)
    {
        throw NotFoundException();
    }
    auto it = users_matches.find(logged_in_user->get_username());
    if (it == users_matches.end())
    {
        throw NotFoundException();
    }
    match *the_match = it->second;
    the_match->print_status(logged_in_user);
}
void Game::dismiss_report(string report_id)
{
    if (logged_in_user == NULL || logged_in_user->get_user_type() == user::PLAYER)
    {
        throw PermissionDeniedException();
    }
    int id=stoi(report_id);
    if (reports.count(id) == 0)
    {
        throw NotFoundException();
    }
    Report *the_report = reports.at(id);
    reports.erase(id);
    delete the_report;
}
void Game::block_user(string username, string status)
{
    if (logged_in_user == nullptr || logged_in_user->get_user_type() == user::ADMIN)
    {
        throw PermissionDeniedException();
    }
    if (users.count(username) == 0)
    {
        throw NotFoundException();
    }
    User *the_user = users.at(username);
    if (the_user->get_user_type() == user::ADMIN)
    {
        throw BadRequestException();
    }
    logged_in_user->block(the_user, status);
}
bool Game::check_invitation(string intivation_id)
{
    int id;
    try
    {
        id = stoi(intivation_id);
    }
    catch (const exception &e)
    {
        throw BadRequestException();
    }

    if (invitations.count(id) == 0)
    {
        return false;
    }
    return true;
}
void Game::start_match(string id)
{
    if (logged_in_user == nullptr || logged_in_user->get_user_type() == user::ADMIN)
    {
        throw PermissionDeniedException();
    }
    if (!check_invitation(id))
    {
        throw NotFoundException();
    }
    int invite_id;
    try
    {
        invite_id = stoi(id);
    }
    catch (const exception &e)
    {
        throw BadRequestException();
    }
    Invitation *the_invitation = invitations.at(invite_id);
    User *player1 = the_invitation->get_destination_user();
    User *player2 = the_invitation->get_origin_user();
    if (player1 != logged_in_user)
    {
        throw PermissionDeniedException();
    }
    if (player1->get_player_status() == status::IN_GAME || player2->get_player_status() == status::IN_GAME)
    {
        throw PermissionDeniedException();
    }
    match *the_match;
    if (the_invitation->get_match_type() == Match::CASUAL)
    {
        the_match = new CasualMatch(player1, player2);
    }
    else if (the_invitation->get_match_type() == Match::RANKED)
    {
        if (player1->get_level() != player2->get_level())
        {
            invitations.erase(invite_id);
            player1->remove_invitation(the_invitation);
            delete the_invitation;
            throw LevelMisMatch();
        }
        the_match = new rankedmatch(player1, player2);
    }
    player1->set_player_status(status::IN_GAME);
    player2->set_player_status(status::IN_GAME);
    users_matches[player2->get_username()] = the_match;
    users_matches[player1->get_username()] = the_match;
    invitations.erase(invite_id);
    player1->remove_invitation(the_invitation);
    delete the_invitation;
}
void Game::penalty(int report_id,std::string penalty_type,int amount,int number_of_matches)
{
    if (logged_in_user == NULL || logged_in_user->get_user_type() == user::PLAYER)
    {
        throw PermissionDeniedException();
    }
    if(reports.count(report_id)==0){
        throw NotFoundException();
    }
    Report *the_report = reports.at(report_id);
    User* penalized_player=users.at(the_report->get_reciever());
    if(penalty_type=="health_penalty"){
        penalized_player->health_penalty(amount,number_of_matches);
    }
    else if(penalty_type=="bullet_penalty"){
        penalized_player->bullet_penalty(amount,number_of_matches);
    }
    reports.erase(report_id);
    delete the_report;
}
void Game::reject_invitation(string id)
{
    if (logged_in_user == nullptr || logged_in_user->get_user_type() == user::ADMIN)
    {
        throw PermissionDeniedException();
    }
    if (!check_invitation(id))
    {
        throw NotFoundException();
    }
    int invite_id;
    try
    {
        invite_id = stoi(id);
    }
    catch (const exception &e)
    {
        throw BadRequestException();
    }

    Invitation *the_invitation = invitations.at(invite_id);
    if (the_invitation->get_destination_user() != logged_in_user)
    {
        throw PermissionDeniedException();
    }

    invitations.erase(invite_id);
    logged_in_user->remove_invitation(the_invitation);
    delete the_invitation;
}
void print_opponents_detailes(const map<string, int> &opponents_detailes, string show_type, string match_type)
{
    vector<pair<string, int>> vector_of_pairs(opponents_detailes.begin(), opponents_detailes.end());
    if (show_type == "asc")
    {
        sort(vector_of_pairs.begin(), vector_of_pairs.end(), compare_by_asc_value);
    }
    else if (show_type == "desc")
    {
        sort(vector_of_pairs.begin(), vector_of_pairs.end(), compare_by_desc_value);
    }
    int number = 1;
    string value_name;
    match_type == "casual" ? value_name = "XP" : value_name = "RP";
    for (const auto &the_pair : vector_of_pairs)
    {

        cout << number << ". " << the_pair.first << " with " << the_pair.second << " " << value_name << endl;
        number++;
    }
}
void Game::fill_opponents_map(User *the_opponent, map<string, int> &opponents_detailes, bool &opponent_exist, string match_type)
{
    if (match_type == "casual")
    {
        if (the_opponent->get_readiness_status())
        {
            opponent_exist = true;
            opponents_detailes[the_opponent->get_username()] = the_opponent->get_xp();
        }
    }
    else if (match_type == "ranked")
    {
        if (the_opponent->get_level() == logged_in_user->get_level())
        {
            opponent_exist = true;
            opponents_detailes[the_opponent->get_username()] = the_opponent->get_rp();
        }
    }
}
void Game::show_opponents(string show_type, string match_type)
{
    if (logged_in_user == nullptr || logged_in_user->get_user_type() == user::ADMIN)
    {
        throw PermissionDeniedException();
    }
    bool opponent_exist = false;
    User *the_player = logged_in_user;
    map<string, int> opponents_detailes;
    for (auto &[user_name, the_opponent] : users)
    {
        if (the_opponent == the_player)
        {
            continue;
        }
        fill_opponents_map(the_opponent, opponents_detailes, opponent_exist, match_type);
    }
    if (!opponent_exist)
    {
        throw EmptyException();
    }
    print_opponents_detailes(opponents_detailes, show_type, match_type);
}
Game::Game()
{
    next_invitation_id = 1;
    next_report_id = 1;
    logged_in_user = nullptr;
}
void Game::load_players(const string &filepath)
{
    ifstream file(filepath);
    if (!file.is_open())
    {
        return;
    }
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        string username, password, xp_str, rp_str;
        getline(ss, username, COMMA_SEPARATOR);
        getline(ss, password, COMMA_SEPARATOR);
        getline(ss, xp_str, COMMA_SEPARATOR);
        getline(ss, rp_str, COMMA_SEPARATOR);
        int xp = stoi(xp_str);
        int rp = stoi(rp_str);
        users[username] = new Player(username, password, xp, rp);
    }
    file.close();
}

void Game::logout_user()
{
    if (logged_in_user == nullptr)
    {
        throw PermissionDeniedException();
    }
    logged_in_user = nullptr;
}

void Game::change_status(string user_status)
{
    if (logged_in_user == nullptr)
    {
        throw PermissionDeniedException();
    }
    User *the_player = logged_in_user;
    the_player->set_readiness_status(user_status);
}

void Game::load_admins(const string &filepath)
{
    ifstream file(filepath);
    if (!file.is_open())
    {
        return;
    }
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        string username, password;
        getline(ss, username, COMMA_SEPARATOR);
        getline(ss, password, COMMA_SEPARATOR);
        users[username] = new Admin(username, password);
    }
    file.close();
}

void Game::register_user(string username, string password)
{
    if (logged_in_user != nullptr)
    {
        throw PermissionDeniedException();
    }
    if (users.count(username) > 0)
    {
        throw BadRequestException();
    }
    Player *the_player = new Player(username, password, INITIAL_XP, INITIAL_RP);
    users[username] = the_player;
    logged_in_user = the_player;
}
bool Game::user_exists(std::string the_username)
{
    if (users.count(the_username) > 0)
    {
        return true;
    }
    return false;
}

Game::~Game()
{
    for (auto it = users.begin(); it != users.end(); it++)
    {
        delete it->second;
    }
    for (auto it = reports.begin(); it != reports.end(); it++)
    {
        delete it->second;
    }
    for (auto it = invitations.begin(); it != invitations.end(); it++)
    {
        delete it->second;
    }
    set<match *> unique_matches;
    for (auto it = users_matches.begin(); it != users_matches.end(); it++)
    {
        unique_matches.insert(it->second);
    }

    for (match *the_match : unique_matches)
    {
        delete the_match;
    }
}
void Game::post_inviation(string opponent_username, string match_type)
{
    if (logged_in_user == nullptr || logged_in_user->get_user_type() == user::ADMIN)
    {
        throw PermissionDeniedException();
    }
    if (users.count(opponent_username) == 0)
    {
        throw NotFoundException();
    }
    User *the_opponent_user = users.at(opponent_username);
    User *the_player = logged_in_user;
    if (the_opponent_user->get_user_type() == user::ADMIN)
    {
        throw PermissionDeniedException();
    }
    if (the_opponent_user->check_block(the_player))
    {
        throw NotFoundException();
    }
    Invitation *the_invitation = new Invitation(the_player, the_opponent_user, match_type, next_invitation_id);
    the_opponent_user->add_invitation(the_invitation);
    invitations[next_invitation_id] = the_invitation;
    next_invitation_id++;
}

void Game::login_user(string entered_username, string entered_password)
{
    if (logged_in_user != nullptr)
    {
        throw PermissionDeniedException();
    }
    if (users.count(entered_username) == 0)
    {
        throw NotFoundException();
    }
    User *the_user = users.at(entered_username);
    if (the_user->get_password() != entered_password)
    {
        throw PermissionDeniedException();
    }
    logged_in_user = the_user;
}