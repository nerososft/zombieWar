#pragma once
#include <glm/glm.hpp>
#include <NeroEngine/Vertex.h>
#include <NeroEngine/GLTexture.h>
#include <NeroEngine/SpriteBatch.h>
class GunSight
{
public:
	GunSight();
	~GunSight();
	void init(glm::vec2 pos, NeroEngine::Color color, NeroEngine::GLTexture texture,float width);

	void draw(NeroEngine::SpriteBatch& spriteBatch);

	void update(glm::vec2 pos, NeroEngine::Color color, NeroEngine::GLTexture texture, float width);

private:
	glm::vec2 _position;
	NeroEngine::Color _color;
	NeroEngine::GLTexture _texture;
	float _width = 20.0f;
};

