    #include "Game.h"
    

    /*-------------------------------*/
    /* Private fucntions */
    /*-------------------------------*/

    void Game::initializeVariables()
    {
        this->fenetre = NULL;
        // no need to initialise event (it has a default initialisation)
        // video mode 
        this->videoMode.height = 600 ;
        this->videoMode.width = 800;

        this->gameOver = false;
        this->score = 0;
        this->enemySpawnTimerMax = 150.f;
        this->enemySpwanTimer = this->enemySpawnTimerMax;
        this->maxEnemies = 8;
        this->mouseClicked = false;
        this->health = 20;
        this->energy = 0;

        this->button.left = false;
        this->button.right = false;
        this->button.space = false;

        this->initEnemy();
        this->initFont();
        this->initText();
        this->initPlayer();
        this->initShoot();

        this->plane.loadFromFile("fight_plane_1.png");
        this->sprite.setTexture(this->plane);
        this->sprite.setScale(sf::Vector2f(0.2f, 0.2f));
        this->sprite.setPosition(sf::Vector2f(100.f, 100.f));
        this->sprite.setColor(sf::Color::Red);

    }

    void Game::initWindow()
    {
        this->fenetre = new sf::RenderWindow( this->videoMode , "game1" , sf::Style::Titlebar  | sf::Style::Close );  // titre + fermeture
        this->fenetre->setFramerateLimit(60);
    }

    void Game::initEnemy()
    {
        this->enemie.setPosition(sf::Vector2f(10.f , 10.f));
        this->enemie.setSize(sf::Vector2f(100.f , 100.f));
        this->enemie.setScale(sf::Vector2f(0.5f, 0.5f)); // 50% of its orignal size
        this->enemie.setFillColor(sf::Color::Blue);
        this->enemie.setOutlineColor(sf::Color::White);
        this->enemie.setOutlineThickness(2.f); 
        
    }

    void Game::initFont()
    {
        if ( this->font.loadFromFile("fonts/Dosis-Light.ttf") == false )
            std::cout << "ERROR :: Font :: Failed to load.\n";
    }

    void Game::initText()
    {
        this->guiText.setFont(this->font);
        this->guiText.setCharacterSize(22);
        this->guiText.setFillColor(sf::Color::Yellow);
        //this->guiText.setOutlineColor(sf::Color::White);
        // this->guiText.setOutlineThickness(1.f);
        this->guiText.setString(""); // initialised to nothing

    }

    void Game::initPlayer()
    {
        
/*
        this->player.setPosition(sf::Vector2f( posyPlayer , posxPlayer));
        this->player.setSize(sf::Vector2f(lPlayer , hPlayer));
       // this->player.setScale(sf::Vector2f(0.5f, 0.5f)); // 50% of its orignal size
        this->player.setFillColor(sf::Color::Blue);
        this->player.setOutlineColor(sf::Color::Blue);
        this->player.setOutlineThickness(2.f); 
*/
        // player as a plane:
        this->player_texture.loadFromFile("player.png");
        this->player.setTexture(this->player_texture);
        this->player.setScale(sf::Vector2f(0.2f, 0.2f));
        this->player.setColor(sf::Color::Green);    

        int hPlayer = this->player.getTexture()->getSize().y * player.getScale().y ,
         lPlayer = this->player.getTexture()->getSize().x * player.getScale().x ;
        
        this->size_player.x = lPlayer;
        this->size_player.y = hPlayer;
        
        float posxPlayer = this->videoMode.height - hPlayer - 5 ;
        float posyPlayer = (this->videoMode.width - lPlayer) / 2 ;

        this->player.setPosition(sf::Vector2f( posyPlayer , posxPlayer));
    
    }

    void Game::initShoot()
    {
        this->shoot.setSize(sf::Vector2f(3.f , 3.f));
        this->shoot.setFillColor(sf::Color::Yellow);
        this->shoot.setOutlineColor(sf::Color::Yellow);
        this->shoot.setOutlineThickness(0.f); 

    }

    /*-------------------------------*/
    /*  Public Functions */
    /*-------------------------------*/

    /*-------------------------------*/
    /*  constructor / destructor   */
    /*-------------------------------*/
    Game::Game()
    {
        // configure the setup of the game
        this->setup();
    }


    Game::~Game()
    {
        delete this->fenetre; 
    }


    /*-------------------------------*/
    /* Accessors */
    /*-------------------------------*/

    const bool Game::getIfWindowIsOpen() const
    {
        return this->fenetre->isOpen();
    }

    bool Game::getGameOver() const
    {
        return this->gameOver;
    }


    void Game::setup()
    {
        this->initializeVariables();
        this->initWindow();
        this->initEnemy();
    }

    void Game::input()
    {
        while (this->fenetre->pollEvent(this->evnt))  // we dont have to use this (just to see that its a part of the classs )
        {
            switch (this->evnt.type) 
            {
                case sf::Event::Closed:
                    this->fenetre->close();
                    break;
                
                case sf::Event::KeyPressed:
                    if(evnt.key.code == sf::Keyboard::Escape)
                    {
                        this->fenetre->close();
                        break;
                    }
                    if(this->evnt.key.code == sf::Keyboard::Left)
                    {
                        this->button.left = true;
                        break;
                    }
                    if(this->evnt.key.code == sf::Keyboard::Right)
                    {
                        this->button.right = true;
                        break;
                    }
                    if(this->evnt.key.code == sf::Keyboard::Space)
                    {
                        this->button.space = true;
                        break;
                    }
              

                case sf::Event::KeyReleased :
                    if(this->evnt.key.code == sf::Keyboard::Left)
                    {
                        this->button.left = false;
                        break;
                    }
                    if(this->evnt.key.code == sf::Keyboard::Right)
                    {
                        this->button.right = false;
                        break;
                    }
                    if(this->evnt.key.code == sf::Keyboard::Space)
                    {
                        this->button.space = false;
                        break;
                    }
            }
        }

    }
    void Game::update()
    {
        /*
            IMPORTANT : 
            for me the difenition of update() is the switch(event.type) => we are taking actions according to inputs
        */
        
        // get mouse position (relative to the screen)
        //std::cout << "Mouse pos: " << sf::Mouse::getPosition().x  << " , " << sf::Mouse::getPosition().y << std::endl;

        // get mouse position (relative to the window)
        //std::cout << "Mouse pos: " << sf::Mouse::getPosition(*this->fenetre).x  << " , " << sf::Mouse::getPosition(*this->fenetre).y << std::endl;

        if( this->gameOver == false)
        {
            this->updateMousePosition(); 
            this->updateEnemies();
            this->updatePlayer();
            this->updateText();
            this->updateEnergy();
            this->updateShoots();
            
        }
        
        if(this->health <= 0)
            this->gameOver = true;

    }

    void Game::render()
    { 
         /* 
            Always :
            1 - clear old frame
            2 - draw 
            3 - then display new frame
         */
        
        // clear the window (with last config)
        this->fenetre->clear();  //(sf::Color(255 , 250 , 150 , 255)); 

        // draw the window (with the new config)
        //this->fenetre->draw(this->enemie);  // we draw an enemy
        
        this->renderEnemies();
        this->renderPlayer();
        this->renderShoots();
        this->renderText(*this->fenetre); // render text on window target

        // display the new window
        this->fenetre->display();
    }


    /* Other functions */
    // update sub function

    void Game::updateMousePosition()
    {
        this->mousePosWindow = sf::Mouse::getPosition(*this->fenetre);
        this->mousePosView = this->fenetre->mapPixelToCoords(this->mousePosWindow);  // its a coordinate from pixel in float
    }


    void Game::spawnEnemies() 
    {
        /*
            spawn enemies and set there random positions and colors
            -set the random position
            -set the random color
            -add enemy to the vector
        */

       this->enemie.setPosition(
        static_cast<float> (rand() % static_cast<int>(this->fenetre->getSize().x - this->enemie.getSize().x) ) ,
        0.f 
       );

       this->enemie.setFillColor(sf::Color(
        static_cast<int>(rand() % 255 ), 
        static_cast<int>(rand() % 255 ),
        static_cast<int>(rand() % 255 ), 255 ) 
        );
        
        // random scale if wanted
        float sizeEnemy , minSize = 0.2;
        sizeEnemy = (static_cast<float>(rand() % 80) / 100) + minSize;
        this->enemie.setScale(sf::Vector2f( sizeEnemy , sizeEnemy));
        
        // spawn the enemy
        this->enemies.push_back(enemie);

    }

    void Game::updateEnemies()
    {
        /* 
            updating the timer for enemies spawning
            when the enemies number is < maxEnemies 
            spawn enemies when the timer is = timerMax and reset the timer
            move enmeies down 
            remove enemies when clicked and when they pass the screen

        */
        
        if(this->enemies.size() < this->maxEnemies )
        {
            if( this->enemySpwanTimer >= this->enemySpawnTimerMax)
            {
                // spawn then enemies and reset the timer
                this->enemySpwanTimer = 0;
                this->spawnEnemies(); // create new enemies
            }
            else
                this->enemySpwanTimer += 5.f;
        }
        
        // il manque le else 

        // move the enemies to down (with for each loop)
        /* for( auto &e : this->enemies)
        {
            e.move(0.f , 2.f);
        }
        */
       if( sf::Mouse::isButtonPressed(sf::Mouse::Left)  )
       {
            
            if( this->mouseClicked == false )
            {
                bool deleted_flag = false;
                this->mouseClicked = true ;  // mouse is clicked
                
                for(int i = 0 ; i < this->enemies.size() && deleted_flag==false ; i++ )
                {
                        // check if clicked on the enemy then rsemove it       
                        if( this->enemies[i].getGlobalBounds().contains(this->mousePosView) ) 
                        {
                            deleted_flag = true;

                            calculateScore(i);

                                // delete the enemy
                            this->enemies.erase( this->enemies.begin() + i );
                        }      
                                    
                }
            }
        }
        else 
        {
            this->mouseClicked = false;
        }
       

       for( int i = 0 ; i < this->enemies.size() ; i++)
       {
            bool deleted_flag = false;
            this->enemies[i].move(0.f , 2.f);

                // remove enemies who passed the down border
            if( this->enemies[i].getPosition().y > this->fenetre->getSize().y)
            {
                this->enemies.erase( this->enemies.begin() + i );
                health -= 1;
            }
       }

    }

    void Game::updatePlayer()
    {
        /*
            Waiting for key pressed (left and right and space for shoot)
            define boundaries for player positions        
        */
        float pas = 15.f;

        // mouve left

        if(this->button.left)
        {
            if( (this->player.getPosition().x - pas) <= 0 )
                this->player.setPosition(0 , this->player.getPosition().y);
            else
                this->player.move(-pas , 0.f);
            
            
        }
        // move right
        if(this->button.right)
        {
             // remark :  this->player.getSize().x = this->player.getTexture()->getSize().x * player.getScale().x
            if(this->player.getPosition().x + pas >= (this->videoMode.width - (this->player.getTexture()->getSize().x * player.getScale().x) )) 
                this->player.setPosition( (this->videoMode.width - (this->player.getTexture()->getSize().x * player.getScale().x)) , this->player.getPosition().y);
            else 
                this->player.move( pas , 0.f);             
        }

    }

    void Game::generateShoots()
    {

        if(this->button.space )
        {
            this->shoot.setPosition(this->player.getPosition().x + (this->size_player.x/2) , this->player.getPosition().y + 5);
            shoots.push_back(shoot);        
        }
    }

    void Game::updateShoots()
    {
        /*
            generate shoots
            move shoots to up
            dell shoot if its is out of the screen 
            to do : if a shoot colide with an enemy => dell the enemy
                ycondition, xcondition
            
            xPlayerColisionCondition
            yPlayerColisionCondition
            check if an enmy touched the player then health -= 1
        
        */

        // genrate shoots
        generateShoots();

        float pas = 15.f;
        bool yCondition = false , xCondition = false , 
            yplayerColisionCondition = false , xplayerColisionCondition =false;
        
        for(int i = 0 ; i < this->shoots.size() ; i++)
        {
            // dell shoot if its out of screan
            if( this->shoots[i].getPosition().y + pas <= 0)
            {
                this->shoots.erase(shoots.begin() + i);
            }
            // move shoots
            else
                this->shoots[i].move(0.f , -pas); 

            // colision management
            // for each shoot check if it touchs any enemy

            for(int j = 0 ; j <this->enemies.size() ; j++)
            {
               // std::cout << "enmy size before : " <<this->enemies.size() << std::endl;
                
                yCondition = ( this->shoots[i].getPosition().y <=  this->enemies[j].getPosition().y + this->enemies[j].getSize().y  && 
                                this->shoots[i].getPosition().y >=  this->enemies[j].getPosition().y );
                xCondition = ( this->shoots[i].getPosition().x >= this->enemies[j].getPosition().x  &&  
                                this->shoots[i].getPosition().x <=  this->enemies[j].getPosition().x +  this->enemies[j].getSize().x );
                
                yplayerColisionCondition = ( this->player.getPosition().y <=  this->enemies[j].getPosition().y + this->enemies[j].getSize().y  );
                xplayerColisionCondition = ( this->player.getPosition().x + (this->player.getTexture()->getSize().x * player.getScale().x) >=  this->enemies[j].getPosition().x  && 
                                this->player.getPosition().x <  this->enemies[j].getPosition().x +  this->enemies[j].getSize().x );

                if(  xCondition && yCondition )
                {
                    this->enemies.erase( this->enemies.begin() + j) ;
                    this->shoots.erase( this->shoots.begin() + i);

                    // update score value
                    calculateScore(j);
                        
                }
                // check if any enemy touched the player
                if( yplayerColisionCondition && xplayerColisionCondition)
                {
                    this->enemies.erase( this->enemies.begin() + j) ;
                    health += -1;
                }
            }


        }

        
        
        
    }

    void Game:: updateText()
    {   
         // way1
        std::stringstream ss;
        ss << "Score : " << this->score 
            << "\nHealth : " << this->health   
            << "\nEnergy : " << this->energy ;// then use : ss.str()

         // way2
        std::string s;
        s = "Score : " + std::to_string(this->score) 
            + "\nHealth : " + std::to_string(this->health)  // then use s
            + "\nEnergy : " + std::to_string(this->energy);

         // update guiTsext
        this->guiText.setString(s);
    }

    void Game::updateEnergy()
    {
        this->energy = static_cast<int>(score / 20) ; 
        if(this->energy == 10)
        {
            this->energy = 0;
            this->health += 1;
        }
    }

    // runder sub functions
    void Game::renderEnemies()
    {
        // rendering all the enemies
        for( auto &e : this->enemies)
        {
            this->fenetre->draw(e);
        }
        this->fenetre->draw(sprite);
    }

    void Game::renderPlayer()
    {
        this->fenetre->draw(this->player);
    }

    void Game::renderText(sf::RenderTarget &target)
    {   
        target.draw(guiText);  // draw the text on the selected target (ex: window or other targets)
    }

    void Game::renderShoots()
    {
        for (auto &s : this->shoots)
        {
            this->fenetre->draw(s);
        }
    }


    void Game::calculateScore(int i)
    {
        /*
            update score value,
            i : is the index of the deleted enemy (shooted enemy)
        */
            // caculate score
        unsigned additionalScore = 0;
        float enemyScale = this->enemies[i].getScale().x;
        
        if( enemyScale <= 0.3)
            additionalScore = 5;
        else if (enemyScale > 0.3 && enemyScale <= 0.5)
            additionalScore = 3;
        else
            additionalScore = 1;
        
        this->score += additionalScore;
    }