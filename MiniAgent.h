#pragma once
#include "Agent.h"
class MiniAgent:public Agent
{
public:
	MiniAgent();
	~MiniAgent();

	void init(NeroEngine::Color color,glm::vec2 position);

	virtual void update(const std::vector<std::string>& levelData, std::vector<Human *>& humans, std::vector<Zombie *>& zombies, float deltaTime) override;

};

