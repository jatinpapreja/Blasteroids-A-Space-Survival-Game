#include "Health.h"
#include "iostream"

void Health::initVariables()
{
	this->pointCount = 4; //min = 3 max = 10
	this->type		= 0;
	this->speed		= static_cast<float>(this->pointCount/3);
	this->hpMax		= static_cast<int>(this->pointCount);
	this->hp		= this->hpMax;
	this->damage	= -1*(this->pointCount);
	this->points	= 0;
}
/*
void Health::initShape()
{
	this->shape.setRadius(this->pointCount * 6);
	this->shape.setPointCount(this->pointCount);
	this->shape.setFillColor(sf::Color(255, 255, 255, 200));
}
*/

void Health::initTexture()
{
    if (!this->texture.loadFromFile("Textures/healthkit.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
	}
}

void Health::initSprite()
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);
	//Resize the sprite
	this->sprite.scale(float(this->pointCount*0.02), float(this->pointCount*0.02));
}

Health::Health(float pos_x, float pos_y)
{
	this->initVariables();
	//this->initShape();
	this->initTexture();
	this->initSprite();
	this->sprite.setPosition(pos_x, pos_y);
	//this->shape.setPosition(pos_x, pos_y);
}

Health::~Health()
{

}

//Accessors
/*
const sf::FloatRect Health::getBounds() const
{
	return this->shape.getGlobalBounds();
}
*/
const sf::FloatRect Health::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

const int & Health::getPoints() const
{
	return this->points;
}

const int & Health::getDamage() const
{
	return this->damage;
}

//Functions
/*void Health::update()
{
	this->shape.move(0.f, this->speed);
}
*/

void Health::update()
{
	this->sprite.move(0.f, this->speed);
}

void Health::setPosition(const float x, const float y)
{
    this->sprite.setPosition(x, y);
}
/*
void Health::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
}
*/
void Health::render(sf::RenderTarget * target)
{
    target->draw(this->sprite);
}
