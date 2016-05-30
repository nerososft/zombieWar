#pragma once
#include "MainGame.h"
#include <SDL\SDL.h>
#include <NeroEngine\NeroEngine.h>
#include "Zombie.h"
#include <iostream>
#include <random>
#include <ctime>
#include <NeroEngine\Errors.h>
#include "Gun.h"
#include <NeroEngine\SpriteFont.h>
#include <NeroEngine\ParticleBatch2D.h>
#include <NeroEngine\ResourceManager.h>
#include <glm\gtx\rotate_vector.hpp>
#include <algorithm>
#include <GL\glut.h>
#include "light2D.h"

MainGame::MainGame() :
_screenWidth(640), 
_screenHeight(480), 
_gameState(GameState::PLAY), 
_fps(0.0f), 
_player(nullptr),
_numHumKilled(0),
_numZombieKilled(0)
{
}


MainGame::~MainGame()
{
	for (int i = 0; i < _levels.size();i++){
		delete _levels[i];
	}

}

void MainGame::initSystems(){
	//��ʼ������
	NeroEngine::init();

	_audioEngine.init();

	//��������
	_window.create("ZombieWar1.0", _screenWidth, _screenHeight, 0);

	//��ʼ��shader
	initShaders();

	_agentSpriteBatch.init();
	//camera��ʼ��
	_camera.init(_screenWidth,_screenHeight);
	
	_bloodParticlesBatch = new NeroEngine::ParticleBatch2D;
	_bloodParticlesBatch->init(1000, 0.05f,
		NeroEngine::ResourceManager::getTexture("Textures/blood.png"),
		[](NeroEngine::Particle2D& particle, float deltaTime)->void{
		particle._position += particle._velocity*deltaTime;
		particle._color.r = (GLubyte)(particle._life * 255);
		particle._width = (float)(particle._life * 20);
	});

	_particleEngine.addParticleBatch(_bloodParticlesBatch);

}


void MainGame::initShaders(){
	_textureProgram.complieShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	_textureProgram.addAttribute("vertexPosition");
	_textureProgram.addAttribute("vertexColor");
	_textureProgram.addAttribute("vertexUV");
	_textureProgram.linkShaders();

	_lightProgram.complieShaders("Shaders/lightShading.vert", "Shaders/lightShading.frag");
	_lightProgram.addAttribute("vertexPosition");
	_lightProgram.addAttribute("vertexColor");
	_lightProgram.addAttribute("vertexUV");
	_lightProgram.linkShaders();
}
void MainGame::initLevel(){
	//��һ�ص�ͼ
	_levels.push_back(new Level("Levels/level1.txt"));

	_currentLevel = 0;
	std::map<std::string, NeroEngine::SoundEffect> playerSoundMap;
	playerSoundMap["zombie"] = _audioEngine.loadSoundEffect("Sound/zombie.mp3");
	playerSoundMap["changeGun"] = _audioEngine.loadSoundEffect("Sound/oog/changeGun.ogg");
	//playerSoundMap["walk"] = _audioEngine.loadSoundEffect("Sound/oog/walk.ogg");
	_player = new Player();

	_player->init(PLAYER_SPEED, 
		_levels[_currentLevel]->getPlayerPos(),
		&_inputManager,&_camera,&_bullets,
		playerSoundMap
		);
 
	_humans.push_back(_player);

	std::mt19937 randomEngine;
	randomEngine.seed(time(nullptr));
	std::cout <<"��ͼ���ȣ�"<<(_levels[_currentLevel]->getWidth() - 1)*TILE_WIDTH << std::endl;
	std::cout <<"��ͼ��ȣ�"<< (_levels[_currentLevel]->getHeight() - 1)*TILE_WIDTH << std::endl;

	//ע�⻻�з��Ϳ���
	std::uniform_int_distribution<int> randX(2,_levels[_currentLevel]->getWidth()-2);
	std::uniform_int_distribution<int> randY(2, _levels[_currentLevel]->getHeight() - 2);

	
	std::cout <<"���ࣺ"<< _levels[_currentLevel]->getNumHuman()<<std::endl;
	//�������
	for (int i = 0; i < _levels[_currentLevel]->getNumHuman(); i++){
		_humans.push_back(new Human);
		glm::vec2 pos(randX(randomEngine)*TILE_WIDTH, randY(randomEngine)*TILE_WIDTH);
		_humans.back()->init(HUMAN_SPEED,pos);
	}
	const std::vector<glm::ivec2>& zombiePositions = _levels[_currentLevel]->getZombiesPositions();
	//��ӽ�ʬ
	for (int i = 0; i <zombiePositions.size(); i++){
		_zombies.push_back(new Zombie);
		_zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i]);
	}
	//���ǹ
	const float BULLET_SPEED = 10.0f;
	_player->addGun(new Gun("ɳĮ֮ӥ", 30, 1, 0.0f, 20, BULLET_SPEED, _audioEngine.loadSoundEffect("Sound/oog/tuizi.mp3")));
	_player->addGun(new Gun("����", 60, 10, 0.6f, 30, BULLET_SPEED,_audioEngine.loadSoundEffect("Sound/oog/M4_Head1.ogg")));
	_player->addGun(new Gun("����֮��", 5, 5, 0.05f, 2, BULLET_SPEED, _audioEngine.loadSoundEffect("Sound/oog/M4_Auto3.ogg")));
	_player->addGun(new Gun("���֮��", 1, 800, 4.0f, 0.1, BULLET_SPEED, _audioEngine.loadSoundEffect("Sound/oog/M4_Tail1.ogg")));

	
	


}



//���
void MainGame::run(){

	initSystems();

	initLevel();
	
	NeroEngine::Music bgMusic =  _audioEngine.loadMusic("Sound/background.mp3");
	
	bgMusic.play(-1);
	gameLoop();
}
void MainGame::checkVictory(){
	//��ʬ������
	if (_zombies.empty()){
		std::cout << "mt19937������ʧ!" << std::endl;
		std::cout << "����" <<_humans.size()<<"�������Ҵ棡"<< std::endl;
		NeroEngine::fatalError("����NeroYang");
	}
}
void MainGame::gameLoop(){

	NeroEngine::FpsLimter _fpsLimter;
	_fpsLimter.setMaxFps(60.0f);

	const float CAMERA_SCALA = 1.5f;
	_camera.setScale(CAMERA_SCALA);
	
	const int  MAX_PHYSISC_STEPS = 1.0f;
	const float DESIREO_FPS = 60.0f;
	const float MS_PER_SECOND = 1000;
	const float MAX_DETLA_TIME = 1.0f;
	const float DESIREO_FRAMETIME = MS_PER_SECOND / DESIREO_FPS;
	float previousTicks = SDL_GetTicks();
	while (_gameState==GameState::PLAY){
		_fpsLimter.begin();
		float newTicks = SDL_GetTicks();
		float frameTime = newTicks - previousTicks;
		previousTicks = newTicks;

		float totalDeltaTime = frameTime / DESIREO_FRAMETIME;

		checkVictory();

		processInput();
		int i = 0;
		while (totalDeltaTime>=0.0f && i<MAX_PHYSISC_STEPS)
		{
			_deltaTime = 1.0f;// std::min(totalDeltaTime, MAX_DETLA_TIME);
			updateAgent(_deltaTime);
			updateBullet(_deltaTime);
			totalDeltaTime += _deltaTime;
			i++;
		}
		
		_particleEngine.update(_deltaTime);

		_camera.setPosition(_player->getAgentPos());

		_camera.update();

		drawGame();

		_fps = _fpsLimter.end();
	}
}
void MainGame::updateBullet(float deltaTime){

	bool wasBulletRemoved;
	//=��ǽ
	for (int i = 0; i < _bullets.size();i++){
		//��ǽ����
		
		if (_bullets[i].update(_levels[_currentLevel]->getLevelData(), _deltaTime)){
			_bloodColor.r = 139;
			_bloodColor.g = 170;
			_bloodColor.b = 102;
			_bloodColor.a = 128;
			addBlood(_bullets[i].getPosition(), 10,3.0f);///<�Ҳܣ�ðѪ��
			_bullets[i] = _bullets.back();
			_bullets.pop_back();
		}
	}
	//����
	for (int i = 0; i < _bullets.size();i++){
		wasBulletRemoved = false;
		for (int j = 0; j < _zombies.size();){
			//��ʬ
			if (_bullets[i].collideWithAgent(_zombies[j])){
				_bloodColor.r = 139;
				_bloodColor.g = 0;
				_bloodColor.b = 0;
				_bloodColor.a = 128;
				addBlood(_zombies[j]->getAgentPos(), 20,30.0f);///<�Ҳܣ�ðѪ��
				if (_zombies[j]->applyDamage(_bullets[i].getDamge())){
					//��ʬ��ʧ
					delete _zombies[j];
					_zombies[j] = _zombies.back();
					_zombies.pop_back();
				}else{
					j++;
				}
				//�ӵ���ʧ
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
				_numZombieKilled++;
				wasBulletRemoved = true;
				i--;
				break;
			}
			else{
				j++;
			}
		}
		if (wasBulletRemoved == false){

			for (int j = 1; j < _humans.size();){
				//������
				if (_bullets[i].collideWithAgent(_humans[j])){
					_bloodColor.r = 139;
					_bloodColor.g = 0;
					_bloodColor.b = 0;
					_bloodColor.a = 128;
					addBlood(_humans[j]->getAgentPos(),20,30.0f);///<ðѪ��
					if (_humans[j]->applyDamage(_bullets[i].getDamge())){
						//����ʧ
						delete _humans[j];
						_humans[j] = _humans.back();
						_humans.pop_back();
					}
					else{
						j++;
					}
					//�ӵ���ʧ
					_bullets[i] = _bullets.back();
					_bullets.pop_back();
					_numHumKilled++;
					wasBulletRemoved = true;
					i--;
					break;
				}
				else{
					j++;
				}
			}
		}
	}

}

void MainGame::updateAgent(float deltaTime){
	//��������
	for (int i = 0; i < _humans.size();i++){
		_humans[i]->update(_levels[_currentLevel]->getLevelData(), _humans, _zombies, _deltaTime);
	}

	//���½�ʬ
	for (int i = 0; i < _zombies.size(); i++){
		_zombies[i]->update(_levels[_currentLevel]->getLevelData(), _humans, _zombies, _deltaTime);
	}

	for (int i = 0; i < _humans.size(); i++){
		for (int j = i + 1; j < _humans.size();j++){
			_humans[i]->collideWithAgent(_humans[j]);
		}
	}

	for (int i = 0; i < _zombies.size(); i++){
		//ͬ��
		for (int j = i + 1; j < _zombies.size(); j++){
			_zombies[i]->collideWithAgent(_zombies[j]);
		}
		//��Ⱦ
		for (int j = 1; j < _humans.size(); j++){
			if (_zombies[i]->collideWithAgent(_humans[j])){
				//��ӽ�ʬ
				//�˴���ʬ����

				_zombies[i]->beStronger();
				_zombies.push_back(new Zombie);
				_zombies.back()->init(ZOMBIE_SPEED, _humans[j]->getAgentPos());

				//���ű���ʬ��Ⱦ��Ч
				_audioEngine.loadSoundEffect("Sound/zombie.mp3").play();
				

				_humans[j] = _humans.back();
				_humans.pop_back();
				
			}
		}
		//��������ϣ���ұ�ҧ��
		if (_zombies[i]->collideWithAgent(_player)){
			//�˴���Ҫ�޸�
			if (_player->applyDamage(_zombies[i]->getDamage())){
				//_audioEngine.loadSoundEffect("Sound/die.ogg").play();
				addBlood(_player->getAgentPos(),10,50.0f);
				NeroEngine::fatalError("���ѱ�ҧ����");
			}
		}
	}


}

void MainGame::processInput(){
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(evnt.button.button);
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_MOUSEWHEEL:
			
			_player->changeGunByWheel(evnt.wheel.y);
			
			break;
		default:
			break;
		}
	}
}

void MainGame::drawGame(){

	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f,0.0f,0.0f, 1.0f);
	_textureProgram.use();

	glActiveTexture(GL_TEXTURE0);
	
	GLuint textureUniform = _textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	glm::mat4 projectionMatrix = _camera.getCameraMatrix();
	GLuint pUniform = _textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	_levels[_currentLevel]->draw();
	_agentSpriteBatch.begin();
	_particleEngine.draw(&_agentSpriteBatch);


	const glm::vec2 agentDemisions = glm::vec2(AGENT_RADIUS*2);
	for (int i = 0; i < _humans.size();i++){
		if (_camera.isBoxiInView(_humans[i]->getAgentPos(), agentDemisions)){
			_humans[i]->draw(_agentSpriteBatch);
		}
	}
	for (int i = 0; i < _zombies.size(); i++){
		if (_camera.isBoxiInView(_zombies[i]->getAgentPos(), agentDemisions)){
			_zombies[i]->draw(_agentSpriteBatch);
		}
	}

	for (int i = 0; i < _bullets.size();i++){
	
			_bullets[i].draw(_agentSpriteBatch);
		
	}

	
	
	_agentSpriteBatch.end();
	_agentSpriteBatch.renderBatch();


	_textureProgram.unuse();

	
	NeroEngine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 200;
	
	_playerLight._color = color;
	_playerLight._position = _player->getAgentPos()+AGENT_RADIUS;
	_playerLight._size = 300.0f;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	_lightProgram.use();
	pUniform = _lightProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	_agentSpriteBatch.begin();

	_playerLight.draw(_agentSpriteBatch);
	_agentSpriteBatch.end();
	_agentSpriteBatch.renderBatch();
	_lightProgram.unuse();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	_window.swapBuffer();
}
void MainGame::addBlood(const glm::vec2& position, int numParticles,const float width){
	static std::mt19937 randEngine(time(nullptr));
	static std::uniform_real_distribution<float> randAngle(0.0f, 360.0f);
	glm::vec2 vel(1.0f, 0.0f);

	vel = glm::rotate(vel, randAngle(randEngine));


	for (int i = 0; i < numParticles;i++){
		_bloodParticlesBatch->addParticle(position, vel, _bloodColor, width);
	}
}

