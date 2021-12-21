#include "Game.h"
int main()
{
    bool og_val = true;
    while(og_val)
    {
        Game game;
        og_val = game.run();
    }
    return 0;
}
