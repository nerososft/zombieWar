#pragma once
#include <NeroEngine\IGameScreen.h>
#include <memory>
class GamePlayScreen :public NeroEngine::IGameScreen
{
public:
	GamePlayScreen();
	~GamePlayScreen();
	NeroEngine::IGameScreen* get(){
		return _gamescreen;
	}
	virtual int getNextScreenIndex() const override;


	virtual int getPreviousScreenIndex() const override;


	virtual void build() override;


	virtual void destroy() override;


	virtual void onEntry() override;


	virtual void onExit() override;


	virtual void update() override;


	virtual void draw() override;
private:
	IGameScreen* _gamescreen = nullptr;
};

