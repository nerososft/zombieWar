#pragma once
#include <glm\glm.hpp>
#include <NeroEngine\SpriteBatch.h>
#include <vector>
class Agent;
class Human;
class Zombie;
const int BULLET_RADIUS = 2;
class Bullet
{
public:
	Bullet(glm::vec2 _position, glm::vec2 _direction, float _damage, float _speed);
	~Bullet();

	bool update(const std::vector<std::string>& levelData, float deltaTime);
	float getDamge()const { return _damage; }
	void draw(NeroEngine::SpriteBatch& spriteBatch);

	bool collideWithAgent(Agent* agent);

	glm::vec2 getPosition(){ return _position; }
private:
	bool collideWithWorld(const std::vector<std::string>& levelData);
	float _damage;
	glm::vec2 _position;
	glm::vec2 _direction;
	float _speed;
};

