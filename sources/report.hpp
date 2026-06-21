#ifndef _REPORT_HPP
#define _REPORT_HPP
#include <string>
class Report
{
private:
    int id;
    std::string sender_username;
    std::string reciever_username;
    std::string reason;

public:
    Report(int id, std::string _sender_username, std::string _reciever_username, std::string _reason);
    std::string get_reciever();
    std::string get_deatiles();
};
#endif