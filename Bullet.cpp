#include "Bullet.h"
#include <NeroEngine\ResourceManager.h>
#include "Agent.h"
#include "Human.h"
#include "Zombie.h"
#include "Level.h"

Bullet::Bullet(glm::vec2 position, glm::vec2 direction, float damage, float speed)
:_position(position),
_direction(direction),
_damage(damage),
_speed(speed)
{

} 
bool Bullet::update(const std::vector<std::string>& levelData, float deltaTime){

	_position += _direction*_speed*deltaTime;
	return collideWithWorld(levelData);
}
bool Bullet::collideWithWorld(const std::vector<std::string>& levelData){
	glm::vec2 gridPosition;
	gridPosition.x = floor(_position.x / (float)TILE_WIDTH);
	gridPosition.y = floor(_position.y / (float)TILE_WIDTH);

	//超出地图边界
	if (gridPosition.x<0 || gridPosition.x>levelData[0].size() ||
		gridPosition.y<0 || gridPosition.y>levelData.size()){

		return true;
	}
	return (levelData[gridPosition.y][gridPosition.x] != '.');

}
void Bullet::draw(NeroEngine::SpriteBatch& spriteBatch){
	glm::vec4 destRect(_position.x + BULLET_RADIUS,
		_position.y + BULLET_RADIUS,
		BULLET_RADIUS + BULLET_RADIUS, 
		BULLET_RADIUS + BULLET_RADIUS);
	const glm::vec4 uvRect(0.0f,0.0f,1.0f,1.0f);
	NeroEngine::Color color;
	color.r = 254;
	color.g = 221;
	color.b = 79;
	color.a = 255;
	spriteBatch.draw(destRect,uvRect,NeroEngine::ResourceManager::getTexture("Textures/circle.png").id,0.0f,color);

	
}
bool Bullet::collideWithAgent(Agent* agent){

	const float MIN_DISTANCE = AGENT_RADIUS + BULLET_RADIUS;//半径之和

	glm::vec2 cornerPosA = _position;

	glm::vec2 cornerPosB = agent->getAgentPos() + glm::vec2(AGENT_RADIUS);
	glm::vec2 distRect = cornerPosA - cornerPosB;
	float distance = glm::length(distRect);
	float collisionDepth = MIN_DISTANCE - distance;

	if (collisionDepth>0){
		return true;
	}
	return false;
}

Bullet::~Bullet()
{
}
