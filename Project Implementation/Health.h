#ifndef HEAlTH_H
#define HEALTH_H

#include<SFML/Graphics.hpp>

class Health
{
private:
	unsigned pointCount;
	//sf::CircleShape shape;
	sf::Sprite sprite;
	sf::Texture texture;
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;

	void initVariables();
	//void initShape();
	void initTexture();
	void initSprite();

public:
	Health(float pos_x, float pos_y);
	virtual ~Health();

	//Accessors
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;

	void setPosition(const float x, const float y);
	//Functions
	void update();
	void render(sf::RenderTarget* target);
};

#endif //!HEALTH_H
