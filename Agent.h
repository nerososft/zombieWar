#pragma once
#include <glm\glm.hpp>
#include <NeroEngine\SpriteBatch.h>

const float AGENT_WIDTH = 16;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;
class Human;
class Zombie;
class Agent
{
public:
	Agent();
	virtual void update(const std::vector<std::string>& levelData,
						std::vector<Human*>& humans,
						std::vector<Zombie*>& zombies, 
						float deltaTime) = 0;

	bool collideWithLevel(const std::vector<std::string>& levelData);

	bool collideWithAgent(Agent* agent);

	void draw(NeroEngine::SpriteBatch& spriteBatch);

	bool applyDamage(float damage);
	virtual ~Agent();

	glm::vec2 getAgentPos()const { return _position; }

	
protected:
	void checkTilePosition(const std::vector<std::string>& levelData,
		std::vector<glm::vec2>& collideTilePosition,
		float x, 
		float y);

	void collideWithTile(glm::vec2 tilePos);
	glm::vec2 _position;
	float _speed;
	NeroEngine::Color _color;

	float _health;
};

