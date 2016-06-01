#include "Player.h"
#include <SDL/SDL.h>
#include <iostream>
#include  "Gun.h"
#include "Zombie.h"
#include <NeroEngine\Errors.h>


Player::Player():
_currentGunIndex(-1)
{
}
void Player::playSound(std::string soundName){

	auto it = _playerAudioEffectMap.find(soundName);
	if (it!=_playerAudioEffectMap.end()){
		it->second.play();
	}

}

void Player::changeGunByWheel(int change){

	//此处应有换枪声
	playSound("changeGun");
	if (change==1){
		if (_currentGunIndex<_guns.size()-1){
			_currentGunIndex++;
		}
		else{
			_currentGunIndex = 0;
		}
	}
	else{
		if (_currentGunIndex>0){
			_currentGunIndex--;
		}
		else{
			_currentGunIndex = _guns.size()-1;
		}
	}
	std::cout << "换枪：" << _guns[_currentGunIndex]->getName() << " 射速：" << _guns[_currentGunIndex]->getRate() << " 角度：" << _guns[_currentGunIndex]->getSpread() << " 杀伤力：" << _guns[_currentGunIndex]->getDamage() << std::endl;
}
void Player::addGun(Gun* gun){
	//给一把
	_guns.push_back(gun);

	if (_currentGunIndex==-1){
		_currentGunIndex = 0;
	}
}

Player::~Player()
{
}
void Player::init(float speed, 
	glm::vec2 pos, 
	NeroEngine::InputManager* inputManager, 
	NeroEngine::Camera2D* camera, 
	std::vector<Bullet>* bullets,
	std::map<std::string, NeroEngine::SoundEffect> playerAudioEffectMap){
	_speed = speed;
	_position = pos;
	_inputManager = inputManager;
	_playerAudioEffectMap = playerAudioEffectMap;
	_camera = camera;
	_bullets = bullets;
	_color.r = 0;
	_health = 150;
	_color.g = 100;
	_color.b = 200;
	_color.a = 255;
	_scan = 200.0f;

}
void Player::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies,
	float deltaTime){



	//判断周围是否有僵尸
	for (int i = 0; i < zombies.size(); i++){
		glm::vec2 zombiePosition = zombies[i]->getAgentPos();
		glm::vec2 distance = _position - zombiePosition;
		float playToZombie = glm::length(distance);
		if (playToZombie < _scan){//僵尸进入视野
			//播放僵尸音效
			playSound("zombie");
		}
	}


	//按键事件
	if (_inputManager->isKeyPressed(SDLK_w)){
		_position.y += _speed*deltaTime;
		
			//playSound("walk");///<<<<<<此方式冗余，需优化
		
	}else if (_inputManager->isKeyPressed(SDLK_s)){
		_position.y -= _speed*deltaTime;
		//playSound("walk");///<
	}
	if (_inputManager->isKeyPressed(SDLK_a)){
		//playSound("walk");///<
		_position.x -= _speed*deltaTime;
	}else if (_inputManager->isKeyPressed(SDLK_d)){
		//playSound("walk");///<
		_position.x += _speed*deltaTime;
	}
	else if (_inputManager->isKeyPressed(SDLK_ESCAPE)){
		exit(0);

	}

	if(_inputManager->isKeyPressed(SDLK_1) && _guns.size()>=0){
		playSound("changeGun");///<
		_currentGunIndex = 0;
	}
	if (_inputManager->isKeyPressed(SDLK_2) && _guns.size()>= 1){
		playSound("changeGun");///<
		_currentGunIndex = 1;
	}
	if (_inputManager->isKeyPressed(SDLK_3) && _guns.size() >= 2){
		playSound("changeGun");///<
		_currentGunIndex = 2;
	}
	if (_inputManager->isKeyPressed(SDLK_4) && _guns.size() >= 3){
		playSound("changeGun");///<
		_currentGunIndex = 3;
	}
	glm::vec2 mouseCoords = _inputManager->getMouseCoords();
	mouseCoords = _camera->convertScreenToWorld(mouseCoords);

	glm::vec2 centerPosition = _position + glm::vec2(AGENT_RADIUS);
	_direction = glm::normalize(mouseCoords - centerPosition);

	if (_currentGunIndex!=-1){
		
		//std::cout << _direction.x << "_" << _direction.y << ::std::endl;
		
		_guns[_currentGunIndex]->update(_inputManager->isKeyPressed(SDL_BUTTON_LEFT),
			centerPosition+(_direction.x*5.0f,_direction.y*5.0f),_direction,*_bullets,deltaTime);
	}

	collideWithLevel(levelData);
}
