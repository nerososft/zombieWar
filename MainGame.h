#pragma once
#include <NeroEngine\Camera2D.h>
#include <NeroEngine\Window.h>
#include <NeroEngine\InputManager.h>
#include <NeroEngine\GLSLProgram.h>
#include <NeroEngine\Timing.h>
#include <NeroEngine\SpriteBatch.h>
#include <NeroEngine\AudioEngine.h>
#include <NeroEngine\ParticleEngine2D.h>
#include "Player.h"
#include "Bullet.h"
#include "Level.h"
#include "Light2D.h"
#include "MiniMap.h"
class Zombie;
const float HUMAN_SPEED = 1.0f;
const float ZOMBIE_SPEED = 0.5f;
const float PLAYER_SPEED = 5.0f;
const float PI = 3.14159926f;
enum  class GameState
{
	PLAY,
	EXIT
};
class MainGame
{
public:
	MainGame();
	~MainGame();
	
	void run();

private:
	void initSystems();

	void initLevel();

	void initShaders();

	void gameLoop();

	void checkVictory();

	void updateAgent(float deltaTime);

	void updateBullet(float deltaTime);

	void processInput();

	void drawGame();

	void addBlood(const glm::vec2& position, int numParticles, const float width);

	void updateMinimap(glm::vec2 pos);

	NeroEngine::Window _window;

	NeroEngine::GLSLProgram _textureProgram;
	NeroEngine::GLSLProgram _lightProgram;

	NeroEngine::InputManager _inputManager;

	NeroEngine::Camera2D _camera;

	NeroEngine::SpriteBatch _agentSpriteBatch;
	NeroEngine::ParticleEngine2D _particleEngine;
	NeroEngine::ParticleBatch2D* _bloodParticlesBatch;

	NeroEngine::AudioEngine _audioEngine;



	Light2D _playerLight;
	MiniMap _miniMap;

	std::vector<Level*> _levels;

	int _screenWidth;
	int _screenHeight;

	GameState _gameState;


	float _fps;
	int _currentLevel;
	
	Player* _player;
	std::vector<Human*> _humans;
	std::vector<Zombie*> _zombies;
	std::vector<Bullet> _bullets;



	int _numHumKilled;
	int _numZombieKilled;


	NeroEngine::Color _bloodColor;
	float _deltaTime = 1.0f;


	
};



