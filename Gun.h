#pragma once
#include <string>
#include <glm\glm.hpp>
#include <vector>
#include <NeroEngine\AudioEngine.h>
#include "Bullet.h"
class Gun
{
public:
	Gun(std::string name, 
		int fireRate, 
		int bulletPerShot, 
		float spread, 
		float bulletDamage, 
		float bulletSpeed,
		NeroEngine::SoundEffect fireEffect);
	~Gun();
	std::string getName() const{ return _name; }
	float getRate() const{ return _bulletPerShot; }
	float getDamage() const{ return _buletDamage; }
	float getSpread() const{ return _spread; }

	void update(bool isMouseDown,
		const glm::vec2& position, 
		const glm::vec2& direction, 
		std::vector<Bullet>& bulltes,
		float deltaTime);
private:

	void fire(const glm::vec2& direction, const glm::vec2& position, std::vector<Bullet>& bulltes);
	
	std::string _name;

	NeroEngine::SoundEffect _fireEffect;

	int _fireRate;//

	int _bulletPerShot;

	float _spread;

	float _bulletSpeed;

	float _buletDamage;

	float _frameCounter;

};

