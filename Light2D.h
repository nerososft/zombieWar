#pragma once 
#include <NeroEngine\NeroEngine.h>
#include <NeroEngine\Vertex.h>
#include <NeroEngine\SpriteBatch.h>
#include <glm/glm.hpp>
class Light2D{

public:

	void init();

	void draw(NeroEngine::SpriteBatch& spriteBatch){
		glm::vec4 destRect;
		destRect.x = _position.x - _size / 2.0f;
		destRect.y = _position.y - _size / 2.0f;
		destRect.z = _size;
		destRect.w = _size;

		spriteBatch.draw(destRect, glm::vec4(-1, -1, 2, 2), 0, 0, _color);

	}

	float _size;
	
	NeroEngine::Color _color;
	

	glm::vec2 _position;



};