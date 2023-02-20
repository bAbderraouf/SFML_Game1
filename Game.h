//#ifndef Game
//#define Game

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>  // to store enmies
#include <ctime>  // for randomizing
#include <sstream>  // string streams for updatings texts
#include <string>

/* 
    defintion de la classe principale du jeux
*/

class Game
{
private:

    /* variables */
    sf::VideoMode videoMode;
    sf::RenderWindow *fenetre;  // its a pointer because we need to delete it if need (dynamiquement alouée )
    sf::Event evnt;

    sf::Vector2i mousePosWindow ; // position of mouse relative to window
    sf::Vector2f mousePosView;

    /* Fonts */
    sf::Font font;

    /* Text */
    sf::Text guiText;

    /* Game logic */

    unsigned score; 
    float enemySpwanTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    bool gameOver;
    bool mouseClicked;
    int health;
    unsigned energy;

    /* Private fucntions */
    void initializeVariables();
    void initWindow();
    void initEnemy();
    void initFont();
    void initText();
    

    /* Game objects */
    sf::RectangleShape enemie;
    std::vector <sf::RectangleShape> enemies;

public:

    /* constructor / destructor */
    Game();
    virtual ~Game();

    /* Accessors */
    const bool getIfWindowIsOpen() const;
    bool getGameOver() const;

    /*  Public Functions */
    void setup();
    void input();
    void update();
    void render();

    // update sub functions
    void updateMousePosition();
    void spawnEnemies() ; // multiply enemies
    void updateEnemies(); 
    void updateText();
    void updateEnergy();

    // runder sub functions
    void renderEnemies();
    void renderText(sf::RenderTarget &target); /// to be able to render it on any target (not only window)
};


//#endif