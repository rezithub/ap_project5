#include "admin.hpp"

using namespace std;
Admin::Admin(string _username, string _password) : User(_username, _password) {}
bool Admin::get_readiness_status()
{
    return false;
}
string Admin::get_user_type()
{
    return user::ADMIN;
}