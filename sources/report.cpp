#include "report.hpp"
#include <iostream>
using namespace std;
Report::Report(int _id, string _sender_username, string _reciever_username, string _reason)
{
    id = _id;
    sender_username = _sender_username;
    reciever_username = _reciever_username;
    reason = _reason;
}
void Report::print_detailes()
{
    cout << id << ": " << '"' << sender_username << '"' <<
    " reported " << '"' << reciever_username << '"'   
    << " for: " << '"' << reason << '"' << endl;
}