#include "Game.h"
#include <iostream>


int main()
{
  
    std::srand(static_cast<unsigned> (time(NULL)) );  // intialising srand

    // setup()  
    Game game;


    // game loop 

    while (game.getIfWindowIsOpen()    &&  !game.getGameOver() )
    {
        // Input() 
        game.input();
        

        // update()  = logic 
        game.update();

        // render() 
        game.render();

    }
    
    return 0;
}