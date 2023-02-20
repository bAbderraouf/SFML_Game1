#include <SFML/Graphics.hpp>

// using namespace sf;

    /* 
    The game loop is always :

    setup();

    while(true)
    {
        Input();
        update();  // somtimes not realy needed
        render(); // draw
    }

    */

int main()
{
  
    /*  config de la fenetre  */

    sf::RenderWindow fenetre(sf::VideoMode(640, 480) , "game1" , sf::Style::Titlebar  | sf::Style::Close );  // titre + fermeture
    sf::Event evnt;   // listener for events

    /* game loop */

    while (fenetre.isOpen())
    {
        /* Input() = listening for events */
        while (fenetre.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                fenetre.close();
                break;
            
            case sf::Event::KeyPressed:
                if(evnt.key.code == sf::Keyboard::Escape)
                {
                    fenetre.close();
                    break;
                }
            }
        }

        /* update() : the game (change values if needed) */
        

        /* render() :  (apply new values on the game) == draw it again */

        fenetre.clear(sf::Color(255 , 25 , 150 , 255));  
        fenetre.display();

    }
    
    return 0;
}