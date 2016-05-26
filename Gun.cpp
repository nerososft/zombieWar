#include "Gun.h"
#include <random>
#include <ctime>
#include <glm\gtx\rotate_vector.hpp>


Gun::Gun(std::string name,
	int fireRate,
	int bulletPerShot,
	float spread,
	float bulletDamage,
	float bulletSpeed,
	NeroEngine::SoundEffect fireEffect)
	:_name(name),
	_fireRate(fireRate),
	_bulletPerShot(bulletPerShot),
	_spread(spread),
	_buletDamage(bulletDamage),
	_bulletSpeed(bulletSpeed),
	_frameCounter(0),
	_fireEffect(fireEffect)
{

}
void Gun::update(bool isMouseDown,
			const glm::vec2& position,
			const glm::vec2& direction,
			std::vector<Bullet>& bulltes,
			float deltaTime){
	_frameCounter += 1.0f*deltaTime;
	if (_frameCounter>=_fireRate&&isMouseDown){
		

		_fireEffect.play();

		fire(direction,position,bulltes);//…‰À¿TA
		_frameCounter = 0;

	}
}
void Gun::fire(const glm::vec2& direction, const glm::vec2& position, std::vector<Bullet>& bulltes){
	static std::mt19937 randomEngine(time(nullptr));
	std::uniform_real_distribution<float> randRotate(-_spread, _spread);

	for (int i = 0; i < _bulletPerShot;i++){
		bulltes.emplace_back(position,
			glm::rotate(direction,randRotate(randomEngine)),
			_buletDamage,
			_bulletSpeed);
	}
}


Gun::~Gun()
{

}
