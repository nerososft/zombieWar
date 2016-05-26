#pragma once
#include "Agent.h"
class Zombie:public Agent
{
public:
	Zombie();
	~Zombie();
	void init(float speed, glm::vec2 pos);
	void beStronger();
	float getDamage() const { return _damage; }

	virtual void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies,
		float deltaTime) override;
private:
	Human* getNerestHuman(std::vector<Human*>& humans);
	float _damage;
};

