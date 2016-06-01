#pragma once 
#include <glm\glm.hpp>
#include <NeroEngine\Vertex.h>
#include <NeroEngine\GLTexture.h>
#include <NeroEngine\SpriteBatch.h>
#include <functional>
class MiniAgent;
class Zombie;
class Human;
const float MINI_MAP_WIDTH = 100.0;
const float MINI_MAP_HEIGHT = 40.0f;
class MiniMap
{
public:
	void init(glm::vec2 pos,NeroEngine::Color color,NeroEngine::GLTexture texture);

	void draw(NeroEngine::SpriteBatch& spriteBatch);

	void update(std::vector<Zombie*> zombies, std::vector<Human*> humans);

	void setPosition(glm::vec2 pos){ _position = pos; }

	glm::vec2 convertToMinimapMatrix(glm::vec2 Position,float screenWidth, float screenHeight);

	void addAgent();

	std::vector<MiniAgent*>& getMinimapAgent(){ return _agents; }

	glm::vec2 getPosition() { return _position; }

	MiniMap();

	~MiniMap();
private:


	glm::vec2 _position;

	NeroEngine::Color _color;

	NeroEngine::GLTexture _texture;

	std::vector<MiniAgent*> _agents;


};
