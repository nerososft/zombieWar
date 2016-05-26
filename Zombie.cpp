#include "Zombie.h"
#include <random>
#include <ctime>
#include "Human.h"

Zombie::Zombie()
{
}


Zombie::~Zombie()
{
}
Human* Zombie::getNerestHuman(std::vector<Human*>& humans){
	Human* cloestHuman = nullptr;
	float samllestDistace = 999999.0f;
	for (int i = 0; i < humans.size();i++){
		glm::vec2 distVec = humans[i]->getAgentPos() - _position;
		float distance = glm::length(distVec);
		if (distance<samllestDistace){
			samllestDistace = distance;
			cloestHuman = humans[i];
		}
	}
	return cloestHuman;
}
void Zombie::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies,
	float deltaTime ){
	Human* cloestHuman = getNerestHuman(humans);
	if (cloestHuman!=nullptr){
		glm::vec2 direction = glm::normalize(cloestHuman->getAgentPos() - _position);
		_position += direction*_speed*deltaTime;
	}

	collideWithLevel(levelData);
}
void Zombie::init(float speed, glm::vec2 pos){
	
	_color.r = 200;
	_color.g = 0;
	_color.b = 0;
	_color.a = 255;

	_health = 50;
	
	_damage = 20;
	_speed = speed;
	_position = pos;

	
}
void Zombie::beStronger(){
	_health += 30;
	_damage += 10;
	_speed += 0.001f;
	if (_color.r>30){
		_color.r -= 30;
	}
}