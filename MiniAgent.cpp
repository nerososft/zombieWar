#include "MiniAgent.h"


MiniAgent::MiniAgent()
{
}


MiniAgent::~MiniAgent()
{
}

void MiniAgent::init(NeroEngine::Color color, glm::vec2 position)
{
	_position = position;
	_color = color;
	
}


void MiniAgent::update(const std::vector<std::string>& levelData, std::vector<Human *>& humans, std::vector<Zombie *>& zombies, float deltaTime)
{

}
