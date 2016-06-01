#include "Agent.h"
#include <NeroEngine/ResourceManager.h>
#include "Level.h"
#include <algorithm>

Agent::Agent()
{
}
void Agent::draw(NeroEngine::SpriteBatch& spriteBatch){
	static GLuint textureId = NeroEngine::ResourceManager::getTexture("Textures/zombie.ntex").id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	


	glm::vec4 destRect;
	destRect.x = _position.x; 
	destRect.y = _position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;
	
	spriteBatch.draw(destRect,uvRect,textureId, 0.0f,_color,_direction);
}
bool Agent::collideWithLevel(const std::vector<std::string>& levelData){
	std::vector<glm::vec2> collideTilePosition;

	checkTilePosition(levelData, 
		collideTilePosition, 
		_position.x,
		_position.y);//bottmleft

	checkTilePosition(levelData,
		collideTilePosition,
		_position.x + TILE_WIDTH,
		_position.y);//bottomright

	checkTilePosition(levelData,
		collideTilePosition,
		_position.x,
		_position.y+TILE_WIDTH);//topleft

	checkTilePosition(levelData, 
		collideTilePosition,
		_position.x + TILE_WIDTH,
		_position.y + TILE_WIDTH);//topright
	if (collideTilePosition.size()==0){
		return false;
	}
	for (int i = 0; i < collideTilePosition.size();i++){
		
		collideWithTile(collideTilePosition[i]); 

	}

	return true;
}
bool Agent::collideWithAgent(Agent* agent){

	const float MIN_DISTANCE = AGENT_RADIUS + AGENT_RADIUS;//半径之和

	glm::vec2 cornerPosA = _position + glm::vec2(AGENT_RADIUS);

	glm::vec2 cornerPosB = agent->getAgentPos() + glm::vec2(AGENT_RADIUS);
	glm::vec2 distRect = cornerPosA - cornerPosB;
	float distance = glm::length(distRect);
	float collisionDepth = MIN_DISTANCE - distance;
	
	if (collisionDepth>0){
		glm::vec2 collisionDepthVec = glm::normalize(distRect)*collisionDepth;
		_position += collisionDepthVec / 2.0f;
		agent->_position -= collisionDepthVec / 2.0f;
		return true;
	}
	return false;
}
bool Agent::applyDamage(float damage){
	_health -= damage;
	if (_health<=0){
		return true;
	}
	return false;
}



void Agent::checkTilePosition(const std::vector<std::string>& levelData,
							  std::vector<glm::vec2>& collideTilePosition, 
							  float x, 
							  float y){
	
	glm::vec2 cornerPos = glm::vec2(floor(x / (float)TILE_WIDTH),
		floor(y / (float)TILE_WIDTH));

	//超出地图边界
	if (cornerPos.x<0||cornerPos.x>levelData[0].size()||
		cornerPos.y<0||cornerPos.y>levelData.size()){

		return;
	}

	if (levelData[cornerPos.y][cornerPos.x] != '.'){
		glm::vec2 pos = cornerPos *(float)TILE_WIDTH + glm::vec2((float)TILE_WIDTH / 2.0f);
		collideTilePosition.push_back(pos);
	}
	
}

void Agent::collideWithTile(glm::vec2 tilePos){
	const float TILE_RADIUS = (float)TILE_WIDTH / 2.0f;
	///<----------------此处留坑---------------->>
	float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;//半径之
	///<----------------此处留坑---------------->>
	glm::vec2 centerPlayerPos = _position + glm::vec2(AGENT_RADIUS);
	glm::vec2 distVec = centerPlayerPos - tilePos;

	float xDepth = MIN_DISTANCE - abs(distVec.x);
	float yDepth = MIN_DISTANCE - abs(distVec.y);




	if (xDepth>0 && yDepth>0){
		if (std::max(xDepth,0.0f)<std::max(yDepth,0.0f)){
			if (distVec.x < 0){
				_position.x -= xDepth;
			}
			else{
				_position.x += xDepth;
			}
		}
		else{
			if (distVec.y < 0){
				_position.y -= yDepth;
			}
			else{
				_position.y += yDepth;
			}
		}
	}
}
Agent::~Agent()
{

}
