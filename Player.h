#pragma once
#include "Human.h"
#include <NeroEngine\InputManager.h>
#include <NeroEngine\Camera2D.h>
#include <NeroEngine\AudioEngine.h>
#include "Bullet.h"
#include <map>
class Gun;
class Player:public Human
{
public:
	Player();
	virtual ~Player();
	void init(float speed, 
		glm::vec2 pos,
		NeroEngine::InputManager* inputManager, 
		NeroEngine::Camera2D* camera, 
		std::vector<Bullet>* bullets,
		std::map<std::string, NeroEngine::SoundEffect> playerAudioEffectMap);

	void addGun(Gun* gun);
	void changeGunByWheel(int change);

	void playSound(std::string soundName);


	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies, 
		float deltaTime) override;
private:
	NeroEngine::InputManager* _inputManager;

	std::vector<Gun*> _guns;
	int _currentGunIndex;

	NeroEngine::Camera2D* _camera;

	std::map<std::string, NeroEngine::SoundEffect> _playerAudioEffectMap;
	

	std::vector<Bullet>* _bullets;
	float _scan;
};

