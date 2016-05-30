#pragma once 
#include <glm\glm.hpp>
#include <NeroEngine\Vertex.h>
#include <NeroEngine\GLTexture.h>
#include <NeroEngine\SpriteBatch.h>
#include <functional>
const float MINI_MAP_WIDTH = 100.0;
const float MINI_MAP_HEIGHT = 40.0f;
class MiniMap
{
public:
	void init(glm::vec2 pos,NeroEngine::Color color,NeroEngine::GLTexture texture);

	void draw(NeroEngine::SpriteBatch& spriteBatch);

	void update(std::function<void(MiniMap minimap,glm::vec2 pos)> updateFunc);

	void setPosition(glm::vec2 pos){ _position = pos; }
	MiniMap();

	~MiniMap();


	glm::vec2 _position;

	NeroEngine::Color _color;

	NeroEngine::GLTexture _texture;

	


	

};
