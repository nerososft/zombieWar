#include "MiniMap.h"
#include <NeroEngine\ResourceManager.h>


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
	color.r = 50;
	color.g = 50;
	color.b = 50;
	color.a = 180;

	spriteBatch.draw(destRect, uvRect, textureId, 0.0f, color);
}

void MiniMap::update(std::function<void(MiniMap minimap,glm::vec2 pos)> updateFunc){
	
}