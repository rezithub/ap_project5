#include <iostream>
#include "game.hpp"
#include "commandhandler.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cout << "Error : input users & admins file please !" << endl;
        return 1;
    }
    Game UTGame;
    UTGame.load_players(argv[1]);
    UTGame.load_admins(argv[2]);
    CommandHandler commandhandler(UTGame);
    commandhandler.run();
    return 0;
}