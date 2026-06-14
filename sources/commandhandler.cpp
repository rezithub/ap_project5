#include "commandhandler.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void read_question_symbole(stringstream &ss)
{
    char question_symbole;
    if (!(ss >> question_symbole) || question_symbole != '?')
    {
        throw BadRequestException();
    }
}
void read_quote_symbole(stringstream &ss)
{
    char quote;
    ss >> quote;
    if (quote != QUOTE_SEPERATOR)
    {
        throw BadRequestException();
    }
}

CommandHandler::CommandHandler(Game &UTGame)
{
    game = &UTGame;
}
void CommandHandler::fill_invitation_detailes(string &username, string &match_type, string remaining_line)
{
    stringstream ss(remaining_line);
    read_question_symbole(ss);
    string key;
    bool find_username = false, find_match_type = false;
    while (ss >> key)
    {
        read_quote_symbole(ss);
        string value;
        getline(ss, value, QUOTE_SEPERATOR);
        if (key == "username")
        {
            username = value;
            if (username.empty())
            {
                throw BadRequestException();
            }
            find_username = true;
        }
        else if (key == "match_type")
        {
            match_type = value;
            if (match_type.empty())
            {
                throw BadRequestException();
            }
            find_match_type = true;
        }
    }
    if (!find_username || !find_match_type)
    {
        throw BadRequestException();
    }
}
void CommandHandler::fill_user_detailes(string &username, string &password, string remaining_line)
{
    stringstream ss(remaining_line);
    read_question_symbole(ss);
    string key;
    bool find_username = false, find_password = false;
    while (ss >> key)
    {
        read_quote_symbole(ss);
        string value;
        getline(ss, value, QUOTE_SEPERATOR);
        if (key == "username")
        {
            username = value;
            find_username = true;
        }
        else if (key == "password")
        {
            password = value;
            find_password = true;
        }
    }
    if (!find_username || !find_password)
    {
        throw BadRequestException();
    }
}
void read_match_detailes(string remaining_line, string &show_type)
{
    stringstream ss(remaining_line);
    read_question_symbole(ss);
    string key;
    show_type = "desc";
    bool find_sort = false;
    while (ss >> key)
    {
        if (key == "sort_order")
        {
            find_sort = true;
            read_quote_symbole(ss);
            getline(ss, show_type, QUOTE_SEPERATOR);
            if (show_type != "asc" && show_type != "desc")
            {
                throw BadRequestException();
            }
        }
    }
}
void read_username(string remaining_line, string &username, bool &find_username)
{
    stringstream ss(remaining_line);
    read_question_symbole(ss);
    string key;
    while (ss >> key)
    {
        read_quote_symbole(ss);
        string value;
        getline(ss, value, QUOTE_SEPERATOR);
        if (key == "username")
        {
            username = value;
            if (username.empty())
            {
                throw BadRequestException();
            }
            find_username = true;
        }
    }
}
void CommandHandler::get_process(string action, string remaining_line)
{
    if (action == "casual_match_opponents")
    {
        string show_type;
        read_match_detailes(remaining_line, show_type);
        game->show_opponents(show_type, "casual");
    }
    else if (action == "ranked_match_opponents")
    {
        string show_type;
        read_match_detailes(remaining_line, show_type);
        game->show_opponents(show_type, "ranked");
    }
    else if (action == "profile")
    {
        string username;
        bool find_username = false;
        read_username(remaining_line, username, find_username);
        game->report_profile(username, !find_username);
    }
    else if (action == "received_invitations")
    {
        stringstream ss(remaining_line);
        read_question_symbole(ss);
        game->show_user_invitations();
    }
    else if (action == "reports")
    {
        stringstream ss(remaining_line);
        read_question_symbole(ss);
        game->show_reports();
    }
    else if (action == "match_status")
    {
        stringstream ss(remaining_line);
        read_question_symbole(ss);
        game->show_match_status();
    }
    else
    {
        throw NotFoundException();
    }
}
void CommandHandler::put_process(string action, string remaining_line)
{
    throw NotFoundException();
}
void read_casual_match_readiness(string remaining_line, string &is_ready)
{
    stringstream ss(remaining_line);
    read_question_symbole(ss);
    string key;
    bool find_status = false;
    while (ss >> key)
    {
        if (key == "status")
        {
            read_quote_symbole(ss);
            getline(ss, is_ready, QUOTE_SEPERATOR);
            if (is_ready != "true" && is_ready != "false")
            {
                throw BadRequestException();
            }
            find_status = true;
        }
    }
    if (!find_status)
    {
        throw BadRequestException();
    }
}
void read_id(string remaining_line, string expected_key, string &id)
{
    stringstream ss(remaining_line);
    read_question_symbole(ss);
    bool find_id = false;
    string key;
    while (ss >> key)
    {
        if (key == expected_key)
        {
            read_quote_symbole(ss);
            getline(ss, id, QUOTE_SEPERATOR);
            find_id = true;
        }
    }
    if (!find_id)
    {
        throw BadRequestException();
    }
}
void read_report(string remaining_line, string &username, string &reason)
{
    stringstream ss(remaining_line);
    read_question_symbole(ss);
    string key;
    bool find_username = false, find_reason = false;
    while (ss >> key)
    {
        read_quote_symbole(ss);
        string value;
        getline(ss, value, QUOTE_SEPERATOR);
        if (key == "username")
        {
            username = value;
            find_username = true;
        }
        else if (key == "reason")
        {
            reason = value;
            if (reason.empty())
            {
                throw BadRequestException();
            }
            find_reason = true;
        }
    }
    if (!find_username || !find_reason)
    {
        throw BadRequestException();
    }
}
void read_action(string remaining_line, string &action)
{
    stringstream ss(remaining_line);
    read_question_symbole(ss);
    string key;
    bool find_action = false;
    while (ss >> key)
    {
        if (key == "action")
        {
            read_quote_symbole(ss);
            getline(ss, action, QUOTE_SEPERATOR);
            if (action != SHOOT_ACTION && action != DEFEND_ACTION && action != RELOAD_ACTION)
            {
                throw BadRequestException();
            }
            find_action = true;
        }
    }
    if (!find_action)
    {
        throw BadRequestException();
    }
}
void fill_block_detailes(string remaining_line, string &username, string &status)
{
    stringstream ss(remaining_line);
    read_question_symbole(ss);
    string key;
    bool find_username = false, find_status = false;
    while (ss >> key)
    {
        read_quote_symbole(ss);
        string value;
        getline(ss, value, QUOTE_SEPERATOR);
        if (key == "username")
        {
            username = value;
            find_username = true;
        }
        else if (key == "status")
        {
            status = value;
            if (status != "blocked" && status != "unblocked")
            {
                throw BadRequestException();
            }
            find_status = true;
        }
    }
    if (!find_username || !find_status)
    {
        throw BadRequestException();
    }
}
void CommandHandler::post_process(string action, string remaining_line)
{

    if (action == "register")
    {
        string username, password;
        fill_user_detailes(username, password, remaining_line);
        game->register_user(username, password);
        cout << "OK" << endl;
    }
    else if (action == "login")
    {
        string username, password;
        fill_user_detailes(username, password, remaining_line);
        game->login_user(username, password);
        cout << "OK" << endl;
    }
    else if (action == "logout")
    {
        stringstream ss(remaining_line);
        read_question_symbole(ss);
        game->logout_user();
        cout << "OK" << endl;
    }
    else if (action == "casual_match_ready")
    {
        string is_ready;
        read_casual_match_readiness(remaining_line, is_ready);
        game->change_status(is_ready);
        cout << "OK" << endl;
    }
    else if (action == "invitation")
    {
        string opponent_username;
        string match_type;
        fill_invitation_detailes(opponent_username, match_type, remaining_line);
        if (match_type != CASUAL_MATCH && match_type != RANKED_MATCH)
        {
            throw BadRequestException();
        }
        game->post_inviation(opponent_username, match_type);
        cout << "OK" << endl;
    }
    else if (action == "start_match")
    {
        string invitation_id;
        read_id(remaining_line, "invitation_id", invitation_id);
        game->start_match(invitation_id);
        cout << "OK" << endl;
    }
    else if (action == "reject_invitation")
    {
        string invitation_id;
        read_id(remaining_line, "invitation_id", invitation_id);
        game->reject_invitation(invitation_id);
        cout << "OK" << endl;
    }
    else if (action == "report")
    {
        string username;
        string reason;
        read_report(remaining_line, username, reason);
        game->add_report(username, reason);
        cout << "OK" << endl;
    }
    else if (action == "action")
    {
        string action;
        read_action(remaining_line, action);
        game->do_action(action);
        cout << "OK" << endl;
    }
    else if (action == "dismiss_report")
    {
        string report_id;
        read_id(remaining_line, "report_id", report_id);
        game->dismiss_report(report_id);
        cout << "OK" << endl;
    }
    else if (action == "block")
    {
        string username;
        string status;
        fill_block_detailes(remaining_line, username, status);
        game->block_user(username, status);
        cout << "OK" << endl;
    }
    else
    {
        throw NotFoundException();
    }
}

void CommandHandler::delete_process(string action, string remaining_line)
{
    throw NotFoundException();
}

void CommandHandler::run()
{
    string line;
    while (getline(cin, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);
        string command;
        ss >> command;

        try
        {
            string action;
            ss >> action;

            string remaining_line;
            getline(ss, remaining_line);

            if (command == "GET")
            {
                get_process(action, remaining_line);
            }
            else if (command == "POST")
            {
                post_process(action, remaining_line);
            }
            else if (command == "PUT")
            {
                put_process(action, remaining_line);
            }
            else if (command == "DELETE")
            {
                delete_process(action, remaining_line);
            }
            else
            {
                throw BadRequestException();
            }
        }
        catch (const BadRequestException &e)
        {
            cout << e.what() << endl;
        }
        catch (const NotFoundException &e)
        {
            cout << e.what() << endl;
        }
        catch (const PermissionDeniedException &e)
        {
            cout << e.what() << endl;
        }
        catch (const EmptyException &e)
        {
            cout << e.what() << endl;
        }
        catch (const exception &e)
        {
            cout << "An unexpected error occurred: " << e.what() << endl;
        }
    }
}