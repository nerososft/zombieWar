#include "GunSight.h"
#include <NeroEngine/ResourceManager.h>


GunSight::GunSight()
{
}


GunSight::~GunSight()
{
}


void GunSight::init(glm::vec2 pos, NeroEngine::Color color, NeroEngine::GLTexture texture,float width)
{
	_position = pos;
	_color = color;
	_texture = texture;
	_width = width;
}

void GunSight::draw(NeroEngine::SpriteBatch& spriteBatch)
{
	static GLuint textureId = _texture.id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);



	glm::vec4 destRect;
	destRect.x = _position.x;
	destRect.y = _position.y;
	destRect.z = _width;
	destRect.w = _width;
	
	spriteBatch.draw(destRect, uvRect, textureId, 0.0f, _color);
}

void GunSight::update(glm::vec2 pos,NeroEngine::Color color,NeroEngine::GLTexture texture,float width)
{
	_position = pos;
	_color  = color;
	_texture = texture;
	_width = width;
}
