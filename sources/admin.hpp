#ifndef _ADMIN_HPP
#define _ADMIN_HPP
#include "user.hpp"
#include "constants.hpp"
class Admin : public User
{
private:
public:
    Admin(std::string _username, std::string _password);
    bool get_readiness_status();
    std::string get_user_type() override;
};
#endif