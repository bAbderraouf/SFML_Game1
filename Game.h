#ifndef Game_h
#define Game_h

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

    struct Button{bool left , right  , space ;};
    Button button;
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
    void initPlayer();
    void initShoot();
    void calculateScore(int i); 
    

    /* Game objects */
    sf::Texture enemie_texture;
    sf::Sprite enemie;
    std::vector <sf::Sprite> enemies;

    sf::Texture player_texture;
    sf::Sprite player;
    sf::Vector2i size_player;

    sf::RectangleShape shoot;
    std::vector <sf::RectangleShape> shoots;

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
    void updatePlayer();
    void updateShoots();
    void generateShoots();

    // runder sub functions
    void renderEnemies();
    void renderText(sf::RenderTarget &target); /// to be able to render it on any target (not only window)
    void renderPlayer();
    void renderShoots();
};


#endif