#pragma once

#include<map>
#include<string>
#include<sstream>
#include"Player.h"
#include"Bullet.h"
#include"Enemy.h"
#include"Health.h"
#include "SFML/Audio.hpp"
class Game
{
private:
	//Window
	sf::RenderWindow* window;///To create a 2d Drawing Window
    sf::SoundBuffer buffer1;
    sf::Sound sound1;
    sf::SoundBuffer buffer2;
    sf::Sound sound2;
	//Resources
	std::map<std::string, sf::Texture*> textures;///Textures: To store pixels in graphic memory to load them faster.
	std::vector<Bullet*> bullets;

	//GUI
	sf::Font font;
	sf::Text pointText;
    sf::Text HealthBarText;
	sf::Text gameOverText;
	sf::Text PlayAgain;

	//World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	//Systems
	unsigned points;

	//Player
	Player* player;

	//PlayerGUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;
	sf::RectangleShape PlayAgainBack;
	sf::RectangleShape gameOverBack;
	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;
	float spawnTimer_H;
	float spawnTimerMax_H;
    std::vector<Health*> health;
	//Private functions
	void initWindow();
	void initTextures();
	void initGUI();
	void initWorld();
	void initSystems();

	void initPlayer();
	void initEnemies();
	void initHealth();

public:
	Game();
	virtual ~Game();

	//Functions
	bool run();

	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateBullets();
	void updateEnemies();
	void updateCombat_E();
	void updateCombat_H();
	void updateHealth();
	void update();

	void renderGUI();
	void renderWorld();
	bool render();
};

