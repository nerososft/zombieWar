#include "MiniMap.h"
#include <NeroEngine\ResourceManager.h>
#include "Agent.h"
#include "Zombie.h"
#include "MiniAgent.h"


MiniMap::MiniMap()
{
}


MiniMap::~MiniMap()
{

}
void MiniMap::init(glm::vec2 pos, NeroEngine::Color color, NeroEngine::GLTexture texture)
{
	_position = pos;
	_color = color;
	_texture = texture;
// 	for (int i = 0; i < _agents.size();i++){
// 		_agents[i]->init();
// 	}
}

void MiniMap::draw(NeroEngine::SpriteBatch& spriteBatch){
	static GLuint textureId = NeroEngine::ResourceManager::getTexture("Textures/minimap.png").id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);



	glm::vec4 destRect;
	destRect.x = _position.x;
	destRect.y = _position.y;
	destRect.z = MINI_MAP_WIDTH;
	destRect.w = MINI_MAP_HEIGHT;
	NeroEngine::Color color;
	color.r = 20;
	color.g = 20;
	color.b = 20;
	color.a = 180;

	spriteBatch.draw(destRect, uvRect, textureId, 0.0f, color);
	for (int i = 0; i < _agents.size();i++){
		_agents[i]->draw(spriteBatch);
	}
}

glm::vec2  MiniMap::convertToMinimapMatrix(glm::vec2 Position, float screenWidth, float screenHeight)
{

	//_positoion = _playerPos + glm::vec2(_screenWidth/4.0f-MINI_MAP_WIDTH,_screenHeight/4.0f-MINI_MAP_HEIGHT)  minimap×óÏÂ½Ç×ø±ê

	float xDepth =  Position.x / screenWidth;
	float yDepth = Position.y / screenHeight;

	float xNew = xDepth*MINI_MAP_WIDTH;
	float yNew = yDepth*MINI_MAP_HEIGHT;


	return _position + glm::vec2(xNew, yNew);
}

void MiniMap::addAgent(){
	_agents.push_back(new MiniAgent);
}
void MiniMap::update(std::vector<Zombie*> zombies, std::vector<Human*> humans){
	
}