#include "rankedmatch.hpp"
using namespace std;

rankedmatch::rankedmatch(User *p1, User *p2) 
    : match(p1, p2, 
            3 - p1->get_health_penalty_amount(), 
            3 - p1->get_bullet_penalty_amount(), 
            3 - p2->get_health_penalty_amount(), 
            3 - p2->get_bullet_penalty_amount()) 
{
    p1->consume_penalties();
    p2->consume_penalties();
}