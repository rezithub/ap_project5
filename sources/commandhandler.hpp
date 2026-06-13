#ifndef _COMMANDHANDLER_HPP
#define _COMMANDHANDLER_HPP
#include "game.hpp"

class CommandHandler
{
private:
    Game *game;
    void fill_user_detailes(std::string &username, std::string &password, std::string remaining_line);
    void get_process(std::string action, std::string remaining_line);
    void post_process(std::string action, std::string remaining_line);
    void put_process(std::string action, std::string remaining_line);
    void delete_process(std::string action, std::string remaining_line);
    void fill_invitation_detailes(std::string &username, std::string &match_type, std::string remaining_line);
public:
    CommandHandler(Game &UTGame);
    void run();
};
#endif