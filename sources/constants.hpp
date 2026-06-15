#ifndef _CONSTANTS_HPP_
#define _CONSTANTS_HPP_
#include <string>
namespace action
{
    const std::string SHOOT = "shoot";
    const std::string RELOAD = "reload";
    const std::string PENDING = "pending";
    const std::string DEFEND = "defend";
}
namespace user
{
    const std::string ADMIN = "admin";
    const std::string PLAYER = "player";
}
namespace level
{
    const std::string BORONZE = "Bronze";
    const std::string SILVER = "Silver";
    const std::string GOLD = "Golden";
    const std::string PLATINUM = "Platinum";
}

namespace Match
{
    const std::string RANKED = "ranked";
    const std::string CASUAL = "casual";
}

namespace status
{
    const std::string NOT_IN_GAME = "NOT_IN_GAME";
    const std::string IN_GAME = "IN_GAME";
    const std::string BLOCKED = "blocked";
    const std::string UNBLOCKED = "unblocked";
}

const int INITIAL_XP = 500;
const int INITIAL_RP = 1200;
const char COMMA_SEPERATOR = ',';
const char QUOTE_SEPERATOR = '"';
const int INITIAL_CS_BULLET = 1;
const int INITIAL_CS_HEALTH = 1;
const int INITIAL_RN_BULLET = 3;
const int INITIAL_RN_HEALTH = 3;
#endif
