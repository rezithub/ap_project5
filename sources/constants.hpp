#ifndef _CONSTANTS_HPP_
#define _CONSTANTS_HPP_
#include <string>
namespace status
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

const std::string NOT_IN_GAME_STATUS = "NOT_IN_GAME";
const std::string IN_GAME_STATUS = "IN_GAME";
const std::string BORONZE_LEVEL = "Bronze";
const std::string SILVER_LEVEL = "Silver";
const std::string GOLD_LEVEL = "Golden";
const std::string BLOCKED_STATUS = "blocked";
const std::string UNBLOCKED_STATUS = "unblocked";
const std::string PLATINUM_LEVEL = "Platinum";
const std::string RANKED_MATCH = "ranked";
const std::string CASUAL_MATCH = "casual";
const int INITIAL_XP = 500;
const int INITIAL_RP = 1200;
const char COMMA_SEPERATOR = ',';
const char QUOTE_SEPERATOR = '"';
const int INITIAL_CS_BULLET = 1;
const int INITIAL_CS_HEALTH = 1;
const int INITIAL_RN_BULLET = 3;
const int INITIAL_RN_HEALTH = 3;
#endif
