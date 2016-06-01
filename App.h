#pragma once

#include <NeroEngine\IMainGame.h>
#include <NeroEngine\ScreenList.h>

#include "GamePlayScreen.h"
class App:public NeroEngine::IMainGame
{
public:
	App();
	~App();
	virtual void onInit() override;
	virtual void addScreen() override;
	virtual void onExit()override;
private:
	std::unique_ptr<GamePlayScreen> _gamescreen = nullptr;
};

