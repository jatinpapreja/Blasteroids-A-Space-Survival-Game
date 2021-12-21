#include "Game.h"
#include "cmath"
#include "iostream"
#include "SFML/Audio.hpp"

//Private functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "SPACE SHOOTER", sf::Style::Fullscreen | sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
}

void Game::initGUI()
{
	//Load font
	if (!this->font.loadFromFile("Fonts/FiveD.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << "\n";

    if (!this->buffer1.loadFromFile("audio/laser.ogg"))
    {
        std::cout<<"ERROR loading the sound"<<std::endl;
    }
    this->sound1.setBuffer(this->buffer1);
    this->sound1.setVolume(30);

    if (!this->buffer2.loadFromFile("audio/blast1.ogg"))
    {
        std::cout<<"ERROR loading the sound"<<std::endl;
    }
    this->sound2.setBuffer(this->buffer2);
    this->sound2.setVolume(30);
	//Init point text
	this->pointText.setPosition(this->window->getSize().x - 300.f, 25.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(40);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("test");

    this->HealthBarText.setPosition(30.f, 75.f);
	this->HealthBarText.setFont(this->font);
	this->HealthBarText.setCharacterSize(40);
	this->HealthBarText.setFillColor(sf::Color::White);
	this->HealthBarText.setString("test");

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(150);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

    this->PlayAgain.setFont(this->font);
	this->PlayAgain.setCharacterSize(50);
	this->PlayAgain.setFillColor(sf::Color::White);
	this->PlayAgain.setString("Do You Want To Play Again? Press Y for Yes!");
	this->PlayAgain.setPosition(
		this->window->getSize().x / 2.f - this->PlayAgain.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->PlayAgain.getGlobalBounds().height / 2.f + 200.f);


	//Init player GUI
	this->playerHpBar.setSize(sf::Vector2f(400.f, 30.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(30.f, 30.f));

	this->playerHpBarBack.setSize(sf::Vector2f(300.f, 30.f));
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
	this->playerHpBarBack.setPosition(sf::Vector2f(30.f, 30.f));

	this->gameOverBack.setSize(sf::Vector2f(1000.f, 200.f));
	this->gameOverBack.setFillColor(sf::Color(255, 255, 255, 175));
	this->gameOverBack.setPosition(this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f - 50.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

	this->PlayAgainBack.setSize(sf::Vector2f(1350.f, 60.f));
	this->PlayAgainBack.setFillColor(sf::Color(25, 25, 25, 200));
	this->PlayAgainBack.setPosition(sf::Vector2f(this->window->getSize().x / 2.f - this->PlayAgain.getGlobalBounds().width / 2.f - 20,
		this->window->getSize().y / 2.f - this->PlayAgain.getGlobalBounds().height / 2.f + 200.f));

}

void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Textures/background1.jpg"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}

	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initSystems()
{
	this->points = 0;
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initEnemies()
{
	this->spawnTimerMax = 10.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::initHealth()
{
    this->spawnTimerMax_H = 250.f;
    this->spawnTimer_H = this->spawnTimerMax_H;
}

//Con/Des
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initWorld();
	this->initSystems();

	this->initPlayer();
	this->initEnemies();
	this->initHealth();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	//Delete textures
	for (auto &i : this->textures)
	{
		delete i.second;
	}

	//Delete bullets
	for (auto *i : this->bullets)
	{
		delete i;
	}

	//Delete enemies
	for (auto *i : this->enemies)
	{
		delete i;
	}
	//Delete health
	for (auto *i : this->health)
	{
		delete i;
	}
}

//Functions
bool Game::run()
{
    bool val = false;
	while(this->window->isOpen() && !val)
	{
		this->updatePollEvents();

		if(this->player->getHp() > 0)
			this->update();

		val = this->render();
	}
	return val;
}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}
}

void Game::updateInput()
{
	//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		this->bullets.push_back(
			new Bullet(
			this->textures["BULLET"],
			this->player->getPos().x + this->player->getBounds().width/2.f,
			this->player->getPos().y,
			0.f,
			-1.f,
			2.5f
			)
		);
		this->sound1.play();
		//this->music.setLoop(true);
	}
}

void Game::updateGUI()
{
	std::stringstream ss;
	std::stringstream ss1;
	ss << "Points: " << this->points; /// string s = "Points: " + str(this->points);

	this->pointText.setString(ss.str());

	//Update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	ss1 << "Health: "<< ceil(hpPercent*100);
	this->HealthBarText.setString(ss1.str());
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));
}

void Game::updateWorld()
{

}

void Game::updateCollision()
{
	//Left world collision
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	//Right world collison
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}

	//Top world collision
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}
	//Bottom world collision
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto *bullet : this->bullets)
	{
		bullet->update();

		//Bullet culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
		}

		++counter;
	}
}

void Game::updateEnemies()
{
	//Spawning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(float(rand() % (this->window->getSize().x - 20)) + 10.f, -100.f));
		this->spawnTimer = 0.f;
	}

	//Update
	unsigned counter = 0;
	for (auto *enemy : this->enemies)
	{
		enemy->update();

		//Bullet culling (top of screen)
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//Delete enemy
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		//Enemy player collision
		else if(enemy->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHp(this->enemies.at(counter)->getDamage());
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			this->sound2.play();
		}

		++counter;
	}
}

void Game::updateHealth()
{
	//Spawning
	this->spawnTimer_H += 0.5f;
	if (this->spawnTimer_H >= this->spawnTimerMax_H)
	{
		this->health.push_back(new Health(float(rand() % (this->window->getSize().x - 40)) + 10.f, -100.f));
		this->spawnTimer_H = 0.f;
	}

	//Update
	unsigned counter = 0;
	for (auto *heal : this->health)
	{
		heal->update();

		//Bullet culling (top of screen)
		if (heal->getBounds().top > this->window->getSize().y)
		{
			//Delete enemy
			delete this->health.at(counter);
			this->health.erase(this->health.begin() + counter);
		}
		//Health player collision
		else if(heal->getBounds().intersects(this->player->getBounds()))
		{
		    if(((this->player->getHp()) - (this->health.at(counter)->getDamage())) > 100)
            {
                this->player->setHp(100);
            }
            else
            {
                this->player->loseHp(this->health.at(counter)->getDamage());
            }
			delete this->health.at(counter);
			this->health.erase(this->health.begin() + counter);
		}
		++counter;
	}
}

void Game::updateCombat_E()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->points += this->enemies[i]->getPoints();

				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				enemy_deleted = true;
				this->sound2.play();
			}
		}
	}
}



void Game::updateCombat_H()
{
    for (int i = 0; i < this->health.size(); ++i)
	{
		bool heal_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && heal_deleted == false; k++)
		{
			if (this->health[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->points += this->health[i]->getPoints();

				delete this->health[i];
				this->health.erase(this->health.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				heal_deleted = true;
			}
		}
	}
}

void Game::update()
{
	this->updateInput();

	this->player->update();

	this->updateCollision();

	this->updateBullets();

	this->updateEnemies();

	this->updateHealth();

	this->updateCombat_E();

	this->updateCombat_H();

	this->updateGUI();

	this->updateWorld();
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->HealthBarText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

bool Game::render()
{
    bool flag = false;
	this->window->clear();

	//Draw world
	this->renderWorld();

	//Draw all the stuffs
	this->player->render(*this->window);

	for (auto *bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto *enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	for (auto *heal : this->health)
    {
        heal->render(this->window);
    }

	this->renderGUI();

	//Game over screen
	if (this->player->getHp() <= 0)
		{
		    this->window->draw(this->gameOverBack);
		    this->window->draw(this->gameOverText);
		    this->window->draw(this->PlayAgainBack);
		    this->window->draw(this->PlayAgain);
		    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
                flag = true;
		}
	this->window->display();
	return flag;
}
